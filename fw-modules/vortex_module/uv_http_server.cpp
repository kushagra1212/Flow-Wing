/*
 * FlowWing Compiler
 * Copyright (C) 2023-2026 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


/*
 * FlowWing Runtime - libuv-native HTTP/1.1 server (see uv_http_server.h).
 *
 * Everything here runs on the FlowWing thread, inside the shared libuv loop.
 * There is no worker thread and no mutex: uv_read_cb and the llhttp callbacks
 * are invoked from uv_run, which the scheduler calls when no task can run.
 *
 * That single-threaded property is what makes it safe to allocate GC memory in
 * the request accessors and to touch the scheduler directly from a callback.
 */

#include "uv_http_server.h"

#include "fw_gc.h"
#include "fw_sched.h"
#include "fw_uv.h"

#include <llhttp.h>

#include <cstdio>
#include <cstring>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

// Limits. cpp-httplib enforced its own; taking the sockets meant taking
// responsibility for these too. Without them one client can exhaust memory or
// hold a connection open forever.
//
// Override at start-up:
//   FW_HTTP_MAX_BODY_KB     default 8192  (8 MB)
//   FW_HTTP_MAX_HEADER_KB   default 32
//   FW_HTTP_IDLE_TIMEOUT_MS default 30000
size_t env_size(const char *name, size_t fallback_bytes, size_t unit) {
  const char *v = std::getenv(name);
  if (v == nullptr || *v == '\0') return fallback_bytes;
  char *end = nullptr;
  long  n = std::strtol(v, &end, 10);
  if (end == nullptr || *end != '\0' || n <= 0) return fallback_bytes;
  return (size_t)n * unit;
}

size_t max_body_bytes() {
  static size_t v = env_size("FW_HTTP_MAX_BODY_KB", 8u * 1024u * 1024u, 1024);
  return v;
}
size_t max_header_bytes() {
  static size_t v = env_size("FW_HTTP_MAX_HEADER_KB", 32u * 1024u, 1024);
  return v;
}
uint64_t idle_timeout_ms() {
  static uint64_t v = (uint64_t)env_size("FW_HTTP_IDLE_TIMEOUT_MS", 30000, 1);
  return v;
}

struct FwConn;

// One HTTP transaction. Lives until FlowWing finishes the response, which may
// be long after the parser produced it.
struct FwRequest {
  std::string method;
  std::string path;   // path ONLY, never the query string
  std::string query;  // everything after '?', without the '?'
  std::string body;

  // Response state, filled in by the FlowWing side.
  int         status = 200;
  std::string headers;
  bool        streaming = false;
  bool        done = false;

  FwConn *conn = nullptr;   // null once the connection has gone away
  bool    keep_alive = true;
};

struct FwServer;

struct FwConn {
  uv_tcp_t     handle{};
  llhttp_t     parser{};
  llhttp_settings_t settings{};
  FwServer    *server = nullptr;

  // Fields being accumulated by the parser for the in-flight request.
  std::string cur_method;
  std::string cur_url;
  std::string cur_body;
  std::string cur_header_field;
  bool        message_complete = false;

  FwRequest *active = nullptr; // request handed to FlowWing, awaiting a reply
  bool       closing = false;

  // Bytes seen for the current message, so a client cannot stream an unbounded
  // header block or body into memory.
  size_t     header_bytes = 0;
  size_t     body_bytes = 0;

  // Reset on every read. When it fires the peer has gone quiet for longer than
  // the idle timeout and the connection is dropped.
  uv_timer_t idle{};
  bool       idle_active = false;

  // A connection owns TWO libuv handles (the socket and the idle timer). Both
  // must finish closing before the struct is freed: deleting after the first
  // callback frees the memory the second one is still using, which libuv
  // catches as "Assertion failed: (handle->flags & UV_HANDLE_CLOSING)".
  int        pending_closes = 0;
};

