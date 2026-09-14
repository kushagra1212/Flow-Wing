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
 * FlowWing Compiler - Vortex Server FFI
 * Requires: cpp-httplib (https://github.com/yhirose/cpp-httplib)
 */

#include "fw_gc.h"
#include "fw_sched.h"
#include "httplib.h"
#include "fw_uv.h"
#include "uv_http_server.h"
#include "uv_http_client.h"
#include <condition_variable>
#include <cstring>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// Helper: Allocate a GC-tracked string to return to FlowWing
static const char *alloc_gc_string(const std::string &str) {
  char *cstr = (char *)fw_gc_alloc(str.length() + 1, &fw_blob_desc);
  if (cstr) {
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
  }
  return cstr;
}

// The shared libuv loop lives in fw-modules/uv_module. Vortex only uses it:
// ensure_loop() creates it (which installs the scheduler waiter) and
// fw_uv_wake() nudges it from a worker thread after queueing work.
//
// Before this, vortex_server_accept blocked on a condition variable, parking
// the whole thread — every other task froze, including timers already due.
static inline void ensure_loop(void) { fw_uv_loop(); }

// The cpp-httplib SERVER implementation lived here and is gone. Serving now
// runs on libuv in uv_http_server.cpp: one uv_tcp_t per connection on the
// shared loop, no thread per connection, no cross-thread handoff.
//
// cpp-httplib is still used below, for the CLIENT only.


// =======================================================================
// FlowWing Compiler - Vortex Client FFI (Stream Receiver Backend)
// Append this to your existing httplib integration C++ file.
// =======================================================================

struct HttpClientContext {
  std::thread worker;
  std::mutex mtx;
  std::condition_variable cv;

  std::queue<std::string> chunks;

  bool headers_received = false;
  bool is_ok = false;
  bool is_done = false;
  bool should_cancel = false;
};

// Helper: Split a URL string into Base URL and Path
static void parse_vortex_url(const std::string &url, std::string &base,
                             std::string &path) {
  size_t pos = url.find("://");
  if (pos != std::string::npos) {
    pos = url.find("/", pos + 3);
    if (pos != std::string::npos) {
      base = url.substr(0, pos);
      path = url.substr(pos);
      return;
    }
  }
  base = url;
  path = "/";
}

extern "C" {

int64_t vortex_client_post_stream_httplib(const char *url_c, const char *body_c) {
  std::string url = url_c ? url_c : "";
  std::string body = body_c ? body_c : "";

  std::string base, path;
  parse_vortex_url(url, base, path);

  ensure_loop(); // a client-only program still needs the scheduler waiter

  HttpClientContext *ctx = new HttpClientContext();

  // Spawn a worker thread so we don't freeze FlowWing while waiting for the
  // network
  ctx->worker = std::thread([ctx, base, path, body]() {
    httplib::Client cli(base);
    cli.set_connection_timeout(5);
    cli.set_read_timeout(120); // Keep alive for long LLM generation

    httplib::Headers headers = {{"Content-Type", "application/json"}};

    // Note: cpp-httplib's Post() only takes a ContentReceiver for streaming.
    // It does not accept a ResponseHandler like Get() does.
    auto res = cli.Post(path, headers, body, "application/json",
                        [ctx](const char *data, size_t data_length) {
                          std::lock_guard<std::mutex> lock(ctx->mtx);
                          if (ctx->should_cancel)
                            return false;

                          // If this is our first chunk of data, we unblock the
                          // caller.
                          if (!ctx->headers_received) {
                            ctx->headers_received = true;
                            ctx->is_ok =
                                true; // LLMs only stream data if HTTP 200 OK
                            ctx->cv.notify_all();
                          }

                          ctx->chunks.push(std::string(data, data_length));
                          ctx->cv.notify_all();
                          // Wake the FlowWing thread if it is idling in
                          // uv_run. Safe across threads; that is the whole
                          // reason the handoff uses uv_async_send.
                          fw_uv_wake();
                          return true;
                        });

    // When the Post completes (or fails outright before any chunks arrive)
    std::lock_guard<std::mutex> lock(ctx->mtx);
    if (!ctx->headers_received) {
      ctx->headers_received = true;
      if (res) {
        ctx->is_ok = (res->status >= 200 && res->status < 300);
      } else {
        ctx->is_ok = false;
      }
    } else if (res) {
      // Update ok status at the end just in case the server returned a short
      // JSON error
      ctx->is_ok = (res->status >= 200 && res->status < 300);
    }
    ctx->is_done = true;
    ctx->cv.notify_all();
    fw_uv_wake();
  });

  // Wait for the first chunk (or a failed connection). Inside a task this
  // suspends only THIS task; other tasks keep running. Outside a task there is
  // nothing to switch to, so block the thread as before.
  if (fw_sched_in_task()) {
    for (;;) {
      {
        std::lock_guard<std::mutex> lock(ctx->mtx);
        if (ctx->headers_received) break;
      }
      fw_sched_park_io();
    }
  } else {
    std::unique_lock<std::mutex> lock(ctx->mtx);
    ctx->cv.wait(lock, [ctx]() { return ctx->headers_received; });
  }

  return reinterpret_cast<int64_t>(ctx);
}

bool vortex_client_res_ok_httplib(int64_t handle) {
  if (!handle)
    return false;
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);
  return ctx->is_ok;
}

const char *vortex_client_read_chunk_httplib(int64_t handle) {
  if (!handle)
    return alloc_gc_string("");
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);

  // Wait for a chunk, or for the stream to end. Suspends the task rather than
  // the thread when there is a scheduler to hand control back to.
  if (fw_sched_in_task()) {
    for (;;) {
      {
        std::lock_guard<std::mutex> lock(ctx->mtx);
        if (!ctx->chunks.empty() || ctx->is_done) break;
      }
      fw_sched_park_io();
    }
  } else {
    std::unique_lock<std::mutex> lock(ctx->mtx);
    ctx->cv.wait(lock, [ctx]() { return !ctx->chunks.empty() || ctx->is_done; });
  }

  std::lock_guard<std::mutex> lock(ctx->mtx);
  if (ctx->chunks.empty()) {
    return alloc_gc_string("");
  }

  std::string chunk = ctx->chunks.front();
  ctx->chunks.pop();

  return alloc_gc_string(chunk);
}

