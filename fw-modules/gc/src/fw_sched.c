/*
 * FlowWing Runtime - Cooperative coroutine scheduler (see fw_sched.h).
 *
 * Stack switching uses ucontext on POSIX, Fibers on Windows, and Emscripten
 * fibers on wasm. All are platform-native, so there is no third-party
 * dependency and no hand-written assembly to keep per-architecture.
 * switch_to_scheduler and switch_to_task are the only places that differ.
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

#ifndef _WIN32
#  include <signal.h>
#  include <sys/mman.h>
#  include <unistd.h>
#  ifndef MAP_ANONYMOUS
#    define MAP_ANONYMOUS MAP_ANON
#  endif
#endif

#if defined(_WIN32)
#  include <windows.h>
#elif defined(__EMSCRIPTEN__)
/* wasm cannot switch stacks by itself. Emscripten's fibers do it with
   Asyncify, which unwinds the wasm call stack into a buffer and rewinds it on
   resume, so a program that spawns is linked with -sASYNCIFY (see
   WasmLinkPass). */
#  include <emscripten/emscripten.h>
#  include <emscripten/fiber.h>
#else
#  include <ucontext.h>
/* ucontext is deprecated on Darwin but still the only dependency-free way to
   swap stacks there. The API is stable; silence the warning rather than take
   on a vendored coroutine library. */
#  if defined(__APPLE__) && defined(__clang__)
#    pragma clang diagnostic ignored "-Wdeprecated-declarations"
#  endif
#endif

/* Default task stack. Big enough for ordinary FlowWing frames plus a C call or
   two through the FFI. Stacks are recycled, so this is a peak-concurrency
   cost, not a per-spawn cost.

   Override at start-up with FW_TASK_STACK_KB. A task that recurses deeply
   needs a bigger number; `main` gets 8 MB, so code that works at top level can
   still overflow inside a task.

   That 8 MB is what Linux and macOS hand out by default. Windows hands out
   1 MB, so FlowWing asks the linker for 64 MB there instead — see
   LinkerCommandBuilder::addSystemLibraries and cmake/targets.cmake for why the
   two numbers differ. The reachable DEPTH is then comparable on all three, and
   a recursion that works on one platform works on the others. */
/* A deadline no clock can reach: the task waits for an event, not a time. */
#define FW_WAKE_NEVER (-1LL)

#define FW_TASK_STACK_DEFAULT (256 * 1024)
#define FW_STACK_ALIGN        16 /* the wasm ABI's stack pointer alignment */
#define FW_TASK_STACK_MIN_KB  16L
#define FW_TASK_STACK_MAX_KB  65536L

typedef enum {
  FW_TASK_NEW,       /* queued, never started, owns no stack yet */
  FW_TASK_SUSPENDED, /* started and parked mid-body, owns a stack */
  FW_TASK_DONE       /* body returned */
} FWTaskState;

