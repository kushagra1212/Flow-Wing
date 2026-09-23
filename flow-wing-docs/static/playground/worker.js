// Runs one compiled Flow-Wing program (Emscripten's main.js + main.wasm) off
// the page's thread and streams its output back.
//
//   page ──{ js, wasm, input? }──────────────────▶ worker
//   page ◀── { type: "output", fd, text }  (many) ── worker
//   page ◀── { type: "exit", code }  or  { type: "crash", message } ── worker
//
// A worker rather than the page itself: a program that loops forever or
// sleeps would otherwise freeze the tab, and Stop is worker.terminate().
// sleep() blocks only this thread, so output already posted keeps appearing.

// Output is buffered per stream and posted a line (or 4 KB) at a time, as
// the program writes it, byte for byte. Emscripten's default prints whole
// lines and adds a newline the program never wrote (see node-host.js).
function outputStream(fd) {
  const decoder = new TextDecoder();
  let pending = [];
  const flush = () => {
    if (pending.length === 0) return;
    const text = decoder.decode(new Uint8Array(pending), { stream: true });
    pending = [];
    if (text) postMessage({ type: "output", fd, text });
  };
  // Emscripten calls this once per byte, and with null to ask for a flush.
  const put = (byte) => {
    if (byte === null) {
      flush();
      return;
    }
    pending.push(byte);
    if (byte === 10 || pending.length >= 4096) flush();
  };
  return { put, flush };
}

let streams = [];
let finished = false;

// A stack overflow is reported the way a native build reports a runtime error
// (see node-host.js, which does the same under Node): the engine's call depth
// ran out (a RangeError), or a task's own stack did (Emscripten's stack check).
const STACK_OVERFLOW =
  "\x1b[91mRuntime Error: Stack Overflow.\n" +
  "  \u25b6 The program recursed deeper than WebAssembly allows.\n" +
  "  \u25b6 WebAssembly shares the JavaScript engine's call stack, which stops\n" +
  "    recursion at about 10,000 to 20,000 calls; a task also has its own stack.\n" +
  "  \u25b6 Reduce the recursion depth, or write it as a loop.\x1b[0m\n";

function isStackOverflow(error) {
  const message = String((error && error.message) || error);
  return (error instanceof RangeError && /call stack/i.test(message)) ||
    /stack overflow/i.test(message);
}

function reportStackOverflow() {
  for (const stream of streams) stream.flush();
  postMessage({ type: "output", fd: 2, text: STACK_OVERFLOW });
  finish({ type: "exit", code: 1 });
}

function finish(message) {
  if (finished) return;
  finished = true;
  for (const stream of streams) stream.flush();
  postMessage(message);
}

// Everything that ends a program other than a normal exit arrives here: a
// wasm trap (RuntimeError), an Emscripten abort, a JavaScript error. A normal
// exit also passes through as an ExitStatus throw after onExit has run.
function onUncaught(error) {
  if (error && error.name === "ExitStatus") return;
  if (isStackOverflow(error)) return reportStackOverflow();
  finish({ type: "crash", message: String((error && error.message) || error) });
}
self.addEventListener("error", (event) => {
  event.preventDefault();
  onUncaught(event.error ?? event.message);
});
self.addEventListener("unhandledrejection", (event) => {
  event.preventDefault();
  onUncaught(event.reason);
});

// What the program reads from standard input: the text given with the run,
// then end of input.
function inputStream(text) {
  const bytes = new TextEncoder().encode(text || "");
  let next = 0;
  return () => (next < bytes.length ? bytes[next++] : null);
}

self.onmessage = ({ data: { js, wasm, input } }) => {
  const stdout = outputStream(1);
  const stderr = outputStream(2);
  streams = [stdout, stderr];

  self.Module = {
    // The page already has the .wasm bytes. Not `wasmBinary`: Emscripten reads
    // only the Module keys in INCOMING_MODULE_JS_API, and that one is not in
    // its default list; instantiateWasm is.
    instantiateWasm: (imports, receiveInstance) => {
      WebAssembly.instantiate(wasm, imports).then(
        ({ instance }) => receiveInstance(instance),
        onUncaught,
      );
      return {};
    },
    stdin: inputStream(input),
    stdout: stdout.put,
    stderr: stderr.put,
    // Emscripten's own notices, not the program's output.
    printErr: (text) => console.warn(text),
    onExit: (code) => finish({ type: "exit", code }),
    onAbort: (what) => {
      if (isStackOverflow(what)) reportStackOverflow();
    },
  };
  importScripts(URL.createObjectURL(new Blob([js], { type: "text/javascript" })));
};
