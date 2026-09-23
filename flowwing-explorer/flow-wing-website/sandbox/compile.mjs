#!/usr/bin/env node
// Compiles one playground program and prints what the compiler made, as one
// JSON document on stdout. Nothing is run.
//
//   node compile.mjs <file.fg> [--target=wasm32|native] [--opt=0..3] [--wat]
//
//   file.fg ─▶ FlowWing --emit=ir          LLVM IR, or the diagnostics
//           ─▶ FlowWing --emit=exe         wasm32 only: main.js + main.wasm
//           ─▶ wasm-dis                    --wat only: the text format
//           ─▶ { ok, stage, compiler, target, opt, log, diagnostics,
//                ir, js, wasm (base64), wat, watTruncated }
//
// server.fg runs this inside the playground sandbox (Dockerfile next to this
// file), or directly on the host for local development. It builds the JSON
// here, not in server.fg, because compiler output carries ANSI colour codes and
// the json module does not escape control characters.
//
// Environment:
//   FLOWWING   the compiler (default: flowwing on PATH)
//   EMSDK      emsdk, for wasm-dis (default: ~/emsdk). FlowWing finds emcc
//              through it too.

import { spawnSync } from "node:child_process";
import { copyFileSync, existsSync, mkdtempSync, readFileSync, realpathSync, rmSync } from "node:fs";
import { homedir, tmpdir } from "node:os";
import path from "node:path";

const STEP_TIMEOUT_MS = 40_000;
// The text format of a small program is ~1 MB, nearly all of it the runtime.
const WAT_LIMIT = 4 * 1024 * 1024;
const IR_LIMIT = 4 * 1024 * 1024;

// Modules whose runtime is native only. Linking one for wasm32 fails with
// wasm-ld naming a symbol, which tells a playground user nothing.
const NATIVE_ONLY_MODULES = [
  { module: "vortex", symbolPrefix: "vortex_" },
  { module: "mongo", symbolPrefix: "_mongo_" },
  { module: "raylib", symbolPrefix: "_ray_" },
];

function parseArgs(argv) {
  const args = { file: null, target: "wasm32", opt: 0, wat: false };
  for (const arg of argv) {
    if (arg.startsWith("--target=")) args.target = arg.slice(9);
    else if (arg.startsWith("--opt=")) args.opt = Number(arg.slice(6));
    else if (arg === "--wat") args.wat = true;
    else if (!arg.startsWith("--") && !args.file) args.file = arg;
    else throw new Error(`unknown argument ${arg}`);
  }
  if (!args.file) throw new Error("no program given");
  if (!["wasm32", "native"].includes(args.target)) throw new Error(`unknown target ${args.target}`);
  if (![0, 1, 2, 3].includes(args.opt)) throw new Error(`unknown optimisation level ${args.opt}`);
  return args;
}

function run(command, args, cwd) {
  const started = performance.now();
  const result = spawnSync(command, args, {
    cwd,
    encoding: "utf8",
    timeout: STEP_TIMEOUT_MS,
    maxBuffer: 16 << 20,
  });
  return {
    code: result.error ? -1 : result.status,
    output: (result.stdout ?? "") + (result.stderr ?? "") +
      (result.error ? String(result.error.message) : ""),
    timedOut: result.error?.code === "ETIMEDOUT",
    ms: Math.round(performance.now() - started),
  };
}

function compile(args) {
  const flowwing = process.env.FLOWWING || "flowwing";
  const emsdk = process.env.EMSDK || path.join(homedir(), "emsdk");
  const log = [];
  const reply = {
    ok: false, stage: "compile", compiler: "", target: args.target, opt: args.opt,
    log, diagnostics: "", ir: "", js: "", wasm: "", wat: "", watTruncated: false,
  };

  // The program is compiled as main.fg in a folder of its own, so diagnostics
  // name the file the user knows, and the build files never touch the input.
  const dir = mkdtempSync(path.join(tmpdir(), "fw-compile-"));
  // The compiler names the folder as it resolved it: on macOS /var is
  // /private/var.
  const tidy = (text) => {
    for (const folder of new Set([realpathSync(dir), dir])) {
      text = text.split(folder + path.sep).join("").split(folder).join(".");
    }
    return text;
  };
  try {
    copyFileSync(args.file, path.join(dir, "main.fg"));

    const version = run(flowwing, ["--version"], dir);
    const number = version.output.match(/Version:\s*(\S+)/);
    reply.compiler = number ? `FlowWing ${number[1]}` : version.output.trim();

    const optFlag = `-O${args.opt}`;
    const ir = run(flowwing, [
      "main.fg", `--target=${args.target}`, "--emit=ir", optFlag,
      "--output-dir=ir", "--progress=never",
    ], dir);
    log.push({ step: "ir", ms: ir.ms, ok: ir.code === 0 });
    if (ir.timedOut) {
      reply.diagnostics = `Compiling took longer than ${STEP_TIMEOUT_MS / 1000} s.`;
      return reply;
    }
    if (ir.code !== 0) {
      reply.diagnostics = tidy(ir.output);
      return reply;
    }
    const irFile = path.join(dir, "ir", "llvm_ir.ll");
    reply.ir = existsSync(irFile) ? tidy(readFileSync(irFile, "utf8")).slice(0, IR_LIMIT) : "";

    if (args.target !== "wasm32") {
      reply.ok = true;
      reply.stage = "done";
      return reply;
    }

    reply.stage = "link";
    const exe = run(flowwing, [
      "main.fg", "--target=wasm32", "--emit=exe", optFlag,
      "--output-dir=build", "-o", "out/main.js", "--progress=never",
    ], dir);
    log.push({ step: "exe", ms: exe.ms, ok: exe.code === 0 });
    if (exe.timedOut) {
      reply.diagnostics = `Linking took longer than ${STEP_TIMEOUT_MS / 1000} s.`;
      return reply;
    }
    if (exe.code !== 0) {
      reply.diagnostics = explain(tidy(exe.output));
      return reply;
    }
    const js = readFileSync(path.join(dir, "out", "main.js"), "utf8");
    const wasm = readFileSync(path.join(dir, "out", "main.wasm"));
    reply.js = js;
    reply.wasm = wasm.toString("base64");
    log.push({ step: "sizes", js: js.length, wasm: wasm.length });

    if (args.wat) {
      const wat = run(path.join(emsdk, "upstream", "bin", "wasm-dis"), ["out/main.wasm"], dir);
      log.push({ step: "wat", ms: wat.ms, ok: wat.code === 0 });
      if (wat.code === 0) {
        reply.wat = wat.output.slice(0, WAT_LIMIT);
        reply.watTruncated = wat.output.length > WAT_LIMIT;
      }
    }

    reply.ok = true;
    reply.stage = "done";
    reply.diagnostics = tidy(exe.output).trim() === "" ? "" : tidy(exe.output);
    return reply;
  } finally {
    rmSync(dir, { recursive: true, force: true });
  }
}

function explain(diagnostics) {
  for (const { module, symbolPrefix } of NATIVE_ONLY_MODULES) {
    if (diagnostics.includes(`undefined symbol: ${symbolPrefix}`)) {
      return `The ${module} module runs only in native builds, not in the browser. ` +
        `Switch the playground to "Run on server".\n\n${diagnostics}`;
    }
  }
  return diagnostics;
}

let reply;
try {
  reply = compile(parseArgs(process.argv.slice(2)));
} catch (error) {
  reply = { ok: false, stage: "internal", log: [], diagnostics: String(error?.message ?? error) };
}
process.stdout.write(JSON.stringify(reply));