struct FwServer {
  uv_tcp_t              listener{};
  std::deque<FwRequest *> ready;       // parsed, waiting for fw_http_accept
  unsigned long         open_conns = 0;
  bool                  listening = false;

  // Every request created and not yet completed. A handler that returns
  // without replying would otherwise leak its request and the memory behind
  // it; this bounds the damage and lets shutdown free them all.
  std::unordered_map<FwRequest *, bool> live;
};

// ---- GC helper ------------------------------------------------------------

const char *gc_str(const std::string &s) {
  char *p = (char *)fw_gc_alloc(s.size() + 1, &fw_blob_desc);
  if (p == nullptr) return nullptr;
  std::memcpy(p, s.data(), s.size());
  p[s.size()] = '\0';
  return p;
}

// ---- libuv plumbing -------------------------------------------------------

void alloc_buffer(uv_handle_t *, size_t suggested, uv_buf_t *buf) {
  buf->base = (char *)malloc(suggested);
  buf->len = suggested;
}

void on_idle_timeout(uv_timer_t *timer);
void conn_release(FwConn *c);

void arm_idle(FwConn *c) {
  if (c == nullptr || c->closing || !c->idle_active) return;
  uv_timer_start(&c->idle, on_idle_timeout, idle_timeout_ms(), 0);
}

void on_close(uv_handle_t *handle) {
  FwConn *c = static_cast<FwConn *>(handle->data);
  if (c == nullptr) return;
  if (c->active != nullptr) {
    // FlowWing still holds this request; sever the link so a later send is a
    // no-op rather than a write to a dead socket.
    c->active->conn = nullptr;
  }
  conn_release(c);
}

void conn_release(FwConn *c) {
  if (c == nullptr) return;
  if (--c->pending_closes > 0) return; // the other handle is still closing
  if (c->server != nullptr && c->server->open_conns > 0) c->server->open_conns--;
  delete c;
}

void on_idle_closed(uv_handle_t *handle) {
  conn_release(static_cast<FwConn *>(handle->data));
}

void conn_close(FwConn *c) {
  if (c == nullptr || c->closing) return;
  c->closing = true;

  // Count both handles up front, so whichever callback lands last is the one
  // that frees the struct.
  if (c->idle_active) {
    uv_timer_stop(&c->idle);
    c->idle_active = false;
    if (!uv_is_closing((uv_handle_t *)&c->idle)) {
      c->pending_closes++;
      uv_close((uv_handle_t *)&c->idle, on_idle_closed);
    }
  }
  if (!uv_is_closing((uv_handle_t *)&c->handle)) {
    c->pending_closes++;
    uv_close((uv_handle_t *)&c->handle, on_close);
  }

  if (c->pending_closes == 0) { // nothing was open; free directly
    if (c->server != nullptr && c->server->open_conns > 0) c->server->open_conns--;
    delete c;
  }
}

// The peer went quiet for longer than the idle timeout. Without this a client
// could open a socket, send one byte and hold the connection for ever.
void on_idle_timeout(uv_timer_t *timer) {
  conn_close(static_cast<FwConn *>(timer->data));
  fw_sched_wake_io();
}

struct WriteReq {
  uv_write_t req{};
  std::string payload;
  bool close_after = false;
};

void on_write(uv_write_t *req, int status) {
  WriteReq *w = static_cast<WriteReq *>(req->data);
  FwConn   *c = static_cast<FwConn *>(req->handle->data);
  if (w->close_after || status != 0) conn_close(c);
  delete w;
}

void conn_write(FwConn *c, std::string payload, bool close_after) {
  if (c == nullptr || c->closing) return;

  WriteReq *w = new WriteReq();
  w->payload = std::move(payload);
  w->close_after = close_after;
  w->req.data = w;

  uv_buf_t buf = uv_buf_init(const_cast<char *>(w->payload.data()),
                             (unsigned int)w->payload.size());
  if (uv_write(&w->req, (uv_stream_t *)&c->handle, &buf, 1, on_write) != 0) {
    delete w;
    conn_close(c);
  }
}

