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
 * Unit tests for the coroutine scheduler (fw_sched.c).
 *
 * The .fg fixtures drive the scheduler through the `spawn` keyword, which only
 * reaches the parts of the API that the language exposes. Several functions
 * have no FlowWing spelling at all and are called only by the event layer:
 *
 *   fw_sched_park_io / fw_sched_wake_io / fw_sched_io_waiting
 *   fw_sched_set_waiter
 *   fw_sched_pending / fw_sched_in_task
 *
 * Those are the ones a socket depends on, so they are tested here directly.
 */

#include "fw_gc.h"
#include "fw_sched.h"
#include "test_harness.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ---- shared recording state -------------------------------------------- */

#define LOG_CAP 4096
static char  g_log[LOG_CAP];
static int   g_ran;

static void log_reset(void) {
  g_log[0] = '\0';
  g_ran = 0;
}

/* Bounded append. strncat/strcpy/strncpy are avoided throughout this file:
   MSVC reports them as deprecated (C4996), and test_gc.c — which is known to
   build on the Windows CI job — does not use them either. */
static void log_put(const char *s) {
  size_t used = strlen(g_log);
  size_t len  = strlen(s);
  if (used + len < LOG_CAP) {
    memcpy(g_log + used, s, len + 1);
  }
  g_ran++;
}

/* Copy at most cap-1 bytes and always terminate. */
static void copy_bounded(char *dst, size_t cap, const char *src) {
  size_t len = strlen(src);
  if (len > cap - 1) {
    len = cap - 1;
  }
  memcpy(dst, src, len);
  dst[len] = '\0';
}

/* ---- basic queueing ----------------------------------------------------- */

static void task_a(void) { log_put("a"); }
static void task_b(void) { log_put("b"); }
static void task_c(void) { log_put("c"); }

static void test_spawn_runs_in_fifo_order(void) {
  log_reset();
  fw_sched_spawn(task_a);
  fw_sched_spawn(task_b);
  fw_sched_spawn(task_c);

  /* Queued, not run: a spawn never executes inline. */
  CHECK(fw_sched_pending() == 3);
  CHECK(strcmp(g_log, "") == 0);

  fw_sched_drain();

  CHECK(strcmp(g_log, "abc") == 0);
  CHECK(fw_sched_pending() == 0);
}

static void test_spawn_null_is_ignored(void) {
  log_reset();
  fw_sched_spawn(NULL);
  CHECK(fw_sched_pending() == 0);

  fw_sched_drain();
  CHECK(g_ran == 0);
}

static void test_drain_on_empty_queue_is_a_no_op(void) {
  log_reset();
  CHECK(fw_sched_pending() == 0);
  fw_sched_drain();
  fw_sched_drain();
  CHECK(g_ran == 0);
  CHECK(fw_sched_pending() == 0);
}

/* ---- in_task ------------------------------------------------------------ */

static int g_in_task_inside = -1;

static void task_checks_in_task(void) {
  g_in_task_inside = fw_sched_in_task();
}

static void test_in_task_reports_the_right_context(void) {
  /* On the main stack there is no task running. */
  CHECK(fw_sched_in_task() == 0);

  g_in_task_inside = -1;
  fw_sched_spawn(task_checks_in_task);
  fw_sched_drain();

  CHECK(g_in_task_inside == 1);

  /* And the flag is cleared once the drain is over. */
  CHECK(fw_sched_in_task() == 0);
}

/* ---- yield -------------------------------------------------------------- */

static void task_yields_twice(void) {
  log_put("1");
  fw_sched_yield();
  log_put("2");
  fw_sched_yield();
  log_put("3");
}

static void task_plain(void) { log_put("x"); }

static void test_yield_sends_the_task_to_the_back(void) {
  log_reset();
  fw_sched_spawn(task_yields_twice);
  fw_sched_spawn(task_plain);
  fw_sched_drain();

  /* Y runs to its first yield, X then runs to completion, Y resumes.
     Interleaving is what proves the task really suspended rather than
     running straight through. */
  CHECK(strcmp(g_log, "1x23") == 0);
}

static void test_yield_outside_a_task_is_a_no_op(void) {
  /* Nothing to switch to: it must return rather than crash or hang. */
  fw_sched_yield();
  fw_sched_yield();
  CHECK(fw_sched_in_task() == 0);
}

/* ---- spawning from inside a task ---------------------------------------- */

static void task_child(void) { log_put("C"); }

static void task_parent(void) {
  log_put("P");
  fw_sched_spawn(task_child);
}

static void test_task_can_spawn_another_task(void) {
  log_reset();
  fw_sched_spawn(task_parent);
  fw_sched_drain();

  /* One drain call handles work queued by the work it is already running. */
  CHECK(strcmp(g_log, "PC") == 0);
  CHECK(fw_sched_pending() == 0);
}

