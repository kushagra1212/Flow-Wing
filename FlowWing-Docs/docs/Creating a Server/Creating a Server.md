---
sidebar_position: 8
title: HTTP server (Vortex)
sidebar_label: HTTP server (Vortex)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# HTTP server (Vortex)

## What this page is

**Vortex** is Flow-Wing’s **HTTP** library: you **`bring vortex`**, start a **`vortex::Server`**, **listen** on a port, then **accept** requests and **send** a response. Most calls that can fail return **`Err::Result`**, so you usually **`bring Err`** too. You need a working compiler install—see *Getting Started → Installation*.

## In five steps (mental model)

1. **`bring vortex`** and **`bring Err`**
2. **`new vortex::Server()`** and **`app.listen(8080)`** — if **`listen` fails, print the error and stop**
3. **`app.accept()`** gives you a **request** and a **response** for **one** client
4. Branch on **`req.getMethod()`** and **`req.getPath()`** to decide what to return
5. Use **`res.status(code).send("…")`** (or **`.json(...)`** when you add JSON) to answer

A **real** service keeps a **loop** around **`accept()`** and handles many requests. The example below uses **one** request so the program stays short; you can add **`while`** / **`for`** the same way as in *LatestTests/ServerTests* (see the bottom of this page).

## Minimal example

Save as something like **`main.fg`**, then compile and run it (next section). This handles a single **GET** for **`/`**; anything else returns **404**.

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
  /; One request for a short demo—use a loop in production
  var req: vortex::Request, res: vortex::Response = app.accept()
  if req == null {
    printErrorLog("Failed to accept connection")
    return :
  }
  if req.getMethod() == "GET" && req.getPath() == "/" {
    res.status(200).send("Hello from Vortex")
  } else {
    res.status(404).send("Not found")
  }
}
fg_main()
`} language="fg"/>

:::note `return :` syntax

In functions that return `nthg`, use **`return :`** (with a colon) for early exit. The colon distinguishes it from value-returning `return expr`. Both `listen()` failure and `accept()` failure examples above use `return :` to bail out early without producing a value.
:::

## Run it

1. **Build** a native executable with your **AOT** compiler, same as *Hello World*:

   ```bash
   flowwing main.fg -o vortexdemo
   ./vortexdemo
   ```

   On Windows, use **`flowwing` / `FlowWing.exe`**, and **`-o vortexdemo.exe`**.

2. In another terminal, call the server (or open **`http://127.0.0.1:8080/`** in a browser while the program is running):

   ```bash
   curl -s http://127.0.0.1:8080/
   ```

3. **JIT:** if you have **`flowwing-jit`**, you can run **`flowwing-jit main.fg`** in one step instead of **`-o`** (see *Flow-Wing CLI*).

**`bring vortex` is usually enough** for the linker. A **`-S` / `--server`** switch exists on some builds as a link hint; you typically **do not** need it when your source already has **`bring vortex`**. Use **`--help`** on the binary you have.

## What to add next (still beginner-friendly)

- **More paths** — add **`if` / `else if`** on **`getPath()`** and **`getMethod()`** (for example an **`/api/…`** JSON handler).
- **JSON** — **`bring json`**, build or **`json::parse`** a payload, return with **`res.status(200).json(node)`** when your program needs an API.
- **Static or HTML files** — **`bring file`**, read with **`file::readText`**, and send text or HTML in **`send`**; **`file::__DIR__`** is handy for files next to your **`.fg`** (see the larger *ServerTests* demo below).
- **Maps** for small in-memory data — **`bring map`**, or **`vec`** for lists—same as the rest of the language.

## Request and response (API cheat sheet)

- **`vortex::Server`**: **`listen(port)`** → **`Err::Result`**. On success, call **`accept()`** when you are ready.
- **`accept()`** — returns **`vortex::Request`** and **`vortex::Response`**.
- **Request** — **`getMethod()`**, **`getPath()`**, **`getBody()`**, and related accessors (for headers and bodies on **POST/PUT**).
- **Response** — chained style: **`status(n).send("text")`**, **`json(...)`** for JSON bodies, and **streaming** helpers (**`streamBegin` / `streamWrite` / `streamEnd`**) where the module provides them. Prefer the chained API over a single “options” object.
- Tighten **timeouts**, **TLS**, and **error handling** for anything exposed on a public network. This page is a starting point, not a production checklist.

## Deeper: patterns and repository examples (contributors & curious readers)

The Flow-Wing repository keeps **regression and demo** programs under **`tests/fixtures/LatestTests/ServerTests/`**:

| Path | What it shows |
|------|----------------|
| **`vortex_router.fg`** | Several **GET/POST** routes, **JSON** via **`json::parse` / `.json`**, and **text streaming** (chunked **`.streamWrite`**)—good template for a small **API** or router. The file uses a fixed test port; pick your own for local runs. |
| **`mission_control_server/mission_control.fg`** | Bigger **HTML** example: **templates** on disk, **`file::__DIR__`**, **classes**, **`text::Text`**, and **`file::readText`** to load **`.html`** next to the source—useful if you are building a **page**-style app. |

Those paths are for people who have **cloned the repo**; you do not need them to follow the **minimal example** at the top. They are **not** a separate “engine” product—just sample **`.fg`** you can read and borrow from.

## See also

- **Blog** — *Creating a server* (short walkthrough in this site’s blog)
- *Language Fundamentals → **Flow-Wing CLI*** — flags and **`--entry-point`**
- Standard modules are **case-sensitive**; the import is always **`bring vortex`** in lowercase

<iframe
  width="800"
  height="400"
  src="https://github.com/user-attachments/assets/4d7502a9-e1de-4c20-a82b-4ffee80df2b9"
  title="YouTube — Flow-Wing Vortex (optional video)"
  frameborder="0"
  allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
  allowfullscreen
></iframe>
