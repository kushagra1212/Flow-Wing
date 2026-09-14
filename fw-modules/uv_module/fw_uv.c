/*
 * FlowWing Runtime - shared libuv event loop (see fw_uv.h).
 *
 * This translation unit also carries libuv itself: the archive built from it
 * has libuv merged in by the POST_BUILD step in CMakeLists.txt.
 *
 * Why one archive owns libuv, instead of each module merging its own copy:
 *
 *   The JIT build force-loads every module archive (cmake/targets.cmake, the
 *   `if(NOT BUILD_AOT)` block). It has to: the JIT resolves runtime functions
 *   by NAME at run time through JITRuntimeSymbols.def, and nothing in the
 *   compiler's own C++ references them, so an ordinary archive link would drop
 *   them as unused.
 *
 *   force_load pulls in EVERY member, used or not. Merge libuv into two
 *   force-loaded archives and every uv_* symbol is defined twice — measured at
 *   444 duplicate-symbol errors.
 */

#include "fw_uv.h"
#include "fw_sched.h"

static uv_loop_t  g_loop;
static uv_async_t g_wake;
static uv_timer_t g_deadline;
static int        g_ready = 0;

/* Runs on the FlowWing thread, inside uv_run, so touching the scheduler here
   is safe. Releasing every event-parked task is correct even if only one of
   them can make progress: the others re-check their condition and park again. */
static void on_wake(uv_async_t *handle) {
  (void)handle;
  fw_sched_wake_io();
}

static void on_deadline(uv_timer_t *handle) {
  (void)handle; /* exists only to cap how long uv_run waits */
}

/* Installed as the scheduler's idle waiter. A negative max_wait_ns means no
   timer is pending, so only an event can make progress and we may wait
   indefinitely. */
static void fw_uv_wait(long long max_wait_ns) {
  if (!g_ready) return;

  if (max_wait_ns >= 0) {
    uint64_t ms = (uint64_t)(max_wait_ns / 1000000LL);
    if (max_wait_ns > 0 && ms == 0) ms = 1; /* never round a real wait to zero */
    uv_timer_start(&g_deadline, on_deadline, ms, 0);
  }

  uv_run(&g_loop, UV_RUN_ONCE);

  if (max_wait_ns >= 0) uv_timer_stop(&g_deadline);
}

uv_loop_t *fw_uv_loop(void) {
  if (g_ready) return &g_loop;

  if (uv_loop_init(&g_loop) != 0) return NULL;
  uv_async_init(&g_loop, &g_wake, on_wake);
  uv_timer_init(&g_loop, &g_deadline);

  /* The deadline timer exists only to bound uv_run; it must not by itself keep
     the loop alive. The async handle stays referenced on purpose, so uv_run
     blocks waiting for a wake instead of returning at once. */
  uv_unref((uv_handle_t *)&g_deadline);

  g_ready = 1;
  fw_sched_set_waiter(fw_uv_wait);
  return &g_loop;
}

int fw_uv_ready(void) { return g_ready; }

void fw_uv_wake(void) {
  if (g_ready) uv_async_send(&g_wake);
}

const char *fw_uv_version(void) { return uv_version_string(); }
