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
 * FlowWing Runtime - shared libuv event loop
 *
 * One loop per process, owned here rather than by any single module, so the
 * HTTP server, the HTTP client and file I/O all wait in the same place.
 *
 * The first call to fw_uv_loop() installs the scheduler's idle waiter. After
 * that the scheduler idles inside uv_run instead of nanosleep, which is what
 * lets a task park on a socket or a file without stopping every other task.
 */

#ifndef FW_UV_H
#define FW_UV_H

#include <uv.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The shared loop. Initialises it and installs the scheduler waiter on first
   call. Returns NULL only if the loop could not be created. */
uv_loop_t *fw_uv_loop(void);

/* Non-zero once the loop exists. */
int fw_uv_ready(void);

/* Wake the loop. This is the ONLY function here that may be called from a
   thread other than the FlowWing thread — it is a thin wrapper over
   uv_async_send, which libuv documents as thread-safe. Use it after handing
   work to FlowWing from a worker thread. */
void fw_uv_wake(void);

/* libuv version the runtime was built against. */
const char *fw_uv_version(void);

#ifdef __cplusplus
}
#endif

#endif /* FW_UV_H */
