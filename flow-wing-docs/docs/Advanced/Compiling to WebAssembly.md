---
sidebar_position: 7
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Compiling to WebAssembly

The compiler can build a program as **WebAssembly** instead of a native
executable. The result runs in **Node.js** or in a **web browser**, and prints
exactly what the native build prints.

```
flowwing hello.fg --target=wasm32 --emit=exe -o hello.js
                 │
                 ▼
     hello.js    the loader: starts the program and connects its output
     hello.wasm  your program and the Flow-Wing runtime
```

## What you need

- **Emscripten (emsdk)**, which does the final link to WebAssembly. Install it
  from [emscripten.org](https://emscripten.org/docs/getting_started/downloads.html).
  The compiler finds it without extra setup if `emcc` is on your `PATH`, if
  `EMSDK` points at the emsdk folder, or if emsdk is installed in `~/emsdk`.
  To choose one explicitly, set `FLOWWING_EMCC` to the `emcc` you want.
- **Node.js 18 or newer**, to run the result outside a browser.

## Build and run with Node

<CodeBlock code={
`fun square(n: int) -> int {
    return n * n
}

println("Hello from WebAssembly")
println(square(7))
`} language="fg"/>

```bash
flowwing hello.fg --target=wasm32 --emit=exe -o out/hello.js
node out/hello.js
```

```
Hello from WebAssembly
49
```

`-o` decides the output: a name ending in `.js` (or with no extension) gives a
program for Node, and a name ending in `.html` gives a web page.

## Build a web page

```bash
flowwing hello.fg --target=wasm32 --emit=exe -o web/hello.html
```

This writes `hello.html`, `hello.js` and `hello.wasm`. Browsers do not load
WebAssembly from a `file://` address, so serve the folder with any web server
and open the page:

```bash
cd web && python3 -m http.server 8000
# then open http://localhost:8000/hello.html
```

The page shows the program's output. Your program runs on the page's own
thread, so a program that runs for a long time, or calls `sys::sleep`, keeps
the page busy until it finishes. To keep the page responsive, run the `.js`
file in a Web Worker instead, as the [playground](/playground) does.

## Build an interactive page

To work with the page itself (read what is typed, change elements, handle
clicks, fetch data), bring the [dom module](../Built-in%20Libraries/Dom%20Module.md),
build to `app.js`, and load it from your own HTML:

```bash
flowwing app.fg --target=wasm32 -o app.js
```

```html
<button id="add">+</button> <span id="count">0</span>
<script src="app.js"></script>
```

While it waits for the next event, the program sleeps and the page stays
responsive. For browser APIs `dom` does not cover, the
[js module](../Built-in%20Libraries/Js%20Module.md) reaches any JavaScript value.

## What works

The whole language, including classes, inheritance, the garbage collector,
`spawn` with `sys::yield` and `sys::sleep`, and these modules:
`vec`, `map`, `text`, `io`, `json`, `Err`, `sys` and `file`, plus `dom` and
`js`, which work only here.

In Node, a program sees the real disk and the real standard input, and
`sys::run` and `sys::exec` run their command, all as a native build would.

A browser has none of these. There, `file` works on files kept in memory for
the length of the run, standard input is whatever text the page supplies, and
`sys::run` returns `-1` with an error message, because a page has no shell.

## What does not work yet

| | Why |
|---|---|
| `vortex`, `mongo`, `raylib` | They need what WebAssembly cannot reach: a listening socket, a database connection, a window. Bringing one stops the build with `ModuleNotForTarget`. |
| Very deep recursion | Every WebAssembly call also uses the JavaScript engine's own stack, which stops recursion at roughly 10,000 to 20,000 calls, and a task also has its own stack. The program then ends with `Runtime Error: Stack Overflow.` A native `main` reaches far deeper. |

## Seeing the generated code

`--emit=ir` with `--target=wasm32` writes the LLVM IR for the WebAssembly
target, where pointers are 4 bytes instead of 8:

```bash
flowwing hello.fg --target=wasm32 --emit=ir --output-dir=ir
```

## Size and speed

A small program is about 30 to 60 KB of WebAssembly, most of it the runtime.
Programs that use `spawn` are larger and somewhat slower, because switching
between tasks needs extra machinery in WebAssembly; programs that do not
spawn do not pay for it.

## If something goes wrong

| Message | What to do |
|---|---|
| `needs Emscripten (emcc), which was not found` | Install emsdk, or point `EMSDK` or `FLOWWING_EMCC` at it. |
| `The Flow-Wing runtime for wasm32 is not built` | Your install is missing the WebAssembly runtime. Reinstall a release that includes it. |
| `--target=wasm32 cannot --emit=obj or --emit=jit` | Object files and the JIT are native only. |
| `[Error:ModuleNotForTarget] The 'vortex' module works only in native builds.` | The module needs a native build (see above). |
| `[Error:ModuleNotForTarget] The 'dom' module works only in WebAssembly builds` | Build with `--target=wasm32`: `dom` and `js` talk to a web page. |
