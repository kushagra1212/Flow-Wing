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
 * FlowWing Runtime - libuv-native streaming HTTP client (see uv_http_client.h).
 *
 * The shape mirrors uv_http_server.cpp: a struct per request, llhttp for
 * parsing, and every callback running on the FlowWing thread inside the shared
 * loop. Because the loop only turns while the scheduler is idle, no callback
 * can interleave with FlowWing code — which is why the chunk queue below is a
 * plain std::deque with no lock around it.
 *
 * Lifetime is the part worth reading carefully. A request owns three libuv
 * handles (socket, timer, and a getaddrinfo request), and libuv forbids freeing
 * a handle before its close callback has run. `pending_closes` counts the
 * handles still closing; the struct is deleted by whichever close callback
 * brings it to zero. FlowWing may also drop its handle at any time, so the free
 * is driven by that counter rather than by the FlowWing side.
 */

#include "uv_http_client.h"

#include "fw_gc.h"
#include "fw_sched.h"
#include "fw_uv.h"

#include <llhttp.h>

#include <cstdlib>
#include <cstring>
#include <deque>
#include <string>

namespace {

// Timeouts, matching the values the cpp-httplib client used so behaviour does
// not change for existing programs. Long LLM generations were the reason the
// read timeout is minutes rather than seconds.
//
//   FW_HTTP_CLIENT_CONNECT_MS  default 5000
//   FW_HTTP_CLIENT_READ_MS     default 120000
uint64_t env_ms(const char *name, uint64_t fallback) {
  const char *v = std::getenv(name);
  if (v == nullptr || *v == '\0') return fallback;
  char *end = nullptr;
  unsigned long long parsed = std::strtoull(v, &end, 10);
  if (end == v || parsed == 0ULL) return fallback;
  return (uint64_t)parsed;
}

uint64_t connect_timeout_ms() {
  static uint64_t v = env_ms("FW_HTTP_CLIENT_CONNECT_MS", 5000);
  return v;
}

uint64_t read_timeout_ms() {
  static uint64_t v = env_ms("FW_HTTP_CLIENT_READ_MS", 120000);
  return v;
}

const char *gc_str(const std::string &s) {
  char *p = (char *)fw_gc_alloc(s.size() + 1, &fw_blob_desc);
  std::memcpy(p, s.data(), s.size());
  p[s.size()] = '\0';
  return p;
}

struct FwClientReq {
  uv_tcp_t         socket{};
  uv_connect_t     connect_req{};
  uv_getaddrinfo_t resolver{};
  uv_timer_t       timer{};
  uv_write_t       write_req{};

  llhttp_t          parser{};
  llhttp_settings_t settings{};

  std::string host;
  std::string port;
  std::string path;
  std::string body;

  // uv_write does not copy: this must stay alive until on_write runs.
  std::string request_buf;

  std::deque<std::string> chunks;

  int  status_code = 0;
  bool headers_done = false;   // headers parsed, or the attempt failed
  bool response_done = false;  // no more body will arrive
  bool ok = false;
  bool socket_open = false;
  bool timer_open = false;

  // FlowWing has called close() and no longer holds this handle.
  bool abandoned = false;

