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
 * Unit tests for the shared event loop (fw-modules/uv_module/fw_uv.c).
 *
 * fw_uv is four functions, and the interesting one is fw_uv_wake(): it is the
 * ONLY call in the whole runtime that another thread may make. The HTTP client
 * and the async file worker both rely on it to hand results back to the
 * FlowWing thread while that thread is asleep inside uv_run.
 *
 * The server and file fixtures exercise this indirectly. Here it is driven
 * directly, including the cross-thread case, because "a socket woke us" is not
 * something a .fg file can assert about.
 *
 * Threads come from libuv (uv_thread_create / uv_sleep) rather than pthreads,
 * so this file builds on Windows as well.
 */

#include "fw_uv.h"
#include "fw_sched.h"
#include "test_harness.h"
#include <string.h>

/* ---- creation ----------------------------------------------------------- */

static void test_not_ready_before_first_use(void) {
  /* The loop is created on demand, so nothing exists until it is asked for.
     A program that never opens a socket never pays for a loop. */
  CHECK(fw_uv_ready() == 0);
}

static void test_wake_before_the_loop_exists_is_a_no_op(void) {
  /* A worker thread can in principle call this before the loop is up. It must
     not touch the uninitialised async handle. */
  fw_uv_wake();
  fw_uv_wake();
  CHECK(fw_uv_ready() == 0);
}

static void test_loop_is_created_once_and_shared(void) {
  uv_loop_t *first = fw_uv_loop();
  CHECK(first != NULL);
  CHECK(fw_uv_ready() == 1);

  /* Every module asks for "the" loop and must get the same one — two loops
     would mean a socket registered on one and a timer on the other, with only
     one of them ever being run. */
  uv_loop_t *second = fw_uv_loop();
  CHECK(second == first);

  uv_loop_t *third = fw_uv_loop();
  CHECK(third == first);
}

static void test_version_is_reported(void) {
  const char *v = fw_uv_version();
  CHECK(v != NULL);
  CHECK(strlen(v) > 0);
  /* It is libuv's own string, not a copy that could drift. */
  CHECK(strcmp(v, uv_version_string()) == 0);
}

/* ---- the cross-thread wake ---------------------------------------------- */

static int g_task_resumed;
static int g_watchdog_fired;

static void parking_task(void) {
  /* No deadline: only an event can release this. The scheduler therefore
     hands control to the installed waiter, which blocks inside uv_run. */
  fw_sched_park_io();
  g_task_resumed = 1;
}

static void waker_thread(void *arg) {
  (void)arg;
  uv_sleep(60);
  /* THE cross-thread call. uv_async_send is the one libuv function documented
     as safe from any thread, and fw_uv_wake is a thin wrapper over it. */
  fw_uv_wake();
}

/* Without this, a broken wake would hang the test run instead of failing it —
   uv_run waits indefinitely when a task is parked with no deadline. The
   watchdog releases the loop after a delay far longer than the real wake needs,
   and sets a flag so the test still reports a failure. */
static void watchdog_thread(void *arg) {
  (void)arg;
  uv_sleep(5000);
  if (!g_task_resumed) {
    g_watchdog_fired = 1;
    fw_uv_wake();
  }
}

static void test_wake_from_another_thread_releases_a_parked_task(void) {
  CHECK(fw_uv_loop() != NULL);

  g_task_resumed = 0;
  g_watchdog_fired = 0;

  uv_thread_t waker, watchdog;
  CHECK(uv_thread_create(&waker, waker_thread, NULL) == 0);
  CHECK(uv_thread_create(&watchdog, watchdog_thread, NULL) == 0);

  fw_sched_spawn(parking_task);

  /* Nothing is ready, so the drain loop calls the waiter that fw_uv_loop
     installed, which sleeps inside uv_run until the async handle fires. */
  fw_sched_drain();

  uv_thread_join(&waker);
  uv_thread_join(&watchdog);

  CHECK(g_task_resumed == 1);
  CHECK(g_watchdog_fired == 0);   /* the real wake arrived, not the backstop */
  CHECK(fw_sched_io_waiting() == 0);
}

/* ---- the loop stays usable ---------------------------------------------- */

static int g_timer_fired;

static void on_test_timer(uv_timer_t *handle) {
  g_timer_fired++;
  uv_timer_stop(handle);
  uv_close((uv_handle_t *)handle, NULL);
}

static void test_loop_still_runs_timers(void) {
  uv_loop_t *loop = fw_uv_loop();
  CHECK(loop != NULL);

  /* The scheduler borrows this loop through its waiter, so a module must still
     be able to register its own handles on it — that is how the HTTP server
     puts its listening socket somewhere the scheduler will poll. */
  g_timer_fired = 0;
  uv_timer_t t;
  CHECK(uv_timer_init(loop, &t) == 0);
  CHECK(uv_timer_start(&t, on_test_timer, 10, 0) == 0);

  /* UV_RUN_ONCE can return after the async handle rather than the timer, so
     keep running until the timer has actually fired. */
  for (int i = 0; i < 50 && g_timer_fired == 0; i++) {
    uv_run(loop, UV_RUN_NOWAIT);
    uv_sleep(5);
  }

  CHECK(g_timer_fired == 1);
}

static void test_repeated_wakes_are_coalesced_safely(void) {
  /* uv_async_send may collapse several sends into one callback. Nothing here
     depends on the count, only on it never being unsafe to call. */
  for (int i = 0; i < 100; i++) {
    fw_uv_wake();
  }
  uv_run(fw_uv_loop(), UV_RUN_NOWAIT);
  CHECK(fw_uv_ready() == 1);
}

/* ---- entry point -------------------------------------------------------- */

int main(void) {
  /* Order matters for the first two: they assert on the state BEFORE the loop
     has ever been created, which is only true once. */
  RUN_TEST(test_not_ready_before_first_use);
  RUN_TEST(test_wake_before_the_loop_exists_is_a_no_op);

  RUN_TEST(test_loop_is_created_once_and_shared);
  RUN_TEST(test_version_is_reported);

  RUN_TEST(test_wake_from_another_thread_releases_a_parked_task);
  RUN_TEST(test_loop_still_runs_timers);
  RUN_TEST(test_repeated_wakes_are_coalesced_safely);

  return TEST_SUMMARY();
}
