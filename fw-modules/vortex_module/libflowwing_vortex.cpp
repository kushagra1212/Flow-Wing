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
#include "httplib.h"
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

struct VortexServer;

// Represents a single HTTP transaction
struct HttpContext {
  const httplib::Request *req;
  httplib::Response *res;

  std::mutex mtx;
  std::condition_variable cv;
  bool handled = false;

  // Stream state
  bool is_streaming = false;
  std::string stream_content_type;
  std::queue<std::string> stream_chunks;
  bool stream_done = false;

  // Owning server, so completion handlers can drop the keep-alive reference.
  VortexServer *server = nullptr;
};

// Represents the Vortex Server
struct VortexServer {
  httplib::Server svr;
  std::thread listener_thread;

  std::queue<HttpContext *> req_queue;
  std::mutex queue_mtx;
  std::condition_variable queue_cv;

  // Keep-alive registry: FlowWing holds each HttpContext by a RAW int64 pointer
  // across many FFI calls, but the C++ side (the httplib worker thread and the
  // chunked content-provider) owns the real lifetime. Under GC stress FlowWing
  // runs ~100x slower, so httplib can tear down the response — and destroy the
  // context — while FlowWing is still using its raw pointer (e.g. mid-stream),
  // giving "mutex lock failed: Invalid argument". Holding a shared_ptr here
  // keeps every in-flight context alive until FlowWing signals it is done (send
  // / streamEnd), independent of the httplib teardown timing.
  std::map<HttpContext *, std::shared_ptr<HttpContext>> live_ctxs;
  std::mutex live_mtx;
};

// Drop the server's keep-alive reference once FlowWing is finished with a
// request. Any still-live C++ owner (worker thread / content provider) keeps
// the object alive until it, too, is done; this only removes the extra safety
// ref.
static void vortex_release_ctx(HttpContext *ctx) {
  if (ctx == nullptr || ctx->server == nullptr)
    return;
  std::lock_guard<std::mutex> lock(ctx->server->live_mtx);
  ctx->server->live_ctxs.erase(ctx);
}

extern "C" {

void vortex_res_send_file(int64_t req_handle, const char *filepath,
                          const char *content_type) {
  if (!req_handle || !filepath || !content_type)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);

  // Read the file in binary mode
  std::ifstream file(filepath, std::ios::binary);
  if (!file) {
    ctx->res->status = 404;
    ctx->res->set_content("File Not Found", "text/plain");
  } else {
    // Read the entire file buffer into a string safely (preserves null bytes)
    std::ostringstream oss;
    oss << file.rdbuf();
    std::string data = oss.str();

    // Use the explicit length set_content method so httplib doesn't truncate it
    ctx->res->set_content(data.c_str(), data.size(), content_type);
  }

  // Unblock the FlowWing thread. Notify under the lock so the worker cannot
  // wake, return, and destroy this HttpContext before notify completes (see
  // vortex_res_send for the full rationale).
  {
    std::lock_guard<std::mutex> lock(ctx->mtx);
    ctx->handled = true;
    ctx->cv.notify_one();
  }
  vortex_release_ctx(ctx); // FlowWing is done with this request
}

int64_t vortex_server_new() {
  VortexServer *server = new VortexServer();
  // Catch-all route to intercept every request and pipe it to FlowWing
  server->svr.set_error_handler(
      [](const httplib::Request &, httplib::Response &) {});

  // 1. Define the handler logic once
  auto universal_handler = [server](const httplib::Request &req,
                                    httplib::Response &res) {
    // Shared pointer keeps context alive during async streaming
    auto ctx = std::make_shared<HttpContext>();
    ctx->req = &req;
    ctx->res = &res;
    ctx->server = server;

    // Register a keep-alive reference so FlowWing's raw pointer stays valid for
    // the whole request even if httplib tears the response down first (dropped
    // when FlowWing finishes via send/streamEnd → vortex_release_ctx).
    {
      std::lock_guard<std::mutex> lock(server->live_mtx);
      server->live_ctxs[ctx.get()] = ctx;
    }

    // Push to FlowWing queue
    {
      std::lock_guard<std::mutex> lock(server->queue_mtx);
      server->req_queue.push(ctx.get());
    }
    server->queue_cv.notify_one();

    // Block the C++ worker thread until FlowWing calls vortex_res_send
    std::unique_lock<std::mutex> wait_lock(ctx->mtx);
    ctx->cv.wait(wait_lock, [&ctx] { return ctx->handled; });

    // If streaming was initialized, register cpp-httplib's chunked provider
    if (ctx->is_streaming) {
      res.set_content_provider(
          ctx->stream_content_type
              .c_str(), // Content type triggers chunked transfer
          [ctx](size_t offset, httplib::DataSink &sink) {
            std::unique_lock<std::mutex> lock(ctx->mtx);

            // Wait until we have chunks or the stream signals end
            ctx->cv.wait(lock, [&ctx] {
              return !ctx->stream_chunks.empty() || ctx->stream_done;
            });

            // Unload buffer onto the connection socket
            while (!ctx->stream_chunks.empty()) {
              std::string chunk = ctx->stream_chunks.front();
              ctx->stream_chunks.pop();
              sink.write(chunk.c_str(), chunk.size());
            }

            if (ctx->stream_done && ctx->stream_chunks.empty()) {
              sink.done();
            }

            return true; // continue fetching chunks
          });
    }
  };

  // 2. Register the same handler for all HTTP methods using a regex catch-all
  server->svr.Get(".*", universal_handler);
  server->svr.Post(".*", universal_handler);
  server->svr.Put(".*", universal_handler);
  server->svr.Delete(".*", universal_handler);
  server->svr.Patch(".*", universal_handler);
  server->svr.Options(".*", universal_handler);

  return reinterpret_cast<int64_t>(server);
}

