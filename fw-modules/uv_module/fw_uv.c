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
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#  include <signal.h>
#endif

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

/* ---- running a command without blocking (fw_sched_exec) ------------------
 *
 * The same command popen would run, started with uv_spawn instead: the
 * calling task parks while it runs and the other tasks keep going. A process
 * and a pipe on the loop, not a threadpool job: the pool has four threads by
 * default, and a command that takes seconds would hold one the whole time,
 * starving the file reads that share it.
 *
 * Everything below lives in one FWExec on the calling task's stack, which
 * stays valid while the task is parked. The task is woken only once the
 * process has exited AND both handles are closed, so libuv is done with the
 * memory before the task's frame goes away. */

typedef struct {
  uv_process_t process;
  uv_pipe_t    out;
  char        *data;
  size_t       len;
  size_t       cap;
  int          status;
  int          process_closed;
  int          out_closed;
} FWExec;

static void exec_wake_when_done(FWExec *e) {
  if (e->process_closed && e->out_closed) fw_sched_wake_io();
}

static void exec_on_process_closed(uv_handle_t *handle) {
  FWExec *e = (FWExec *)handle->data;
  e->process_closed = 1;
  exec_wake_when_done(e);
}

static void exec_on_out_closed(uv_handle_t *handle) {
  FWExec *e = (FWExec *)handle->data;
  e->out_closed = 1;
  exec_wake_when_done(e);
}

static void exec_on_exit(uv_process_t *process, int64_t exit_status,
                         int term_signal) {
  FWExec *e = (FWExec *)process->data;
  /* The status a shell reports in $?, as fg_decode_exec_status gives popen. */
  e->status = term_signal != 0 ? 128 + term_signal : (int)exit_status;
  uv_close((uv_handle_t *)process, exec_on_process_closed);
}

static void exec_alloc(uv_handle_t *handle, size_t suggested, uv_buf_t *buf) {
  FWExec *e = (FWExec *)handle->data;
  if (e->cap - e->len < suggested + 1) {
    size_t cap = e->cap * 2;
    if (cap < e->len + suggested + 1) cap = e->len + suggested + 1;
    char *grown = (char *)realloc(e->data, cap);
    if (grown == NULL) {
      *buf = uv_buf_init(NULL, 0); /* libuv reports UV_ENOBUFS to on_read */
      return;
    }
    e->data = grown;
    e->cap = cap;
  }
  /* One byte kept back for the terminating NUL. */
  *buf = uv_buf_init(e->data + e->len, (unsigned int)(e->cap - e->len - 1));
}

static void exec_on_read(uv_stream_t *stream, ssize_t nread,
                         const uv_buf_t *buf) {
  (void)buf;
  FWExec *e = (FWExec *)stream->data;
  if (nread > 0) {
    e->len += (size_t)nread;
  } else if (nread < 0) { /* UV_EOF, or an error: either way, the end */
    uv_close((uv_handle_t *)stream, exec_on_out_closed);
  }
}

static int fw_uv_exec(const char *command, char **output, int *status) {
  FWExec e;
  memset(&e, 0, sizeof e);
  e.cap = 1024;
  e.data = (char *)malloc(e.cap);
  if (e.data == NULL) return -1;

  if (uv_pipe_init(&g_loop, &e.out, 0) != 0) {
    free(e.data);
    return -1;
  }
  e.out.data = &e;
  e.process.data = &e;

  uv_stdio_container_t stdio[3];
  stdio[0].flags = UV_INHERIT_FD;
  stdio[0].data.fd = 0;
  stdio[1].flags = (uv_stdio_flags)(UV_CREATE_PIPE | UV_WRITABLE_PIPE);
  stdio[1].data.stream = (uv_stream_t *)&e.out;
  stdio[2].flags = UV_INHERIT_FD;
  stdio[2].data.fd = 2;

  uv_process_options_t options;
  memset(&options, 0, sizeof options);
#ifdef _WIN32
  /* What _popen runs: %COMSPEC% /c <command>, the command line passed as is. */
  const char *shell = getenv("COMSPEC");
  char *args[] = {(char *)(shell != NULL ? shell : "cmd.exe"), (char *)"/c",
                  (char *)command, NULL};
  options.flags = UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS;
#else
  char *args[] = {(char *)"/bin/sh", (char *)"-c", (char *)command, NULL};
#endif
  options.file = args[0];
  options.args = args;
  options.stdio = stdio;
  options.stdio_count = 3;
  options.exit_cb = exec_on_exit;

  if (uv_spawn(&g_loop, &e.process, &options) != 0) {
    /* Both handles still have to be closed before this frame can go. */
    uv_close((uv_handle_t *)&e.process, exec_on_process_closed);
    uv_close((uv_handle_t *)&e.out, exec_on_out_closed);
    while (!(e.process_closed && e.out_closed)) fw_sched_park_io();
    free(e.data);
    return -1; /* the caller runs it with popen instead */
  }

  uv_read_start((uv_stream_t *)&e.out, exec_alloc, exec_on_read);
  while (!(e.process_closed && e.out_closed)) fw_sched_park_io();

  e.data[e.len] = '\0';
  *output = e.data;
  *status = e.status;
  return 0;
}

uv_loop_t *fw_uv_loop(void) {
  if (g_ready) return &g_loop;

#ifndef _WIN32
  /* Ignore SIGPIPE before any socket exists.
   *
   * A peer that closes early is ordinary HTTP — a browser cancels a request, a
   * client reads what it wanted and hangs up. Writing to that socket afterwards
   * raises SIGPIPE, whose default action is to KILL THE PROCESS. A server must
   * never die because a client left.
   *
   * libuv does not cover this for us on every platform:
   *
   *   macOS/BSD  uv__socket sets SO_NOSIGPIPE, but the call sits behind
   *              `#if defined(SO_NOSIGPIPE)`.
   *   Linux      SO_NOSIGPIPE does not exist, so that block compiles away, and
   *              libuv uses writev() with no MSG_NOSIGNAL anywhere in its
   *              source. A write to a closed socket signals.
   *
   * That difference is exactly what made ServerTests/vortex_router.fg pass on
   * macOS and die on Linux in the same run, with signal=13 and no output at all.
   *
   * cpp-httplib did this for us at httplib.h:10712 — but that path is dead
   * since the server moved to libuv, so the protection went with it.
   *
   * Nothing is lost by ignoring it: uv_write reports the failure through its
   * callback, and on_read already tears the connection down when nread < 0.
   *
   * Installed here rather than in the HTTP server because the client writes to
   * sockets too, and this is the one place both of them must pass through.
   */
  signal(SIGPIPE, SIG_IGN);
#endif

  if (uv_loop_init(&g_loop) != 0) return NULL;
  uv_async_init(&g_loop, &g_wake, on_wake);
  uv_timer_init(&g_loop, &g_deadline);

  /* The deadline timer exists only to bound uv_run; it must not by itself keep
     the loop alive. The async handle stays referenced on purpose, so uv_run
     blocks waiting for a wake instead of returning at once. */
  uv_unref((uv_handle_t *)&g_deadline);

  g_ready = 1;
  fw_sched_set_waiter(fw_uv_wait);
  fw_sched_set_exec(fw_uv_exec);
  return &g_loop;
}

int fw_uv_ready(void) { return g_ready; }

void fw_uv_wake(void) {
  if (g_ready) uv_async_send(&g_wake);
}

const char *fw_uv_version(void) { return uv_version_string(); }
