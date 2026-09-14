---
sidebar_position: 6
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Concurrency with `spawn`

## Start here

`spawn f()` does **not** call `f`. It puts `f` on a queue. Queued work runs after
the top-level body of your program finishes.

<CodeBlock code={
`fun greet() -> nthg {
    println("hello from a task")
}

println("before")
spawn greet()
println("after")
`} language="fg"/>

Output:

```
before
after
hello from a task
```

`greet` runs last, not where you wrote it.

## Why a queue and not a thread

Every task gets its **own machine stack**, so it can stop half-way through and
continue later from the same line. Tasks are **cooperative and
single-threaded**: exactly one runs at a time, and a switch happens only where
you suspend.

That means you never need a lock. Two tasks cannot be inside the same function
at the same instant, so there is no data race to protect against.

## Waiting without blocking

`sys::sleep` inside a task suspends **that task**. Other tasks keep running.

<CodeBlock code={
`bring sys

fun waiter(id: int) -> nthg {
    sys::sleep(200)
    println("task " + String(id) + " woke")
}

for var i: int = 0 to 4 {
    spawn waiter(i)
}
println("5 tasks queued")
`} language="fg"/>

Five tasks each waiting 200 ms finish in about **200 ms**, not 1000 ms. Outside
a task there is nothing to switch to, so `sys::sleep` blocks the thread as you
would expect.

`sys::yield()` gives up the CPU without a deadline. The task goes to the back of
the queue and resumes on the next line.

<CodeBlock code={
`bring sys

fun worker(name: str) -> nthg {
    println(name + " step 1")
    sys::yield()
    println(name + " step 2")
}

spawn worker("A")
spawn worker("B")
`} language="fg"/>

```
A step 1
B step 1
A step 2
B step 2
```

`A` resumes on the line **after** its `yield`, not from the top. That is what
the per-task stack buys you.

## Passing arguments

Arguments are evaluated where you write the `spawn` and copied into a
garbage-collected block. The task reads them when it eventually runs.

What the task sees depends on the type:

| Argument | Stored as | Caller changes it after the spawn |
|---|---|---|
| `int`, `deci`, `bool`, `char` | value copy | not visible |
| `str` | pointer copy | not visible |
| array | element-by-element copy | **not visible** — a snapshot |
| `dyn` | box copy, tag included | not visible, even a re-type |
| object / class | **pointer** copy | **visible** — one shared instance |
| global | not an argument at all | **visible** — read when the task runs |

<CodeBlock code={
`type Box = { n: int }

fun show(count: int, numbers: int[3], box: Box) -> nthg {
    println("count   = " + String(count))     /; 10   - copied
    println("numbers = " + String(numbers[0]))/; 7    - copied
    println("box.n   = " + String(box.n))     /; 999  - SHARED
}

var count: int = 10
var numbers: int[3] = [7, 8, 9]
var box: Box = { n: 1 }

spawn show(count, numbers, box)

/; all of this happens before the task runs
count = 999
numbers[0] = 999
box.n = 999
`} language="fg"/>

:::caution
`spawn f(numbers)` and `spawn f(box)` carrying the same data behave
**differently**. An array argument is a snapshot. An object argument is shared,
so the task and the caller see each other's writes.
:::

## Rules

A spawned function must:

- return `nthg` — a value-returning function takes a hidden out-parameter the scheduler cannot supply
- not be a method — `self` is a hidden argument
- not be a built-in such as `println` — wrap it in your own function
- not take `inout` parameters — they alias a stack frame that is gone by the time the task runs

Each of these is a compile-time error with its own message:

| Mistake | Error |
|---|---|
| `spawn 42` | `SpawnRequiresFunctionCall` |
| `spawn returnsAnInt()` | `SpawnRequiresNthgReturn` |
| `spawn obj.method()` | `SpawnRequiresPlainFunction` |
| `spawn println("x")` | `SpawnRequiresUserFunction` |
| `spawn f(inout x)` | `SpawnByReferenceArgument` |

## Task stacks

Each running task owns a stack, **256 KB** by default — much smaller than the
main stack. A task that recurses deeply can run out.

Set the size with an environment variable:

```bash
FW_TASK_STACK_KB=4096 ./myprogram
```

Overflow is reported, not silent:

```
Runtime Error: Task Stack Overflow.
  ▶ A spawned task used more stack than it owns.
  ▶ Raise it with FW_TASK_STACK_KB (e.g. FW_TASK_STACK_KB=4096), or reduce the recursion depth.
```

Stacks are taken when a task first runs and released when it finishes, so
queuing a million tasks costs a million small records — not a million stacks.

## Tasks and the garbage collector

A suspended task's variables live on that task's own stack. The collector knows
about them: the scheduler hands every parked task's roots to the GC during
marking, along with the arguments of tasks that have not started yet.

You can check this yourself by running any program under maximum collection
pressure:

```bash
FW_GC_STRESS=1 ./myprogram
```

That collects on **every** allocation. If your program behaves the same, its
tasks are holding their data correctly.

## Where to go next

- *Creating a Server* — handling requests concurrently with `spawn`
- *Built-in Libraries → System (sys)* — `sleep`, `yield`, and the monotonic clock
