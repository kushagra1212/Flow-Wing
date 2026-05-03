import React, { useEffect, useState } from "react";
import Prism from "prismjs";
import "prismjs/themes/prism-tomorrow.css"; // You can choose your theme
import "../../../utils/prism-flowwing"; // Make sure to adjust the path
import Styles from "./CodeBlock.module.css";

const CodeBlock = ({ code, language }) => {
  const [copyText, setCopyText] = useState("Copy");
  const [showCopyButton, setShowCopyButton] = useState(false);
  useEffect(() => {
    Prism.highlightAll();
  }, [code]);

  const copyToClipboard = () => {
    navigator.clipboard
      .writeText(code)
      .then(() => {
        setCopyText("Copied!");
        setTimeout(() => setCopyText("Copy"), 2000); // Reset after 2 seconds
      })
      .catch((err) => console.error("Failed to copy: ", err));
  };

  const handleMouseEnter = () => {
    setShowCopyButton(true);
  };

  const handleMouseLeave = () => {
    setShowCopyButton(false);
  };

  return (
    <div
      className={language === "fg" ? Styles.codeblock : ""}
      onMouseEnter={handleMouseEnter}
      onMouseLeave={handleMouseLeave}
    >
      {showCopyButton && (
        <button onClick={copyToClipboard} className={Styles.copyButton}>
          {copyText}
        </button>
      )}
      <pre>
        <code className={language === "fg" ? "language-flowwing" : ""}>
          {code}
        </code>
      </pre>
    </div>
  );
};

export default CodeBlock;