/* ---- re-entrant drain --------------------------------------------------- */

static int g_nested_drain_returned;

static void task_drains_from_inside(void) {
  log_put("O");
  fw_sched_spawn(task_child);     /* queued work for the OUTER loop */

  /* The scheduler saves its resume point in a single global and clears the
     queue indices when it finishes, so a nested drain used to overwrite both
     and crash the process with SIGSEGV once the outer task ended. It now
     returns at once instead. */
  fw_sched_drain();
  g_nested_drain_returned = 1;

  log_put("o");
}

static void test_nested_drain_is_refused(void) {
  log_reset();
  g_nested_drain_returned = 0;

  fw_sched_spawn(task_drains_from_inside);
  fw_sched_drain();

  /* Reaching this line at all is the main assertion: before the guard the
     outer drain never returned. */
  CHECK(g_nested_drain_returned == 1);

  /* The nested call ran nothing itself, so the child runs after the parent
     finishes, in the outer loop, in ordinary queue order. */
  CHECK(strcmp(g_log, "OoC") == 0);
  CHECK(fw_sched_pending() == 0);
}

static void test_many_tasks_all_run(void) {
  const int N = 5000;
  log_reset();
  for (int i = 0; i < N; i++) {
    fw_sched_spawn(task_plain);
  }
  CHECK(fw_sched_pending() == (unsigned long)N);

  fw_sched_drain();
  CHECK(g_ran == N);
  CHECK(fw_sched_pending() == 0);
}

/* ---- arguments ---------------------------------------------------------- */

typedef struct {
  int   value;
  char *text;          /* GC pointer: must stay traced until the task runs */
} ArgBlock;

static const uint32_t g_argblock_ptr_offsets[] = {
  (uint32_t)offsetof(ArgBlock, text)
};

static const FWTypeDescriptor g_argblock_desc = {
  .name = "ArgBlock",
  .kind = FW_KIND_PLAIN,
  .num_ptrs = 1,
  .ptr_offsets = g_argblock_ptr_offsets
};

static int  g_seen_value;
static char g_seen_text[64];

/* A stable address the collector can treat as a root slot. A C local cannot
   be one: the GC scans globals and the shadow stack, not this file's frames. */
static void *g_block_slot;

static void task_with_args(void *args) {
  ArgBlock *a = (ArgBlock *)args;
  g_seen_value = a->value;
  g_seen_text[0] = '\0';
  if (a->text) {
    copy_bounded(g_seen_text, sizeof(g_seen_text), a->text);
  }
}

static void test_spawn_args_delivers_the_block(void) {
  fw_gc_init();
  g_seen_value = 0;
  g_seen_text[0] = '\0';

  ArgBlock *a = (ArgBlock *)fw_gc_alloc(sizeof(ArgBlock), &g_argblock_desc);
  g_block_slot = a;
  fw_gc_add_root(&g_block_slot);   /* see test_stress_mode_with_tasks */

  a->value = 42;
  a->text = (char *)fw_gc_alloc(8, &fw_blob_desc);
  copy_bounded(a->text, 8, "hello");

  fw_sched_spawn_args(task_with_args, a);
  fw_gc_remove_root(&g_block_slot);
  g_block_slot = NULL;

  fw_sched_drain();

  CHECK(g_seen_value == 42);
  CHECK(strcmp(g_seen_text, "hello") == 0);
}

static void test_spawn_args_survives_collection_before_the_task_runs(void) {
  fw_gc_init();
  g_seen_value = 0;
  g_seen_text[0] = '\0';

  ArgBlock *a = (ArgBlock *)fw_gc_alloc(sizeof(ArgBlock), &g_argblock_desc);
  g_block_slot = a;
  fw_gc_add_root(&g_block_slot);   /* rooted only while the block is built */

  a->value = 7;
  a->text = (char *)fw_gc_alloc(16, &fw_blob_desc);
  copy_bounded(a->text, 16, "survive");

  fw_sched_spawn_args(task_with_args, a);

  /* Drop the test's own root: from here the scheduler's root is the ONLY
     thing keeping the block and its string alive. */
  fw_gc_remove_root(&g_block_slot);
  g_block_slot = NULL;

  /* This is the whole point of rooting the block in the scheduler: a queued
     task owns no stack yet, so nothing else refers to these two objects.
     Without the root they would both be swept right here. */
  fw_gc_collect();
  fw_gc_collect();

  fw_sched_drain();

  CHECK(g_seen_value == 7);
  CHECK(strcmp(g_seen_text, "survive") == 0);
}

static void test_spawn_args_null_fn_is_ignored(void) {
  fw_sched_spawn_args(NULL, NULL);
  CHECK(fw_sched_pending() == 0);
  fw_sched_drain();
}

static int g_null_block_seen;

