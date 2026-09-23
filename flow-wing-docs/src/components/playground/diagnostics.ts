// The compiler's diagnostics, as structured problems. It prints them for a
// terminal:
//
//   [Error:VariableNotFound] : Line 3:14  "Variable 'zz' does not exist."
//   ...
//   [Note] Check for typos ...
//   [Help] Declare the variable ...
//
// with colour codes, a quoted snippet, and lines and columns counted from 0.

import type { Point } from "./source";

export type Problem = {
  severity: "error" | "warning";
  code: string;
  message: string;
  at: Point | null; // null: the diagnostic names no place, e.g. a link error
  notes: string[];
  raw: string; // the compiler's own text, colours included
};

export function stripAnsi(text: string): string {
  return text.replace(/\x1b\[[0-9;?]*[ -/]*[@-~]/g, "");
}

const HEADER = /^\[(Error|Warning):(\w+)\]\s*:\s*Line\s+(\d+):(\d+)\s+"(.*)"\s*$/;
const NOTE = /^\[(Note|Help)\]\s*(.*)$/;

export function parseDiagnostics(text: string, fallbackCode = "Error"): Problem[] {
  if (!text.trim()) return [];
  const lines = stripAnsi(text).split("\n");
  const problems: Problem[] = [];
  for (const line of lines) {
    const header = HEADER.exec(line.trim());
    if (header) {
      problems.push({
        severity: header[1] === "Warning" ? "warning" : "error",
        code: header[2],
        message: header[5],
        at: [Number(header[3]), Number(header[4])],
        notes: [],
        raw: text,
      });
      continue;
    }
    const note = NOTE.exec(line.trim());
    if (note && problems.length > 0) {
      problems[problems.length - 1].notes.push(note[2]);
    }
  }
  if (problems.length === 0) {
    // Not the compiler's format: a link error, a crash, a timeout. Still a
    // problem, shown as the text it is.
    const first = lines.map((l) => l.trim()).find(Boolean) ?? "";
    problems.push({ severity: "error", code: fallbackCode, message: first, at: null, notes: [], raw: text });
  }
  return problems;
}
