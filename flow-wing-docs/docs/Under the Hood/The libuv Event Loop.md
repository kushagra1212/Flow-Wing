---
sidebar_position: 3
title: The libuv Event Loop
---

# The libuv event loop

The scheduler on its own can only wait on a clock. This page is about the layer
that lets it wait on a **socket** instead — how a timer bounds the wait, how an
arriving request wakes a parked task, and what happens when work has to leave
the thread entirely.

:::tip Interactive version
Step through the idle handshake state by state, follow a request from the kernel
to your handler, and watch the threadpool handoff.

**[▶ Open the interactive event-loop walkthrough](pathname:///internals/event-loop.html)**
:::

<iframe
  src="/internals/event-loop.html"
  title="Interactive walkthrough of the Flow-Wing libuv event loop"
  style={{width:'100%', height:'760px', border:'1px solid #30363d', borderRadius:'8px'}}
/>

## The seam

The scheduler does not know libuv exists. It declares a hole and calls a
function pointer:

```c
typedef void (*FWWaitFn)(long long max_wait_ns);
void fw_sched_set_waiter(FWWaitFn fn);   /* NULL = fall back to nanosleep */
```

The first call to `fw_uv_loop()` fills that hole in. From then on, whenever no
task can run, the thread idles inside `uv_run` instead of `nanosleep` — so a
socket and a timer can both end the wait.

If nothing ever installs a waiter, programs still work. They just cannot wait on
anything but a clock.

## Three handles, four functions

| Handle | Type | Job |
|---|---|---|
| `g_loop` | `uv_loop_t` | the one loop; every socket, timer and job in the process |
| `g_wake` | `uv_async_t` | the doorbell another thread may ring — stays **referenced** |
| `g_deadline` | `uv_timer_t` | caps how long one `uv_run` may block — **unreferenced** |

```c
uv_loop_t *fw_uv_loop(void);     /* create-once, and install the waiter */
int        fw_uv_ready(void);
void       fw_uv_wake(void);     /* the one cross-thread call */
const char*fw_uv_version(void);
```

## How long to wait

| `max_wait_ns` | Meaning | `uv_run` |
|---|---|---|
| `> 0` | a timer is due in N ns | blocks, but no longer than N |
| `0` | poll | returns at once |
| `-1` | no timer pending | blocks until an event arrives |

`sys::sleep` does **not** create a libuv timer — it writes a wake-up instant onto
the task and lets `pop_ready()` promote it later. Sleeping is pure scheduler
bookkeeping. `g_deadline` exists only so `uv_run` cannot overshoot the nearest of
those instants; its callback body is empty.

## The one rule about threads

`uv_async_send` is the only libuv function documented as thread-safe.
`fw_uv_wake()` is a thin wrapper over it, and it is the **only** call in the
whole runtime that another thread may make. Every other `uv_*`, scheduler and GC
function is FlowWing-thread only.

A worker thread must touch nothing the GC owns. The collector is
single-threaded, so calling `fw_gc_alloc` from a threadpool thread corrupts the
heap. Off-thread code works with plain `std::string`; the GC object is built
afterwards, back on the FlowWing thread.

## Park, wake, re-check

`fw_sched_wake_io()` releases **every** event-parked task, not the one task the
event belongs to. That is correct because every caller re-checks its own
condition and parks again:

```c
while (!job.done)                            fw_sched_park_io();  /* file read  */
while (s->ready.empty())                     fw_sched_park_io();  /* accept     */
while (ctx->chunks.empty() && !ctx->is_done) fw_sched_park_io();  /* read chunk */
```

A spurious wake costs one queue scan and one stack switch. A wait-set per socket
would cost allocation, bookkeeping, and a class of bugs where a task stays parked
because the single event it registered for never arrives.

## See also

- *[Concurrency and the Event Loop](./Concurrency%20and%20the%20Event%20Loop.md)* — tasks, stacks and the scheduler itself
- *[Garbage Collector](./Garbage%20Collector.md)* — why single-threaded matters
- *Creating a Server → Handling many requests* — the same machinery from the outside
