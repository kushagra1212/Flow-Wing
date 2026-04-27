---
sidebar_position: 5
title: Err module
sidebar_label: Err
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Err module (`Err`)

## Start here

**`Err`** is the usual way to return **"something went wrong"** from APIs that can fail. You **`bring Err`**. Many library calls return a **pair** (for example a **value** and an **`Err::Result`**, or a **bool** and an **`Err::Result`**). **Check the error first** with **`isErr()`** on the result or **`Err::isErr(err)`** before you trust the "success" part.

- **`Err::Result`** — holds a **message**, a small **code** (see **`Err::CODE`**), and optional **details**.
- **`Err::CODE`** — named **constants** for **stable** error kinds.

### A tiny program

<CodeBlock code={
`bring Err
print(Err::CODE.NOT_FOUND)
`} language="fg"/>

**Output:**
```
1
```

**Pattern with `file` or other modules** — the **second** (or last) return is often the **`Result`**:

<CodeBlock code={
`bring file
bring Err

var content: str, err: Err::Result = file::readText("missing.txt")
if err.isErr() {
    println(err.toString())
} else {
    println(content)
}
`} language="fg"/>

## Complete error codes

| Constant | Integer value | Meaning |
|----------|--------------|---------|
| `Err::CODE.OK` | `0` | No error / success |
| `Err::CODE.NOT_FOUND` | `1` | Resource not found |
| `Err::CODE.FAILED` | `2` | General failure |
| `Err::CODE.INVALID_ARGUMENT` | `3` | Bad input |

## Building and inspecting errors

**Constructors and helpers** include an **`init`** with **message**, optional **code**, and optional **details**; and methods such as:

- **`getMessage()`**, **`getCode()`**, **`getDetails()`**
- **`withMessage(extraMessage)`** — returns a **new** `Err::Result` with the extra message appended to the original message (joined with ` -> `). The original code and details are preserved.
- **`withDetails(details)`** — returns a **new** `Err::Result` with the details field set to the given string. The original message and code are preserved.
- **`withCode(code)`** — returns a **new** `Err::Result` with the code replaced. The original message and details are preserved.
- **`hasDetails()`** — returns `bool`, true if details is non-empty.
- **`isOk()`** / **`isErr()`** — check success or failure.
- **`clone()`** — returns a **new** `Err::Result` with all fields copied.
- **`toString()`** — a single **human-readable** line for **logging** or **println**.
- **`clearDetails()`** — returns a **new** `Err::Result` with details cleared to `""`.

**Free functions:**

- **`Err::ok(message)`** — returns a success `Err::Result` (code `OK`).
- **`Err::error(message, code, details)`** — returns a failure `Err::Result`.
- **`Err::isOk(result)`** / **`Err::isErr(result)`** — static checks on any `Err::Result`.

**Longer example:**

<CodeBlock code={
`bring Err

fun handle_error() -> nthg {
  var err1: Err::Result = new Err::Result("File not found", Err::CODE.NOT_FOUND)
  print(err1.getMessage())

  var err2: Err::Result = err1.withMessage("Please check the path")
  print(err2.toString())

  var err3: Err::Result = err2.withDetails("The file might have been deleted")
  print(err3.toString())

  var err4: Err::Result = new Err::Result("Invalid argument", Err::CODE.INVALID_ARGUMENT)
  print(err4.toString())
}

handle_error()
`} language="fg"/>

**Output:**
```
Error: 
File not foundError: File not found -> Please check the pathError: File not found -> Please check the path (Details: The file might have been deleted)Error: Invalid argument
```

## More detail: `ErrorCode` and `Err::Result`

**`Err::CODE`** is a **shared vocabulary** between your code and the standard library. **`Err::Result`** is designed so you can **thread** **messages** and **details** through calls without a separate exception system—Flow-Wing's model is **explicit** **return** values, not try/catch.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/error_module/Err-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/ErrModuleTests/`**. |

Cloning the repo is **optional** for **day-to-day** use of **`Err`**.
