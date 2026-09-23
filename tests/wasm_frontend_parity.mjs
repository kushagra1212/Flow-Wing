#!/usr/bin/env node
// Checks the browser build of the front end (scripts/wasm/build-frontend.sh)
// against the native compiler: for every fixture, `--emit=sem` must exit the
// same way, print the same diagnostics, and write the same semantic tree.
//
//   node tests/wasm_frontend_parity.mjs --bin build/sdk/bin/FlowWing
//   make test-wasm-frontend
//
// The wasm front end reads each fixture at its real path, with the files it
// brings, through NODEFS mounts of the real disk (as scripts/wasm/node-host.js
// does for programs).

import { execFile } from "node:child_process";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { createRequire } from "node:module";
import { fileURLToPath } from "node:url";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

function parseArgs() {
  const args = { bin: null, frontend: "build/wasm-frontend/flowwing-frontend.js",
                 dirs: [], jobs: os.availableParallelism(), verbose: false };
  const argv = process.argv.slice(2);
  for (let i = 0; i < argv.length; i++) {
    const [flag, inline] = argv[i].split("=");
    const value = () => inline ?? argv[++i];
    if (flag === "--bin") args.bin = value();
    else if (flag === "--frontend") args.frontend = value();
    else if (flag === "--dir") args.dirs.push(value());
    else if (flag === "--jobs") args.jobs = Number(value());
    else if (flag === "--verbose") args.verbose = true;
    else throw new Error(`unknown option ${argv[i]}`);
  }
  if (!args.bin) throw new Error("--bin <FlowWing> is required");
  if (args.dirs.length === 0) args.dirs.push("tests/fixtures/LatestTests");
  return args;
}

// Both sides decode the same raw bytes the same way. The diagnostic printer
// colours a quoted source line byte by byte, which splits multi-byte
// characters, and Node and Emscripten's own line printer repair broken UTF-8
// differently.
const decode = (stdout, stderr) => Buffer.concat([stdout, stderr]).toString("utf8");

