// A code editor made of a textarea laid over a syntax-highlighted copy of its
// text. The textarea's own text is transparent, so the caret, selection and
// typing are the browser's, and the colours come from the <pre> behind it.
// Both layers share font, padding and wrapping, so every character lines up.
// Highlighting uses the same Prism grammar as the docs' code blocks.

import React, { useMemo, useRef } from "react";
import Prism from "prismjs";
import "prismjs/themes/prism-tomorrow.css";
import "../../utils/prism-flowwing";
import styles from "./Playground.module.css";

type Props = {
  value: string;
  onChange: (value: string) => void;
  onRun: () => void;
};

export default function Editor({ value, onChange, onRun }: Props) {
  const highlighted = useRef<HTMLPreElement>(null);

  // The trailing newline gives a final empty line a height, so the two
  // layers stay the same size while the caret sits on it.
  const html = useMemo(
    () => Prism.highlight(value + "\n", Prism.languages.flowwing, "flowwing"),
    [value],
  );

  const onKeyDown = (event: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if ((event.metaKey || event.ctrlKey) && event.key === "Enter") {
      event.preventDefault();
      onRun();
    } else if (event.key === "Tab" && !event.shiftKey && !event.altKey) {
      // Indent instead of leaving the editor. insertText keeps the browser's
      // undo history, which setting the value directly would reset.
      event.preventDefault();
      document.execCommand("insertText", false, "  ");
    }
  };

  const onScroll = (event: React.UIEvent<HTMLTextAreaElement>) => {
    if (highlighted.current) {
      highlighted.current.scrollTop = event.currentTarget.scrollTop;
      highlighted.current.scrollLeft = event.currentTarget.scrollLeft;
    }
  };

  return (
    <div className={styles.editor}>
      <pre
        ref={highlighted}
        aria-hidden="true"
        className={`${styles.layer} ${styles.highlighted} language-flowwing`}
        dangerouslySetInnerHTML={{ __html: html }}
      />
      <textarea
        className={`${styles.layer} ${styles.input}`}
        value={value}
        onChange={(event) => onChange(event.target.value)}
        onKeyDown={onKeyDown}
        onScroll={onScroll}
        spellCheck={false}
        autoCapitalize="off"
        autoComplete="off"
        autoCorrect="off"
        aria-label="Flow-Wing source code"
      />
    </div>
  );
}
