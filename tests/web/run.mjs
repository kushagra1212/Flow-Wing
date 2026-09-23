#!/usr/bin/env node
// Runs Flow-Wing programs that use the js and dom modules in a simulated page
// (jsdom), and checks what they do to it.
//
//   node tests/web/run.mjs --bin build/sdk/bin/FlowWing [--filter text] [--keep]
//   make test-web
//
// A fixture is a folder in tests/fixtures/WebTests:
//
//   app.fg       the program, built with --target=wasm32
//   page.html    the page it runs in (default: an empty body)
//   expect.txt   what it prints, checked when the test is done
//   test.mjs     optional: drives the page and checks it
//
//     export async function setup(t) { ... }   before the program starts
//     export default async function (t) { ... } after it has started
//
//   t.window, t.document    the page
//   t.$(selector)           document.querySelector
//   t.click(selector)       a click on the element
//   t.type(selector, text)  sets a field's value and fires "input"
//   t.key(selector, key)    a keydown with that key
//   t.wait(ms)              lets timers and the program run
//   t.until(check, ms)      waits for check() to be true
//   t.output()              what the program has printed so far
//   t.exited()              the exit code, or null while it runs
//   t.expect(ok, message)   fails the test unless ok
//   t.expectText(selector, text)
//
// Without test.mjs, the program runs until it exits (or 5 s pass).

import { execFileSync } from "node:child_process";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";
import { JSDOM } from "jsdom";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..", "..");
const FIXTURES = path.join(ROOT, "tests", "fixtures", "WebTests");
const RUN_LIMIT_MS = 5000;

function parseArgs() {
  const args = { bin: null, filter: "", keep: false };
  const argv = process.argv.slice(2);
  for (let i = 0; i < argv.length; i++) {
    const [flag, inline] = argv[i].split("=");
    const value = () => inline ?? argv[++i];
    if (flag === "--bin") args.bin = path.resolve(value());
    else if (flag === "--filter") args.filter = value();
    else if (flag === "--keep") args.keep = true;
    else throw new Error(`unknown option ${argv[i]}`);
  }
  if (!args.bin) throw new Error("--bin <FlowWing> is required");
  return args;
}

const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms));

class Failure extends Error {}

function build(bin, fixture, work) {
  const out = path.join(work, "app.js");
  try {
    execFileSync(bin, [
      path.join(fixture, "app.fg"), "--target=wasm32", "--emit=exe",
      "--progress=never", `--output-dir=${path.join(work, "build")}`, "-o", out,
    ], { cwd: fixture, stdio: "pipe", timeout: 120_000 });
  } catch (error) {
    const text = String(error.stdout ?? "") + String(error.stderr ?? "");
    throw new Failure(`did not build:\n${text.replace(/\x1b\[[0-9;]*m/g, "")}`);
  }
  return { js: fs.readFileSync(out, "utf8"), wasm: fs.readFileSync(out.replace(/\.js$/, ".wasm")) };
}

