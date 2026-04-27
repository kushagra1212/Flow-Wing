---
sidebar_position: 6
title: System module (sys)
sidebar_label: System (sys)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# System utilities (`sys`)

## Start here

**`bring sys`** gives your program access to **command-line arguments**, the **current script directory**, a **timestamp** helper, and **`exit`**. No extra native libraries or link flags are needed.

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

// sys::getArg(0) is the program name
// sys::getArg(1) is "hello"
// sys::getArg(2) is "world"
// sys::getArg(3) is "42"

var count: int = sys::getArgCount()
for (var i: int = 0 to count : 1) {
    println(i, ": ", sys::getArg(i))
}
`} language="fg"/>

## Common operations

| Function | Returns | Description |
|----------|---------|-------------|
| `sys::getArgCount()` | `int` | Number of command-line arguments |
| `sys::getArg(n)` | `str` | The nth argument (0 = program name) |
| `sys::scriptDir()` | `str` | Directory of the running script |
| `sys::timestamp()` | `int` | Current timestamp (milliseconds) |
| `sys::exit(code)` | — | Terminates the program with exit code `code` |

### Early exit

<CodeBlock code={
`bring sys

println("before")
sys::exit(42)
println("after")      // this never runs
`} language="fg"/>

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source** | `fw-modules/sys_module/sys-module.fg` |
| **Integration fixtures** | `tests/fixtures/LatestTests/SysModuleTests/` |