static void task_tolerates_null_args(void *args) {
  g_null_block_seen = (args == NULL) ? 1 : 0;
}

static void test_spawn_args_allows_a_null_block(void) {
  /* Only a null FUNCTION means "no task". A null BLOCK is a value like any
     other and is handed to the task unchanged, so a caller that has nothing
     to pass does not need a separate entry point. */
  g_null_block_seen = -1;

  fw_sched_spawn_args(task_tolerates_null_args, NULL);
  CHECK(fw_sched_pending() == 1);

  fw_sched_drain();

  CHECK(g_null_block_seen == 1);
  CHECK(fw_sched_pending() == 0);
}

/* ---- sleeping ----------------------------------------------------------- */

static void task_sleeps_then_logs(void) {
  fw_sched_sleep_ms(15);
  log_put("s");
}

static void test_sleep_inside_a_task_overlaps(void) {
  log_reset();

  /* Three tasks each waiting 15 ms. If sleeping blocked the thread they would
     take 45 ms in total; because each one suspends, they overlap. The check
     is on ORDER and completion rather than wall time, which is not
     reproducible on a loaded machine. */
  fw_sched_spawn(task_sleeps_then_logs);
  fw_sched_spawn(task_sleeps_then_logs);
  fw_sched_spawn(task_sleeps_then_logs);
  fw_sched_spawn(task_plain);

  fw_sched_drain();

  /* The non-sleeping task finishes first even though it was queued last. */
  CHECK(strcmp(g_log, "xsss") == 0);
  CHECK(fw_sched_pending() == 0);
}

static void test_sleep_outside_a_task_returns(void) {
  /* Nothing to switch to, so this blocks the thread — briefly. It must
     return rather than park for ever. */
  fw_sched_sleep_ms(1);
  CHECK(fw_sched_in_task() == 0);
}

static void test_negative_and_zero_sleep_do_not_hang(void) {
  fw_sched_sleep_ms(0);
  fw_sched_sleep_ms(-5);
  CHECK(fw_sched_in_task() == 0);
}

/* ---- event parking: the API the socket layer uses ----------------------- */

static void task_parks_then_logs(void) {
  log_put("p");
  fw_sched_park_io();
  log_put("r");
}

static int g_waiter_calls;

/* Stands in for the vortex event loop: called when nothing is ready to run,
   and releases the parked tasks the way a socket becoming readable would. */
static void waking_waiter(long long max_wait_ns) {
  (void)max_wait_ns;
  g_waiter_calls++;
  fw_sched_wake_io();
}

static void test_park_io_suspends_until_woken(void) {
  log_reset();
  g_waiter_calls = 0;
  fw_sched_set_waiter(waking_waiter);

  fw_sched_spawn(task_parks_then_logs);
  fw_sched_spawn(task_plain);
  fw_sched_drain();

  /* The parked task steps aside for the ready one, then resumes once the
     waiter releases it. */
  CHECK(strcmp(g_log, "pxr") == 0);
  CHECK(g_waiter_calls >= 1);
  CHECK(fw_sched_io_waiting() == 0);

  fw_sched_set_waiter(NULL);
}

static void task_parks_only(void) {
  log_put("P");
  fw_sched_park_io();
  log_put("R");
}

static void test_io_waiting_counts_parked_tasks(void) {
  log_reset();
  g_waiter_calls = 0;

  /* A waiter that reports the count before releasing anything. */
  fw_sched_set_waiter(waking_waiter);

  fw_sched_spawn(task_parks_only);
  fw_sched_spawn(task_parks_only);
  fw_sched_spawn(task_parks_only);
  fw_sched_drain();

  /* All three parked, all three resumed. */
  CHECK(g_ran == 6);
  CHECK(fw_sched_io_waiting() == 0);

  fw_sched_set_waiter(NULL);
}

static void test_wake_io_with_nothing_parked_is_a_no_op(void) {
  CHECK(fw_sched_io_waiting() == 0);
  fw_sched_wake_io();
  fw_sched_wake_io();
  CHECK(fw_sched_io_waiting() == 0);
}

static void test_park_io_outside_a_task_is_a_no_op(void) {
  /* Parking the main stack would deadlock the process, so it must be
     refused rather than performed. */
  fw_sched_park_io();
  CHECK(fw_sched_io_waiting() == 0);
  CHECK(fw_sched_in_task() == 0);
}

/* A waiter that does nothing: the scheduler must not assume a waiter always
   makes progress, and must still finish when the parked task is released by
   someone else. */
static int g_idle_waiter_calls;

static void idle_waiter(long long max_wait_ns) {
  (void)max_wait_ns;
  g_idle_waiter_calls++;
  /* Release only after being asked a few times, imitating a loop that polls
     before an event finally arrives. */
  if (g_idle_waiter_calls >= 3) {
    fw_sched_wake_io();
  }
}

