---
sidebar_position: 4
title: File module
sidebar_label: File (file)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# File module (`file`)

## Start here

The **`file`** module reads and writes **disk paths** from Flow-Wing. You **`bring file`**. When an operation can fail, you get **`Err::Result`** on the result side, so in real code you also **`bring Err`** and use **`isErr()`** (or **`Err::isErr`**) to branch on failures.

**Two styles:**

- **All at once** — **`file::readText`**, **`file::writeText`**, **`file::appendText`** (good for small files).
- **Open, then read/write** — **`file::File`** for **`open`**, **`readLine`**, **`close`**, when you work like a small script with a file handle.

**Script location:** **`file::__DIR__`** is a string path to the **current** **`.fg`** file’s directory (handy for loading assets next to the program).

## Example (read and write, with errors)

<CodeBlock code={
`bring file
bring Err

var path: str = "example.txt"
var ok: bool, werr: Err::Result = file::writeText(path, "Hello\\n")
if werr.isErr() {
  println(werr.getMessage())
} else {
  var content: str, rerr: Err::Result = file::readText(path)
  if rerr.isErr() {
    println(rerr.getMessage())
  } else {
    println(content)
  }
}
`} language="fg"/>

## Whole-file helpers (summary)

- **`file::readText(path: str) -> str, Err::Result`**
- **`file::writeText(path: str, content: str) -> bool, Err::Result`**
- **`file::appendText(path: str, content: str) -> bool, Err::Result`**
- **`file::exists(path: str) -> bool`**
- **`file::delete(path: str) -> bool, Err::Result`**

## Stateful `file::File` (open file)

`new file::File(path)` then **`open("r" | "w" | "a")`**, **`readLine`**, **`close`**, as declared in the **`file`** module for your compiler version.

## More detail: errors and paths

Always treat **I/O** as fallible: missing files, **permission** errors, and **invalid paths** show up on **`Err::Result`**. Use the **`Err`** module’s patterns in *Built-in libraries → **Err** module* to report messages and codes. Path strings follow your **OS** rules; on Windows, **backslashes** in string literals and **string building** are normal in **`.fg`** programs.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/file_module/file-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/FileModuleTests/`** — reads, writes, and **`__DIR__` behavior** in the test harness. |
