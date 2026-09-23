// The tab bar, drawn as the compiler's pipeline: each stage a tab, in the
// order a program goes through them, lit by how far the program got.
//
//   01 Tokens ── 02 Syntax tree ── 03 Semantic tree ── 04 LLVM IR ── 05 WebAssembly ── 06 Output │ Problems  Logs
//
// While anything is working, a pulse runs along the line.

import React, { useRef } from "react";
import styles from "./Playground.module.css";

export type TabId = "tokens" | "ast" | "sem" | "ir" | "wasm" | "output" | "problems" | "logs";

// idle: not reached yet. skipped: not part of this kind of run.
// stale: shows a result for an older version of the program.
export type StageState = "idle" | "working" | "ok" | "error" | "skipped" | "stale";

export type Tab = {
  id: TabId;
  label: string;
  state: StageState;
  detail: string;
  stage: boolean; // part of the pipeline, not a side panel
};

type Props = {
  tabs: Tab[];
  selected: TabId;
  onSelect: (id: TabId) => void;
};

export function tabId(id: TabId): string {
  return `pg-tab-${id}`;
}

export function panelId(id: TabId): string {
  return `pg-panel-${id}`;
}

const STATE_LABEL: Record<StageState, string> = {
  idle: "not run yet",
  working: "working",
  ok: "done",
  error: "failed",
  skipped: "not used",
  stale: "out of date",
};

export default function Pipeline({ tabs, selected, onSelect }: Props) {
  const buttons = useRef<Record<string, HTMLButtonElement | null>>({});
  const busy = tabs.some((tab) => tab.state === "working");

  // Arrow keys move between tabs, as in any tab list.
  const onKeyDown = (event: React.KeyboardEvent) => {
    const index = tabs.findIndex((tab) => tab.id === selected);
    let next = -1;
    if (event.key === "ArrowRight") next = (index + 1) % tabs.length;
    else if (event.key === "ArrowLeft") next = (index - 1 + tabs.length) % tabs.length;
    else if (event.key === "Home") next = 0;
    else if (event.key === "End") next = tabs.length - 1;
    if (next < 0) return;
    event.preventDefault();
    onSelect(tabs[next].id);
    buttons.current[tabs[next].id]?.focus();
  };

  let number = 0;
  const render = (tab: Tab) => {
    const isSelected = tab.id === selected;
    return (
      <button
        key={tab.id}
        ref={(element) => { buttons.current[tab.id] = element; }}
        type="button"
        role="tab"
        id={tabId(tab.id)}
        aria-selected={isSelected}
        aria-controls={panelId(tab.id)}
        tabIndex={isSelected ? 0 : -1}
        className={`${styles.tab} ${tab.stage ? styles.stageTab : styles.sideTab}`}
        data-state={tab.state}
        onClick={() => onSelect(tab.id)}
        title={`${tab.label}: ${STATE_LABEL[tab.state]}${tab.detail ? ` (${tab.detail})` : ""}`}
      >
        <span className={styles.tabTop}>
          <span className={styles.dot} aria-hidden="true" />
          {tab.stage && (
            <span className={styles.stageNumber} aria-hidden="true">
              {String(++number).padStart(2, "0")}
            </span>
          )}
          <span className={styles.tabLabel}>{tab.label}</span>
        </span>
        <span className={styles.tabDetail}>{tab.detail || " "}</span>
        <span className={styles.srOnly}>{`, ${STATE_LABEL[tab.state]}`}</span>
      </button>
    );
  };

  return (
    <div
      className={styles.pipeline}
      role="tablist"
      aria-label="Compiler stages"
      data-busy={busy}
      onKeyDown={onKeyDown}
    >
      <div className={styles.stages}>
        <span className={styles.wire} aria-hidden="true" />
        {tabs.filter((tab) => tab.stage).map(render)}
      </div>
      <div className={styles.sides}>{tabs.filter((tab) => !tab.stage).map(render)}</div>
    </div>
  );
}