static void test_waiter_is_polled_until_the_event_arrives(void) {
  log_reset();
  g_idle_waiter_calls = 0;
  fw_sched_set_waiter(idle_waiter);

  fw_sched_spawn(task_parks_then_logs);
  fw_sched_drain();

  CHECK(strcmp(g_log, "pr") == 0);
  CHECK(g_idle_waiter_calls >= 3);

  fw_sched_set_waiter(NULL);
}

static void test_waiter_can_be_removed(void) {
  fw_sched_set_waiter(waking_waiter);
  fw_sched_set_waiter(NULL);

  /* With no waiter installed the scheduler falls back to its own timer, so an
     ordinary sleeping task still completes. */
  log_reset();
  fw_sched_spawn(task_sleeps_then_logs);
  fw_sched_drain();
  CHECK(strcmp(g_log, "s") == 0);
}

/* ---- GC integration ----------------------------------------------------- */

static void task_sleeps_while_gc_runs(void) {
  fw_sched_sleep_ms(10);
  log_put("g");
}

static void test_collection_during_a_suspended_task(void) {
  fw_gc_init();
  log_reset();

  fw_sched_spawn(task_sleeps_while_gc_runs);
  fw_sched_spawn(task_sleeps_while_gc_runs);

  /* Collect with tasks queued but not yet started. */
  fw_gc_collect();
  fw_sched_drain();

  CHECK(strcmp(g_log, "gg") == 0);
}



static void test_stress_mode_with_tasks(void) {
  fw_gc_init();
  log_reset();

  /* A C local is NOT a GC root: the collector scans globals and the shadow
     stack, and knows nothing about this function's frame. The block therefore
     has to be rooted while the rest of the arguments are built, because each
     of those allocations can collect — which is exactly what IRGen emits at a
     spawn site (an alloca registered with addGcRootAlloca).
     Skipping this step swept the block between its own two allocations. */
  ArgBlock *a = (ArgBlock *)fw_gc_alloc(sizeof(ArgBlock), &g_argblock_desc);
  g_block_slot = a;
  fw_gc_add_root(&g_block_slot);

  fw_gc_set_stress(1);          /* from here every allocation collects */

  a->value = 99;
  a->text = (char *)fw_gc_alloc(16, &fw_blob_desc);
  copy_bounded(a->text, 16, "stressed");

  g_seen_value = 0;
  g_seen_text[0] = '\0';

  fw_sched_spawn_args(task_with_args, a);

  /* Hand ownership over: from here only the scheduler's root keeps the block
     and its string alive, and the drain below allocates under stress. */
  fw_gc_remove_root(&g_block_slot);
  g_block_slot = NULL;

  fw_sched_spawn(task_plain);
  fw_sched_drain();

  CHECK(g_seen_value == 99);
  CHECK(strcmp(g_seen_text, "stressed") == 0);

  fw_gc_set_stress(0);
}

/* ---- entry point -------------------------------------------------------- */

int main(void) {
  fw_gc_init();

  /* Queueing */
  RUN_TEST(test_spawn_runs_in_fifo_order);
  RUN_TEST(test_spawn_null_is_ignored);
  RUN_TEST(test_drain_on_empty_queue_is_a_no_op);
  RUN_TEST(test_in_task_reports_the_right_context);

  /* Suspension */
  RUN_TEST(test_yield_sends_the_task_to_the_back);
  RUN_TEST(test_yield_outside_a_task_is_a_no_op);
  RUN_TEST(test_task_can_spawn_another_task);
  RUN_TEST(test_nested_drain_is_refused);
  RUN_TEST(test_many_tasks_all_run);

  /* Arguments */
  RUN_TEST(test_spawn_args_delivers_the_block);
  RUN_TEST(test_spawn_args_survives_collection_before_the_task_runs);
  RUN_TEST(test_spawn_args_null_fn_is_ignored);
  RUN_TEST(test_spawn_args_allows_a_null_block);

  /* Clocks */
  RUN_TEST(test_sleep_inside_a_task_overlaps);
  RUN_TEST(test_sleep_outside_a_task_returns);
  RUN_TEST(test_negative_and_zero_sleep_do_not_hang);

  /* Event parking */
  RUN_TEST(test_park_io_suspends_until_woken);
  RUN_TEST(test_io_waiting_counts_parked_tasks);
  RUN_TEST(test_wake_io_with_nothing_parked_is_a_no_op);
  RUN_TEST(test_park_io_outside_a_task_is_a_no_op);
  RUN_TEST(test_waiter_is_polled_until_the_event_arrives);
  RUN_TEST(test_waiter_can_be_removed);

  /* GC integration */
  RUN_TEST(test_collection_during_a_suspended_task);
  RUN_TEST(test_stress_mode_with_tasks);

  return TEST_SUMMARY();
}