const stripAnsi = (text) => text.replace(/\x1b\[[0-9;?]*[ -/]*[@-~]/g, "");

function fixturesIn(dir) {
  const found = [];
  for (const entry of fs.readdirSync(dir, { withFileTypes: true })) {
    const full = path.join(dir, entry.name);
    if (entry.isDirectory()) found.push(...fixturesIn(full));
    else if (entry.name.endsWith(".fg")) found.push(full);
  }
  return found;
}

// ---- native ---------------------------------------------------------------

function runNative(bin, fixture, outDir) {
  return new Promise((resolve) => {
    execFile(bin, [fixture, "--emit=sem", `--output-dir=${outDir}`, "--progress=never"],
      { timeout: 30_000, maxBuffer: 16 << 20, encoding: "buffer" },
      (error, stdout, stderr) => {
        resolve({ status: error ? (error.code ?? 1) : 0, text: decode(stdout, stderr) });
      });
  });
}

// ---- wasm -----------------------------------------------------------------

function mountHost(instance) {
  const { FS } = instance;
  const { NODEFS } = FS.filesystems;
  // Emscripten's own /dev and /proc stay; /lib holds the embedded standard
  // modules, which a Linux host's /lib would hide.
  const keep = new Set(["dev", "proc", "lib"]);
  const removeTree = (dir) => {
    for (const name of FS.readdir(dir)) {
      if (name === "." || name === "..") continue;
      const child = `${dir}/${name}`;
      if (FS.isDir(FS.stat(child).mode)) removeTree(child);
      else FS.unlink(child);
    }
    FS.rmdir(dir);
  };
  for (const name of fs.readdirSync("/")) {
    if (keep.has(name)) continue;
    const dir = `/${name}`;
    try {
      if (!fs.statSync(dir).isDirectory()) continue;
    } catch {
      continue;
    }
    if (FS.analyzePath(dir).exists) removeTree(dir);
    FS.mkdir(dir);
    FS.mount(NODEFS, { root: dir }, dir);
  }
}

async function runWasm(createFrontend, wasmModule, fixture, outDir) {
  const stdout = [];
  const stderr = [];
  const instance = await createFrontend({
    // Byte by byte, called with null to flush.
    stdout: (byte) => { if (byte !== null) stdout.push(byte); },
    stderr: (byte) => { if (byte !== null) stderr.push(byte); },
    instantiateWasm: (imports, receive) => {
      WebAssembly.instantiate(wasmModule, imports).then((inst) => receive(inst));
      return {};
    },
  });
  instance.ENV.FLOWWING_MODULES_PATH = "/lib/modules";
  mountHost(instance);
  instance.FS.chdir(path.dirname(fixture));
  let status;
  try {
    status = instance.callMain([fixture, "--emit=sem", `--output-dir=${outDir}`, "--progress=never"]);
  } catch (error) {
    status = typeof error?.status === "number" ? error.status : `threw ${error}`;
  }
  return { status, text: decode(Buffer.from(stdout), Buffer.from(stderr)) };
}

// ---- comparison -----------------------------------------------------------

function readTree(outDir) {
  try {
    const tree = JSON.parse(fs.readFileSync(path.join(outDir, "semantic_tree.json"), "utf8"));
    delete tree.generatedAt;
    return JSON.stringify(tree);
  } catch {
    return null;
  }
}

function normalise(text, outDir, modulesDir) {
  return stripAnsi(text)
    .split(outDir).join("<out>")
    .split(modulesDir).join("/lib/modules")
    .replace(/\s+$/, "");
}

function firstDifference(a, b) {
  let i = 0;
  while (i < a.length && a[i] === b[i]) i++;
  return `at ${i}: native ${JSON.stringify(a.slice(i, i + 50))}, wasm ${JSON.stringify(b.slice(i, i + 50))}`;
}

async function main() {
  const args = parseArgs();
  const bin = path.resolve(args.bin);
  const modulesDir = path.join(path.dirname(bin), "..", "lib", "modules");
  const frontendJs = path.resolve(args.frontend);
  const require = createRequire(import.meta.url);
  const createFrontend = require(frontendJs);
  const wasmModule = await WebAssembly.compile(
    fs.readFileSync(frontendJs.replace(/\.js$/, ".wasm")));

  const fixtures = args.dirs.flatMap((d) => fixturesIn(path.resolve(ROOT, d))).sort();
  const work = fs.mkdtempSync(path.join(os.tmpdir(), "fw-frontend-parity-"));
  console.log(`Comparing the wasm front end with ${path.relative(ROOT, bin)} on ` +
              `${fixtures.length} fixtures (--emit=sem)`);

  // Native runs in parallel; each wasm run is one fresh instance, in order.
  const native = new Array(fixtures.length);
  let next = 0;
  await Promise.all(Array.from({ length: args.jobs }, async () => {
    while (next < fixtures.length) {
      const i = next++;
      native[i] = await runNative(bin, fixtures[i], path.join(work, `n${i}`));
    }
  }));

  const failures = [];
  for (let i = 0; i < fixtures.length; i++) {
    const nativeOut = path.join(work, `n${i}`);
    const wasmOut = path.join(work, `w${i}`);
    const wasm = await runWasm(createFrontend, wasmModule, fixtures[i], wasmOut);
    const name = path.relative(ROOT, fixtures[i]);
    const nativeText = normalise(native[i].text, nativeOut, modulesDir);
    const wasmText = normalise(wasm.text, wasmOut, modulesDir);
    let problem = null;
    if (native[i].status !== wasm.status) {
      problem = `exit status: native ${native[i].status}, wasm ${wasm.status}`;
    } else if (nativeText !== wasmText) {
      problem = `output differs ${firstDifference(nativeText, wasmText)}`;
    } else if (wasm.status === 0) {
      const nativeTree = readTree(nativeOut);
      const wasmTree = readTree(wasmOut);
      if (nativeTree === null || wasmTree === null) {
        problem = `no semantic tree from ${nativeTree === null ? "native" : "wasm"}`;
      } else if (nativeTree !== wasmTree) {
        problem = `semantic tree differs ${firstDifference(nativeTree, wasmTree)}`;
      }
    }
    if (problem) {
      failures.push(name);
      console.log(`  [FAIL] ${name}  ${problem}`);
    } else if (args.verbose) {
      console.log(`  [PASS] ${name}`);
    }
  }

  fs.rmSync(work, { recursive: true, force: true });
  console.log("-".repeat(60));
  console.log(`${fixtures.length} fixtures: ${fixtures.length - failures.length} match, ` +
              `${failures.length} differ`);
  process.exitCode = failures.length ? 1 : 0;
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 2;
});
