// Runs one compiled Flow-Wing program (Emscripten's main.js + main.wasm) off
// the page's thread and streams its output back.
//
//   page ──{ js, wasm }──────────────────────────▶ worker
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

self.onmessage = ({ data: { js, wasm } }) => {
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
    stdout: stdout.put,
    stderr: stderr.put,
    // Emscripten's own notices, not the program's output.
    printErr: (text) => console.warn(text),
    onExit: (code) => finish({ type: "exit", code }),
  };
  importScripts(URL.createObjectURL(new Blob([js], { type: "text/javascript" })));
};
