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

#include "httplib.h"
#include <condition_variable>
#include <cstring>
#include <gc/gc.h>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// Helper: Allocate a GC-tracked string to return to FlowWing
static const char *alloc_gc_string(const std::string &str) {
  char *cstr = (char *)GC_MALLOC_ATOMIC(str.length() + 1);
  if (cstr) {
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
  }
  return cstr;
}

// Represents a single HTTP transaction
struct HttpContext {
  const httplib::Request *req;
  httplib::Response *res;

  std::mutex mtx;
  std::condition_variable cv;
  bool handled = false;
};

// Represents the Vortex Server
struct VortexServer {
  httplib::Server svr;
  std::thread listener_thread;

  std::queue<HttpContext *> req_queue;
  std::mutex queue_mtx;
  std::condition_variable queue_cv;
};

extern "C" {

  int64_t dyn_vortex_server_new() {
    VortexServer* server = new VortexServer();
    // Catch-all route to intercept every request and pipe it to FlowWing
    server->svr.set_error_handler([](const httplib::Request&, httplib::Response&) {});
    
    // 1. Define the handler logic once
    auto universal_handler = [server](const httplib::Request& req, httplib::Response& res) {
        HttpContext ctx;
        ctx.req = &req;
        ctx.res = &res;

        // Push to FlowWing queue
        {
            std::lock_guard<std::mutex> lock(server->queue_mtx);
            server->req_queue.push(&ctx);
        }
        server->queue_cv.notify_one();

        // Block the C++ worker thread until FlowWing calls dyn_vortex_res_send
        std::unique_lock<std::mutex> wait_lock(ctx.mtx);
        ctx.cv.wait(wait_lock, [&ctx] { return ctx.handled; });
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

bool dyn_vortex_server_listen(int64_t handle, int32_t port) {
  if (!handle)
    return false;
  VortexServer *server = reinterpret_cast<VortexServer *>(handle);

  // Start HTTP server in a background thread so FlowWing isn't blocked
  server->listener_thread =
      std::thread([server, port]() { server->svr.listen("0.0.0.0", port); });

  server->listener_thread.detach();
  return true;
}

int64_t dyn_vortex_server_accept(int64_t handle) {
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

const char *dyn_vortex_req_method(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->method);
}

const char *dyn_vortex_req_path(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->path);
}

const char *dyn_vortex_req_body(int64_t req_handle) {
  if (!req_handle)
    return alloc_gc_string("");
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  return alloc_gc_string(ctx->req->body);
}

// --- Response FFI ---

void dyn_vortex_res_status(int64_t req_handle, int32_t status) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  ctx->res->status = status;
}

void dyn_vortex_res_header(int64_t req_handle, const char *key,
                           const char *val) {
  if (!req_handle)
    return;
  HttpContext *ctx = reinterpret_cast<HttpContext *>(req_handle);
  ctx->res->set_header(key, val);
}

void dyn_vortex_res_send(int64_t req_handle, const char *body) {
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
  // client
  {
    std::lock_guard<std::mutex> lock(ctx->mtx);
    ctx->handled = true;
  }
  ctx->cv.notify_one();
}
}