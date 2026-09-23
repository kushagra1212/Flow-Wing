// A read-only listing with syntax colours: the LLVM IR, or the WebAssembly
// text format. Very long text is shown plain: colouring a megabyte would
// stall the page for longer than it is worth.

import React, { useMemo, useState } from "react";
import Prism from "prismjs";
import "prismjs/components/prism-llvm";
import "prismjs/components/prism-wasm";
import styles from "./Playground.module.css";

const COLOUR_LIMIT = 300 * 1024;

type Props = {
  text: string;
  language: "llvm" | "wasm";
  fileName: string;
};

export function formatBytes(bytes: number): string {
  if (bytes < 1024) return `${bytes} B`;
  if (bytes < 1024 * 1024) return `${(bytes / 1024).toFixed(1)} KB`;
  return `${(bytes / 1024 / 1024).toFixed(2)} MB`;
}

export function download(fileName: string, data: BlobPart, type: string): void {
  const url = URL.createObjectURL(new Blob([data], { type }));
  const link = document.createElement("a");
  link.href = url;
  link.download = fileName;
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
}

export default function CodeView({ text, language, fileName }: Props) {
  const [copied, setCopied] = useState(false);
  const html = useMemo(
    () => (text.length <= COLOUR_LIMIT ? Prism.highlight(text, Prism.languages[language], language) : null),
    [text, language],
  );
  const lines = useMemo(() => text.split("\n").length, [text]);

  return (
    <>
      <div className={styles.viewBar}>
        <span className={styles.viewTitle}>{lines.toLocaleString()} lines · {formatBytes(text.length)}</span>
        <span className={styles.spacer} />
        <button
          type="button"
          className={styles.miniButton}
          onClick={async () => {
            await navigator.clipboard.writeText(text);
            setCopied(true);
            setTimeout(() => setCopied(false), 1500);
          }}
        >
          {copied ? "Copied" : "Copy"}
        </button>
        <button type="button" className={styles.miniButton} onClick={() => download(fileName, text, "text/plain")}>
          Download {fileName}
        </button>
      </div>
      {html !== null
        ? <pre className={`${styles.listing} language-${language}`} dangerouslySetInnerHTML={{ __html: html }} />
        : <pre className={styles.listing}>{text}</pre>}
    </>
  );
}
