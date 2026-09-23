// The panels that are not a compiler stage: the program's output, the
// problems found, and the log of everything the page did.

import React, { useMemo } from "react";
import { PLAIN, renderAnsi } from "./ansi";
import type { Problem } from "./diagnostics";
import { SourceMap, describePoint } from "./source";
import styles from "./Playground.module.css";

// ---- Output ----

export type Chunk = { stream: "stdout" | "stderr" | "diagnostics" | "notice"; text: string };

// Adjacent pieces of the same stream become one chunk, so the number of
// chunks follows how often the program switches between stdout and stderr,
// not how many lines it prints.
export function appendChunks(chunks: Chunk[], more: Chunk[]): Chunk[] {
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

export function OutputPanel({ chunks, footer }: { chunks: Chunk[]; footer: string }) {
  // Colour state carries across chunks of the same stream.
  const rendered = useMemo(() => {
    const states: Record<string, typeof PLAIN> = {};
    return chunks.map((chunk, index) => {
      const { nodes, state } = renderAnsi(chunk.text, states[chunk.stream] ?? PLAIN, `c${index}`);
      states[chunk.stream] = state;
      return <span key={index} className={styles[chunk.stream]}>{nodes}</span>;
    });
  }, [chunks]);

  return (
    <>
      <pre className={styles.output} aria-label="Program output">
        {rendered.length > 0
          ? rendered
          : <span className={styles.placeholder}>Press Run (Ctrl+Enter). The output appears here.</span>}
      </pre>
      {footer && <div className={styles.outputFooter}>{footer}</div>}
    </>
  );
}

// ---- Problems ----

export type SourcedProblem = Problem & { from: string };

export function ProblemsPanel({ problems, map, onPick }: {
  problems: SourcedProblem[];
  map: SourceMap;
  onPick: (problem: SourcedProblem) => void;
}) {
  if (problems.length === 0) {
    return <p className={styles.empty}>No problems. The compiler checks the program as you type.</p>;
  }
  return (
    <ul className={styles.problems}>
      {problems.map((problem, index) => (
        <li key={index} className={styles[`problem_${problem.severity}`]}>
          <button
            type="button"
            className={styles.problemHead}
            onClick={() => onPick(problem)}
            disabled={!problem.at}
          >
            <span className={styles.problemIcon} aria-hidden="true">{problem.severity === "error" ? "✕" : "!"}</span>
            <span className={styles.problemMessage}>{problem.message}</span>
            <span className={styles.problemWhere}>
              {problem.code}
              {problem.at && ` · line ${describePoint(map, problem.at).replace(":", ", column ")}`}
              {` · ${problem.from}`}
            </span>
          </button>
          {problem.notes.length > 0 && (
            <ul className={styles.problemNotes}>
              {problem.notes.map((note, i) => <li key={i}>{note}</li>)}
            </ul>
          )}
          <details className={styles.details}>
            <summary>The compiler's full message</summary>
            <pre className={styles.output}>{renderAnsi(problem.raw.trim(), PLAIN, `p${index}`).nodes}</pre>
          </details>
        </li>
      ))}
    </ul>
  );
}

// ---- Logs ----

export type LogLevel = "info" | "ok" | "warn" | "error";
export type LogEntry = { at: number; level: LogLevel; source: string; text: string };

function clock(at: number): string {
  const time = new Date(at);
  return time.toLocaleTimeString([], { hour12: false }) + "." + String(time.getMilliseconds()).padStart(3, "0");
}

export function LogsPanel({ entries, onClear }: { entries: LogEntry[]; onClear: () => void }) {
  const copy = () => navigator.clipboard.writeText(
    entries.map((entry) => `${clock(entry.at)}  ${entry.level.padEnd(5)} ${entry.source.padEnd(9)} ${entry.text}`).join("\n"));
  return (
    <>
      <div className={styles.viewBar}>
        <span className={styles.viewTitle}>{entries.length} entries</span>
        <span className={styles.viewHint}>Every step: live analysis, server requests, the program's run.</span>
        <span className={styles.spacer} />
        <button type="button" className={styles.miniButton} onClick={copy} disabled={!entries.length}>Copy</button>
        <button type="button" className={styles.miniButton} onClick={onClear} disabled={!entries.length}>Clear</button>
      </div>
      <ol className={styles.logs} aria-live="off">
        {entries.map((entry, index) => (
          <li key={index} className={styles[`log_${entry.level}`]}>
            <time className={styles.logTime}>{clock(entry.at)}</time>
            <span className={styles.logSource}>{entry.source}</span>
            <span className={styles.logText}>{entry.text}</span>
          </li>
        ))}
      </ol>
    </>
  );
}