async function runFixture(bin, name, work) {
  const fixture = path.join(FIXTURES, name);
  const program = build(bin, fixture, work);
  const pagePath = path.join(fixture, "page.html");
  const html = fs.existsSync(pagePath)
    ? fs.readFileSync(pagePath, "utf8")
    : "<!doctype html><html><body></body></html>";

  const dom = new JSDOM(html, {
    runScripts: "outside-only",
    pretendToBeVisual: true,
    url: "http://localhost/",
  });
  const { window } = dom;
  const printed = [];
  let exitCode = null;
  let crash = null;

  const $ = (selector) => {
    const element = window.document.querySelector(selector);
    if (!element) throw new Failure(`no element matches ${selector}`);
    return element;
  };
  const t = {
    window,
    document: window.document,
    $,
    click: (selector) => $(selector).click(),
    type: (selector, text) => {
      const element = $(selector);
      element.value = text;
      element.dispatchEvent(new window.Event("input", { bubbles: true }));
    },
    key: (selector, key) => {
      $(selector).dispatchEvent(new window.KeyboardEvent("keydown", { key, bubbles: true }));
    },
    wait: (ms = 0) => sleep(ms),
    until: async (check, ms = 2000) => {
      const deadline = Date.now() + ms;
      while (!check()) {
        if (crash) throw new Failure(`the program crashed: ${crash}`);
        if (Date.now() > deadline) throw new Failure(`timed out after ${ms} ms waiting for ${check}`);
        await sleep(5);
      }
    },
    output: () => printed.join("\n") + (printed.length ? "\n" : ""),
    exited: () => exitCode,
    expect: (ok, message) => {
      if (!ok) throw new Failure(message);
    },
    expectText: (selector, text) => {
      const actual = $(selector).textContent;
      if (actual !== text) throw new Failure(`${selector} holds ${JSON.stringify(actual)}, expected ${JSON.stringify(text)}`);
    },
  };

  const testPath = path.join(fixture, "test.mjs");
  const test = fs.existsSync(testPath) ? await import(pathToFileURL(testPath).href) : null;
  if (test?.setup) await test.setup(t);

  let started = false;
  window.Module = {
    // The page has the bytes already; not wasmBinary, which Emscripten does
    // not read from Module by default (see static/playground/worker.js).
    instantiateWasm: (imports, receive) => {
      WebAssembly.instantiate(program.wasm, imports).then(
        ({ instance }) => receive(instance),
        (error) => { crash = String(error); },
      );
      return {};
    },
    print: (line) => printed.push(line),
    printErr: (line) => printed.push(line),
    onRuntimeInitialized: () => { started = true; },
    onExit: (code) => { exitCode = code; },
    onAbort: (what) => { crash = String(what); },
  };
  window.addEventListener("error", (event) => {
    if (event.error?.name !== "ExitStatus") crash = String(event.error ?? event.message);
  });
  window.eval(program.js);
  await t.until(() => started || exitCode !== null, RUN_LIMIT_MS);

  if (test?.default) {
    await test.default(t);
  } else {
    await t.until(() => exitCode !== null, RUN_LIMIT_MS);
  }
  if (crash) throw new Failure(`the program crashed: ${crash}`);

  const expectPath = path.join(fixture, "expect.txt");
  if (fs.existsSync(expectPath)) {
    const expected = fs.readFileSync(expectPath, "utf8");
    const actual = t.output();
    if (actual !== expected) {
      throw new Failure(`printed:\n${actual}\nexpected:\n${expected}`);
    }
  }
  window.close();
}

async function main() {
  const args = parseArgs();
  const names = fs.readdirSync(FIXTURES, { withFileTypes: true })
    .filter((entry) => entry.isDirectory() && entry.name.includes(args.filter))
    .map((entry) => entry.name)
    .sort();
  const workRoot = fs.mkdtempSync(path.join(os.tmpdir(), "fw-web-tests-"));
  console.log(`Running ${names.length} web fixtures in jsdom`);

  const failures = [];
  for (const name of names) {
    const work = path.join(workRoot, name);
    fs.mkdirSync(work, { recursive: true });
    const started = performance.now();
    try {
      await runFixture(args.bin, name, work);
      console.log(`  [PASS] ${name} (${Math.round(performance.now() - started)} ms)`);
    } catch (error) {
      failures.push(name);
      const message = error instanceof Failure ? error.message : (error?.stack ?? String(error));
      console.log(`  [FAIL] ${name}\n         ${message.replace(/\n/g, "\n         ")}`);
    }
  }

  if (!args.keep) fs.rmSync(workRoot, { recursive: true, force: true });
  console.log("-".repeat(60));
  console.log(failures.length
    ? `${failures.length} of ${names.length} web fixtures failed: ${failures.join(", ")}`
    : `All ${names.length} web fixtures passed.`);
  // jsdom keeps timers alive; the verdict is in, so leave.
  process.exit(failures.length ? 1 : 0);
}

main().catch((error) => {
  console.error(error);
  process.exit(2);
});
