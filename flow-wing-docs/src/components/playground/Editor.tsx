// A code editor made of a textarea laid over a syntax-highlighted copy of its
// text. The textarea's own text is transparent, so the caret, selection and
// typing are the browser's, and the colours come from the <pre> behind it.
// Both layers share font, padding and wrapping, so every character lines up.
// Highlighting uses the same Prism grammar as the docs' code blocks.
//
// Around them: line numbers, and marks: a band on each line with a problem,
// and a highlight over the code a tree node or token stands for. Scrolling
// moves all layers by setting their positions directly, without a render.

import React, { forwardRef, useImperativeHandle, useLayoutEffect, useMemo, useRef } from "react";
import Prism from "prismjs";
import "prismjs/themes/prism-tomorrow.css";
import "../../utils/prism-flowwing";
import type { Span } from "./source";
import { SourceMap } from "./source";
import styles from "./Playground.module.css";

// Must match .editor .layer in Playground.module.css.
const LINE_HEIGHT = 21;
const PADDING_TOP = 14;
const TAB_SIZE = 2;

export type LineMark = { line: number; severity: "error" | "warning"; message: string };

export type EditorHandle = {
  // Scrolls the span into view and selects it, without taking focus.
  reveal(span: Span): void;
  focus(): void;
};

type Props = {
  value: string;
  onChange: (value: string) => void;
  onRun: () => void;
  marks: LineMark[];
  highlight: Span | null;
};

// Visual column of an offset in its line: tabs expanded.
function columnOf(text: string, lineStart: number, offset: number): number {
  let column = 0;
  for (let i = lineStart; i < offset; i++) {
    column = text[i] === "\t" ? column + TAB_SIZE - (column % TAB_SIZE) : column + 1;
  }
  return column;
}

const Editor = forwardRef<EditorHandle, Props>(function Editor(
  { value, onChange, onRun, marks, highlight },
  ref,
) {
  const input = useRef<HTMLTextAreaElement>(null);
  const highlighted = useRef<HTMLPreElement>(null);
  const gutter = useRef<HTMLDivElement>(null);
  const overlay = useRef<HTMLDivElement>(null);

  const map = useMemo(() => new SourceMap(value), [value]);

  // The trailing newline gives a final empty line a height, so the two
  // layers stay the same size while the caret sits on it.
  const html = useMemo(
    () => Prism.highlight(value + "\n", Prism.languages.flowwing, "flowwing"),
    [value],
  );

  const syncScroll = () => {
    const area = input.current;
    if (!area) return;
    if (highlighted.current) {
      highlighted.current.scrollTop = area.scrollTop;
      highlighted.current.scrollLeft = area.scrollLeft;
    }
    if (gutter.current) gutter.current.style.transform = `translateY(${-area.scrollTop}px)`;
    if (overlay.current) {
      overlay.current.style.transform = `translate(${-area.scrollLeft}px, ${-area.scrollTop}px)`;
    }
  };
  useLayoutEffect(syncScroll, [value]);

  useImperativeHandle(ref, () => ({
    reveal(span: Span) {
      const area = input.current;
      if (!area) return;
      const line = map.lineOf(span.start);
      const top = PADDING_TOP + line * LINE_HEIGHT;
      if (top < area.scrollTop || top + LINE_HEIGHT > area.scrollTop + area.clientHeight) {
        area.scrollTop = Math.max(0, top - area.clientHeight / 3);
      }
      area.setSelectionRange(span.start, span.end);
      syncScroll();
    },
    focus() {
      input.current?.focus();
    },
  }), [map]);

  // Escape, then Tab, moves focus on as usual: a keyboard user is never
  // trapped in the editor.
  const escaped = useRef(false);

  const onKeyDown = (event: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if ((event.metaKey || event.ctrlKey) && event.key === "Enter") {
      event.preventDefault();
      onRun();
    } else if (event.key === "Tab" && !event.shiftKey && !event.altKey && !event.metaKey &&
               !event.ctrlKey && !escaped.current) {
      // Indent instead of leaving the editor. insertText keeps the browser's
      // undo history, which setting the value directly would reset.
      event.preventDefault();
      document.execCommand("insertText", false, "  ");
    }
    escaped.current = event.key === "Escape";
  };

  // The highlight, as one rectangle per line it covers.
  const highlightBoxes = useMemo(() => {
    if (!highlight || highlight.end < highlight.start) return [];
    const boxes: { line: number; from: number; to: number }[] = [];
    const first = map.lineOf(highlight.start);
    const last = map.lineOf(Math.max(highlight.start, highlight.end - 1));
    for (let line = first; line <= last && line - first < 400; line++) {
      const lineStart = map.offset([line, 0]);
      const lineEnd = line + 1 < map.lineCount ? map.offset([line + 1, 0]) - 1 : value.length;
      const from = columnOf(value, lineStart, Math.max(highlight.start, lineStart));
      const to = columnOf(value, lineStart, Math.min(highlight.end, lineEnd));
      boxes.push({ line, from, to: Math.max(to, from + 1) });
    }
    return boxes;
  }, [highlight, map, value]);

  const markedLines = useMemo(() => {
    const byLine = new Map<number, LineMark>();
    for (const mark of marks) {
      const existing = byLine.get(mark.line);
      if (!existing || (existing.severity === "warning" && mark.severity === "error")) {
        byLine.set(mark.line, mark);
      }
    }
    return byLine;
  }, [marks]);

  return (
    <div className={styles.editor}>
      <div className={styles.gutter} aria-hidden="true">
        <div ref={gutter} className={styles.gutterInner}>
          {Array.from({ length: map.lineCount }, (_, line) => {
            const mark = markedLines.get(line);
            return (
              <div
                key={line}
                className={mark ? styles[`gutter_${mark.severity}`] : undefined}
                title={mark?.message}
              >
                {line + 1}
              </div>
            );
          })}
        </div>
      </div>

      <div className={styles.code}>
        <div className={styles.overlayClip} aria-hidden="true">
          <div ref={overlay} className={styles.overlay}>
            {[...markedLines.values()].map((mark) => (
              <div
                key={`m${mark.line}`}
                className={`${styles.lineMark} ${styles[`lineMark_${mark.severity}`]}`}
                style={{ top: PADDING_TOP + mark.line * LINE_HEIGHT }}
              />
            ))}
            {highlightBoxes.map((box) => (
              <div
                key={`h${box.line}`}
                className={styles.highlightBox}
                style={{
                  top: PADDING_TOP + box.line * LINE_HEIGHT,
                  left: `calc(var(--pg-code-padding-x) + ${box.from}ch)`,
                  width: `${box.to - box.from}ch`,
                }}
              />
            ))}
          </div>
        </div>
        <pre
          ref={highlighted}
          aria-hidden="true"
          className={`${styles.layer} ${styles.highlighted} language-flowwing`}
          dangerouslySetInnerHTML={{ __html: html }}
        />
        <textarea
          ref={input}
          className={`${styles.layer} ${styles.input}`}
          value={value}
          onChange={(event) => onChange(event.target.value)}
          onKeyDown={onKeyDown}
          onScroll={syncScroll}
          spellCheck={false}
          autoCapitalize="off"
          autoComplete="off"
          autoCorrect="off"
          aria-label="Flow-Wing source code. Ctrl+Enter runs it. Escape, then Tab, leaves the editor."
        />
      </div>
    </div>
  );
});

export default Editor;
