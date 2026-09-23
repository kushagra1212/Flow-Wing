/*
 * The C half of Flow-Wing's js module: between js-module.fg, which declares
 * these fw_js_* functions, and js-bridge.js, which implements the fwjs_* ones
 * in JavaScript. wasm32 only (scripts/wasm/build-runtime.sh); a page is the
 * only place there is JavaScript to talk to.
 *
 * What this layer adds to the JavaScript one:
 *
 *   strings     JavaScript hands back fresh UTF-8 (malloc); callers get a
 *               Flow-Wing string (GC) and the original is freed
 *   errors      a JavaScript exception ends the program as a runtime error,
 *               unless js::try is collecting it
 *   waiting     the scheduler's waiter, which sleeps in JavaScript (Asyncify)
 *               until an event arrives or a timer is due
 */

#include <emscripten.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "fw_gc.h"
#include "fw_sched.h"

char *fg_cs(const char *str1, const char *str2); /* built_in_module.c */
void fg_re(const char *message);                 /* built_in_module.c */

/* js-bridge.js */
extern int fwjs_global(void);
extern int fwjs_null(void);
extern int fwjs_from_str(const char *s);
extern int fwjs_from_num(double n);
extern int fwjs_from_bool(int b);
extern void fwjs_release(int h);
extern int fwjs_retain(int h);
extern char *fwjs_to_str(int h);
extern double fwjs_to_num(int h);
extern int fwjs_to_bool(int h);
extern char *fwjs_type(int h);
extern int fwjs_same(int a, int b);
extern int fwjs_get(int h, const char *name);
extern char *fwjs_get_str(int h, const char *name);
extern double fwjs_get_num(int h, const char *name);
extern int fwjs_get_bool(int h, const char *name);
extern int fwjs_at(int h, int index);
extern void fwjs_set(int h, const char *name, int v);
extern void fwjs_set_str(int h, const char *name, const char *s);
extern void fwjs_set_num(int h, const char *name, double n);
extern void fwjs_set_bool(int h, const char *name, int b);
extern int fwjs_call(int h, const char *method, int args);
extern int fwjs_invoke(int h, int args);
extern int fwjs_new(int h, int args);
extern int fwjs_eval(const char *code);
extern int fwjs_array(void);
extern void fwjs_push(int a, int v);
extern void fwjs_push_str(int a, const char *s);
extern void fwjs_push_num(int a, double n);
extern void fwjs_push_bool(int a, int b);
extern int fwjs_threw(void);
extern char *fwjs_take_error(void);
extern int fwjs_listen(int h, const char *type, int flags);
extern void fwjs_unlisten(int id);
extern int fwjs_timer(double ms, int repeat);
extern int fwjs_alive(int id);
extern int fwjs_live_handles(void);
extern int fwjs_next_event(void);
extern int fwjs_event(void);
extern int fwjs_await(int h);
extern int fwjs_await_state(int id);
extern int fwjs_await_take(int id);
extern int fwjs_pending(void);
extern int fwjs_take_pending(void);
extern void fwjs_sleep(double ms);

/* ---- strings and errors -------------------------------------------------- */

/* JavaScript's fresh UTF-8 as a Flow-Wing string. */
static char *take_text(char *raw) {
  char *text = fg_cs(raw != NULL ? raw : "", "");
  free(raw);
  return text;
}

/* Depth of js::try blocks. Inside one, an exception waits in js-bridge.js for
   fw_js_try_end to collect it; outside, it ends the program. */
static int g_try_depth = 0;

static void check(void) {
  if (g_try_depth > 0 || !fwjs_threw()) return;
  char *message = fwjs_take_error();
  char *text = fg_cs("Runtime Error: JavaScript threw an exception.\n  \xe2\x96\xb6 ",
                     message);
  free(message);
  fg_re(text);
}

void fw_js_try_begin(void) { g_try_depth++; }

/* The message of an exception thrown since fw_js_try_begin, or "". */
char *fw_js_try_end(void) {
  if (g_try_depth > 0) g_try_depth--;
  if (!fwjs_threw()) return fg_cs("", "");
  return take_text(fwjs_take_error());
}

/* A JavaScript number as a Flow-Wing int: truncated, and 0 for NaN or a
   value out of range, rather than undefined behaviour. */
static int to_int(double n) {
  if (!(n == n) || n >= 2147483648.0 || n < -2147483648.0) return 0;
  return (int)n;
}

/* ---- boxes ---------------------------------------------------------------- */

/* A js::Value keeps its handle in a box: a small GC object held in the
   value's `_handle` field (an int64 the compiler traces as a pointer, see
   IRGenerator's native-handle offsets). When the value is collected, so is the
   box, and its finalizer releases the handle, so the JavaScript object can be
   collected too. The same pattern as the vec and map modules' handles. */
typedef struct {
  int handle;
} JsBox;

static void finalize_box(void *raw) {
  JsBox *box = (JsBox *)raw;
  fwjs_release(box->handle);
  box->handle = 0;
}

long long fw_js_box(int handle) {
  JsBox *box = (JsBox *)fw_gc_alloc(sizeof(JsBox), &fw_blob_desc);
  if (box == NULL) {
    fwjs_release(handle);
    fg_re("Runtime Error: out of memory in the js module.");
    return 0;
  }
  box->handle = handle;
  fw_gc_register_finalizer(box, finalize_box);
  return (long long)(uintptr_t)box;
}

int fw_js_unbox(long long box) {
  return box == 0 ? 0 : ((JsBox *)(uintptr_t)box)->handle;
}

/* Release now rather than at collection. The box then holds undefined, so its
   finalizer releases nothing a second time. */
