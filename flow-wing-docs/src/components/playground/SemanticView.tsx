// The semantic analyser's output (--emit=sem): the tree again, now with
// every name resolved to a symbol and every expression given a type, plus the
// two tables the tree points into.

import React, { useState } from "react";
import type { Range } from "./source";
import { SourceMap, describePoint } from "./source";
import TreeView, { typeName } from "./TreeView";
import styles from "./Playground.module.css";

type Props = {
  sem: { tree: any; symbols: Record<string, any>; types: Record<string, any> };
  map: SourceMap;
  onPick: (range: Range) => void;
  onHover: (range: Range | null) => void;
};

type View = "tree" | "symbols" | "types";

export default function SemanticView({ sem, map, onPick, onHover }: Props) {
  const [view, setView] = useState<View>("tree");
  const symbols = Object.entries(sem.symbols ?? {});
  const types = Object.entries(sem.types ?? {});

  return (
    <>
      <div className={styles.segmented} role="group" aria-label="Semantic analysis view">
        {([
          ["tree", "Tree"],
          ["symbols", `Symbols (${symbols.length})`],
          ["types", `Types (${types.length})`],
        ] as [View, string][]).map(([id, label]) => (
          <button
            key={id}
            type="button"
            aria-pressed={view === id}
            className={view === id ? styles.segmentOn : styles.segment}
            onClick={() => setView(id)}
          >
            {label}
          </button>
        ))}
      </div>

      {view === "tree" && (
        <TreeView
          root={sem.tree}
          symbols={sem.symbols}
          types={sem.types}
          map={map}
          label="Semantic tree"
          onPick={onPick}
          onHover={onHover}
        />
      )}

      {view === "symbols" && (
        <table className={styles.table}>
          <thead>
            <tr><th>Id</th><th>Name</th><th>Kind</th><th>Type</th><th>Declared</th></tr>
          </thead>
          <tbody>
            {symbols.map(([id, symbol]) => {
              const range: Range | undefined = symbol.declaration_range;
              const here = range && !/[\\/]lib[\\/]modules[\\/]/.test(symbol.declaration_source ?? "");
              return (
                <tr
                  key={id}
                  tabIndex={here ? 0 : -1}
                  onClick={() => here && onPick(range!)}
                  onMouseEnter={() => here && onHover(range!)}
                  onMouseLeave={() => onHover(null)}
                >
                  <td className={styles.muted}>{id}</td>
                  <td className={styles.code}>{symbol.name}</td>
                  <td>{symbol.kind}</td>
                  <td className={styles.code}>{symbol.type_id ? typeName(sem.types, symbol.type_id) : ""}</td>
                  <td className={styles.muted}>
                    {symbol.is_declaration ? "built in" : here ? describePoint(map, range!.start) : "module"}
                  </td>
                </tr>
              );
            })}
          </tbody>
        </table>
      )}

      {view === "types" && (
        <table className={styles.table}>
          <thead>
            <tr><th>Id</th><th>Kind</th><th>Name</th><th>Details</th></tr>
          </thead>
          <tbody>
            {types.map(([id, type]) => {
              const { kind, name, ...rest } = type;
              return (
                <tr key={id}>
                  <td className={styles.muted}>{id}</td>
                  <td>{kind}</td>
                  <td className={styles.code}>{name ?? typeName(sem.types, id)}</td>
                  <td className={styles.muted}>
                    {Object.entries(rest).map(([key, value]) =>
                      `${key}: ${typeof value === "string" && sem.types[value] ? typeName(sem.types, value) : JSON.stringify(value)}`,
                    ).join(" · ")}
                  </td>
                </tr>
              );
            })}
          </tbody>
        </table>
      )}
    </>
  );
}