bool vortex_server_listen(int64_t handle, int32_t port) {
  if (!handle)
    return false;
  VortexServer *server = reinterpret_cast<VortexServer *>(handle);

  // Start HTTP server in a background thread so FlowWing isn't blocked
  server->listener_thread =
      std::thread([server, port]() { server->svr.listen("0.0.0.0", port); });

  server->svr.wait_until_ready();

  if (!server->svr.is_running()) {
    if (server->listener_thread.joinable()) {
      server->listener_thread.join();
    }
    return false;
  }

  server->listener_thread.detach();
  return true;
}

int64_t vortex_server_accept(int64_t handle) {
  if (!handle)
    return 0;
  VortexServer *server = reinterpret_cast<VortexServer *>(handle);

  std::unique_lock<std::mutex> lock(server->queue_mtx);
  // Block FlowWing thread until an HTTP request arrives
  server->queue_cv.wait(lock, [server] { return !server->req_queue.empty(); });

  HttpContext *ctx = server->req_queue.front();
  server->req_queue.pop();

  return reinterpret_cast<int64_t>(ctx);
}

// --- Request FFI ---

const char *vortex_req_method(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->method);
}

const char *vortex_req_path(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->path);
}

const char *vortex_req_body(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->body);
}

// --- Response FFI ---

void vortex_res_status(int64_t req_handle, int32_t status) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  ctx->res->status = status;
}

void vortex_res_header(int64_t req_handle, const char *key, const char *val) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  ctx->res->set_header(key, val);
}

void vortex_res_send(int64_t req_handle, const char *body) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);

  // If content-type wasn't set by json(), default to text/plain
  if (!ctx->res->has_header("Content-Type")) {
    ctx->res->set_content(body, "text/plain");
  } else {
    ctx->res->body = body; // httplib will use the user-set content type
  }

  // Unblock the C++ worker thread so it can send the HTTP response to the
  // client. Notify WHILE holding the lock: once `handled` is set and the lock
  // is released, the worker's universal_handler wakes and, for a non-streaming
  // request, returns and drops the last shared_ptr — destroying this
  // HttpContext (mutex + condvar). Notifying after unlocking would then touch a
  // freed condvar ("mutex lock failed: Invalid argument" under GC stress, which
  // widens the window). Under the lock the worker cannot re-acquire and destroy
  // the context until notify has completed.
  {
    std::lock_guard<std::mutex> lock(ctx->mtx);
    ctx->handled = true;
    ctx->cv.notify_one();
  }
  vortex_release_ctx(ctx); // FlowWing is done with this request
}

// --- Stream FFI ---

void vortex_res_stream_begin(int64_t req_handle, const char *content_type) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);

  std::lock_guard<std::mutex> lock(ctx->mtx);
  ctx->is_streaming = true;
  ctx->stream_content_type = content_type;
  ctx->handled = true;
  ctx->cv.notify_one();
}

void vortex_res_stream_write(int64_t req_handle, const char *chunk) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);

  std::lock_guard<std::mutex> lock(ctx->mtx);
  ctx->stream_chunks.push(chunk);
  ctx->cv.notify_one(); // Awaken the inner httplib provider
}

void vortex_res_stream_end(int64_t req_handle) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);

  {
    std::lock_guard<std::mutex> lock(ctx->mtx);
    ctx->stream_done = true;
    ctx->cv.notify_one();
  }
  // FlowWing is done producing the stream. Drop the keep-alive ref; the chunked
  // content-provider keeps the context alive until it has flushed and finished.
  vortex_release_ctx(ctx);
}
}

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

int64_t vortex_client_post_stream(const char *url_c, const char *body_c) {
  std::string url = url_c ? url_c : "";
  std::string body = body_c ? body_c : "";

  std::string base, path;
  parse_vortex_url(url, base, path);

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
  });

  // Pause the FlowWing thread ONLY until the first chunk arrives (or connection
  // fails)
  std::unique_lock<std::mutex> lock(ctx->mtx);
  ctx->cv.wait(lock, [ctx]() { return ctx->headers_received; });

  return reinterpret_cast<int64_t>(ctx);
}

bool vortex_client_res_ok(int64_t handle) {
  if (!handle)
    return false;
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);
  return ctx->is_ok;
}

const char *vortex_client_read_chunk(int64_t handle) {
  if (!handle)
    return alloc_gc_string("");
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);

  std::unique_lock<std::mutex> lock(ctx->mtx);
  // Yield the thread until there is a chunk to read or the connection is done
  ctx->cv.wait(lock, [ctx]() { return !ctx->chunks.empty() || ctx->is_done; });

  if (ctx->chunks.empty()) {
    return alloc_gc_string("");
  }

  std::string chunk = ctx->chunks.front();
  ctx->chunks.pop();

  return alloc_gc_string(chunk);
}

bool vortex_client_is_done(int64_t handle) {
  if (!handle)
    return true;
  HttpClientContext *ctx = reinterpret_cast<HttpClientContext *>(handle);

  std::lock_guard<std::mutex> lock(ctx->mtx);
  return ctx->is_done && ctx->chunks.empty();
}

void vortex_client_close(int64_t handle) {
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