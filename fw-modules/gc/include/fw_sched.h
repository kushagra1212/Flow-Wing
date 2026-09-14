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

/* A task body. Void-void: arguments are evaluated at the spawn site only once
   the binder allows them (see kSpawnArgumentsNotSupported). */
typedef void (*FWTaskFn)(void);

/* Queue `fn` as a task. NULL is ignored. The task's stack is NOT allocated
   here — it is taken on first resume and released on completion, so queueing a
   million tasks costs a million small records, not a million stacks. */
void fw_sched_spawn(FWTaskFn fn);

/* Suspend the running task and hand control back to the scheduler. The task
   goes to the BACK of the ready queue, so other queued work runs before it
   continues. A no-op when called outside a task (e.g. from main). */
void fw_sched_yield(void);

/* Run queued tasks until none are ready. Tasks may spawn or yield; both are
   handled inside this one call. */
void fw_sched_drain(void);

/* Wait `ms` milliseconds.
 *
 * Inside a task this SUSPENDS: the task is parked with a deadline and other
 * ready work runs meanwhile, so N tasks each waiting 100ms finish in ~100ms
 * total rather than N*100ms. Outside a task there is nothing to switch to, so
 * it blocks the thread instead. */
void fw_sched_sleep_ms(long long ms);

/* Number of tasks still queued. Test/introspection hook. */
unsigned long fw_sched_pending(void);

/* Non-zero while a task body is on the CPU. Lets primitives decide between
   yielding and blocking. */
int fw_sched_in_task(void);

#ifdef __cplusplus
}
#endif

#endif /* FW_SCHED_H */
