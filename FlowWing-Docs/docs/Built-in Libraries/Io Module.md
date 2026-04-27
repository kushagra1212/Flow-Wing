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

## Common operations

| Function | Returns | Description |
|----------|---------|-------------|
| `io::printLog(msg)` | — | Print a log message (no newline) |
| `io::printLogln(msg)` | — | Print a log message with newline |
| `io::printErrorLog(msg)` | — | Print an error log message (no newline) |
| `io::printErrorLogln(msg)` | — | Print an error log message with newline |
| `io::flush()` | — | Flush the output buffer |
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
