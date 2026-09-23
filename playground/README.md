# Flow-Wing playground

Write Flow-Wing on the docs site and run it in the browser.

```
 docs site: /playground                      playground/server
 ┌───────────────────────────┐   code    ┌──────────────────────────────┐
 │ editor · Run · Stop       │ ────────▶ │ FlowWing --target=wasm32      │
 │ output                    │ ◀──────── │   --emit=exe                  │
 └── program runs in a Web ──┘ js + wasm └──────────────────────────────┘
     Worker (static/playground/worker.js)
```

The server only compiles. The program runs in the visitor's browser.

## One-time setup

You need emsdk in `~/emsdk` (or on `PATH`, or `$EMSDK`) and Node 18 or newer.

```bash
make build-aot-release     # the compiler
make build-wasm-runtime    # the Flow-Wing runtime, compiled to wasm
```

## Run it locally

Two terminals, from the repository root:

```bash
# 1. the compile server, on http://localhost:8787
node playground/server/server.mjs

# 2. the docs site, on http://localhost:3000
cd flow-wing-docs && npx docusaurus start
```

Open http://localhost:3000/playground, pick an example or type a program, and
press **Run** (or Ctrl+Enter / Cmd+Enter).

Do not `source ~/emsdk/emsdk_env.sh` in the terminal you run `make` from: it
puts a directory named `cmake` on `PATH`, and GNU Make 4 then fails with
"cmake: Permission denied". Nothing here needs it.

## Check the server on its own

```bash
curl http://localhost:8787/health
# {"ok":true}

curl -s http://localhost:8787/compile -H 'Content-Type: application/json' \
     -d '{"source": "println(\"hi\")"}' | head -c 120
# {"ok":true,"js":"...
```

## Try a program without the browser

`hello.fg`:

```
fun square(n: int) -> int {
  return n * n
}

println("Hello, Flow-Wing!")
println(square(7))
```

```bash
make run-aot-release FILE=hello.fg     # native
make run-wasm FILE=hello.fg            # the same program as wasm, under Node
make run-wasm FILE=hello.fg ARGS=--html  # also writes a page to open in a browser
```

## Turn it into a test

Put `hello.fg` next to a `hello.expect` holding its exact output, in a folder
under `tests/fixtures/LatestTests/`:

```bash
make test-aot FILTER='MyTests*'                                  # native
make test-wasm ARGS="--dir tests/fixtures/LatestTests/MyTests"   # same output as wasm
```

A test of a runtime error has no `.expect`. Its first line names the error
instead, and wasm must also exit non-zero:

```
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
```

## Tests for the playground itself

```bash
node --test playground/server/compile.test.mjs   # the compile server
make test-wasm                                     # every fixture as wasm
```

## Configuration

Server (`server.mjs`), through the environment:

| Variable | Default |
|---|---|
| `FLOWWING` | `build/sdk/bin/FlowWing` |
| `PORT` | `8787` |
| `ALLOWED_ORIGINS` | `https://flow-wing-docs.vercel.app,http://localhost:3000` |
| `MAX_COMPILES` | number of CPUs |

Docs site: `PLAYGROUND_COMPILE_URL` sets where the page sends code (default
`http://localhost:8787/compile`).

## Deploying the server

Programs run in the browser, so the server never runs user code. It does read
files while compiling: `bring "path"` makes the compiler open that path. The
server refuses file brings before compiling (see `refuseFileBrings` in
`compile.mjs`), but run it where nothing worth reading is on disk anyway,
such as a container that holds only the Flow-Wing SDK and emsdk.
