// Terminal colour codes (ESC [ ... m) to styled spans. The compiler colours
// its diagnostics and the runtime colours its errors; this handles the subset
// they use: reset, bold, and the 16 foreground colours.

import React from "react";
import styles from "./Playground.module.css";

export type AnsiState = { bold: boolean; color: string | null };

export const PLAIN: AnsiState = { bold: false, color: null };

const COLORS: Record<number, string> = {
  30: "black", 31: "red", 32: "green", 33: "yellow",
  34: "blue", 35: "magenta", 36: "cyan", 37: "white",
  90: "gray", 91: "red", 92: "green", 93: "yellow",
  94: "blue", 95: "magenta", 96: "cyan", 97: "white",
};

const SEQUENCE = /\x1b\[([0-9;]*)m/g;

function apply(state: AnsiState, params: string): AnsiState {
  let next = { ...state };
  for (const part of (params || "0").split(";")) {
    const code = Number(part);
    if (code === 0) next = { ...PLAIN };
    else if (code === 1) next.bold = true;
    else if (code === 22) next.bold = false;
    else if (code === 39) next.color = null;
    else if (COLORS[code]) next.color = COLORS[code];
  }
  return next;
}

// Colours carry over from one chunk to the next (a runtime error opens red on
// its first line and resets after its last), so the caller threads `state`
// through successive calls.
export function renderAnsi(
  text: string,
  state: AnsiState,
  key: string,
): { nodes: React.ReactNode[]; state: AnsiState } {
  const nodes: React.ReactNode[] = [];
  let last = 0;
  let current = state;
  const push = (segment: string) => {
    if (!segment) return;
    const className = [
      current.color ? styles[`ansi_${current.color}`] : "",
      current.bold ? styles.ansi_bold : "",
    ].filter(Boolean).join(" ");
    nodes.push(className
      ? <span key={`${key}-${nodes.length}`} className={className}>{segment}</span>
      : segment);
  };
  for (const match of text.matchAll(SEQUENCE)) {
    push(text.slice(last, match.index));
    current = apply(current, match[1]);
    last = (match.index ?? 0) + match[0].length;
  }
  push(text.slice(last));
  return { nodes, state: current };
}