typedef struct FWTask {
  FWTaskFn     fn;      /* used when args_fn is NULL */
  FWTaskArgsFn args_fn; /* takes the argument block below */
  void        *args;    /* GC object; rooted while this task is alive */
  FWTaskState  state;

  /* GC chain head while this task is NOT the one running. */
  FWFrame *shadow_top;

  /* 0            = runnable now.
     FW_WAKE_NEVER = parked on an event; only fw_sched_wake_io releases it.
     otherwise     = the monotonic-ns instant before which it must not run. */
  long long wake_at_ns;

  char *stack; /* NULL until first resume */

#if defined(_WIN32)
  LPVOID fiber;
#elif defined(__EMSCRIPTEN__)
  emscripten_fiber_t fiber;
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

#if defined(_WIN32)
static LPVOID g_sched_fiber = NULL;
#elif defined(__EMSCRIPTEN__)
/* The drain loop's fiber, which is main's. Asyncify keeps main's suspended
   wasm locals in g_sched_asyncify while a task runs. */
static emscripten_fiber_t g_sched_fiber;
static char *g_sched_asyncify = NULL;
/* Set by main's first switch to a task; see end_program. */
static int g_main_suspended = 0;
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

/* ---- stack size --------------------------------------------------------- */

static size_t g_stack_size = 0; /* 0 = not resolved yet */

static size_t page_size(void) {
#ifdef _WIN32
  return 4096;
#else
  long p = sysconf(_SC_PAGESIZE);
  return (p > 0) ? (size_t)p : 4096;
#endif
}

/* Resolved once, on the first spawn. Reading it later cannot change the size
   of stacks already handed out, so the pool never holds mixed sizes. */
static size_t stack_size(void) {
  if (g_stack_size != 0) return g_stack_size;

  size_t want = FW_TASK_STACK_DEFAULT;

  const char *env = getenv("FW_TASK_STACK_KB");
  if (env != NULL && env[0] != '\0') {
    char *end = NULL;
    long  kb = strtol(env, &end, 10);
    if (end != NULL && *end == '\0' && kb >= FW_TASK_STACK_MIN_KB &&
        kb <= FW_TASK_STACK_MAX_KB) {
      want = (size_t)kb * 1024;
    }
    /* A value outside the range is ignored rather than honoured: a stack of
       0 KB would fault on the first call, and a 4 GB one would fail to map. */
  }

  {
    size_t page = page_size();
    want = ((want + page - 1) / page) * page; /* whole pages */
  }

  g_stack_size = want;
  return g_stack_size;
}

/* ---- guard pages -------------------------------------------------------- */

#if defined(__EMSCRIPTEN__)

/* wasm memory has no page protection, so there is no guard page to fault on.
   A program that spawns is linked with -sSTACK_OVERFLOW_CHECK=2 instead: every
   function entry checks the stack pointer against the running fiber's limits,
   which emscripten_fiber_swap updates, and aborts with "stack overflow". */
static void install_stack_overflow_handler_once(void) {}

#elif !defined(_WIN32)
/* Every live stack's guard page, so the SIGSEGV handler can tell a task stack
   overflow apart from an ordinary bad pointer. Entries are never removed:
   stacks are pooled and reused for the whole run. */
typedef struct {
  char *lo;
  char *hi;
} FWGuard;

static FWGuard *g_guards = NULL;
static size_t   g_guards_len = 0, g_guards_cap = 0;

static void guard_record(char *lo, char *hi) {
  if (g_guards_len == g_guards_cap) {
    size_t   new_cap = g_guards_cap ? g_guards_cap * 2 : 16;
    FWGuard *grown = (FWGuard *)realloc(g_guards, new_cap * sizeof(FWGuard));
    if (grown == NULL) return; /* lose the record, keep the stack */
    g_guards = grown;
    g_guards_cap = new_cap;
  }
  g_guards[g_guards_len].lo = lo;
  g_guards[g_guards_len].hi = hi;
  g_guards_len++;
}

static int addr_in_guard(const void *addr) {
  const char *p = (const char *)addr;
  for (size_t i = 0; i < g_guards_len; i++) {
    if (p >= g_guards[i].lo && p < g_guards[i].hi) return 1;
  }
  return 0;
}

/* Async-signal-safe only: write() and _exit(). No printf, no malloc. */
static void segv_handler(int sig, siginfo_t *info, void *uctx) {
  (void)uctx;

  if (info != NULL && addr_in_guard(info->si_addr)) {
    /* Same shape as fg_panic's output: red, "Runtime Error: <Title>." on the
       first line, then indented detail lines marked with U+25B6. This handler
       cannot call fg_panic itself — printf and malloc are not safe in a signal
       handler — so the text is pre-built and written with write(2). */
    static const char msg[] =
        "\033[91mRuntime Error: Task Stack Overflow.\n"
        "  ▶ A spawned task used more stack than it owns.\n"
        "  ▶ A task stack is much smaller than main's.\n"
        "  ▶ Raise it with FW_TASK_STACK_KB (e.g. FW_TASK_STACK_KB=4096),"
        " or reduce the recursion depth.\033[0m\n";
    ssize_t ignored = write(2, msg, sizeof(msg) - 1);
    (void)ignored;
    _exit(1);
  }

  /* Not one of our guard pages: let the default handler produce the usual
     crash, so a real bug is not disguised as a stack overflow. */
  signal(sig, SIG_DFL);
  raise(sig);
}

/* The handler runs on its own small stack. Without this it would try to run on
   the stack that just overflowed, and fault again immediately. */
static void install_stack_overflow_handler_once(void) {
  static int installed = 0;
  if (installed) return;
  installed = 1;

  size_t alt_size = (size_t)SIGSTKSZ < 32768u ? 32768u : (size_t)SIGSTKSZ;
  void  *alt = malloc(alt_size);
  if (alt == NULL) return;

  stack_t ss;
  ss.ss_sp = alt;
  ss.ss_size = alt_size;
  ss.ss_flags = 0;
  if (sigaltstack(&ss, NULL) != 0) { free(alt); return; }

  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
  sa.sa_sigaction = segv_handler;
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGBUS, &sa, NULL); /* Darwin reports guard hits as SIGBUS */
}

