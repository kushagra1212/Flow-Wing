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
 * FlowWing Runtime - libuv-native streaming HTTP/1.1 client.
 *
 * Replaces the cpp-httplib client, which started a std::thread per request and
 * handed chunks back through a mutex, a condition variable and uv_async_send.
 * The server moved to libuv first; this is the other half.
 *
 * Everything now runs on the FlowWing thread inside the shared loop, so there
 * is no thread, no mutex and no cross-thread handoff. A request in flight costs
 * one socket, not one socket plus a 512 KB thread stack, and ten concurrent
 * requests from ten tasks use one thread between them.
 *
 * Scope is deliberately the same as the client it replaces: plain HTTP, one
 * POST with a streaming response body. There is no TLS here, exactly as there
 * was none before — cpp-httplib was compiled without CPPHTTPLIB_OPENSSL_SUPPORT,
 * so `https://` never worked through this path.
 */

#ifndef FW_UV_HTTP_CLIENT_H
#define FW_UV_HTTP_CLIENT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Start a POST and wait until the response headers have arrived (or the
   attempt has failed). Inside a task this SUSPENDS that task and lets other
   work run; outside a task it pumps the loop instead of blocking on a
   condition variable. Returns a request handle, or 0 if the URL was unusable.
   The handle is valid until fw_http_client_close. */
int64_t fw_http_client_post_stream(const char *url, const char *body);

/* Whether the response status was 2xx. Meaningful once the call above has
   returned. */
int fw_http_client_ok(int64_t req);

/* Next body chunk, as a GC string. Empty when the stream has finished.
   Suspends the calling task until a chunk arrives or the response ends. */
const char *fw_http_client_read_chunk(int64_t req);

/* Non-zero once the response has ended AND every buffered chunk has been
   read. */
int fw_http_client_is_done(int64_t req);

/* Release the request. Safe at any point, including with a transfer still in
   flight and with chunks still buffered. */
void fw_http_client_close(int64_t req);

#ifdef __cplusplus
}
#endif

#endif /* FW_UV_HTTP_CLIENT_H */
