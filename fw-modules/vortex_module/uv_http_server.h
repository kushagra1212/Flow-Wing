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
 * FlowWing Runtime - libuv-native HTTP/1.1 server
 *
 * Replaces the cpp-httplib path for serving. The difference that matters:
 *
 *   cpp-httplib   one OS THREAD per in-flight connection, from a pool of
 *                 max(8, cores-1) growing to 4x that. Concurrency is capped by
 *                 that pool, and each connection costs a thread stack.
 *
 *   this          one uv_tcp_t per connection on the SHARED loop. Concurrency
 *                 is capped by file descriptors, and a connection costs a few
 *                 hundred bytes. No thread per connection, and no cross-thread
 *                 handoff at all — requests arrive on the FlowWing thread.
 *
 * Parsing is llhttp (the parser Node.js uses). Sockets, response writing,
 * chunked encoding and keep-alive are Flow-Wing's own, so the request/response
 * lifetime matches what the scheduler needs.
 *
 * NOT provided: TLS. cpp-httplib had it via OpenSSL. Driving OpenSSL memory
 * BIOs from uv_write by hand is security-sensitive work and is deliberately
 * left out rather than done badly. Terminate TLS in front (nginx, Caddy) until
 * it exists here.
 */

#ifndef FW_UV_HTTP_SERVER_H
#define FW_UV_HTTP_SERVER_H

#include <cstddef>   // size_t, for the length-aware send below
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Create a server. Returns 0 on failure. */
int64_t fw_http_server_new(void);

/* Bind and start listening. Returns 0 on success, a uv error code otherwise. */
int fw_http_server_listen(int64_t server, int port);

/* Take the next complete request, suspending the calling task while none is
   ready. Returns a request handle, or 0 if the server shut down. */
int64_t fw_http_accept(int64_t server);

/* Request accessors. Each returns GC memory owned by FlowWing. */
const char *fw_http_req_method(int64_t req);
const char *fw_http_req_path(int64_t req);
const char *fw_http_req_query(int64_t req);  // '?' onwards, without the '?'
const char *fw_http_req_body(int64_t req);

/* Response building. */
void fw_http_res_status(int64_t req, int status);
void fw_http_res_header(int64_t req, const char *key, const char *value);
void fw_http_res_send(int64_t req, const char *body);
// Binary-safe: use when the body may contain NUL bytes (images, archives).
void fw_http_res_send_n(int64_t req, const char *body, size_t len);

/* Chunked streaming. */
void fw_http_res_stream_begin(int64_t req, const char *content_type);
void fw_http_res_stream_write(int64_t req, const char *chunk);
void fw_http_res_stream_end(int64_t req);

/* Stop listening and free every request the handler never answered. */
void fw_http_server_close(int64_t server);

/* Connections currently open. Used by tests to show that concurrency is not
   bounded by a thread pool. */
unsigned long fw_http_open_connections(int64_t server);

#ifdef __cplusplus
}
#endif

#endif /* FW_UV_HTTP_SERVER_H */