void fw_js_box_release(long long box) {
  if (box == 0) return;
  JsBox *b = (JsBox *)(uintptr_t)box;
  fwjs_release(b->handle);
  b->handle = 0;
}

/* ---- values --------------------------------------------------------------- */

int fw_js_global(void) { return fwjs_global(); }
int fw_js_null(void) { return fwjs_null(); }
int fw_js_from_str(const char *s) { return fwjs_from_str(s != NULL ? s : ""); }
int fw_js_from_num(double n) { return fwjs_from_num(n); }
int fw_js_from_bool(bool b) { return fwjs_from_bool(b ? 1 : 0); }
void fw_js_release(int h) { fwjs_release(h); }
int fw_js_retain(int h) { return fwjs_retain(h); }

char *fw_js_to_str(int h) {
  char *raw = fwjs_to_str(h);
  check();
  return take_text(raw);
}

double fw_js_to_num(int h) {
  double n = fwjs_to_num(h);
  check();
  return n;
}

int fw_js_to_int(int h) { return to_int(fw_js_to_num(h)); }
bool fw_js_to_bool(int h) { return fwjs_to_bool(h) != 0; }
char *fw_js_type(int h) { return take_text(fwjs_type(h)); }
bool fw_js_same(int a, int b) { return fwjs_same(a, b) != 0; }

/* ---- properties ----------------------------------------------------------- */

int fw_js_get(int h, const char *name) {
  int v = fwjs_get(h, name);
  check();
  return v;
}

char *fw_js_get_str(int h, const char *name) {
  char *raw = fwjs_get_str(h, name);
  check();
  return take_text(raw);
}

double fw_js_get_num(int h, const char *name) {
  double n = fwjs_get_num(h, name);
  check();
  return n;
}

int fw_js_get_int(int h, const char *name) { return to_int(fw_js_get_num(h, name)); }

bool fw_js_get_bool(int h, const char *name) {
  int b = fwjs_get_bool(h, name);
  check();
  return b != 0;
}

int fw_js_at(int h, int index) {
  int v = fwjs_at(h, index);
  check();
  return v;
}

void fw_js_set(int h, const char *name, int v) {
  fwjs_set(h, name, v);
  check();
}

void fw_js_set_str(int h, const char *name, const char *s) {
  fwjs_set_str(h, name, s != NULL ? s : "");
  check();
}

void fw_js_set_num(int h, const char *name, double n) {
  fwjs_set_num(h, name, n);
  check();
}

void fw_js_set_bool(int h, const char *name, bool b) {
  fwjs_set_bool(h, name, b ? 1 : 0);
  check();
}

/* ---- calls ---------------------------------------------------------------- */

int fw_js_call(int h, const char *method, int args) {
  int v = fwjs_call(h, method, args);
  check();
  return v;
}

int fw_js_invoke(int h, int args) {
  int v = fwjs_invoke(h, args);
  check();
  return v;
}

int fw_js_new(int h, int args) {
  int v = fwjs_new(h, args);
  check();
  return v;
}

int fw_js_eval(const char *code) {
  int v = fwjs_eval(code != NULL ? code : "");
  check();
  return v;
}

int fw_js_array(void) { return fwjs_array(); }
void fw_js_push(int a, int v) { fwjs_push(a, v); }
void fw_js_push_str(int a, const char *s) { fwjs_push_str(a, s != NULL ? s : ""); }
void fw_js_push_num(int a, double n) { fwjs_push_num(a, n); }
void fw_js_push_bool(int a, bool b) { fwjs_push_bool(a, b ? 1 : 0); }

/* ---- events and promises -------------------------------------------------- */

int fw_js_listen(int h, const char *type, int flags) {
  int id = fwjs_listen(h, type, flags);
  check();
  return id;
}

void fw_js_unlisten(int id) { fwjs_unlisten(id); }
int fw_js_timer(int ms, bool repeat) { return fwjs_timer(ms, repeat ? 1 : 0); }
bool fw_js_alive(int id) { return fwjs_alive(id) != 0; }
int fw_js_live_handles(void) { return fwjs_live_handles(); }
int fw_js_next_event(void) { return fwjs_next_event(); }
int fw_js_event(void) { return fwjs_event(); }
int fw_js_await(int h) { return fwjs_await(h); }
int fw_js_await_state(int id) { return fwjs_await_state(id); }

int fw_js_await_take(int id) {
  int v = fwjs_await_take(id);
  check();
  return v;
}

/* ---- waiting -------------------------------------------------------------- */

/* When fw_js_wait last gave the page a turn while tasks were still ready. */
static double g_last_turn_ms = 0;

/* The scheduler's waiter (fw_sched_set_waiter): called when tasks are parked
   waiting for events. Instead of blocking the thread, which in a browser
   freezes the page, it sleeps in JavaScript until an event or promise result
   arrives (js-bridge.js notify) or the next timer is due. */
static void fw_js_wait(long long max_wait_ns) {
  if (!fwjs_pending()) {
    if (max_wait_ns == 0) {
      /* A poll while other tasks are still ready to run. Give the page a turn
         about once a frame, so input and painting keep up with a program
         that never waits; not on every task switch, which would crawl. */
      double now = emscripten_get_now();
      if (now - g_last_turn_ms >= 16) {
        g_last_turn_ms = now;
        fwjs_sleep(0);
      }
    } else {
      fwjs_sleep(max_wait_ns < 0 ? -1 : (double)max_wait_ns / 1e6);
    }
  }
  /* Tasks parked on events recheck what they wait for. */
  if (fwjs_take_pending()) fw_sched_wake_io();
}

/* Called once by the js module before it first waits for anything. */
void fw_js_start(void) { fw_sched_set_waiter(fw_js_wait); }

bool fw_js_in_task(void) { return fw_sched_in_task() != 0; }
