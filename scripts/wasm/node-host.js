// What a wasm build run under Node gets from its host, as a native program
// gets it from the operating system (emcc --pre-js):
//
//   - byte-exact stdout and stderr
//   - the process environment
//   - the real file system
//   - a stack overflow reported as a Flow-Wing runtime error
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

  // The real file system. Emscripten's own lives in memory: a file a program
  // writes is gone when it exits, and the files around it are not there to
  // read. So the host's top-level folders are mounted into it at the same
  // paths, and the program starts in the real working folder: file:: then
  // reads and writes the disk at the paths a native build would use.
  //
  // /dev and /proc stay Emscripten's own; stdin, stdout and stderr live there.
  // Windows paths start with a drive letter, which has no place in this tree,
  // so there only the working folder is mounted, which covers relative paths.
  // NODEFS comes from -lnodefs.js; FS and NODEFS exist only when the program
  // can reach the file system at all.
  Module["preRun"].push(() => {
    if (typeof FS !== "object" || typeof NODEFS !== "object") {
      return;
    }
    if (process.platform === "win32") {
      FS.mkdir("/cwd");
      FS.mount(NODEFS, { root: process.cwd() }, "/cwd");
      FS.chdir("/cwd");
      return;
    }
    // Emscripten creates /tmp and /home itself; the host's replace them.
    const removeTree = (dir) => {
      for (const name of FS.readdir(dir)) {
        if (name === "." || name === "..") continue;
        const child = dir + "/" + name;
        if (FS.isDir(FS.stat(child).mode)) removeTree(child);
        else FS.unlink(child);
      }
      FS.rmdir(dir);
    };
    for (const name of fs.readdirSync("/")) {
      if (name === "dev" || name === "proc") continue;
      const dir = "/" + name;
      let isDirectory = false;
      try {
        isDirectory = fs.statSync(dir).isDirectory(); // follows /tmp -> private/tmp
      } catch (error) {
        continue;
      }
      if (!isDirectory) continue;
      if (FS.analyzePath(dir).exists) removeTree(dir);
      FS.mkdir(dir);
      FS.mount(NODEFS, { root: dir }, dir);
    }
    FS.chdir(process.cwd());
  });

  // A stack overflow, reported the way a native build reports a runtime
  // error rather than as a JavaScript stack trace. WebAssembly runs out of
  // stack in two ways: the JavaScript engine's own call depth (a RangeError
  // thrown through the program), or a task's stack, which Emscripten's stack
  // check catches and aborts on. Any other error keeps Node's full report.
  const stackOverflow = [
    "\x1b[91mRuntime Error: Stack Overflow.",
    "  \u25b6 The program recursed deeper than WebAssembly allows.",
    "  \u25b6 WebAssembly shares the JavaScript engine's call stack, which stops",
    "    recursion at about 10,000 to 20,000 calls; a task also has its own stack.",
    "  \u25b6 Reduce the recursion depth, or write it as a loop.\x1b[0m",
    "",
  ].join("\n");
  const reportStackOverflow = () => {
    out.flush();
    err.flush();
    try {
      fs.writeSync(2, stackOverflow);
    } catch (error) {
      // stderr is gone; the exit status still says what happened.
    }
    process.exit(1);
  };
  const isStackOverflow = (error) =>
    (error instanceof RangeError && /call stack/i.test(error.message)) ||
    /stack overflow/i.test(String(error && error.message));
  for (const event of ["uncaughtException", "unhandledRejection"]) {
    process.on(event, (error) => {
      if (isStackOverflow(error)) reportStackOverflow();
      // What Node would have printed had nothing been listening.
      process.stderr.write(String((error && error.stack) || error) + "\n");
      process.exit(1);
    });
  }
  // Emscripten calls this before printing its own "Aborted(...)" line, so
  // ending here keeps that line out of the program's output.
  const previousOnAbort = Module["onAbort"];
  Module["onAbort"] = (what) => {
    if (/stack overflow/i.test(String(what))) reportStackOverflow();
    if (previousOnAbort) previousOnAbort(what);
  };

  const previousOnExit = Module["onExit"];
  Module["onExit"] = (status) => {
    out.flush();
    err.flush();
    if (previousOnExit) {
      previousOnExit(status);
    }
  };
}