#else /* _WIN32 */

/* Windows needs no guard page of ours to record. CreateFiberEx reserves the
   stack and the kernel places its own guard page at the low end, so the
   overflow arrives as a structured exception rather than a signal:
   EXCEPTION_STACK_OVERFLOW (0xC00000FD).

   Without a handler the process dies on that exception before anything is
   flushed, which is exactly the "exit code and no message" case the POSIX
   guard page was added to remove. */
static LONG CALLBACK stack_overflow_handler(EXCEPTION_POINTERS *info) {
  if (info == NULL || info->ExceptionRecord == NULL ||
      info->ExceptionRecord->ExceptionCode != EXCEPTION_STACK_OVERFLOW) {
    return EXCEPTION_CONTINUE_SEARCH;
  }

  /* Only a task fiber earns the named message. An overflow with no task on the
     CPU is ordinary too-deep recursion on main's stack, and it must keep its
     usual crash — the same rule the POSIX handler applies when the faulting
     address is not one of our guard pages. */
  if (g_current == NULL) return EXCEPTION_CONTINUE_SEARCH;

  /* Barely any stack is left at this point, so this does what the POSIX
     handler does: one pre-built message, one write, no formatting and no
     allocation. WriteFile is a thin syscall wrapper; printf is not.

     The U+25B6 markers are written as explicit UTF-8 bytes because MSVC
     re-encodes non-ASCII characters in narrow literals to the local code page
     unless /utf-8 is passed, which would corrupt them. */
  static const char msg[] =
      "\033[91mRuntime Error: Task Stack Overflow.\n"
      "  \xe2\x96\xb6 A spawned task used more stack than it owns.\n"
      "  \xe2\x96\xb6 A task stack is much smaller than main's.\n"
      "  \xe2\x96\xb6 Raise it with FW_TASK_STACK_KB (e.g. FW_TASK_STACK_KB=4096),"
      " or reduce the recursion depth.\033[0m\n";

  HANDLE err = GetStdHandle(STD_ERROR_HANDLE);
  if (err != NULL && err != INVALID_HANDLE_VALUE) {
    DWORD written = 0;
    WriteFile(err, msg, (DWORD)(sizeof(msg) - 1), &written, NULL);
  }

  /* TerminateProcess rather than exit(): the CRT's exit path runs atexit
     handlers and stream flushes on the stack that just ran out. */
  TerminateProcess(GetCurrentProcess(), 1);
  return EXCEPTION_CONTINUE_SEARCH; /* not reached */
}

/* First = 1 puts this ahead of any handler registered later, and a vectored
   handler runs before every frame-based (SEH) handler, so nothing downstream
   can swallow the overflow first. */
static void install_stack_overflow_handler_once(void) {
  static int installed = 0;
  if (installed) return;
  installed = 1;
  AddVectoredExceptionHandler(1, stack_overflow_handler);
}

#endif /* __EMSCRIPTEN__ / POSIX / _WIN32 */

