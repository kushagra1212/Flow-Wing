// The playground: edit Flow-Wing, press Run, watch the output.
//
//   Run ─▶ compiler.compile(source) ─▶ runProgram(js, wasm) in a Web Worker
//            (compilers.ts)               (runner.ts)
//
// A run can be stopped at any point. Starting another run stops the one before.

import React, { useMemo, useRef, useState } from "react";
import useBaseUrl from "@docusaurus/useBaseUrl";
import useDocusaurusContext from "@docusaurus/useDocusaurusContext";
import Editor from "./Editor";
import { EXAMPLES } from "./examples";
import { serverCompiler } from "./compilers";
import { runProgram } from "./runner";
import { PLAIN, renderAnsi } from "./ansi";
import styles from "./Playground.module.css";

// A program that prints forever would otherwise grow the page until the tab
// runs out of memory. About 5000 lines; at 1 MB a flood stalled the page for
// over half a second while it rendered.
const OUTPUT_LIMIT = 256 * 1024;

type Chunk = { stream: "stdout" | "stderr" | "diagnostics" | "notice"; text: string };

// Adjacent pieces of the same stream become one chunk, so the number of
// chunks follows how often the program switches between stdout and stderr,
// not how many lines it prints.
function appendChunks(chunks: Chunk[], more: Chunk[]): Chunk[] {
  const merged = chunks.slice();
  for (const chunk of more) {
    const last = merged[merged.length - 1];
    if (last && last.stream === chunk.stream) {
      merged[merged.length - 1] = { stream: last.stream, text: last.text + chunk.text };
    } else {
      merged.push(chunk);
    }
  }
  return merged;
}

type Status =
  | { kind: "idle" }
  | { kind: "compiling" }
  | { kind: "running" }
  | { kind: "exited"; code: number; ms: number }
  | { kind: "crashed" }
  | { kind: "failed" }
  | { kind: "stopped" };

function describe(status: Status): string {
  switch (status.kind) {
    case "idle": return "";
    case "compiling": return "Compiling…";
    case "running": return "Running…";
    case "exited": return `Exited with code ${status.code} · ${Math.round(status.ms)} ms`;
    case "crashed": return "Crashed";
    case "failed": return "Did not compile";
    case "stopped": return "Stopped";
  }
}

export default function Playground() {
  const { siteConfig } = useDocusaurusContext();
  const compileUrl = siteConfig.customFields?.playgroundCompileUrl as string;
  const workerUrl = useBaseUrl("/playground/worker.js");
  const compiler = useMemo(() => serverCompiler(compileUrl), [compileUrl]);

  const [source, setSource] = useState(EXAMPLES[0].source);
  const [status, setStatus] = useState<Status>({ kind: "idle" });
  const [output, setOutput] = useState<Chunk[]>([]);

  // Only the latest run may touch the page; an older one that is still
  // compiling or winding down is ignored.
  const currentRun = useRef(0);
  const stopCurrent = useRef<() => void>(() => {});

  const busy = status.kind === "compiling" || status.kind === "running";

  const stop = () => {
    stopCurrent.current();
    currentRun.current++;
    setStatus({ kind: "stopped" });
  };

  const run = async () => {
    stopCurrent.current();
    const runId = ++currentRun.current;
    const isCurrent = () => runId === currentRun.current;

    // A program can print thousands of lines a second. They reach the page
    // at most once per frame; one render per line made the tab stall long
    // before OUTPUT_LIMIT was reached.
    let pending: Chunk[] = [];
    let frame = 0;
    const flush = () => {
      frame = 0;
      const batch = pending;
      pending = [];
      if (isCurrent()) setOutput((chunks) => appendChunks(chunks, batch));
    };
    const append = (chunk: Chunk) => {
      pending.push(chunk);
      if (!frame) frame = requestAnimationFrame(flush);
    };

    setOutput([]);
    setStatus({ kind: "compiling" });

    const abort = new AbortController();
    stopCurrent.current = () => abort.abort();
    let result;
    try {
      result = await compiler.compile(source, abort.signal);
    } catch {
      return; // stopped while compiling
    }
    if (!isCurrent()) return;

    if (!result.ok) {
      append({ stream: "diagnostics", text: result.diagnostics });
      setStatus({ kind: "failed" });
      return;
    }

    const started = performance.now();
    let printed = 0;
    setStatus({ kind: "running" });
    stopCurrent.current = runProgram(workerUrl, result, (event) => {
      if (!isCurrent()) return;
      if (event.type === "output") {
        printed += event.text.length;
        if (printed > OUTPUT_LIMIT) {
          stopCurrent.current();
          append({ stream: "notice", text: "\n[Stopped: the program printed more than 256 KB.]\n" });
          setStatus({ kind: "stopped" });
          return;
        }
        append({ stream: event.fd === 1 ? "stdout" : "stderr", text: event.text });
      } else if (event.type === "exit") {
        setStatus({ kind: "exited", code: event.code, ms: performance.now() - started });
      } else {
        append({ stream: "stderr", text: `\n${event.message}\n` });
        setStatus({ kind: "crashed" });
      }
    });
  };

  // Colour state carries across chunks of the same stream.
  const rendered = useMemo(() => {
    const states: Record<string, typeof PLAIN> = {};
    return output.map((chunk, index) => {
      const { nodes, state } = renderAnsi(chunk.text, states[chunk.stream] ?? PLAIN, `c${index}`);
      states[chunk.stream] = state;
      return <span key={index} className={styles[chunk.stream]}>{nodes}</span>;
    });
  }, [output]);

  return (
    <div className={styles.playground}>
      <div className={styles.toolbar}>
        <label className={styles.examples}>
          <span>Examples</span>
          <select
            defaultValue=""
            onChange={(event) => {
              const example = EXAMPLES[Number(event.target.value)];
              if (example) setSource(example.source);
              event.target.value = "";
            }}
          >
            <option value="" disabled>Choose…</option>
            {EXAMPLES.map((example, index) => (
              <option key={example.title} value={index}>{example.title}</option>
            ))}
          </select>
        </label>
        <button className="button button--primary" onClick={run} title="Ctrl+Enter">
          Run
        </button>
        <button className="button button--secondary" onClick={stop} disabled={!busy}>
          Stop
        </button>
        <span className={styles.status} role="status">{describe(status)}</span>
      </div>

      <div className={styles.panes}>
        <Editor value={source} onChange={setSource} onRun={run} />
        <pre className={styles.output} aria-label="Program output">
          {rendered.length > 0
            ? rendered
            : <span className={styles.placeholder}>Output appears here.</span>}
        </pre>
      </div>

      <p className={styles.note}>
        Your program is compiled to WebAssembly on the Flow-Wing server, then runs
        in your browser.
      </p>
    </div>
  );
}