bool vortex_client_is_done_httplib(int64_t handle) {
  if (!handle)
    return true;
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);

  std::lock_guard<std::mutex> lock(ctx->mtx);
  return ctx->is_done && ctx->chunks.empty();
}

void vortex_client_close_httplib(int64_t handle) {
  if (!handle)
    return;
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);

  // Alert the worker thread to safely cancel operations
  {
    std::lock_guard<std::mutex> lock(ctx->mtx);
    ctx->should_cancel = true;
  }

  if (ctx->worker.joinable()) {
    ctx->worker.join();
  }

  delete ctx;
}

} // extern "C"

// ===========================================================================
// Public server FFI -> libuv implementation (uv_http_server.cpp)
//
// The cpp-httplib versions above are kept, renamed with a _httplib suffix, as
// a reference and a fallback. They are no longer reachable from FlowWing.
//
// The libuv path has no thread per connection and no cross-thread handoff:
// requests are parsed on the FlowWing thread inside the shared loop.
// ===========================================================================
extern "C" {

int64_t vortex_server_new() {
  // Creating the loop here also installs the scheduler's idle waiter, so the
  // very first server in a process is what enables socket waiting.
  return fw_http_server_new();
}

bool vortex_server_listen(int64_t handle, int32_t port) {
  return fw_http_server_listen(handle, (int)port) == 0;
}

int64_t vortex_server_accept(int64_t handle) { return fw_http_accept(handle); }

const char *vortex_req_method(int64_t r) { return fw_http_req_method(r); }
const char *vortex_req_path(int64_t r)   { return fw_http_req_path(r); }
const char *vortex_req_body(int64_t r)   { return fw_http_req_body(r); }

void vortex_res_status(int64_t r, int32_t status) {
  fw_http_res_status(r, (int)status);
}

void vortex_res_header(int64_t r, const char *key, const char *val) {
  fw_http_res_header(r, key, val);
}

void vortex_res_send(int64_t r, const char *body) { fw_http_res_send(r, body); }

void vortex_res_stream_begin(int64_t r, const char *ct) {
  fw_http_res_stream_begin(r, ct);
}

void vortex_res_stream_write(int64_t r, const char *chunk) {
  fw_http_res_stream_write(r, chunk);
}

void vortex_res_stream_end(int64_t r) { fw_http_res_stream_end(r); }

// Reads the file inline and sends it as one body. The file module's async read
// is not used here: this runs on the loop thread and a handler that streams
// large files should use the stream_* calls instead.
void vortex_res_send_file(int64_t r, const char *filepath,
                          const char *content_type) {
  if (!r || !filepath) return;
  std::ifstream file(filepath, std::ios::binary);
  if (!file) {
    fw_http_res_status(r, 404);
    fw_http_res_send(r, "File Not Found");
    return;
  }
  std::ostringstream oss;
  oss << file.rdbuf();
  std::string data = oss.str();
  if (content_type) fw_http_res_header(r, "Content-Type", content_type);
  fw_http_res_send(r, data.c_str());
}

} // extern "C"

// ===========================================================================
// Public client FFI -> libuv implementation (uv_http_client.cpp)
//
// The cpp-httplib versions above keep a _httplib suffix as reference. They are
// no longer reachable from FlowWing.
//
// The libuv path has no thread per request and no mutex: the response is
// parsed on the FlowWing thread inside the shared loop, so ten concurrent
// requests from ten tasks share one thread instead of starting ten.
// ===========================================================================
extern "C" {

int64_t vortex_client_post_stream(const char *url, const char *body) {
  return fw_http_client_post_stream(url, body);
}

bool vortex_client_res_ok(int64_t handle) {
  return fw_http_client_ok(handle) != 0;
}

const char *vortex_client_read_chunk(int64_t handle) {
  return fw_http_client_read_chunk(handle);
}

bool vortex_client_is_done(int64_t handle) {
  return fw_http_client_is_done(handle) != 0;
}

void vortex_client_close(int64_t handle) { fw_http_client_close(handle); }

} // extern "C"
