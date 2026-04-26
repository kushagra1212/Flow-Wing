---
sidebar_position: 5
title: Err module
sidebar_label: Err
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Err module (`Err`)

## Start here

**`Err`** is the usual way to return **“something went wrong”** from APIs that can fail. You **`bring Err`**. Many library calls return a **pair** (for example a **value** and an **`Err::Result`**, or a **bool** and an **`Err::Result`**). **Check the error first** with **`isErr()`** on the result or **`Err::isErr(err)`** before you trust the “success” part.

- **`Err::Result`** — holds a **message**, a small **code** (see **`Err::CODE`**), and optional **details**.
- **`Err::CODE`** — named **constants** (for example **NOT_FOUND**, **FAILED**, **INVALID_ARGUMENT** in a typical build) for **stable** error kinds.

### A tiny program

<CodeBlock code={
`bring Err
print(Err::CODE.NOT_FOUND)
`} language="fg"/>

**Pattern with `file` or other modules** — the **second** (or last) return is often the **`Result`**:

```text
if err.isErr() { … } else { use the good value }
```

## Building and inspecting errors

**Constructors and helpers** (your exact overload set follows the installed module) commonly include an **`init`** with **message**, optional **code**, and optional **details**; and methods such as:

- **`getMessage()`**, **`getCode()`**, **`getDetails()`**
- **`withMessage(…)`**, **`withDetails(…)`** — return **new** **`Err::Result`** with extra context
- **`toString()`** — a single **human-readable** line for **logging** or **println**

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

## More detail: `ErrorCode` and `Err::Result`

The **`Err::ErrorCode` / `Err::CODE`** story is a **shared vocabulary** between your code and the standard library. **`Err::Result`** is designed so you can **thread** **messages** and **details** through calls without a separate exception system—Flow-Wing’s model is **explicit** **return** values, not try/catch.

**Fields on `Err::CODE`** in a default install often include (integer values are **illustrative**; trust your binary):

- **`NOT_FOUND`** (example value **`1`**) — resource not found
- **`FAILED`** (example value **`2`**) — general failure
- **`INVALID_ARGUMENT`** (example value **`3`**) — bad input

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/error_module/Err-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/ErrModuleTests/`**. |

Cloning the repo is **optional** for **day-to-day** use of **`Err`**.
