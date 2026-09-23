// Tests for compile.mjs, with the compiler of this repository:
//
//   node --test flowwing-explorer/flow-wing-website/sandbox/compile.test.mjs
//
// FLOWWING picks another compiler. The wasm32 tests need emsdk (~/emsdk,
// $EMSDK, or emcc on PATH) and the wasm32 runtime (make build-wasm-runtime).

import { test } from "node:test";
import assert from "node:assert/strict";
import { spawnSync } from "node:child_process";
import { mkdtempSync, writeFileSync } from "node:fs";
import { tmpdir } from "node:os";
import path from "node:path";
import { fileURLToPath } from "node:url";

const HERE = path.dirname(fileURLToPath(import.meta.url));
const ROOT = path.resolve(HERE, "..", "..", "..");
const FLOWWING = process.env.FLOWWING ||
  path.join(ROOT, "build", "sdk", "bin", process.platform === "win32" ? "FlowWing.exe" : "FlowWing");

const dir = mkdtempSync(path.join(tmpdir(), "fw-compile-test-"));

function compile(source, ...args) {
  const file = path.join(dir, `p${Math.random().toString(36).slice(2)}.fg`);
  writeFileSync(file, source);
  const result = spawnSync(process.execPath, [path.join(HERE, "compile.mjs"), file, ...args], {
    encoding: "utf8",
    env: { ...process.env, FLOWWING },
  });
  return JSON.parse(result.stdout);
}

const stripAnsi = (text) => text.replace(/\x1b\[[0-9;]*m/g, "");

test("a program compiles to IR, js and wasm", () => {
  const reply = compile('println("hi")\n');
  assert.equal(reply.ok, true, reply.diagnostics);
  assert.equal(reply.stage, "done");
  assert.match(reply.compiler, /^FlowWing \d/);
  assert.match(reply.ir, /target triple = "wasm32-unknown-emscripten"/);
  assert.match(reply.ir, /^; ModuleID = 'main\.fg'/, "the temporary folder is not shown");
  const wasm = Buffer.from(reply.wasm, "base64");
  assert.deepEqual([...wasm.subarray(0, 4)], [0x00, 0x61, 0x73, 0x6d], "\\0asm");
  assert.ok(reply.js.length > 1000);
  assert.deepEqual(reply.log.map((s) => s.step), ["ir", "exe", "sizes"]);
});

test("native gives IR only", () => {
  const reply = compile('println("hi")\n', "--target=native", "--opt=2");
  assert.equal(reply.ok, true, reply.diagnostics);
  assert.equal(reply.target, "native");
  assert.equal(reply.opt, 2);
  assert.doesNotMatch(reply.ir, /wasm32/);
  assert.equal(reply.wasm, "");
});

test("--wat adds the text format", () => {
  const reply = compile('println("hi")\n', "--wat");
  assert.equal(reply.ok, true, reply.diagnostics);
  assert.match(reply.wat, /^\(module/);
});

test("a compile error stops at the compile stage, naming main.fg", () => {
  const reply = compile('var x: int = "s"\n');
  assert.equal(reply.ok, false);
  assert.equal(reply.stage, "compile");
  const text = stripAnsi(reply.diagnostics);
  assert.match(text, /\[Error:InitializerExpressionTypeMismatch\]/);
  assert.match(text, /main\.fg/);
  assert.doesNotMatch(text, /fw-compile-/, "the temporary folder is not shown");
});

test("a native-only module is refused by the compiler, with the reason", () => {
  const reply = compile("bring vortex\nvar server: vortex::Server = new vortex::Server()\n");
  assert.equal(reply.ok, false);
  assert.equal(reply.stage, "compile");
  assert.match(stripAnsi(reply.diagnostics), /\[Error:ModuleNotForTarget\].*works only in native builds/);
});

test("options outside the fixed lists are refused, as JSON", () => {
  for (const args of [["--target=x86"], ["--opt=9"], ["--opt=1;rm"], ["--unknown"]]) {
    const reply = compile('println("hi")\n', ...args);
    assert.equal(reply.ok, false, args.join(" "));
    assert.equal(reply.stage, "internal");
  }
});