// ---- llhttp callbacks -----------------------------------------------------

int on_url(llhttp_t *p, const char *at, size_t len) {
  FwConn *c = static_cast<FwConn *>(p->data);
  c->header_bytes += len;
  if (c->header_bytes > max_header_bytes()) return -1;
  c->cur_url.append(at, len);
  return 0;
}

int on_body(llhttp_t *p, const char *at, size_t len) {
  FwConn *c = static_cast<FwConn *>(p->data);
  c->body_bytes += len;
  if (c->body_bytes > max_body_bytes()) {
    return -1; // llhttp aborts; on_read turns this into 413 and closes
  }
  c->cur_body.append(at, len);
  return 0;
}

// Header bytes are counted across the url and every header field/value, so a
// client cannot send an endless header block.
int on_header_bytes(llhttp_t *p, const char *, size_t len) {
  FwConn *c = static_cast<FwConn *>(p->data);
  c->header_bytes += len;
  return c->header_bytes > max_header_bytes() ? -1 : 0;
}

int on_message_complete(llhttp_t *p) {
  FwConn *c = static_cast<FwConn *>(p->data);

  FwRequest *r = new FwRequest();
  r->method = llhttp_method_name((llhttp_method_t)p->method);
  // Split the query off the path.
  //
  // llhttp hands us the raw request target, so cur_url is "/a/b.js?v=2" and
  // assigning it straight to path made every comparison and every file lookup
  // see the query as part of the name. A cache-busted asset 404'd, and any
  // route written as `path == "/track"` silently stopped matching once a query
  // was appended. Observed live: /assets/admin.js?v=2 -> 404 while
  // /assets/admin.js -> 200, which left the admin dashboard with no JS at all.
  {
    const std::string &u = c->cur_url;
    std::string::size_type q = u.find('?');
    if (q == std::string::npos) {
      r->path = u;
      r->query.clear();
    } else {
      r->path = u.substr(0, q);
      r->query = u.substr(q + 1);
    }
  }
  r->body = c->cur_body;
  r->conn = c;
  r->keep_alive = llhttp_should_keep_alive(p) != 0;

  c->active = r;
  c->server->ready.push_back(r);
  c->server->live[r] = true; // so shutdown can free it even if never answered

  c->cur_url.clear();
  c->cur_body.clear();
  c->header_bytes = 0;
  c->body_bytes = 0;
  c->message_complete = true;

  // A task may be parked in fw_http_accept. This runs on the FlowWing thread
  // inside uv_run, so waking the scheduler here is safe.
  fw_sched_wake_io();
  return 0;
}

void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  FwConn *c = static_cast<FwConn *>(stream->data);

  if (nread < 0) {
    free(buf->base);
    conn_close(c);
    fw_sched_wake_io(); // a task waiting on this connection must re-check
    return;
  }

  arm_idle(c); // the peer is alive; restart the clock

  bool over_limit = c->body_bytes > max_body_bytes() ||
                    c->header_bytes > max_header_bytes();

  enum llhttp_errno err =
      llhttp_execute(&c->parser, buf->base, (size_t)nread);
  free(buf->base);

  over_limit = over_limit || c->body_bytes > max_body_bytes() ||
               c->header_bytes > max_header_bytes();

  if (err != HPE_OK) {
    conn_write(c,
               over_limit
                   ? "HTTP/1.1 413 Payload Too Large\r\nContent-Length: 0\r\n"
                     "Connection: close\r\n\r\n"
                   : "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n"
                     "Connection: close\r\n\r\n",
               true);
  }
}

