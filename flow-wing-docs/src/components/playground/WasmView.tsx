// What the browser runs: main.wasm and the main.js that loads it. Shows the
// module's sections, imports and exports, read from its bytes, and on request
// its text format (WAT), which the server makes with binaryen's wasm-dis.

import React, { useEffect, useState } from "react";
import type { WasmInfo } from "./wasmInfo";
import { inspectWasm } from "./wasmInfo";
import CodeView, { download, formatBytes } from "./CodeView";
import styles from "./Playground.module.css";

type Props = {
  wasm: ArrayBuffer;
  js: string;
  wat: { state: "idle" | "loading" | "done" | "error"; text: string; truncated: boolean; error?: string };
  onRequestWat: () => void;
};

export default function WasmView({ wasm, js, wat, onRequestWat }: Props) {
  const [info, setInfo] = useState<WasmInfo | null>(null);
  const [failure, setFailure] = useState("");
  useEffect(() => {
    let current = true;
    inspectWasm(wasm).then(
      (result) => current && setInfo(result),
      (error) => current && setFailure(String(error?.message ?? error)),
    );
    return () => { current = false; };
  }, [wasm]);

  if (failure) return <p className={styles.viewHint}>Could not read the module: {failure}</p>;
  if (!info) return <p className={styles.viewHint}>Reading the module…</p>;

  const largest = Math.max(...info.sections.map((section) => section.size), 1);
  const importsByModule = new Map<string, WebAssembly.ModuleImportDescriptor[]>();
  for (const entry of info.imports) {
    importsByModule.set(entry.module, [...(importsByModule.get(entry.module) ?? []), entry]);
  }

  return (
    <>
      <div className={styles.viewBar}>
        <span className={styles.viewTitle}>
          main.wasm {formatBytes(info.size)} · main.js {formatBytes(js.length)}
        </span>
        <span className={styles.spacer} />
        <button type="button" className={styles.miniButton} onClick={() => download("main.wasm", wasm, "application/wasm")}>
          Download main.wasm
        </button>
        <button type="button" className={styles.miniButton} onClick={() => download("main.js", js, "text/javascript")}>
          Download main.js
        </button>
      </div>

      <p className={styles.explain}>
        Your program and the Flow-Wing runtime (garbage collector, task scheduler,
        built-in modules), linked by Emscripten. <code>main.js</code> loads it,
        gives it the functions it imports, and connects its output to this page.
      </p>

      <h4 className={styles.subhead}>Sections</h4>
      <table className={styles.table}>
        <thead><tr><th>Section</th><th>Entries</th><th>Size</th><th aria-hidden="true" /></tr></thead>
        <tbody>
          {info.sections.map((section, index) => (
            <tr key={index}>
              <td className={styles.code}>{section.name}</td>
              <td className={styles.muted}>{section.count ?? ""}</td>
              <td>{formatBytes(section.size)}</td>
              <td className={styles.barCell} aria-hidden="true">
                <span className={styles.bar} style={{ width: `${(section.size / largest) * 100}%` }} />
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      <div className={styles.columns}>
        <div>
          <h4 className={styles.subhead}>Imports ({info.imports.length})</h4>
          <p className={styles.viewHint}>What the module needs from main.js: system calls and the browser.</p>
          {[...importsByModule].map(([module, entries]) => (
            <details key={module} className={styles.details}>
              <summary><code>{module}</code> · {entries.length}</summary>
              <ul className={styles.plainList}>
                {entries.map((entry) => (
                  <li key={entry.name}><code>{entry.name}</code> <span className={styles.muted}>{entry.kind}</span></li>
                ))}
              </ul>
            </details>
          ))}
        </div>
        <div>
          <h4 className={styles.subhead}>Exports ({info.exports.length})</h4>
          <p className={styles.viewHint}>What main.js can call: main, memory, and the runtime's entry points.</p>
          <ul className={styles.plainList}>
            {info.exports.map((entry) => (
              <li key={entry.name}><code>{entry.name}</code> <span className={styles.muted}>{entry.kind}</span></li>
            ))}
          </ul>
        </div>
      </div>

      <h4 className={styles.subhead}>Text format (WAT)</h4>
      {wat.state === "done" ? (
        <>
          {wat.truncated && <p className={styles.viewHint}>Cut at 4 MB.</p>}
          <CodeView text={wat.text} language="wasm" fileName="main.wat" />
        </>
      ) : (
        <p className={styles.viewHint}>
          {wat.state === "error" && <>{wat.error} </>}
          <button type="button" className={styles.miniButton} onClick={onRequestWat} disabled={wat.state === "loading"}>
            {wat.state === "loading" ? "Asking the server…" : "Show the text format"}
          </button>{" "}
          Most of it is the runtime: about 1 MB for a small program.
        </p>
      )}
    </>
  );
}
