/*
 * FlowWing Runtime - task-switch stubs for wasm32 builds.
 *
 * WebAssembly cannot switch stacks, so emscripten's libc declares
 * getcontext, makecontext and swapcontext without defining them. fw_sched.c
 * uses them to switch between `spawn`ed tasks, and every program links
 * fw_sched.c because `main` drains the scheduler on exit.
 *
 * A program that never spawns never switches, so it links and runs normally.
 * One that does stops here with a message, instead of an obscure trap.
 *
 * Defining them here, rather than linking with -sERROR_ON_UNDEFINED_SYMBOLS=0,
 * keeps every OTHER missing symbol a link error that names it.
 *
 * Compiled only by `make build-wasm-runtime`. Delete it when the scheduler
 * gets a wasm backend.
 */
#if defined(__EMSCRIPTEN__)

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

static void fw_no_task_switching(const char *function) {
  fprintf(stderr,
          "Flow-Wing: `spawn` is not supported on wasm yet (%s was called).\n",
          function);
  abort();
}

int getcontext(struct __ucontext *context) {
  (void)context;
  fw_no_task_switching("getcontext");
  return -1;
}

void makecontext(struct __ucontext *context, void (*entry)(), int argc, ...) {
  (void)context;
  (void)entry;
  (void)argc;
  fw_no_task_switching("makecontext");
}

int swapcontext(struct __ucontext *from, const struct __ucontext *to) {
  (void)from;
  (void)to;
  fw_no_task_switching("swapcontext");
  return -1;
}

#endif /* __EMSCRIPTEN__ */
