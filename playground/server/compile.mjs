// Compiles one Flow-Wing program to WebAssembly for the playground.
//
//   source ──▶ FlowWing --emit=tokens   refuse `bring "file"`
//          ──▶ FlowWing --target=wasm32 --emit=exe
//          ──▶ { ok, js, wasm, diagnostics }
//
// The browser runs the result, so nothing a program does at run time touches
// this machine. Compiling can: `bring "path"` makes the compiler read that
// file, and a diagnostic quotes its lines back. The playground is one file, so
// file brings are refused before compiling. Deploy the server where nothing
// worth reading is on disk anyway (see playground/README.md).

import { spawn } from "node:child_process";
import { createHash } from "node:crypto";
import { mkdtemp, readFile, rm, stat, writeFile } from "node:fs/promises";
import { tmpdir } from "node:os";
import path from "node:path";

export const LIMITS = Object.freeze({
  sourceBytes: 64 * 1024,
  compileMs: 30_000,
  // A program run twice unchanged is compiled once.
  cachedResults: 200,
});

const SOURCE_NAME = "main.fg";

// Modules whose runtime is native only. Bringing one fails at link time with
// wasm-ld naming a symbol, which says nothing useful to a playground user.
const NATIVE_ONLY_MODULES = [
  { module: "file", symbolPrefix: "file_" },
  { module: "vortex", symbolPrefix: "vortex_" },
  { module: "mongo", symbolPrefix: "_mongo_" },
  { module: "raylib", symbolPrefix: "_ray_" },
];

export class PlaygroundCompiler {
  /** @param {{ flowwing: string }} options path to the FlowWing binary */
  constructor({ flowwing }) {
    this.flowwing = flowwing;
    // The wasm runtime every program links against, in the same SDK.
    this.runtime = path.join(path.dirname(flowwing), "..", "lib",
      "wasm32-emscripten", "libflowwing_rt.a");
    this.cache = new Map(); // hash -> result, oldest first
  }

  /**
   * @param {string} source
   * @returns {Promise<{ ok: boolean, js?: string, wasm?: string, diagnostics: string }>}
   *   wasm is base64. diagnostics keeps the compiler's colour codes.
   */
  async compile(source) {
    if (Buffer.byteLength(source, "utf8") > LIMITS.sourceBytes) {
      return failure(`The program is larger than ${LIMITS.sourceBytes / 1024} KB.`);
    }

    // Keyed on the toolchain too: a rebuilt compiler or runtime must not be
    // answered with a program linked by the old one.
    const key = createHash("sha256")
      .update(await this.toolchainStamp())
      .update(source)
      .digest("hex");
    const cached = this.cache.get(key);
    if (cached) {
      return cached;
    }

    const result = await this.compileUncached(source);
    this.remember(key, result);
    return result;
  }

  async toolchainStamp() {
    const times = await Promise.all([this.flowwing, this.runtime].map(
      (file) => stat(file).then((s) => s.mtimeMs, () => 0)));
    return times.join(":") + "\n";
  }

  async compileUncached(source) {
    const dir = await mkdtemp(path.join(tmpdir(), "fw-playground-"));
    try {
      const file = path.join(dir, SOURCE_NAME);
      await writeFile(file, source);

      const refused = await this.refuseFileBrings(dir);
      if (refused) {
        return failure(refused);
      }

      const out = path.join(dir, "out", "main.js");
      const run = await this.run(dir, [
        SOURCE_NAME, "--target=wasm32", "--emit=exe", "--progress=never",
        "--output-dir=build", "-o", out,
      ]);
      const diagnostics = explain(tidy(run.output, dir));
      if (run.timedOut) {
        return failure(`Compiling took longer than ${LIMITS.compileMs / 1000} s.`);
      }
      if (run.code !== 0) {
        return failure(diagnostics);
      }

      const [js, wasm] = await Promise.all([
        readFile(out, "utf8"),
        readFile(out.replace(/\.js$/, ".wasm")),
      ]);
      return { ok: true, js, wasm: wasm.toString("base64"), diagnostics };
    } finally {
      await rm(dir, { recursive: true, force: true });
    }
  }

  // Uses the compiler's own tokens, not a pattern over the text: a comment
  // between `bring` and the path, or "bring" inside a string, is then seen
  // exactly as the parser will see it.
  async refuseFileBrings(dir) {
    const run = await this.run(dir, [
      SOURCE_NAME, "--emit=tokens", "--output-dir=tokens",
    ]);
    if (run.code !== 0) {
      return null; // not tokenizable: the real compile reports why
    }
    const { tokens } = JSON.parse(
      await readFile(path.join(dir, "tokens", "tokens.json"), "utf8"));

    for (let i = 0; i < tokens.length; i++) {
      if (tokens[i].type !== "BringKeyword") {
        continue;
      }
      let next = i + 1;
      if (tokens[next]?.type === "OpenBraceToken") {
        while (next < tokens.length && tokens[next].type !== "CloseBraceToken") {
          next++;
        }
        next += 2; // past `}` and `from`
      }
      if (tokens[next]?.type === "StringLiteralToken") {
        const line = tokens[i].range.start[0] + 1;
        return `Line ${line}: the playground runs a single file, so it can ` +
          `only bring built-in modules (bring vec, bring sys, ...), not ` +
          `${tokens[next].lexeme}.`;
      }
    }
    return null;
  }

  run(cwd, args) {
    return new Promise((resolve) => {
      const child = spawn(this.flowwing, args, { cwd, stdio: ["ignore", "pipe", "pipe"] });
      const chunks = [];
      child.stdout.on("data", (c) => chunks.push(c));
      child.stderr.on("data", (c) => chunks.push(c));
      let timedOut = false;
      const timer = setTimeout(() => {
        timedOut = true;
        child.kill("SIGKILL");
      }, LIMITS.compileMs);
      child.on("close", (code) => {
        clearTimeout(timer);
        resolve({ code, timedOut, output: Buffer.concat(chunks).toString("utf8") });
      });
      child.on("error", (error) => {
        clearTimeout(timer);
        resolve({ code: -1, timedOut, output: String(error) });
      });
    });
  }

  remember(key, result) {
    this.cache.set(key, result);
    if (this.cache.size > LIMITS.cachedResults) {
      this.cache.delete(this.cache.keys().next().value);
    }
  }
}

function failure(diagnostics) {
  return { ok: false, diagnostics };
}

// Diagnostics name the temporary folder the program was compiled in. Show the
// file name the user knows instead.
function tidy(output, dir) {
  return output.split(path.join(dir, SOURCE_NAME)).join(SOURCE_NAME)
    .split(dir + path.sep).join("")
    .split(dir).join(".");
}

function explain(diagnostics) {
  for (const { module, symbolPrefix } of NATIVE_ONLY_MODULES) {
    if (diagnostics.includes(`undefined symbol: ${symbolPrefix}`)) {
      return `The ${module} module runs only in native builds, not in the ` +
        `browser.\n\n${diagnostics}`;
    }
  }
  return diagnostics;
}