void on_connection(uv_stream_t *server_stream, int status) {
  if (status != 0) return;
  FwServer *s = static_cast<FwServer *>(server_stream->data);

  FwConn *c = new FwConn();
  c->server = s;
  uv_tcp_init(fw_uv_loop(), &c->handle);
  c->handle.data = c;

  if (uv_accept(server_stream, (uv_stream_t *)&c->handle) != 0) {
    conn_close(c);
    return;
  }

  llhttp_settings_init(&c->settings);
  c->settings.on_url = on_url;
  c->settings.on_body = on_body;
  c->settings.on_message_complete = on_message_complete;
  llhttp_init(&c->parser, HTTP_REQUEST, &c->settings);
  c->parser.data = c;

  uv_timer_init(fw_uv_loop(), &c->idle);
  c->idle.data = c;
  c->idle_active = true;
  uv_unref((uv_handle_t *)&c->idle); // must not keep the loop alive by itself
  arm_idle(c);

  s->open_conns++;
  uv_read_start((uv_stream_t *)&c->handle, alloc_buffer, on_read);
}

const char *status_text(int code) {
  switch (code) {
    case 200: return "OK";
    case 201: return "Created";
    case 204: return "No Content";
    case 400: return "Bad Request";
    case 401: return "Unauthorized";
    case 403: return "Forbidden";
    case 404: return "Not Found";
    case 500: return "Internal Server Error";
    default:  return "OK";
  }
}

} // namespace

// ---- public API -----------------------------------------------------------

