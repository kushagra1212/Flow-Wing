/*
 * FlowWing Runtime - Cooperative coroutine scheduler (see fw_sched.h).
 *
 * Stack switching uses ucontext on POSIX and Fibers on Windows. Both are
 * platform-native, so there is no third-party dependency and no hand-written
 * assembly to keep per-architecture.
 */

/* Must precede every system header. Darwin hides makecontext/swapcontext
   behind _XOPEN_SOURCE, but that macro also switches off the Apple-specific
   namespace that CLOCK_UPTIME_RAW lives in — hence both. */
#if !defined(_WIN32)
#  ifndef _XOPEN_SOURCE
#    define _XOPEN_SOURCE 700
#  endif
#  if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#    define _DARWIN_C_SOURCE 1
#  endif
#endif

#include "fw_sched.h"
#include "fw_gc.h"

#include <errno.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <ucontext.h>
/* ucontext is deprecated on Darwin but still the only dependency-free way to
   swap stacks there. The API is stable; silence the warning rather than take
   on a vendored coroutine library. */
#  if defined(__APPLE__) && defined(__clang__)
#    pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  endif
#endif

/* Big enough for ordinary FlowWing frames plus a C call or two through the
   FFI. Stacks are recycled, so this is a peak-concurrency cost, not a
   per-spawn cost. */
#define FW_TASK_STACK_SIZE (256 * 1024)

typedef enum {
  FW_TASK_NEW,       /* queued, never started, owns no stack yet */
  FW_TASK_SUSPENDED, /* started and parked mid-body, owns a stack */
  FW_TASK_DONE       /* body returned */
} FWTaskState;

typedef struct FWTask {
  FWTaskFn    fn;
  FWTaskState state;

  /* GC chain head while this task is NOT the one running. */
  FWFrame *shadow_top;

  /* 0 = runnable now. Otherwise the monotonic-ns instant before which this
     task must not be resumed. */
  long long wake_at_ns;

  char *stack; /* NULL until first resume */

#ifdef _WIN32
  LPVOID fiber;
#else
  ucontext_t ctx;
#endif

  /* Registry used by the GC root scanner. Doubly linked so a finishing task
     unlinks in O(1): spawn prepends but the drain completes tasks in FIFO
     order, so a singly-linked list would walk the entire registry on every
     completion — quadratic, and it hangs outright at a few hundred thousand
     tasks. */
  struct FWTask *prev_all;
  struct FWTask *next_all;
} FWTask;

/* ---- scheduler state ---------------------------------------------------- */

static FWTask *g_all_tasks = NULL; /* every live task, for GC marking */
static FWTask *g_current = NULL;   /* task on the CPU, NULL inside scheduler */
static int     g_scanner_registered = 0;

#ifdef _WIN32
static LPVOID g_sched_fiber = NULL;
#else
static ucontext_t g_sched_ctx;
#endif

/* ---- ready queue (FIFO of FWTask*) -------------------------------------- */

static FWTask **g_ready = NULL;
static size_t   g_head = 0, g_tail = 0, g_cap = 0;

/* Reclaim the already-run prefix, growing only when compaction is not enough.
   Without the compaction step a long drain would grow the buffer without bound
   even though the live task count stays small. */
static int reserve_one(void) {
  if (g_tail < g_cap) return 1;

  if (g_head > 0) {
    size_t live = g_tail - g_head;
    for (size_t i = 0; i < live; i++) g_ready[i] = g_ready[g_head + i];
    g_head = 0;
    g_tail = live;
    if (g_tail < g_cap) return 1;
  }

  {
    size_t   new_cap = (g_cap == 0) ? 8 : g_cap * 2;
    FWTask **grown = (FWTask **)realloc(g_ready, new_cap * sizeof(FWTask *));
    if (grown == NULL) return 0;
    g_ready = grown;
    g_cap = new_cap;
  }
  return 1;
}

static void queue_push(FWTask *t) {
  if (!reserve_one()) return; /* OOM: drop rather than abort the program */
  g_ready[g_tail++] = t;
}

/* ---- monotonic clock ---------------------------------------------------- */

/* Local copy rather than a call into built_in_module: flowwing_gc sits BELOW
   that library in the link order, so depending on it would invert. */
