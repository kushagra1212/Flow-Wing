---
sidebar_position: 1
title: Writing Good Code
sidebar_label: Writing Good Code
---

import CodeBlock from "../src/components/common/CodeBlock";

# Writing Good Code in Flow-Wing

## Style Conventions

- File extension: `.fg`
- Indentation: 4 spaces
- Variable names: `camelCase`  
- Type names: `PascalCase`
- Function names: `camelCase`

## Naming

<CodeBlock code={
`/; Good
var userName: str = "Alice"
type Point = { x: int; y: int }
class HttpClient { }

/; Avoid
var un: str = "Alice"
type point = { X: int; Y: int }
`} language="fg"/>

## File Organization

- One module per file
- `bring` imports at the top
- Types and classes before functions
- `fg_main()` at the bottom (or omit for simple scripts)

## Error Handling

Always check `Err::Result` return values:

<CodeBlock code={
`var ok: bool, werr: Err::Result = file::readText("data.txt")
if (werr.isErr()) {
    printErrorLog("Failed: " + werr.getMessage())
    return :
}
/; use ok ...
`} language="fg"/>

## Debugging

- Use `print()` for quick inspection
- Use `io::printLog()` for structured logging
- Compile with `--emit=ir` to inspect generated LLVM IR
- Run with `make run-aot-debug FILE=your.fg` for debug mode