extern "C" {

int64_t fw_http_server_new(void) {
  fw_uv_loop(); // makes the loop exist and installs the scheduler waiter
  return reinterpret_cast<int64_t>(new FwServer());
}

int fw_http_server_listen(int64_t handle, int port) {
  if (!handle) return UV_EINVAL;
  FwServer *s = reinterpret_cast<FwServer *>(handle);

  uv_tcp_init(fw_uv_loop(), &s->listener);
  s->listener.data = s;

  struct sockaddr_in addr;
  uv_ip4_addr("0.0.0.0", port, &addr);

  int rc = uv_tcp_bind(&s->listener, (const struct sockaddr *)&addr, 0);
  if (rc != 0) return rc;

  rc = uv_listen((uv_stream_t *)&s->listener, 128, on_connection);
  if (rc != 0) return rc;

  s->listening = true;
  return 0;
}

int64_t fw_http_accept(int64_t handle) {
  if (!handle) return 0;
  FwServer *s = reinterpret_cast<FwServer *>(handle);

  for (;;) {
    if (!s->ready.empty()) {
      FwRequest *r = s->ready.front();
      s->ready.pop_front();
      return reinterpret_cast<int64_t>(r);
    }
    if (!fw_sched_in_task()) {
      // No scheduler to yield to: drive the loop directly so a plain
      // (non-spawned) program still works.
      uv_run(fw_uv_loop(), UV_RUN_ONCE);
      continue;
    }
    fw_sched_park_io();
  }
}

const char *fw_http_req_method(int64_t h) {
  return h ? gc_str(reinterpret_cast<FwRequest *>(h)->method) : gc_str("");
}

const char *fw_http_req_path(int64_t h) {
  return h ? gc_str(reinterpret_cast<FwRequest *>(h)->path) : gc_str("");
}

const char *fw_http_req_query(int64_t h) {
  return h ? gc_str(reinterpret_cast<FwRequest *>(h)->query) : gc_str("");
}

const char *fw_http_req_body(int64_t h) {
  return h ? gc_str(reinterpret_cast<FwRequest *>(h)->body) : gc_str("");
}

void fw_http_res_status(int64_t h, int status) {
  if (h) reinterpret_cast<FwRequest *>(h)->status = status;
}

void fw_http_res_header(int64_t h, const char *key, const char *value) {
  if (!h || !key || !value) return;
  FwRequest *r = reinterpret_cast<FwRequest *>(h);
  r->headers += key;
  r->headers += ": ";
  r->headers += value;
  r->headers += "\r\n";
}

// Length-aware body send.
//
// fw_http_res_send takes a NUL-terminated C string, which silently truncates
// any body containing a zero byte. Every binary file does: a PNG is 8 signature
// bytes followed by 0x00, so sendStaticFile answered 200 with exactly 8 bytes
// and every image on the site rendered as a broken icon. Text assets were fine,
// which is why it went unnoticed. Callers holding a known length must use this.
void fw_http_res_send_n(int64_t h, const char *body, size_t len) {
  if (!h) return;
  FwRequest *r = reinterpret_cast<FwRequest *>(h);
  if (r->done) return;
  r->done = true;

  std::string payload = (body && len) ? std::string(body, len) : std::string();
  char head[256];
  std::snprintf(head, sizeof(head),
                "HTTP/1.1 %d %s\r\nContent-Length: %zu\r\nConnection: %s\r\n",
                r->status, status_text(r->status), payload.size(),
                r->keep_alive ? "keep-alive" : "close");

  std::string out = head;
  out += r->headers;
  out += "\r\n";
  out += payload;

  FwConn *c = r->conn;
  if (c != nullptr) {
    c->active = nullptr;
    conn_write(c, std::move(out), !r->keep_alive);
    c->server->live.erase(r);
  }
  delete r;
}

void fw_http_res_send(int64_t h, const char *body) {
  fw_http_res_send_n(h, body, body ? std::strlen(body) : 0);
}

void fw_http_res_stream_begin(int64_t h, const char *content_type) {
  if (!h) return;
  FwRequest *r = reinterpret_cast<FwRequest *>(h);
  if (r->streaming || r->done) return;
  r->streaming = true;

  char head[256];
  std::snprintf(head, sizeof(head),
                "HTTP/1.1 %d %s\r\nContent-Type: %s\r\n"
                "Transfer-Encoding: chunked\r\nConnection: close\r\n",
                r->status, status_text(r->status),
                content_type ? content_type : "text/plain");

  std::string out = head;
  out += r->headers;
  out += "\r\n";
  conn_write(r->conn, std::move(out), false);
}

void fw_http_res_stream_write(int64_t h, const char *chunk) {
  if (!h || !chunk) return;
  FwRequest *r = reinterpret_cast<FwRequest *>(h);
  if (!r->streaming || r->done) return;

  size_t len = std::strlen(chunk);
  if (len == 0) return;

  char size_line[32];
  std::snprintf(size_line, sizeof(size_line), "%zx\r\n", len);

  std::string out = size_line;
  out += chunk;
  out += "\r\n";
  conn_write(r->conn, std::move(out), false);
}

void fw_http_res_stream_end(int64_t h) {
  if (!h) return;
  FwRequest *r = reinterpret_cast<FwRequest *>(h);
  if (!r->streaming || r->done) return;
  r->done = true;

  FwConn *c = r->conn;
  if (c != nullptr) {
    c->active = nullptr;
    conn_write(c, "0\r\n\r\n", true); // terminal chunk, then close
    c->server->live.erase(r);
  }
  delete r;
}

// Stop listening and release everything the server still owns. Without this
// the listening socket stays bound and any request the handler never answered
// is never freed.
void fw_http_server_close(int64_t h) {
  if (!h) return;
  FwServer *s = reinterpret_cast<FwServer *>(h);

  if (s->listening && !uv_is_closing((uv_handle_t *)&s->listener)) {
    uv_close((uv_handle_t *)&s->listener, nullptr);
    s->listening = false;
  }

  // Requests the handler never replied to. Detach them from their connection
  // first so a late send cannot touch freed memory.
  for (auto &entry : s->live) {
    FwRequest *r = entry.first;
    if (r->conn != nullptr) r->conn->active = nullptr;
    delete r;
  }
  s->live.clear();
  s->ready.clear();
}

unsigned long fw_http_open_connections(int64_t h) {
  return h ? reinterpret_cast<FwServer *>(h)->open_conns : 0;
}

} // extern "C"