  // Handles still waiting for their uv close callback. The struct is deleted
  // when this reaches zero, never before — libuv reads the handle after the
  // user asks for a close.
  int pending_closes = 0;
};

void finish_headers(FwClientReq *c, bool ok) {
  if (c->headers_done) return;
  c->headers_done = true;
  c->ok = ok;
  // Same thread as the scheduler: this is the wake, not fw_uv_wake (which
  // exists only for the worker threads that no longer run here).
  fw_sched_wake_io();
}

void finish_response(FwClientReq *c) {
  if (c->response_done) return;
  c->response_done = true;
  finish_headers(c, c->ok);   // a failure before headers still releases callers
  fw_sched_wake_io();
}

void maybe_delete(FwClientReq *c) {
  if (c->pending_closes > 0) return;
  if (!c->abandoned) return;   // FlowWing still holds the handle
  delete c;
}

void on_handle_closed(uv_handle_t *handle) {
  auto *c = static_cast<FwClientReq *>(handle->data);
  if (c == nullptr) return;
  if (c->pending_closes > 0) c->pending_closes--;
  maybe_delete(c);
}

// Close everything this request owns. Safe to call more than once: each handle
// is only asked once, and uv_is_closing covers the overlap.
void close_request(FwClientReq *c) {
  if (c->timer_open) {
    c->timer_open = false;
    uv_timer_stop(&c->timer);
    if (!uv_is_closing((uv_handle_t *)&c->timer)) {
      c->pending_closes++;
      uv_close((uv_handle_t *)&c->timer, on_handle_closed);
    }
  }
  if (c->socket_open) {
    c->socket_open = false;
    if (!uv_is_closing((uv_handle_t *)&c->socket)) {
      c->pending_closes++;
      uv_close((uv_handle_t *)&c->socket, on_handle_closed);
    }
  }
}

void fail_request(FwClientReq *c) {
  c->ok = false;
  close_request(c);
  finish_response(c);
  maybe_delete(c);
}

void on_timeout(uv_timer_t *timer) {
  auto *c = static_cast<FwClientReq *>(timer->data);
  // A timeout is a failure even if part of the body arrived: the caller gets
  // what was received and then a finished stream, rather than hanging.
  fail_request(c);
}

void arm_timer(FwClientReq *c, uint64_t ms) {
  if (!c->timer_open) return;
  uv_timer_start(&c->timer, on_timeout, ms, 0);
}

// ---- llhttp callbacks ----------------------------------------------------

int on_status_complete(llhttp_t *parser) {
  auto *c = static_cast<FwClientReq *>(parser->data);
  c->status_code = parser->status_code;
  return 0;
}

int on_headers_complete(llhttp_t *parser) {
  auto *c = static_cast<FwClientReq *>(parser->data);
  c->status_code = parser->status_code;
  finish_headers(c, c->status_code >= 200 && c->status_code < 300);
  return 0;
}

int on_body(llhttp_t *parser, const char *at, size_t length) {
  auto *c = static_cast<FwClientReq *>(parser->data);
  if (length > 0) {
    c->chunks.emplace_back(at, length);
    // Every chunk restarts the read clock: a slow but live stream must not be
    // cut off just because the whole response is taking a long time.
    arm_timer(c, read_timeout_ms());
    fw_sched_wake_io();
  }
  return 0;
}

int on_message_complete(llhttp_t *parser) {
  auto *c = static_cast<FwClientReq *>(parser->data);
  // Chunked or content-length, llhttp tells us where the body ends. The socket
  // may stay open (keep-alive); nothing more is wanted from it.
  close_request(c);
  finish_response(c);
  return 0;
}

// ---- socket callbacks ----------------------------------------------------

void alloc_buffer(uv_handle_t *, size_t suggested, uv_buf_t *buf) {
  buf->base = (char *)std::malloc(suggested);
  buf->len = buf->base ? suggested : 0;
}

void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf) {
  auto *c = static_cast<FwClientReq *>(stream->data);

  if (nread > 0) {
    llhttp_errno_t err = llhttp_execute(&c->parser, buf->base, (size_t)nread);
    if (err != HPE_OK && err != HPE_PAUSED) {
      std::free(buf->base);
      fail_request(c);
      return;
    }
  } else if (nread < 0) {
    // UV_EOF with a response that had no content-length is a legitimate end of
    // body: llhttp_finish decides which case this is.
    if (nread == UV_EOF) {
      llhttp_finish(&c->parser);
      close_request(c);
      finish_response(c);
    } else {
      std::free(buf->base);
      fail_request(c);
      return;
    }
  }

  if (buf->base) std::free(buf->base);
  maybe_delete(c);
}

void on_write(uv_write_t *req, int status) {
  auto *c = static_cast<FwClientReq *>(req->data);
  if (status != 0) {
    fail_request(c);
    return;
  }
  // The request is away; from here the read timeout governs.
  arm_timer(c, read_timeout_ms());
}

