---
slug: Creating an Server
title: Creating an Server in Flow-Wing
authors: [kushagra]
tags: [FlowWing, Server]
---
import CodeBlock from "../src/components/common/CodeBlock";

# Creating a server in Flow-Wing (short)

## Get something running in a few minutes

1. **Install** a Flow-Wing **SDK** (see the docs: *Getting Started → **Installation***) so you have **`flowwing`** or **`FlowWing`** and the standard **modules** on disk.
2. Put the program below in **`main.fg`**. It **listens** on a port, **waits** for **one** **HTTP** request, and sends **"Hello"**. **Vortex** is the HTTP stack; **Err** is for **`listen` failures.
3. **Compile** and **run** the executable (AOT) or use **JIT** if you have **`flowwing-jit`** (see *Flow-Wing CLI*). Then **curl** or open the **URL** in a browser while the process is up.

**Minimal example** (one request—add a **loop** around **`accept()`** for a real service):

<CodeBlock code={
`bring vortex
bring Err

fun fg_main() -> nthg {
  var app: vortex::Server = new vortex::Server()
  var err: Err::Result = app.listen(8080)
  if Err::isErr(err) {
    println(err.getMessage())
    return:
  }
  var req: vortex::Request, res: vortex::Response = app.accept()
  res.status(200).send("Hello")
}
fg_main()
`} language="fg"/>

**Build (typical AOT name on PATH):**

<CodeBlock code={
`flowwing main.fg -O3
`} />

`bring vortex` is usually enough; you rarely need extra **“server”** **link** flags on top of a normal app. The full **guide** in the main docs (routing, **JSON**, **streaming**, error handling) is **HTTP server (Vortex)** under *Creating a server* in the **sidebar**—read that next.

## Read next (same site, deeper guide)

- **HTTP server (Vortex)** — **Request** / **Response** API, **paths**, and production-minded notes.
- **Err module** and **Flow-Wing CLI** for flags and result handling.

## Optional video

<iframe
  width="800"
  height="400"
  src="https://github.com/user-attachments/assets/4d7502a9-e1de-4c20-a82b-4ffee80df2b9"
  title="YouTube — Flow-Wing Vortex (optional)"
  frameborder="0"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen
></iframe>

## For repo readers: Vortex in tests

If you have the **Flow-Wing** **repository**, extra **Vortex** samples and router-style programs live under **`tests/fixtures/LatestTests/ServerTests/`** (for example **`vortex_router.fg`** and **`mission_control_server/`**). They are **regression** and **demo** **`.fg`** files, not a separate product—use them after you are comfortable with the **minimal** example above.
