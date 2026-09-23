// The lexer's output (--emit=tokens): every token, in order, with its kind,
// its text and where it starts. Pointing at one highlights it in the editor.

import React, { useMemo, useState } from "react";
import type { Range } from "./source";
import { SourceMap, describePoint } from "./source";
import styles from "./Playground.module.css";

type Token = { type: string; lexeme: string; range: Range };

// Rows beyond this are not drawn; a 64 KB program has ~15,000 tokens.
const SHOWN = 3000;

function category(type: string): string {
  if (type.endsWith("Keyword")) return "keyword";
  if (type === "IdentifierToken") return "identifier";
  if (/Literal|Number|String|Char|True|False/.test(type)) return "literal";
  if (type === "EndOfFileToken") return "eof";
  if (/Bad|Error/.test(type)) return "bad";
  return "punctuation";
}

type Props = {
  tokens: Token[];
  map: SourceMap;
  onPick: (range: Range) => void;
  onHover: (range: Range | null) => void;
};

export default function TokensView({ tokens, map, onPick, onHover }: Props) {
  const [filter, setFilter] = useState("");
  const shown = useMemo(() => {
    const needle = filter.trim().toLowerCase();
    return tokens
      .map((token, index) => ({ token, index }))
      .filter(({ token }) => !needle ||
        token.type.toLowerCase().includes(needle) || token.lexeme.toLowerCase().includes(needle));
  }, [tokens, filter]);

  return (
    <>
      <div className={styles.viewBar}>
        <span className={styles.viewTitle}>{tokens.length} tokens</span>
        <span className={styles.spacer} />
        <input
          className={styles.filter}
          type="search"
          placeholder="Filter by kind or text"
          aria-label="Filter tokens"
          value={filter}
          onChange={(event) => setFilter(event.target.value)}
        />
      </div>
      <table className={styles.table}>
        <thead>
          <tr><th>#</th><th>Kind</th><th>Text</th><th>At</th></tr>
        </thead>
        <tbody>
          {shown.slice(0, SHOWN).map(({ token, index }) => (
            <tr
              key={index}
              tabIndex={0}
              onClick={() => onPick(token.range)}
              onKeyDown={(event) => event.key === "Enter" && onPick(token.range)}
              onMouseEnter={() => onHover(token.range)}
              onMouseLeave={() => onHover(null)}
              onFocus={() => onHover(token.range)}
              onBlur={() => onHover(null)}
            >
              <td className={styles.muted}>{index}</td>
              <td><span className={styles[`token_${category(token.type)}`]}>{token.type}</span></td>
              <td className={styles.code}>{JSON.stringify(token.lexeme).slice(1, -1) || <span className={styles.muted}>(empty)</span>}</td>
              <td className={styles.muted}>{describePoint(map, token.range.start)}</td>
            </tr>
          ))}
        </tbody>
      </table>
      {shown.length > SHOWN && (
        <p className={styles.viewHint}>Showing the first {SHOWN} of {shown.length}. Filter to find the rest.</p>
      )}
    </>
  );
}