void on_connect(uv_connect_t *req, int status) {
  auto *c = static_cast<FwClientReq *>(req->data);
  if (status != 0) {
    fail_request(c);
    return;
  }

  c->request_buf  = "POST " + c->path + " HTTP/1.1\r\n";
  c->request_buf += "Host: " + c->host + "\r\n";
  c->request_buf += "Content-Type: application/json\r\n";
  c->request_buf += "Content-Length: " + std::to_string(c->body.size()) + "\r\n";
  // No keep-alive: this client issues exactly one request per connection, and
  // asking the server to close removes any ambiguity about where the body ends.
  c->request_buf += "Connection: close\r\n\r\n";
  c->request_buf += c->body;

  uv_buf_t out = uv_buf_init(const_cast<char *>(c->request_buf.data()),
                             (unsigned int)c->request_buf.size());

  c->socket.data = c;
  c->write_req.data = c;
  if (uv_write(&c->write_req, (uv_stream_t *)&c->socket, &out, 1, on_write) != 0) {
    fail_request(c);
    return;
  }

  uv_read_start((uv_stream_t *)&c->socket, alloc_buffer, on_read);
}

void on_resolved(uv_getaddrinfo_t *resolver, int status, struct addrinfo *res) {
  auto *c = static_cast<FwClientReq *>(resolver->data);

  if (status != 0 || res == nullptr) {
    if (res) uv_freeaddrinfo(res);
    fail_request(c);
    return;
  }

  // Pick an address rather than taking the first one.
  //
  // A dual-stack name resolves to both families, and on this platform "localhost"
  // yields ::1 before 127.0.0.1. Connecting to the IPv6 address fails outright
  // when the server bound IPv4 only, which is the usual case for a local
  // development server — and was exactly the failure here: the same request
  // worked against 127.0.0.1 and was refused against localhost.
  //
  // libuv will not let a uv_tcp_t be reused after a failed connect, so walking
  // the list on failure would mean closing and re-initialising the socket
  // between attempts. Choosing up front avoids that: IPv4 when the name offers
  // it, otherwise whatever came first, so an IPv6-only host still resolves.
  struct addrinfo *chosen = res;
  for (struct addrinfo *ai = res; ai != nullptr; ai = ai->ai_next) {
    if (ai->ai_family == AF_INET) {
      chosen = ai;
      break;
    }
  }

  c->connect_req.data = c;
  int rc = uv_tcp_connect(&c->connect_req, &c->socket, chosen->ai_addr,
                          on_connect);
  uv_freeaddrinfo(res);

  if (rc != 0) {
    fail_request(c);
    return;
  }
}

// ---- url ------------------------------------------------------------------

// Split "http://host:port/path" into its parts. Anything without a scheme is
// treated as a host, which is how the previous client behaved.
bool parse_url(const std::string &url, std::string &host, std::string &port,
               std::string &path) {
  std::string rest = url;

  size_t scheme = rest.find("://");
  if (scheme != std::string::npos) {
    std::string proto = rest.substr(0, scheme);
    // https would need TLS, which this path has never had. Say so rather than
    // connecting to port 443 in plain text and timing out.
    if (proto != "http") return false;
    rest = rest.substr(scheme + 3);
  }

  size_t slash = rest.find('/');
  if (slash == std::string::npos) {
    path = "/";
  } else {
    path = rest.substr(slash);
    rest = rest.substr(0, slash);
  }

  size_t colon = rest.rfind(':');
  if (colon != std::string::npos && rest.find(']') == std::string::npos) {
    host = rest.substr(0, colon);
    port = rest.substr(colon + 1);
  } else {
    host = rest;
    port = "80";
  }

  return !host.empty();
}

// Wait until `ready` holds. Inside a task this suspends only that task; at the
// top level there is nothing to switch to, so turn the loop directly rather
// than blocking on a condition variable as the old client did.
template <typename Predicate>
void wait_until(FwClientReq *c, Predicate ready) {
  if (fw_sched_in_task()) {
    while (!ready()) {
      fw_sched_park_io();
    }
    return;
  }

  uv_loop_t *loop = fw_uv_loop();
  while (!ready()) {
    if (loop == nullptr) return;
    uv_run(loop, UV_RUN_ONCE);
  }
}

} // namespace

