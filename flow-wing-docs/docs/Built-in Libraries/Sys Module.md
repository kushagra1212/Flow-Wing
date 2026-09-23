---
sidebar_position: 6
title: System module (sys)
sidebar_label: System (sys)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# System utilities (`sys`)

## Start here

**`bring sys`** gives your program access to **command-line arguments**, the **current script directory**, a **monotonic clock**, **task scheduling** helpers, and **`exit`**. No extra native libraries or link flags are needed.

### A tiny program

<CodeBlock code={
`bring sys

println("Program: ", sys::getArg(0))
println("Script dir: ", sys::scriptDir())
println("Timestamp: ", sys::timestamp())
println("Arg count: ", sys::getArgCount())
`} language="fg"/>

## Command-line arguments

Arguments are passed to your program after the **`--`** separator on the compiler command line:

```bash
flowwing myapp.fg -- hello world 42
```

Inside your `.fg`:

<CodeBlock code={
`bring sys

/; sys::getArg(0) is the program name
/; sys::getArg(1) is "hello"
/; sys::getArg(2) is "world"
/; sys::getArg(3) is "42"

var count: int = sys::getArgCount()
for (var i: int = 0 to count - 1 : 1) {
    println(i, ": ", sys::getArg(i))
}
`} language="fg"/>

## Common operations

| Function | Returns | Description |
|----------|---------|-------------|
| `sys::getArgCount()` | `int` | Number of command-line arguments |
| `sys::getArg(n)` | `str` | The nth argument (0 = program name), or `""` if there is none |
| `sys::scriptDir()` | `str` | Directory of the running script |
| `sys::timestamp()` | `int64` | Current Unix timestamp (seconds since epoch). `int64` so it stays correct after 2038, when the value no longer fits in 32 bits. |
| `sys::exit(code)` | — | Terminates the program with exit code `code` |

## Measuring time

`sys::timestamp()` is **seconds**-resolution and it jumps when the system clock
is adjusted, so it cannot measure anything that finishes inside a second. For
timing, use the monotonic clock. It never goes backwards, and its zero point is
arbitrary — only **differences** between readings mean anything.

| Function | Returns | Description |
|----------|---------|-------------|
| `sys::nanos()` | `int64` | Monotonic clock, nanoseconds |
| `sys::micros()` | `int64` | Same clock, microseconds |
| `sys::millis()` | `int64` | Same clock, milliseconds |
| `sys::elapsedNanos(start)` | `int64` | Nanoseconds since an earlier `nanos()` reading |

<CodeBlock code={
`bring sys

var start: int64 = sys::nanos()

var sum: int64 = 0
for var i: int = 0 to 500000 {
    sum = sum + 1
}

println("took ", sys::elapsedNanos(start), " ns")
println("that is ", Int64(sys::elapsedNanos(start) / 1000000l), " ms")
`} language="fg"/>

:::tip
Division in Flow-Wing is floating point, so wrap the result in `Int64(...)` when
you want whole milliseconds.
:::

## Pausing and switching

These two are what make `spawn` useful. See *Advanced → Concurrency with spawn*.

| Function | Returns | Description |
|----------|---------|-------------|
| `sys::sleep(ms)` | `nthg` | Wait `ms` milliseconds |
| `sys::yield()` | `nthg` | Give up the CPU, resume on the next line |

**Inside a spawned task `sys::sleep` suspends only that task** — other queued
work runs while it waits. Outside a task there is nothing to switch to, so it
blocks the thread.

<CodeBlock code={
`bring sys

fun waiter(id: int) -> nthg {
    sys::sleep(200)
    println("task ", id, " woke")
}

for var i: int = 0 to 4 {
    spawn waiter(i)
}
println("5 tasks queued")
`} language="fg"/>

Five tasks each waiting 200 ms finish in about **200 ms** in total, not 1000 ms.

`sys::yield()` has no deadline. The task moves to the back of the queue and
continues from the following line when its turn comes round. It is a no-op
outside a task.

### Early exit

<CodeBlock code={
`bring sys

println("before")
sys::exit(42)
println("after")      /; this never runs
`} language="fg"/>

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source** | `fw-modules/sys_module/sys-module.fg` |
| **Integration fixtures** | `tests/fixtures/LatestTests/SysModuleTests/` |
