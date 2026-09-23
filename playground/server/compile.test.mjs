// node --test playground/server/
//
// Needs a built FlowWing (FLOWWING, default build/sdk/bin/FlowWing) and the
// wasm runtime (make build-wasm-runtime).

import assert from "node:assert/strict";
import { tmpdir } from "node:os";
import path from "node:path";
import { test } from "node:test";
import { fileURLToPath } from "node:url";
import { LIMITS, PlaygroundCompiler } from "./compile.mjs";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../..");
const compiler = new PlaygroundCompiler({
  flowwing: process.env.FLOWWING ??
    path.join(ROOT, "build/sdk/bin/FlowWing" + (process.platform === "win32" ? ".exe" : "")),
});

const plain = (text) => text.replace(/\x1b\[[0-9;]*m/g, "");

test("a program compiles to JavaScript and WebAssembly", async () => {
  const result = await compiler.compile('println("hi")\n');
  assert.equal(result.ok, true, result.diagnostics);
  assert.match(result.js, /WebAssembly/);
  const wasm = Buffer.from(result.wasm, "base64");
  assert.deepEqual([...wasm.subarray(0, 4)], [0x00, 0x61, 0x73, 0x6d]); // "\0asm"
});

test("a compile error names main.fg, never the server's folder", async () => {
  const result = await compiler.compile("println(nope)\n");
  assert.equal(result.ok, false);
  const text = plain(result.diagnostics);
  assert.match(text, /Variable 'nope' does not exist/);
  assert.match(text, /main\.fg/);
  assert.ok(!text.includes(tmpdir()), text);
  assert.ok(!text.includes("fw-playground-"), text);
});

for (const [name, source] of [
  ["bring \"path\"", 'bring "../secret.fg"\n'],
  ["bring {x} from \"path\"", 'bring {x} from "/etc/passwd"\n'],
  ["a comment between bring and the path", 'bring /; hidden\n  "../x.fg"\n'],
]) {
  test(`refuses ${name}`, async () => {
    const result = await compiler.compile(source);
    assert.equal(result.ok, false);
    assert.match(result.diagnostics, /can only bring built-in modules/);
  });
}

test("allows built-in modules, and \"bring\" inside a string", async () => {
  const result = await compiler.compile(
    'bring vec\nbring text\nprintln("bring \\"x.fg\\"")\n');
  assert.equal(result.ok, true, result.diagnostics);
});

test("explains a module that exists only natively", async () => {
  const result = await compiler.compile(
    'bring file\nprintln(file::exists("a.txt"))\n');
  assert.equal(result.ok, false);
  assert.match(result.diagnostics, /The file module runs only in native builds/);
});

test("refuses a program over the size limit without compiling it", async () => {
  const result = await compiler.compile("/;" + "x".repeat(LIMITS.sourceBytes) + "\n");
  assert.equal(result.ok, false);
  assert.match(result.diagnostics, /larger than/);
});

test("compiles an unchanged program once", async () => {
  const source = 'println("cached")\n';
  const first = await compiler.compile(source);
  const second = await compiler.compile(source);
  assert.equal(first, second);
});

test("compiles it again once the toolchain changes", async () => {
  const source = 'println("rebuilt")\n';
  const stamps = ["1:1\n", "2:1\n"];
  const rebuilt = new PlaygroundCompiler({ flowwing: compiler.flowwing });
  rebuilt.toolchainStamp = async () => stamps[0];
  const first = await rebuilt.compile(source);
  stamps.shift();
  const second = await rebuilt.compile(source);
  assert.notEqual(first, second);
  assert.equal(second.ok, true, second.diagnostics);
});