extern "C" {

int64_t fw_http_client_post_stream(const char *url_c, const char *body_c) {
  uv_loop_t *loop = fw_uv_loop();
  if (loop == nullptr) return 0;

  std::string url = url_c ? url_c : "";
  std::string body = body_c ? body_c : "";

  auto *c = new FwClientReq();
  c->body = body;

  if (!parse_url(url, c->host, c->port, c->path)) {
    delete c;
    return 0;
  }

  if (uv_tcp_init(loop, &c->socket) != 0) {
    delete c;
    return 0;
  }
  c->socket.data = c;
  c->socket_open = true;

  if (uv_timer_init(loop, &c->timer) == 0) {
    c->timer.data = c;
    c->timer_open = true;
    arm_timer(c, connect_timeout_ms());
  }

  llhttp_settings_init(&c->settings);
  c->settings.on_status_complete  = on_status_complete;
  c->settings.on_headers_complete = on_headers_complete;
  c->settings.on_body             = on_body;
  c->settings.on_message_complete = on_message_complete;
  llhttp_init(&c->parser, HTTP_RESPONSE, &c->settings);
  c->parser.data = c;

  // Be lenient about what a SERVER sends us.
  //
  // The server side of this module is strict on purpose: it is exposed to the
  // network and a malformed request is a request to reject. A client is in the
  // opposite position. It talks to whatever the user points it at, and
  // refusing a response that every browser accepts is a defect, not safety.
  //
  // Concretely: Python's BaseHTTPRequestHandler answers HTTP/1.0 while still
  // sending "Transfer-Encoding: chunked", which is not legal in 1.0. llhttp
  // rejects it by default, so the reply was discarded and the request looked
  // like a connection failure. cpp-httplib accepted it, as does curl.
  llhttp_set_lenient_transfer_encoding(&c->parser, 1);
  llhttp_set_lenient_version(&c->parser, 1);
  llhttp_set_lenient_keep_alive(&c->parser, 1);
  llhttp_set_lenient_data_after_close(&c->parser, 1);

  struct addrinfo hints{};
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  c->resolver.data = c;
  if (uv_getaddrinfo(loop, &c->resolver, on_resolved, c->host.c_str(),
                     c->port.c_str(), &hints) != 0) {
    fail_request(c);
    // fail_request may have queued closes; the handle stays valid until the
    // caller closes it, exactly as in the success path.
    return reinterpret_cast<int64_t>(c);
  }

  // Block only this task until the headers land (or the attempt fails).
  wait_until(c, [c]() { return c->headers_done; });

  return reinterpret_cast<int64_t>(c);
}

int fw_http_client_ok(int64_t handle) {
  if (!handle) return 0;
  return reinterpret_cast<FwClientReq *>(handle)->ok ? 1 : 0;
}

const char *fw_http_client_read_chunk(int64_t handle) {
  if (!handle) return gc_str("");
  auto *c = reinterpret_cast<FwClientReq *>(handle);

  wait_until(c, [c]() { return !c->chunks.empty() || c->response_done; });

  if (c->chunks.empty()) return gc_str("");

  std::string chunk = std::move(c->chunks.front());
  c->chunks.pop_front();
  return gc_str(chunk);
}

int fw_http_client_is_done(int64_t handle) {
  if (!handle) return 1;
  auto *c = reinterpret_cast<FwClientReq *>(handle);
  return (c->response_done && c->chunks.empty()) ? 1 : 0;
}

void fw_http_client_close(int64_t handle) {
  if (!handle) return;
  auto *c = reinterpret_cast<FwClientReq *>(handle);

  c->abandoned = true;
  c->chunks.clear();
  close_request(c);

  // If the handles closed synchronously there is nothing left to wait for and
  // this frees now; otherwise the last close callback does it.
  maybe_delete(c);
}

} // extern "C"
