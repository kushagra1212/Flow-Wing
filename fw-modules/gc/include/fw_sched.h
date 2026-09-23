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
 * FlowWing Runtime - Cooperative coroutine scheduler
 *
 * `spawn f()` does not call f inline: it queues a TASK. Each task gets its own
 * machine stack, so it can suspend part-way through (fw_sched_yield) and be
 * resumed later exactly where it left off. The queue is drained once the
 * program's top-level body finishes.
 *
 * Single-threaded by construction. FlowWing runs user code on one thread and
 * the GC (fw_gc_*) has no locks, so nothing here needs synchronisation — that
 * is the entire reason tasks are coroutines rather than threads.
 *
 * GC: a suspended task's shadow frames live on ITS stack, not on the chain
 * `fw_gc_shadow_top` points at. The scheduler registers an aux root scanner
 * with the GC so those chains are still marked. Switching tasks saves and
 * restores `fw_gc_shadow_top` around the stack swap.
 */

#ifndef FW_SCHED_H
#define FW_SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

/* A task body with no arguments. */
typedef void (*FWTaskFn)(void);

/* A task body that receives an argument block: a GC object built at the spawn
   site holding the already-evaluated arguments. */
typedef void (*FWTaskArgsFn)(void *args);

/* Queue `fn` as a task. NULL is ignored. The task's stack is NOT allocated
   here — it is taken on first resume and released on completion, so queueing a
   million tasks costs a million small records, not a million stacks. */
void fw_sched_spawn(FWTaskFn fn);

/* Queue `fn` with an argument block.
 *
 * `args` must be GC memory (fw_gc_alloc) whose descriptor describes its
 * pointer fields. The scheduler keeps it rooted for the task's whole life:
 * a queued task owns no stack yet, so without that root the arguments would be
 * collected between the spawn and the call. */
void fw_sched_spawn_args(FWTaskArgsFn fn, void *args);

/* Suspend the running task and hand control back to the scheduler. The task
   goes to the BACK of the ready queue, so other queued work runs before it
   continues. A no-op when called outside a task (e.g. from main). */
void fw_sched_yield(void);

/* Run queued tasks until none are ready. Tasks may spawn or yield; both are
   handled inside this one call.

   NOT re-entrant, and does not need to be: calling it from inside a task
   returns immediately without running anything. The outer drain already picks
   up every queued task, including ones the running task just spawned, so a
   nested call would add nothing. It is refused rather than performed because
   the scheduler keeps a single saved resume point, which a nested call would
   overwrite — that used to crash. */
void fw_sched_drain(void);

/* Wait `ms` milliseconds.
 *
 * Inside a task this SUSPENDS: the task is parked with a deadline and other
 * ready work runs meanwhile, so N tasks each waiting 100ms finish in ~100ms
 * total rather than N*100ms. Outside a task there is nothing to switch to, so
 * it blocks the thread instead. */
void fw_sched_sleep_ms(long long ms);

/* ---- waiting on things that are not clocks ------------------------------
 *
 * On its own the scheduler can only wait on a deadline (nanosleep). That is
 * enough for sys::sleep and nothing else: a task waiting on a SOCKET would
 * have to block the thread, stopping every other task.
 *
 * An event layer (the Vortex module, which owns a libuv loop) plugs itself in
 * here. The scheduler then idles inside uv_run instead of nanosleep, so a
 * socket and a timer can wake it.
 */

/* Idle until something happens, but no longer than max_wait_ns. A negative
   value means "no deadline, wait until an event arrives". Called ONLY from the
   scheduler thread, and only when no task is ready to run. */
typedef void (*FWWaitFn)(long long max_wait_ns);

/* Install the idle waiter. NULL (the default) falls back to nanosleep. */
void fw_sched_set_waiter(FWWaitFn fn);

/* Park the running task until fw_sched_wake_io() is called. Unlike
   fw_sched_sleep_ms there is no deadline — the task waits for an event.
   A no-op outside a task. */
void fw_sched_park_io(void);

/* Move every task parked by fw_sched_park_io back to the ready queue.
   MUST be called on the scheduler thread. An event layer calls it from inside
   its loop callback, never from a worker thread. */
void fw_sched_wake_io(void);

/* Number of tasks parked on fw_sched_park_io. Lets the waiter decide between
   an indefinite wait and returning at once. */
unsigned long fw_sched_io_waiting(void);

/* ---- running a command without stopping every other task ---------------
 *
 * popen blocks the thread, so a task that runs a shell command (sys::exec,
 * sys::run) stops every other task until the command ends. In a server that
 * is every other visitor, for as long as the command takes. An event layer
 * that can run a process asynchronously (flowwing_uv, with its loop) plugs in
 * here, and the task waits for the command the way it waits for a socket.
 */

/* Run `command` through the platform shell, as popen does: stdin and stderr
   are the program's own, stdout is captured. On success returns 0, sets
   *output to a malloc'd, NUL-terminated copy of what the command printed
   (the caller frees it) and *status to the exit status as a shell reports it
   in $?. Returns -1 when the command could not be run this way. */
typedef int (*FWExecFn)(const char *command, char **output, int *status);

/* Install the asynchronous runner. NULL (the default) leaves callers to run
   commands themselves, blocking. */
void fw_sched_set_exec(FWExecFn fn);

/* Runs `command` through the installed runner, parking only the calling
   task. Only inside a task with a runner installed; otherwise it does nothing
   and returns -1, and the caller runs the command itself. Same contract as
   FWExecFn. */
int fw_sched_exec(const char *command, char **output, int *status);

/* Number of tasks still queued. Test/introspection hook. */
unsigned long fw_sched_pending(void);

/* Non-zero while a task body is on the CPU. Lets primitives decide between
   yielding and blocking. */
int fw_sched_in_task(void);

#ifdef __cplusplus
}
#endif

#endif /* FW_SCHED_H */
