# The Flow-Wing website server

`server.fg` serves https://flowwing.kushagrarathore.in: the landing page, its
own "try it" box, analytics, and the two requests the docs site's
[playground](https://flow-wing-docs.vercel.app/playground) makes.

```
 docs playground (browser)                          this server
 ┌──────────────────────────────────┐
 │ tokens, trees, errors as you type│  runs in the browser: the compiler's front
 │                                  │  end built to WebAssembly (no server)
 │ Run, "in browser" ───────────────┼─▶ POST /compile?target=wasm32 ─▶ sandbox: compile.mjs
 │   runs main.wasm in a Web Worker ◀┼── IR + main.js + main.wasm
 │ Run, "on server"  ───────────────┼─▶ POST /run ─▶ sandbox: flowwing-jit
 │                                  ◀┼── output + exit code
 │ LLVM IR tab       ───────────────┼─▶ POST /compile?target=native
 └──────────────────────────────────┘
```

## Requests

| Request | Body | Answer |
|---|---|---|
| `POST /compile?target=wasm32\|native&opt=0..3&wat=1` | the program (text/plain) | JSON from `sandbox/compile.mjs`: `ok`, `stage`, `diagnostics`, `ir`, and for wasm32 `js`, `wasm` (base64), `wat` |
| `POST /run` | `{"code": "...", "input": "..."}` | `{"output": "...", "exitCode": N}`. 124: time limit; 137: killed (memory) |

Both answer any origin (`Access-Control-Allow-Origin: *`): no login or cookie
is involved. Programs are at most 64 KB. `/compile` runs one at a time, up to 8
waiting, and remembers the last 32 results.

## Sandboxes

Every request runs in a throwaway container with no network:

| Image | Used by | Limits | Built from |
|---|---|---|---|
| `flowwing-sandbox` | `/run` | 0.5 CPU, 128 MB, 20 s | the Flow-Wing apt package |
| `flowwing-wasm-sandbox` | `/compile` | 1 CPU, 512 MB, 90 s | `sandbox/Dockerfile`: the apt package, Emscripten 6.0.10, `compile.mjs` |

`flowwing-wasm-sandbox` needs a Flow-Wing release that includes the wasm32
runtime (newer than v1.0.19). Build it from this folder:

```bash
docker build -t flowwing-wasm-sandbox sandbox
```

The deploy scripts build and push both images (`build_portfolio_mac.sh`) and
start them on the server (`deploy-flow-wing.sh`).

## Run it locally

From the repository root:

```bash
make run-website          # http://localhost:8080
```

This builds `server.fg` with this repository's compiler and starts it in
**host mode** (`FLOWWING_PLAYGROUND_SANDBOX=host`): `/compile` and `/run` use
the compiler directly, without Docker. Nothing is sandboxed, so use it only
on your own machine. It needs emsdk (`~/emsdk`, `$EMSDK`, or `emcc` on
`PATH`) for WebAssembly builds.

Then, in another terminal, the docs site, whose playground uses
`http://localhost:8080` when started with `yarn start`:

```bash
make build-wasm-frontend              # the front end for live analysis, once
cd flow-wing-docs && corepack yarn start
# open http://localhost:3000/playground
```

To try the docs against another server, open the playground with
`?server=<url>`, or set `PLAYGROUND_SERVER_URL` when building the docs.

| Environment | Meaning |
|---|---|
| `FLOWWING_PLAYGROUND_SANDBOX` | `docker` (default) or `host` |
| `FLOWWING_PLAYGROUND_COMPILER` | host mode: the FlowWing to use (default `flowwing`) |

The server's own arguments are the analytics settings: `fg-server <mongo-uri> <admin-token>`, both optional.

## Tests

```bash
make test-website         # sandbox/compile.mjs, with this repository's compiler
```

Check a running server by hand:

```bash
curl -s -X POST --data-binary 'println("hi")' 'http://localhost:8080/compile?target=native' | head -c 200
curl -s -X POST -d '{"code": "println(1)", "input": ""}' http://localhost:8080/run
```
