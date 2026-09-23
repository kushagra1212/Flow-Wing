// What a wasm build run under Node gets from its host, as a native program
// gets it from the operating system (emcc --pre-js):
//
//   - byte-exact stdout and stderr
//   - the process environment
//
// Byte-exact output:
//
// Emscripten's default terminal device prints one line at a time through
// console.log, which appends a newline to whatever is left when the program
// ends. So `print("x")` came out as "x\n" instead of "x". Here the program's
// bytes are written unchanged to file descriptors 1 and 2, as a native build
// writes them.
//
// fs.writeSync, not process.stdout.write: to a pipe the latter is
// asynchronous, and the process.exit that ends the program can cut it off.
//
// Needs -sFORCE_FILESYSTEM=1. Without the file system layer Emscripten uses a
// minimal stdout that never reads Module["stdout"], and whose exit-time flush
// prints pending output by emitting a newline character.
//
// In a browser this file does nothing and the page's own output box is used.
if (typeof process === "object" && typeof require === "function") {
  const fs = require("fs");
  const sink = (fd) => {
    let pending = [];
    // Set once the reader has gone, as with `prog | head -1`. A native
    // program dies quietly of SIGPIPE there; this stops writing quietly
    // instead of throwing EPIPE with a stack trace.
    let closed = false;
    const flush = () => {
      if (pending.length > 0 && !closed) {
        try {
          fs.writeSync(fd, Buffer.from(pending));
        } catch (error) {
          if (error.code !== "EPIPE") {
            throw error;
          }
          closed = true;
        }
      }
      pending = [];
    };
    // Emscripten calls this once per byte, and with null to ask for a flush.
    const put = (byte) => {
      if (byte === null) {
        flush();
        return;
      }
      pending.push(byte);
      if (byte === 10 || pending.length >= 4096) {
        flush();
      }
    };
    return { put, flush };
  };
  const out = sink(1);
  const err = sink(2);
  Module["stdout"] = out.put;
  Module["stderr"] = err.put;

  // The environment. Emscripten gives a program a made-up one (USER=web_user,
  // HOME=/home/web_user, ...), so getenv never saw Node's. The runtime reads
  // FW_GC_STRESS and FW_TASK_STACK_KB, and sys::getEnv reads anything. ENV is
  // Emscripten's table behind getenv; it exists only when the program uses
  // getenv, and it is read once, on first use, which is after preRun.
  Module["preRun"] = [].concat(Module["preRun"] || [], () => {
    if (typeof ENV === "object") {
      Object.assign(ENV, process.env);
    }
  });

  const previousOnExit = Module["onExit"];
  Module["onExit"] = (status) => {
    out.flush();
    err.flush();
    if (previousOnExit) {
      previousOnExit(status);
    }
  };
}
