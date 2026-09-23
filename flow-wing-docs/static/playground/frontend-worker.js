// Runs the Flow-Wing front end (lexer, parser, semantic analysis) off the
// page's thread, on every edit. It is the compiler's own code built to
// WebAssembly (scripts/wasm/build-frontend.sh in the Flow-Wing repo), so the
// tokens, trees and errors are exactly the ones `flowwing --emit=...` gives.
//
//   page ──{ id, source, target }──────────────────────────▶ worker
//   page ◀──{ id, stages: [{ emit, ok, ms, json, output }] }── worker
//   page ◀──{ id, unavailable: message }──  (the files did not load)
//
// Stages run in order, tokens → ast → sem, and stop at the first that fails:
// a program that does not parse has no semantic tree to show. `target` is the
// build the program is checked for ("wasm32" or "native"): `bring dom` is
// right for one and an error for the other.

const STAGES = [
  { emit: "tokens", file: "tokens.json" },
  { emit: "ast", file: "ast.json" },
  { emit: "sem", file: "semantic_tree.json" },
];

let factory = null; // createFlowWingFrontend
let compiled = null; // Promise<WebAssembly.Module>, compiled once

function load() {
  if (!compiled) {
    importScripts("frontend/flowwing-frontend.js");
    factory = self.createFlowWingFrontend;
    compiled = fetch("frontend/flowwing-frontend.wasm").then((response) => {
      if (!response.ok) throw new Error(`flowwing-frontend.wasm: HTTP ${response.status}`);
      return WebAssembly.compileStreaming
        ? WebAssembly.compileStreaming(response)
        : response.arrayBuffer().then((bytes) => WebAssembly.compile(bytes));
    });
  }
  return compiled;
}

// One stage, on a fresh instance: main() runs once per instance.
async function runStage(module, source, target, stage) {
  const bytes = [];
  const collect = (byte) => {
    if (byte !== null) bytes.push(byte);
  };
  const instance = await factory({
    instantiateWasm: (imports, receive) => {
      WebAssembly.instantiate(module, imports).then((result) => receive(result));
      return {};
    },
    stdout: collect,
    stderr: collect,
  });
  instance.ENV.FLOWWING_MODULES_PATH = "/lib/modules";
  instance.FS.writeFile("/main.fg", source);

  const started = performance.now();
  let status;
  try {
    status = instance.callMain([
      "/main.fg", `--emit=${stage.emit}`, `--target=${target}`, "--output-dir=/out", "--progress=never",
    ]);
  } catch (error) {
    status = typeof error?.status === "number" ? error.status : 1;
  }
  const ms = performance.now() - started;
  const output = new TextDecoder().decode(new Uint8Array(bytes));

  let json = null;
  if (status === 0) {
    try {
      json = JSON.parse(instance.FS.readFile(`/out/${stage.file}`, { encoding: "utf8" }));
    } catch {
      status = 1;
    }
  }
  return { emit: stage.emit, ok: status === 0, ms, json, output };
}

self.onmessage = async ({ data: { id, source, target } }) => {
  let module;
  try {
    module = await load();
  } catch (error) {
    postMessage({ id, unavailable: String(error?.message ?? error) });
    return;
  }
  const stages = [];
  for (const stage of STAGES) {
    const result = await runStage(module, source, target === "native" ? "native" : "wasm32", stage);
    stages.push(result);
    if (!result.ok) break;
  }
  postMessage({ id, stages });
};
