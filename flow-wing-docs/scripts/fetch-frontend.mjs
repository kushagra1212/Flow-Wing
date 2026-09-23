// Puts the Flow-Wing front end built for the browser (flowwing-frontend.js and
// .wasm) into static/playground/frontend/, where the playground loads it to
// show tokens, trees and errors as you type. Runs before `start` and `build`.
//
// Taken from, in order:
//   1. $FLOWWING_FRONTEND_DIR
//   2. ../build/wasm-frontend, a local `make build-wasm-frontend`
//   3. the latest Flow-Wing release on GitHub (the docs site's own build,
//      which has no emsdk)
//
// Never fails the build: without the files the playground still compiles and
// runs programs, and says the live analysis is unavailable.

import { copyFileSync, existsSync, mkdirSync, statSync, writeFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const DOCS = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const TARGET = path.join(DOCS, "static", "playground", "frontend");
const FILES = ["flowwing-frontend.js", "flowwing-frontend.wasm"];
const RELEASE = "https://github.com/kushagra1212/Flow-Wing/releases/latest/download";

function localSource() {
  const candidates = [
    process.env.FLOWWING_FRONTEND_DIR,
    path.join(DOCS, "..", "build", "wasm-frontend"),
  ].filter(Boolean);
  return candidates.find((dir) => FILES.every((file) => existsSync(path.join(dir, file))));
}

function upToDate(dir) {
  return FILES.every((file) => {
    const target = path.join(TARGET, file);
    return existsSync(target) &&
      statSync(target).mtimeMs >= statSync(path.join(dir, file)).mtimeMs;
  });
}

async function main() {
  mkdirSync(TARGET, { recursive: true });

  const dir = localSource();
  if (dir) {
    if (!upToDate(dir)) {
      for (const file of FILES) copyFileSync(path.join(dir, file), path.join(TARGET, file));
      console.log(`[playground] front end copied from ${path.relative(DOCS, dir) || dir}`);
    }
    return;
  }

  if (FILES.every((file) => existsSync(path.join(TARGET, file))) && !process.env.CI) {
    return; // downloaded before; a CI build always takes the latest
  }
  try {
    for (const file of FILES) {
      const response = await fetch(`${RELEASE}/${file}`);
      if (!response.ok) throw new Error(`${file}: HTTP ${response.status}`);
      writeFileSync(path.join(TARGET, file), Buffer.from(await response.arrayBuffer()));
    }
    console.log("[playground] front end downloaded from the latest release");
  } catch (error) {
    console.warn(`[playground] front end not available (${error.message}). ` +
      "The playground will run programs without live analysis.");
  }
}

await main();
