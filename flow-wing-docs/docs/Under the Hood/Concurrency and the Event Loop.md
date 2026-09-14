---
sidebar_position: 2
title: Concurrency and the Event Loop
---

# Concurrency and the event loop

`spawn` queues a function as a task. Each task gets its own machine stack, so it
can stop half-way through and continue later from the same line. This page shows
the machinery.

:::tip Interactive version
Step through the stack swap register by register, watch the argument block being
built, follow the libuv park-and-wake handshake, and see the `null` bug at the
byte level.

**[▶ Open the interactive concurrency walkthrough](pathname:///internals/concurrency.html)**
:::

<iframe
  src="/internals/concurrency.html"
  title="Interactive walkthrough of Flow-Wing concurrency, tasks and libuv"
  style={{width:'100%', height:'760px', border:'1px solid #30363d', borderRadius:'8px'}}
/>

## The three layers

| Layer | File | Job |
|---|---|---|
| **Scheduler** | `fw-modules/gc/src/fw_sched.c` | queue tasks, swap stacks, wait on deadlines |
| **Event loop** | `fw-modules/uv_module/fw_uv.c` | one shared libuv loop; wait on sockets instead of clocks |
| **HTTP** | `fw-modules/vortex_module/uv_http_*.cpp` | server and client, both on that loop |

## The stack swap

This is the heart of it. `swapcontext` on POSIX, Fibers on Windows:

```
   main stack (8 MB)          task A (256 KB)        task B (256 KB)
   ┌───────────────┐          ┌─────────────┐        ┌─────────────┐
   │ fg_main()     │          │ worker("A") │        │ worker("B") │
   │ drain()       │◄────┐    │ step 1  ⏸   │        │ step 1      │
   └───────────────┘     │    └─────────────┘        └─────────────┘
                         │       frozen               running
          swapcontext ───┘       mid-call
```

The saved registers include the stack pointer, so a switch moves execution to a
different block of memory. Task A's frames are untouched, which is why it
resumes on the line **after** its `yield` rather than from the top.

## Waiting on something that is not a clock

On its own the scheduler can only wait on a deadline — enough for `sys::sleep`
and nothing else. A task waiting on a socket would have to block the thread and
stop every other task. The event layer plugs in here:

```
no task ready
   ↓
fw_sched_drain  →  g_waiter(max_wait_ns)        installed by fw_uv_loop()
                        ↓
                   uv_run(loop, UV_RUN_ONCE)    sleeps in the kernel
                        ↓  socket readable
                   on_read → parse → fw_sched_wake_io()
                        ↓
                   task moves back to the ready queue
```

`fw_uv_wake()` is the only call in the runtime another thread may make. It wraps
`uv_async_send`, the one function libuv documents as thread-safe.

## Task stacks

Each running task owns a stack — **256 KB** by default, much smaller than the
main stack. Stacks are taken when a task first runs and released when it
finishes, so queuing a million tasks costs a million small records, not a
million stacks.

```bash
FW_TASK_STACK_KB=4096 ./myprogram
```

The bottom page of every task stack is mapped `PROT_NONE`, so running off the
end raises a named error instead of a silent crash:

```
Runtime Error: Task Stack Overflow.
  ▶ A spawned task used more stack than it owns.
  ▶ Raise it with FW_TASK_STACK_KB (e.g. FW_TASK_STACK_KB=4096), or reduce the recursion depth.
```

## Why no locks are needed

Tasks are cooperative and single-threaded. Exactly one runs at a time, and a
switch happens **only** where you suspend — a `sys::sleep`, a `sys::yield`, or a
socket read. Two tasks can never be inside the same function at the same
instant, so there is no data race to protect against.

That property is also what lets the garbage collector stay lock-free. See
*[Garbage Collector](./Garbage%20Collector.md)*.

## See also

- *Advanced → Concurrency with spawn* — the language-level guide, with the
  copy-versus-alias rules for arguments
- *Creating a Server* — handling requests concurrently
- *Built-in Libraries → System (sys)* — `sleep`, `yield`, and the monotonic clock