static long long now_ns(void) {
#ifdef _WIN32
  static LARGE_INTEGER freq;
  static int freq_ready = 0;
  LARGE_INTEGER now;
  if (!freq_ready) { QueryPerformanceFrequency(&freq); freq_ready = 1; }
  QueryPerformanceCounter(&now);
  return (long long)((now.QuadPart / freq.QuadPart) * 1000000000LL +
                     ((now.QuadPart % freq.QuadPart) * 1000000000LL) /
                         freq.QuadPart);
#else
  /* CLOCK_MONOTONIC is only microsecond-granular on Darwin, which is fine:
     every deadline here is expressed in whole milliseconds. The ns-precise
     clock (CLOCK_UPTIME_RAW) lives in built_in_module, where benchmarking
     actually needs it, and reaching for it here would mean fighting the
     _XOPEN_SOURCE namespace that makecontext requires. */
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (long long)ts.tv_sec * 1000000000LL + (long long)ts.tv_nsec;
#endif
}

static void block_ns(long long ns) {
  if (ns <= 0) return;
#ifdef _WIN32
  Sleep((DWORD)(ns / 1000000LL));
#else
  struct timespec req;
  req.tv_sec = (time_t)(ns / 1000000000LL);
  req.tv_nsec = (long)(ns % 1000000000LL);
  while (nanosleep(&req, &req) == -1 && errno == EINTR) { }
#endif
}

/* ---- stack recycling ---------------------------------------------------- */

/* Completed tasks hand their stack back instead of freeing it. A program that
   spawns a million short tasks then reuses one stack a million times, because
   only one runs at a time. */
static char **g_stack_pool = NULL;
static size_t g_stack_pool_len = 0, g_stack_pool_cap = 0;

static char *stack_acquire(void) {
  if (g_stack_pool_len > 0) return g_stack_pool[--g_stack_pool_len];
  return (char *)malloc(FW_TASK_STACK_SIZE);
}

static void stack_release(char *s) {
  if (s == NULL) return;
  if (g_stack_pool_len == g_stack_pool_cap) {
    size_t new_cap = g_stack_pool_cap ? g_stack_pool_cap * 2 : 8;
    char **grown =
        (char **)realloc(g_stack_pool, new_cap * sizeof(char *));
    if (grown == NULL) { free(s); return; }
    g_stack_pool = grown;
    g_stack_pool_cap = new_cap;
  }
  g_stack_pool[g_stack_pool_len++] = s;
}

/* ---- GC integration ----------------------------------------------------- */

/* Hand the GC every chain it cannot see. The running task's chain is already
   `fw_gc_shadow_top`; everything else is parked in task->shadow_top. */
static void sched_scan_roots(void) {
  for (FWTask *t = g_all_tasks; t != NULL; t = t->next_all) {
    if (t != g_current && t->state == FW_TASK_SUSPENDED)
      fw_gc_mark_shadow_chain(t->shadow_top);
  }
}

static void register_scanner_once(void) {
  if (!g_scanner_registered) {
    fw_gc_set_aux_root_scanner(sched_scan_roots);
    g_scanner_registered = 1;
  }
}

static void register_task(FWTask *t) {
  t->prev_all = NULL;
  t->next_all = g_all_tasks;
  if (g_all_tasks != NULL) g_all_tasks->prev_all = t;
  g_all_tasks = t;
}

static void unregister_task(FWTask *t) {
  if (t->prev_all != NULL) t->prev_all->next_all = t->next_all;
  else g_all_tasks = t->next_all;

  if (t->next_all != NULL) t->next_all->prev_all = t->prev_all;

  t->prev_all = NULL;
  t->next_all = NULL;
}

/* ---- task entry --------------------------------------------------------- */

#ifdef _WIN32
static VOID CALLBACK task_entry(PVOID param) {
  FWTask *t = (FWTask *)param;
  t->fn();
  t->state = FW_TASK_DONE;
  SwitchToFiber(g_sched_fiber);
}
#else
static void task_entry(void) {
  FWTask *t = g_current;
  t->fn();
  t->state = FW_TASK_DONE;
  /* uc_link returns us to the scheduler. */
}
#endif

/* ---- public API --------------------------------------------------------- */

void fw_sched_spawn(FWTaskFn fn) {
  if (fn == NULL) return;

  FWTask *t = (FWTask *)calloc(1, sizeof(FWTask));
  if (t == NULL) return;

  t->fn = fn;
  t->state = FW_TASK_NEW;
  t->shadow_top = NULL;
  t->stack = NULL;

  register_task(t);
  register_scanner_once();
  queue_push(t);
}

int fw_sched_in_task(void) { return g_current != NULL; }

void fw_sched_yield(void) {
  FWTask *t = g_current;
  if (t == NULL) return; /* not inside a task: nothing to suspend */

  /* Park our chain so the GC can still find our locals while we are off-CPU. */
  t->shadow_top = fw_gc_shadow_top;
  t->state = FW_TASK_SUSPENDED;
  queue_push(t);

#ifdef _WIN32
  SwitchToFiber(g_sched_fiber);
#else
  swapcontext(&t->ctx, &g_sched_ctx);
#endif
  /* Resumed. The drain loop restored fw_gc_shadow_top for us. */
}

