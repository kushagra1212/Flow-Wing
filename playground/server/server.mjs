// HTTP front of the playground compiler (compile.mjs).
//
//   POST /compile   {"source": "..."}  ->  {ok, js, wasm, diagnostics}
//   GET  /health                        ->  {ok: true}
//
//   node playground/server/server.mjs
//
// Environment:
//   FLOWWING         FlowWing binary      (default: build/sdk/bin/FlowWing)
//   PORT             port                 (default: 8787)
//   ALLOWED_ORIGINS  comma-separated list of pages that may call it
//                    (default: the docs site and localhost:3000)
//   MAX_COMPILES     compiles at once     (default: number of CPUs)

import { createServer } from "node:http";
import { availableParallelism } from "node:os";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { LIMITS, PlaygroundCompiler } from "./compile.mjs";

const ROOT = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "../..");
const EXE = process.platform === "win32" ? ".exe" : "";

const config = {
  flowwing: process.env.FLOWWING ?? path.join(ROOT, "build/sdk/bin/FlowWing" + EXE),
  port: Number(process.env.PORT ?? 8787),
  allowedOrigins: (process.env.ALLOWED_ORIGINS ??
    "https://flow-wing-docs.vercel.app,http://localhost:3000")
    .split(",").map((o) => o.trim()).filter(Boolean),
  maxCompiles: Number(process.env.MAX_COMPILES ?? availableParallelism()),
};

const compiler = new PlaygroundCompiler({ flowwing: config.flowwing });

// Each compile is a compiler plus an emcc link, so a burst of requests waits
// here instead of starting one of each per request.
let running = 0;
const waiting = [];
async function withCompileSlot(work) {
  if (running >= config.maxCompiles) {
    await new Promise((resolve) => waiting.push(resolve));
  }
  running++;
  try {
    return await work();
  } finally {
    running--;
    waiting.shift()?.();
  }
}

function send(res, status, body, origin) {
  const headers = { "Content-Type": "application/json" };
  if (origin && config.allowedOrigins.includes(origin)) {
    headers["Access-Control-Allow-Origin"] = origin;
    headers["Vary"] = "Origin";
  }
  res.writeHead(status, headers);
  res.end(JSON.stringify(body));
}

function readBody(req) {
  // JSON escaping can at most double the source, plus the envelope.
  const limit = LIMITS.sourceBytes * 2 + 1024;
  return new Promise((resolve, reject) => {
    const chunks = [];
    let size = 0;
    req.on("data", (chunk) => {
      size += chunk.length;
      if (size > limit) {
        reject(new Error("too large"));
        req.destroy();
        return;
      }
      chunks.push(chunk);
    });
    req.on("end", () => resolve(Buffer.concat(chunks).toString("utf8")));
    req.on("error", reject);
  });
}

const server = createServer(async (req, res) => {
  const origin = req.headers.origin;

  if (req.method === "OPTIONS") {
    res.writeHead(204, {
      "Access-Control-Allow-Origin": config.allowedOrigins.includes(origin) ? origin : "",
      "Access-Control-Allow-Methods": "POST, GET",
      "Access-Control-Allow-Headers": "Content-Type",
      "Access-Control-Max-Age": "86400",
      "Vary": "Origin",
    });
    res.end();
    return;
  }
  if (req.method === "GET" && req.url === "/health") {
    send(res, 200, { ok: true }, origin);
    return;
  }
  if (req.method !== "POST" || req.url !== "/compile") {
    send(res, 404, { ok: false, diagnostics: "Not found." }, origin);
    return;
  }

  let source;
  try {
    source = JSON.parse(await readBody(req)).source;
  } catch {
    send(res, 400, { ok: false, diagnostics: "Expected JSON: {\"source\": \"...\"}." }, origin);
    return;
  }
  if (typeof source !== "string") {
    send(res, 400, { ok: false, diagnostics: "\"source\" must be a string." }, origin);
    return;
  }

  try {
    const result = await withCompileSlot(() => compiler.compile(source));
    send(res, 200, result, origin);
  } catch (error) {
    console.error(error);
    send(res, 500, { ok: false, diagnostics: "The compiler failed unexpectedly." }, origin);
  }
});

server.listen(config.port, () => {
  console.log(`Flow-Wing playground compiler on http://localhost:${config.port}`);
  console.log(`  FlowWing: ${config.flowwing}`);
  console.log(`  pages allowed to call it: ${config.allowedOrigins.join(", ")}`);
});