/* ---- stack pool --------------------------------------------------------- */

/* Completed tasks hand their stack back instead of releasing it. A program
   that spawns a million short tasks reuses one stack a million times, because
   only one runs at a time.

   Each stack is its own mapping with an unreadable page below it. Stacks grow
   DOWNWARD, so the guard sits at the low address and catches the overflow on
   the first write past the end. */
static char **g_stack_pool = NULL;
static size_t g_stack_pool_len = 0, g_stack_pool_cap = 0;

static char *stack_acquire(void) {
  if (g_stack_pool_len > 0) return g_stack_pool[--g_stack_pool_len];

#if defined(_WIN32)
  /* Never called on Windows: CreateFiber owns the stack. Returning NULL keeps
     the signature without allocating memory nothing would use. */
  return NULL;
#elif defined(__EMSCRIPTEN__)
  /* One block: the C stack, then the same size again for Asyncify, which
     saves a suspended task's wasm locals there. No guard page, see
     install_stack_overflow_handler_once.

     16-byte aligned, as the wasm ABI requires of a stack pointer; malloc only
     promises 8. Compiled code relies on it: musl's __stdio_write steps to its
     second iovec with `(sp + 16) | 8`, which on a stack 8 off alignment
     stays on the first. A task that wrote to stderr then looped forever
     writing 0 bytes, whenever the heap happened to hand out such a block. */
  return (char *)aligned_alloc(FW_STACK_ALIGN, 2 * stack_size());
#else
  size_t page = page_size();
  size_t usable = stack_size();

  char *base = (char *)mmap(NULL, usable + page, PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (base == MAP_FAILED) return NULL;

  /* Make the lowest page unreadable and unwritable. */
  if (mprotect(base, page, PROT_NONE) != 0) {
    munmap(base, usable + page);
    return NULL;
  }

  guard_record(base, base + page);
  return base + page; /* the usable stack starts above the guard */
#endif
}

static void stack_release(char *s) {
  if (s == NULL) return;
  if (g_stack_pool_len == g_stack_pool_cap) {
    size_t new_cap = g_stack_pool_cap ? g_stack_pool_cap * 2 : 8;
    char **grown =
        (char **)realloc(g_stack_pool, new_cap * sizeof(char *));
    if (grown == NULL) return; /* keep the mapping rather than leak the guard */
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

    /* Argument blocks belong to tasks that have not started yet, so they are
       reachable from nowhere else. Roots every state, not just SUSPENDED. */
    if (t->args != NULL) fw_gc_push_root_object(t->args);
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

/* ---- stack switching ---------------------------------------------------- */

/* The scheduler's only two moves: from a task back to the drain loop, and from
   the drain loop into a task. Each platform's mechanism lives here and nowhere
   else. */
static void switch_to_scheduler(FWTask *t) {
#if defined(_WIN32)
  (void)t;
  SwitchToFiber(g_sched_fiber);
#elif defined(__EMSCRIPTEN__)
  emscripten_fiber_swap(&t->fiber, &g_sched_fiber);
#else
  swapcontext(&t->ctx, &g_sched_ctx);
#endif
}

static void switch_to_task(FWTask *t) {
#if defined(_WIN32)
  SwitchToFiber(t->fiber);
#elif defined(__EMSCRIPTEN__)
  g_main_suspended = 1;
  emscripten_fiber_swap(&g_sched_fiber, &t->fiber);
#else
  swapcontext(&g_sched_ctx, &t->ctx);
#endif
}

#if defined(__EMSCRIPTEN__)
/* ---- ending the program (wasm) ----------------------------------------------

   Once main has switched to a task, Emscripten cannot end the program the
   usual way. The switch unwound main's stack out to JavaScript, which it
   counts as async work in flight, so main's final return skips exit(): no
   onExit, and a page never hears the program end. exit() in a task prints
   "keepRuntimeAlive() is set" and ends with status 0. Forcing the exit from
   main or from a resumed task does end it, but the exit travels up through
   Emscripten's resume path, which swallows it, and the program is then ended
   a second time.

   A fiber that has never run has no resume path above it. So the program is
   ended from a fresh one: its exit goes straight out to where main was
   started, and the program ends once, with the right status. */

/* Allocated when needed, so a program that never spawns carries none of it,
   and 16-byte aligned like every fiber stack (see stack_acquire). */
#define FW_EXIT_FIBER_STACK    (64 * 1024) /* runs atexit handlers */
#define FW_EXIT_FIBER_ASYNCIFY (4 * 1024)  /* never suspended */

static emscripten_fiber_t g_exit_fiber;
static int g_exit_status = 0;

static void exit_fiber_entry(void *arg) {
  (void)arg;
  emscripten_force_exit(g_exit_status);
}

static void end_program(emscripten_fiber_t *from, int status) {
  char *memory = (char *)aligned_alloc(
      FW_STACK_ALIGN, FW_EXIT_FIBER_STACK + FW_EXIT_FIBER_ASYNCIFY);
  if (memory == NULL) {
    emscripten_force_exit(status); /* ends it, if less tidily */
  }
  g_exit_status = status;
  emscripten_fiber_init(&g_exit_fiber, exit_fiber_entry, NULL,
                        memory, FW_EXIT_FIBER_STACK,
                        memory + FW_EXIT_FIBER_STACK, FW_EXIT_FIBER_ASYNCIFY);
  emscripten_fiber_swap(from, &g_exit_fiber);
}

/* A program that spawns is linked with -Wl,--wrap=exit (see WasmLinkPass),
   so its exit() calls, a runtime error's for one, land here. */
void __wrap_exit(int status) {
  if (g_current != NULL) {
    end_program(&g_current->fiber, status);
  } else if (g_main_suspended) {
    end_program(&g_sched_fiber, status);
  }
  /* main has never switched to a task: the usual exit works. */
  emscripten_force_exit(status);
}
#endif

/* ---- task entry --------------------------------------------------------- */

static void run_task_body(FWTask *t) {
  if (t->args_fn != NULL) t->args_fn(t->args);
  else                    t->fn();
  t->state = FW_TASK_DONE;
}

#if defined(_WIN32)
static VOID CALLBACK task_entry(PVOID param) {
  FWTask *t = (FWTask *)param;
  run_task_body(t);
  switch_to_scheduler(t);
}
#elif defined(__EMSCRIPTEN__)
/* Like the Windows fiber, it switches away for good at the end rather than
   returning from the fiber's entry function. */
static void task_entry(void *param) {
  FWTask *t = (FWTask *)param;
  run_task_body(t);
  switch_to_scheduler(t);
}
#else
static void task_entry(void) {
  run_task_body(g_current);
  /* uc_link returns us to the scheduler. */
}
#endif

/* ---- public API --------------------------------------------------------- */

void fw_sched_spawn(FWTaskFn fn) {
  if (fn == NULL) return;

  FWTask *t = (FWTask *)calloc(1, sizeof(FWTask));
  if (t == NULL) return;

  t->fn = fn;
  t->args_fn = NULL;
  t->args = NULL;
  t->state = FW_TASK_NEW;
  t->shadow_top = NULL;
  t->stack = NULL;

  register_task(t);
  register_scanner_once();
  queue_push(t);
}

void fw_sched_spawn_args(FWTaskArgsFn fn, void *args) {
  if (fn == NULL) return;

  FWTask *t = (FWTask *)calloc(1, sizeof(FWTask));
  if (t == NULL) return;

  t->fn = NULL;
  t->args_fn = fn;
  t->args = args;
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

  switch_to_scheduler(t);
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

    if (t->wake_at_ns == FW_WAKE_NEVER) continue; /* waiting on an event */

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

/* Earliest deadline among queued tasks, or 0 if none is waiting on a clock.
   Event-parked tasks have no deadline and are ignored here. */
static long long earliest_deadline(void) {
  long long best = 0;
  for (size_t i = g_head; i < g_tail; i++) {
    FWTask *t = g_ready[i];
    if (t == NULL || t->wake_at_ns == 0) continue;
    if (t->wake_at_ns == FW_WAKE_NEVER) continue;
    if (best == 0 || t->wake_at_ns < best) best = t->wake_at_ns;
  }
  return best;
}

/* ---- waiting on events -------------------------------------------------- */

static FWWaitFn g_waiter = NULL;

void fw_sched_set_waiter(FWWaitFn fn) { g_waiter = fn; }

unsigned long fw_sched_io_waiting(void) {
  unsigned long n = 0;
  for (size_t i = g_head; i < g_tail; i++) {
    FWTask *t = g_ready[i];
    if (t != NULL && t->wake_at_ns == FW_WAKE_NEVER) n++;
  }
  return n;
}

void fw_sched_park_io(void) {
  FWTask *t = g_current;
  if (t == NULL) return; /* outside a task there is nothing to park */

  t->wake_at_ns = FW_WAKE_NEVER;
  t->shadow_top = fw_gc_shadow_top;
  t->state = FW_TASK_SUSPENDED;
  queue_push(t);

  switch_to_scheduler(t);
}

void fw_sched_wake_io(void) {
  for (size_t i = g_head; i < g_tail; i++) {
    FWTask *t = g_ready[i];
    if (t != NULL && t->wake_at_ns == FW_WAKE_NEVER) t->wake_at_ns = 0;
  }
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

  switch_to_scheduler(t);
}

/* Non-zero while a drain loop is running. See fw_sched_drain. */
static int g_draining = 0;

void fw_sched_drain(void) {
  /* Re-entrancy guard.
   *
   * The loop below saves the scheduler's resume point in ONE global
   * (g_sched_ctx) and zeroes the queue indices when it finishes. Calling it
   * again from inside a task destroys both: the nested call overwrites
   * g_sched_ctx with a point inside the running task, so when that task later
   * finishes and switches back, it returns into a frame that has already been
   * left. Measured result was a SIGSEGV, after the nested call appeared to
   * succeed — the outer drain simply never returned.
   *
   * Nesting also has no useful meaning. The outer loop already runs everything
   * in the queue, including work the current task spawns, so returning at once
   * loses nothing: the tasks still run, just one level up.
   */
  if (g_draining) {
    return;
  }
  g_draining = 1;

#if defined(_WIN32)
  int converted = 0;
  if (g_sched_fiber == NULL) {
    g_sched_fiber = ConvertThreadToFiber(NULL);
    converted = (g_sched_fiber != NULL);
  }
#elif defined(__EMSCRIPTEN__)
  /* Tasks switch back to the fiber this loop runs on, so it must be one. Only
     when there is work: every main drains on the way out. */
  if (g_head < g_tail) {
    if (g_sched_asyncify == NULL) g_sched_asyncify = (char *)malloc(stack_size());
    if (g_sched_asyncify == NULL) { /* OOM: skip the tasks rather than crash */
      g_draining = 0;
      return;
    }
    emscripten_fiber_init_from_current_context(&g_sched_fiber, g_sched_asyncify,
                                               stack_size());
  }
#endif

  /* Last time the event loop was polled while tasks were still runnable. */
  long long last_poll_ns = 0;

  while (g_head < g_tail) {
    /* Turn the event loop even when the ready queue is NOT empty.
     *
     * I/O completions only arrive while the loop is running, and the loop only
     * runs in the "nothing is ready" branch below. A task that spins on
     * fw_sched_yield() — a game loop calling yield once per frame is the
     * obvious case — keeps the ready queue non-empty for ever, so that branch
     * is never reached and a parked read never finishes. Measured before this
     * fix: a loop yielding two million times left five file reads at zero
     * completed, for the life of the program.
     *
     * Timers do not have this problem because pop_ready() promotes tasks whose
     * deadline has passed, which is why sleeping worked where yielding hung.
     *
     * Polling is throttled to once per millisecond so a busy ready queue does
     * not pay for a uv_run on every single task switch.
     */
    if (g_waiter != NULL && fw_sched_io_waiting() > 0) {
      long long now = now_ns();
      if (now - last_poll_ns >= 1000000LL) { /* 1 ms */
        last_poll_ns = now;
        g_waiter(0); /* zero deadline: poll, never block */
      }
    }

    FWTask *t = pop_ready();

    if (t == NULL) {
      /* Nothing can run right now. Work out what could change that. */
      long long due = earliest_deadline();
      unsigned long io = fw_sched_io_waiting();

      if (due == 0 && io == 0) break; /* no timers, no events: finished */

      if (g_waiter != NULL) {
        /* An event layer is installed, so a socket can wake us as well as a
           clock. A pending timer caps the wait; otherwise wait indefinitely,
           because only an event can make progress. */
        g_waiter(due != 0 ? (due - now_ns()) : FW_WAKE_NEVER);
      } else if (due != 0) {
        block_ns(due - now_ns());
      } else {
        /* Tasks are parked on events but nothing can deliver one. Releasing
           them is wrong (they would see no data); hanging is worse. Give up
           and let the program end rather than deadlock in silence. */
        break;
      }
      continue;
    }

    /* Whatever is running now (main, or an outer task) owns this chain. */
    FWFrame *saved_chain = fw_gc_shadow_top;
    FWTask  *saved_current = g_current;

    g_current = t;

    if (t->state == FW_TASK_NEW) {
      /* A task is about to get a stack of its own, so this is the point where
         overflowing one becomes possible. Both platforms install here, which
         keeps the "who reports the overflow" question in one place. */
      install_stack_overflow_handler_once();

#ifndef _WIN32
      /* POSIX only. CreateFiberEx allocates and guards its own stack, so
         asking for one here would waste stack_size() bytes per task on
         Windows. */
      t->stack = stack_acquire();
      if (t->stack == NULL) { /* OOM: skip the task rather than crash */
        g_current = saved_current;
        unregister_task(t);
        free(t);
        continue;
      }
#endif
      /* A fresh task starts with an empty chain of its own. */
      fw_gc_shadow_top = NULL;

#ifdef _WIN32
      /* CreateFiber's one size argument is the COMMIT size; the RESERVE stays
         at the executable's default, which is 1 MB. A 256 KB task would then
         quietly receive a megabyte and FW_TASK_STACK_KB would bound nothing —
         and the overflow would land at 1 MB regardless of the setting.
         CreateFiberEx sets the reserve, and the reserve is what the kernel's
         guard page sits below. Commit 0 keeps the default initial commit, so
         a small task still pays for only the pages it touches. */
      t->fiber = CreateFiberEx(0, stack_size(), 0, task_entry, t);
      if (t->fiber == NULL) { /* OOM: skip the task rather than crash */
        g_current = saved_current;
        unregister_task(t);
        free(t);
        continue;
      }
#elif defined(__EMSCRIPTEN__)
      /* The C stack, then Asyncify's half of the same block. */
      emscripten_fiber_init(&t->fiber, task_entry, t, t->stack, stack_size(),
                            t->stack + stack_size(), stack_size());
#else
      getcontext(&t->ctx);
      t->ctx.uc_stack.ss_sp = t->stack;
      t->ctx.uc_stack.ss_size = stack_size();
      t->ctx.uc_link = &g_sched_ctx;
      makecontext(&t->ctx, task_entry, 0);
#endif
    } else {
      fw_gc_shadow_top = t->shadow_top;
    }

    switch_to_task(t);

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

#if defined(_WIN32)
  if (converted) {
    ConvertFiberToThread();
    g_sched_fiber = NULL;
  }
#endif

  g_draining = 0;

#if defined(__EMSCRIPTEN__)
  /* Every main drains on its way out, and one that switched to a task cannot
     return (see end_program). It returns 0 when nothing called exit(). */
  if (g_main_suspended) {
    end_program(&g_sched_fiber, 0);
  }
#endif
}

unsigned long fw_sched_pending(void) {
  return (unsigned long)(g_tail - g_head);
}