/* Take the first task whose deadline has passed, preserving FIFO order among
   runnable tasks. Returns NULL when every queued task is still sleeping.

   Removal fills the vacated slot from the head, so when the first entry is
   already runnable (the common case) this is a plain FIFO pop. Nothing is
   pushed here, so the queue cannot compact mid-scan and invalidate g_head. */
static FWTask *pop_ready(void) {
  long long now = 0;
  int       have_now = 0;

  for (size_t i = g_head; i < g_tail; i++) {
    FWTask *t = g_ready[i];
    if (t == NULL) continue;

    if (t->wake_at_ns != 0) {
      if (!have_now) { now = now_ns(); have_now = 1; }
      if (t->wake_at_ns > now) continue; /* still parked */
    }

    g_ready[i] = g_ready[g_head];
    g_ready[g_head] = NULL;
    g_head++;
    t->wake_at_ns = 0;
    return t;
  }
  return NULL;
}

/* Earliest deadline among queued tasks, or 0 if none are sleeping. */
static long long earliest_deadline(void) {
  long long best = 0;
  for (size_t i = g_head; i < g_tail; i++) {
    FWTask *t = g_ready[i];
    if (t == NULL || t->wake_at_ns == 0) continue;
    if (best == 0 || t->wake_at_ns < best) best = t->wake_at_ns;
  }
  return best;
}

void fw_sched_sleep_ms(long long ms) {
  if (ms <= 0) return;

  FWTask *t = g_current;
  if (t == NULL) {
    /* No task to switch away from — nothing would run during a yield. */
    block_ns(ms * 1000000LL);
    return;
  }

  t->wake_at_ns = now_ns() + ms * 1000000LL;
  t->shadow_top = fw_gc_shadow_top;
  t->state = FW_TASK_SUSPENDED;
  queue_push(t);

#ifdef _WIN32
  SwitchToFiber(g_sched_fiber);
#else
  swapcontext(&t->ctx, &g_sched_ctx);
#endif
}

void fw_sched_drain(void) {
#ifdef _WIN32
  int converted = 0;
  if (g_sched_fiber == NULL) {
    g_sched_fiber = ConvertThreadToFiber(NULL);
    converted = (g_sched_fiber != NULL);
  }
#endif

  while (g_head < g_tail) {
    FWTask *t = pop_ready();

    if (t == NULL) {
      /* Everything left is waiting on a clock. Idle until the soonest one is
         due instead of spinning. */
      long long due = earliest_deadline();
      if (due == 0) break; /* nothing runnable and nothing timed: done */
      block_ns(due - now_ns());
      continue;
    }

    /* Whatever is running now (main, or an outer task) owns this chain. */
    FWFrame *saved_chain = fw_gc_shadow_top;
    FWTask  *saved_current = g_current;

    g_current = t;

    if (t->state == FW_TASK_NEW) {
      t->stack = stack_acquire();
      if (t->stack == NULL) { /* OOM: skip the task rather than crash */
        g_current = saved_current;
        unregister_task(t);
        free(t);
        continue;
      }
      /* A fresh task starts with an empty chain of its own. */
      fw_gc_shadow_top = NULL;

#ifdef _WIN32
      t->fiber = CreateFiber(FW_TASK_STACK_SIZE, task_entry, t);
#else
      getcontext(&t->ctx);
      t->ctx.uc_stack.ss_sp = t->stack;
      t->ctx.uc_stack.ss_size = FW_TASK_STACK_SIZE;
      t->ctx.uc_link = &g_sched_ctx;
      makecontext(&t->ctx, task_entry, 0);
#endif
    } else {
      fw_gc_shadow_top = t->shadow_top;
    }

#ifdef _WIN32
    SwitchToFiber(t->fiber);
#else
    swapcontext(&g_sched_ctx, &t->ctx);
#endif

    g_current = saved_current;
    fw_gc_shadow_top = saved_chain;

    if (t->state == FW_TASK_DONE) {
#ifdef _WIN32
      if (t->fiber != NULL) DeleteFiber(t->fiber);
#endif
      stack_release(t->stack);
      unregister_task(t);
      free(t);
    }
  }

  g_head = 0;
  g_tail = 0;

#ifdef _WIN32
  if (converted) {
    ConvertFiberToThread();
    g_sched_fiber = NULL;
  }
#endif
}

unsigned long fw_sched_pending(void) {
  return (unsigned long)(g_tail - g_head);
}
