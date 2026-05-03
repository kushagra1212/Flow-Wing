---
sidebar_position: 7
title: I/O utilities (io)
sidebar_label: I/O (io)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# I/O utilities (`io`)

## Start here

**`bring io`** provides **logging helpers**, **output flushing**, and **line-based stdin reading**. It is useful for logging during development and for simple interactive terminal programs.

### A tiny program

<CodeBlock code={
`bring io
bring Err

io::printLogln("Starting...")

var line: str, err: Err::Result = io::readLine()
if err.isErr() {
    io::printErrorLogln("Could not read input")
} else {
    io::printLogln("You typed: ", line)
}

io::flush()
`} language="fg"/>

**Sample output (user types "hello"):**
```
Starting...
hello
You typed: hello
```

## `printLog` / `printErrorLog` vs built-in `print` / `println`

- **`io::printLog(msg)`** and **`io::printLogln(msg)`** — print to **stdout** as log messages (with optional color via the second `color` parameter). These are for structured logging.
- **`io::printErrorLog(msg)`** and **`io::printErrorLogln(msg)`** — print to **stderr** as error log messages (with optional color).
- The built-in **`print`** and **`println`** are general-purpose print to stdout, not part of the `io` module.

Use `io` module functions when you want color-tagged log output or need to flush; use `print`/`println` for simple output.

## Logging examples

<CodeBlock code={
`bring io

io::printLogln("Info: Application started")
io::printLog("Processing...")
io::printLogln(" done")
io::printErrorLogln("Error: Something went wrong")
io::flush()
`} language="fg"/>

**Output:**
```
Info: Application started
Processing... done
Error: Something went wrong
```

## Common operations

| Function | Returns | Description |
|----------|---------|-------------|
| `io::printLog(msg)` | — | Print a log message to stdout (no newline) |
| `io::printLogln(msg)` | — | Print a log message to stdout with newline |
| `io::printErrorLog(msg)` | — | Print an error log message to stderr (no newline) |
| `io::printErrorLogln(msg)` | — | Print an error log message to stderr with newline |
| `io::flush()` | — | Flush the stdout buffer |
| `io::readLine()` | `str, Err::Result` | Read a line from stdin; returns `str` and an error result |

## Reading from stdin

`io::readLine()` returns a **tuple** of `str, Err::Result`. Always check the error result before using the string:

<CodeBlock code={
`bring io
bring Err

var input: str, err: Err::Result = io::readLine()
if err.isErr() {
    println("EOF or error reading input")
}
println("Input was: ", input)
`} language="fg"/>

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source** | `fw-modules/io_module/io-module.fg` |
| **Integration fixtures** | `tests/fixtures/LatestTests/IoModuleTests/` |
