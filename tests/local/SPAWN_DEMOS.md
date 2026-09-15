# spawn / suspension demos

Five runnable programs that show how `spawn` and suspension actually behave.
Every "expected output" block in these files was produced by running the
program, not predicted.

```bash
make run-aot-release FILE=tests/local/spawn_demo_1_queue_not_call.fg ARGS="--emit=exe"
```

Read them in order. Each one depends on the one before it.

| # | File | Shows |
|---|------|-------|
| 1 | `spawn_demo_1_queue_not_call.fg` | `spawn` queues a call; the drain runs only after the top-level body ends |
| 2 | `spawn_demo_2_toplevel_read_blocks.fg` | A read at top level blocks — nothing else runs |
| 3 | `spawn_demo_3_intask_read_suspends.fg` | The **same** read inside a task suspends and lets others run |
| 4 | `spawn_demo_4_timer_vs_event.fg` | A timer wait and an I/O wait use the same field, differently |
| 5 | `spawn_demo_5_write_blocks_read_suspends.fg` | Reads suspend, writes block the whole thread |

Demos 2 and 3 are a matched pair. The read line is byte-for-byte identical in
both, and the behaviour is opposite. That contrast is the point of the set.

## The two ideas being separated

`spawn` and suspension are not alternatives. They are different axes, and
confusing them is the usual source of "should I spawn this?".

|  | What it does | Who decides | Costs |
|---|---|---|---|
| **Suspension** | *This* task waits; other tasks run | The runtime, silently | Nothing — reuses the existing stack |
| **`spawn`** | Starts a *second* task | You, in the source | A new 256 KB stack |

`spawn` never suspends anything. Suspension never creates a task.

The rule the language follows:

> Automatic where it preserves your control flow. Explicit where it changes it.

Reading a file does not change control flow — the next line still runs next, so
suspension is invisible. Starting a second line of work does change it, so you
write `spawn` and can see it.

This is why `spawn` maps onto Go's `go f()`, not onto JavaScript's `await`:

| Language | "Suspend here" | "Start concurrent work" |
|---|---|---|
| JavaScript | `await` | `Promise.all`, `worker_threads` |
| Go | *(nothing — automatic)* | `go f()` |
| FlowWing | *(nothing — automatic)* | `spawn f()` |

## What `spawn` will not accept

Each rule has a fixture under `tests/fixtures/LatestTests/GcTests/`:

| Error | Rejected | Fixture |
|---|---|---|
| `SpawnRequiresUserFunction` | `spawn println("x")` — built-ins are emitted inline, so there is no symbol to call | `gc_spawn_reject_builtin.fg` |
| `SpawnRequiresNthgReturn` | `spawn computes()` returning `int` — a task is called through `void (*)(void)`, so the hidden out-parameter would be garbage | `gc_spawn_reject_value_return.fg` |
| `SpawnRequiresPlainFunction` | `spawn obj.method()` — `self` would need GC tracing from the spawn site until the call | `gc_spawn_rejects_method.fg` |
| `SpawnRequiresFunctionCall` | `spawn value` — the operand has to be a call | `gc_spawn_requires_call.fg` |

So `spawn file::writeText(path, body)` fails twice over: it is a built-in, and
it returns two values.

To run a write in the background, wrap it — but read demo 5 first, because it
will not stop the write from blocking the thread:

```
fun saveLog(path: str, payload: str) -> nthg {
    var ok: bool, e: Err::Result = file::writeText(path, payload)
}

spawn saveLog(path, payload)
```

You also lose `ok` and `e` permanently. Nothing can read them.

## Where the threads are

| Work | Threads | Runs on |
|---|---|---|
| HTTP accept / read / write | **No** | The one event-loop thread (`epoll` / `kqueue` / IOCP) |
| `file::readText` | **Yes** | libuv threadpool — 4 threads |
| DNS (`uv_getaddrinfo`, HTTP *client*) | **Yes** | Same pool |
| `file::writeText` / append / delete / open / readLine | **No** | Blocks the event-loop thread |
| All `.fg` code | **No** | Always the one thread |

`file_read_all` at `libflowwing_file.cpp:122` is the only `uv_queue_work` call
site in the entire runtime.

A pool thread must never touch the GC — `libflowwing_file.cpp:77-80`:

> Deliberately uses `std::string` and not GC memory: `work` runs on a libuv
> threadpool thread, and the GC is single-threaded — calling `fw_gc_alloc` from
> there would corrupt the heap.

## Source these demos point at

| File | What is there |
|---|---|
| `fw-modules/gc/src/fw_sched.c:84-87` | `wake_at_ns` and its three meanings |
| `fw-modules/gc/src/fw_sched.c:529-544` | `fw_sched_yield` and the `swapcontext` switch |
| `fw-modules/gc/src/fw_sched.c:652-731` | `fw_sched_drain` — the re-entrancy guard and the idle branch |
| `fw-modules/file_module/libflowwing_file.cpp:114-142` | `file_read_all` — both the threadpool path and the inline fallback |
| `fw-modules/vortex_module/uv_http_server.cpp:416-434` | `fw_http_accept` — the same in-task / not-in-task split |

## Note

These write temporary files into the working directory and delete them again.
Demo 5 writes about 820 KB for roughly half a second.
