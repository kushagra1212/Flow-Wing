export class CodeEditor {
  constructor(containerId, onTokenHover) {
    this.container = document.getElementById(containerId);
    this.onTokenHover = onTokenHover;
    this.lines = [];
    this.tokenMap = new Map();
    this.isEditMode = false;
    this.textarea = null;
    this.codeMirror = null;
    this.codeMirrorStyle = null;
    this.onCodeChange = null;
    this.currentCode = ""; // Cache current code to avoid reconstruction issues
  }

  setEditMode(enabled) {
    if (this.isEditMode === enabled) {
      return; // Already in the correct mode
    }

    this.isEditMode = enabled;
    if (enabled) {
      this.enableEditMode();
    } else {
      this.disableEditMode();
    }
  }

  enableEditMode() {
    // Get the most up-to-date code before switching
    const currentCode = this.getCurrentCode();
    this.currentCode = currentCode; // Cache it

    // Clear container completely and ensure it's empty
    this.container.innerHTML = "";
    this.container.textContent = "";
    // Remove any child nodes that might remain
    while (this.container.firstChild) {
      this.container.removeChild(this.container.firstChild);
    }

    // Use CodeMirror for syntax highlighting
    if (window.CodeMirror && typeof CodeMirror === "function") {
      try {
        // Ensure container has proper dimensions and is ready
        // Don't override display or position - let CSS handle it
        // Just ensure dimensions are set properly
        const parent = this.container.parentElement;
        if (parent) {
          // Reset any inline styles that might interfere with layout
          this.container.style.display = "";
          this.container.style.position = "";
          this.container.style.top = "";
          this.container.style.left = "";
          this.container.style.right = "";
          this.container.style.bottom = "";
          this.container.style.margin = "";
          this.container.style.transform = "";

          // Ensure container fills parent but doesn't break layout
          this.container.style.height = "100%";
          this.container.style.width = "100%";
          this.container.style.overflow = "hidden"; // Prevent any overflow during initialization
          this.container.style.minHeight = "0"; // Allow flexbox to shrink
        }

        // Use flowwing mode for syntax highlighting (defined in index.html)
        // The mode should be registered by the script in index.html before this runs
        this.codeMirror = CodeMirror(this.container, {
          value: this.currentCode || "",
          mode: "flowwing", // Use the custom Flow-Wing mode
          theme: "monokai", // REQUIRED: Matches the CSS file loaded in HTML
          lineNumbers: true,
          lineWrapping: false,
          indentUnit: 4,
          tabSize: 4,
          indentWithTabs: false,
          autofocus: true,
          viewportMargin: Infinity,
        });

        // Force refresh to ensure syntax highlighting is applied immediately
        this.codeMirror.refresh();

        // Override CodeMirror styles to match our theme
        const cmElement = this.codeMirror.getWrapperElement();
        cmElement.style.height = "100%";
        cmElement.style.width = "100%";
        cmElement.style.fontSize = "14px";
        cmElement.style.fontFamily =
          "SF Mono, Monaco, Cascadia Code, Roboto Mono, Consolas, monospace";
        // Ensure CodeMirror doesn't break layout
        cmElement.style.position = "relative";
        cmElement.style.display = "flex";
        cmElement.style.flexDirection = "column";

        // Remove any old code lines that might still be in the container
        const oldCodeLines = this.container.querySelectorAll(".code-line");
        oldCodeLines.forEach((line) => line.remove());

        // Ensure CodeMirror's internal textarea is hidden
        const textarea = this.codeMirror.getTextArea();
        if (textarea) {
          textarea.style.position = "absolute";
          textarea.style.left = "-9999px";
          textarea.style.opacity = "0";
          textarea.style.pointerEvents = "none";
        }

        // Update CodeMirror theme colors to match our dark theme
        // Always update styles to ensure they're applied
        let style = document.getElementById("codemirror-custom-style");
        if (!style) {
          style = document.createElement("style");
          style.id = "codemirror-custom-style";
          document.head.appendChild(style);
        }
        style.textContent = `
            /* Fix Background: Force Monokai to use your app's bg-dark instead of brown */
            #code-editor .CodeMirror,
            #code-editor .cm-s-monokai.CodeMirror {
              background: var(--bg-dark) !important;
              color: var(--text-main) !important;
              height: 100% !important;
              flex: 1;
            }
            #code-editor .CodeMirror-gutters {
              background: var(--bg-panel) !important;
              border-right: 1px solid var(--border-light) !important;
            }
            #code-editor .CodeMirror-linenumber {
              color: var(--text-dim) !important;
            }
            #code-editor .CodeMirror-cursor {
              border-left: 2px solid var(--accent) !important;
            }
            #code-editor .CodeMirror-selected {
              background: rgba(88, 166, 255, 0.2) !important;
            }
            #code-editor .CodeMirror-line::selection,
            #code-editor .CodeMirror-line > span::selection,
            #code-editor .CodeMirror-line > span > span::selection {
              background: rgba(88, 166, 255, 0.2) !important;
            }
            #code-editor .CodeMirror-cursor {
              border-left: 2px solid var(--accent) !important;
            }
            #code-editor .CodeMirror-selected {
              background: rgba(88, 166, 255, 0.2) !important;
            }
            #code-editor .CodeMirror-line::selection,
            #code-editor .CodeMirror-line > span::selection,
            #code-editor .CodeMirror-line > span > span::selection {
              background: rgba(88, 166, 255, 0.2) !important;
            }
            #code-editor .CodeMirror-activeline-background {
              background: rgba(88, 166, 255, 0.05) !important;
            }
            /* Syntax highlighting colors - maximum specificity */
            #code-editor .CodeMirror .CodeMirror-line .cm-keyword,
            #code-editor .CodeMirror .CodeMirror-line span.cm-keyword { 
              color: #ff7b72 !important; 
              font-weight: 600 !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-string,
            #code-editor .CodeMirror .CodeMirror-line span.cm-string,
            #code-editor .CodeMirror .CodeMirror-line .cm-string-2,
            #code-editor .CodeMirror .CodeMirror-line span.cm-string-2 { 
              color: #a5d6ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-number,
            #code-editor .CodeMirror .CodeMirror-line span.cm-number { 
              color: #79c0ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-variable,
            #code-editor .CodeMirror .CodeMirror-line span.cm-variable { 
              color: #c9d1d9 !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-variable-2,
            #code-editor .CodeMirror .CodeMirror-line span.cm-variable-2,
            #code-editor .CodeMirror .CodeMirror-line .cm-variable-3,
            #code-editor .CodeMirror .CodeMirror-line span.cm-variable-3 { 
              color: #d2a8ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-def,
            #code-editor .CodeMirror .CodeMirror-line span.cm-def { 
              color: #d2a8ff !important; 
              font-weight: 500 !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-operator,
            #code-editor .CodeMirror .CodeMirror-line span.cm-operator { 
              color: #ff7b72 !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-bracket,
            #code-editor .CodeMirror .CodeMirror-line span.cm-bracket { 
              color: #d2a8ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-punctuation,
            #code-editor .CodeMirror .CodeMirror-line span.cm-punctuation { 
              color: #8b949e !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-comment,
            #code-editor .CodeMirror .CodeMirror-line span.cm-comment { 
              color: #8b949e !important; 
              font-style: italic !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-property,
            #code-editor .CodeMirror .CodeMirror-line span.cm-property { 
              color: #79c0ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-atom,
            #code-editor .CodeMirror .CodeMirror-line span.cm-atom { 
              color: #79c0ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-tag,
            #code-editor .CodeMirror .CodeMirror-line span.cm-tag { 
              color: #ff7b72 !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-attribute,
            #code-editor .CodeMirror .CodeMirror-line span.cm-attribute { 
              color: #79c0ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-builtin,
            #code-editor .CodeMirror .CodeMirror-line span.cm-builtin { 
              color: #d2a8ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-qualifier,
            #code-editor .CodeMirror .CodeMirror-line span.cm-qualifier { 
              color: #d2a8ff !important; 
            }
            #code-editor .CodeMirror .CodeMirror-line .cm-meta,
            #code-editor .CodeMirror .CodeMirror-line span.cm-meta { 
              color: #8b949e !important; 
            }
          `;
        this.codeMirrorStyle = style;

        this.codeMirror.on("change", (cm) => {
          const newValue = cm.getValue();
          this.currentCode = newValue; // Keep cache in sync
          if (this.onCodeChange) {
            this.onCodeChange(newValue);
          }
        });

        this.textarea = this.codeMirror.getTextArea();

        // Ensure proper sizing and focus immediately
        // Use requestAnimationFrame to ensure layout is stable before sizing
        requestAnimationFrame(() => {
          if (this.codeMirror) {
            const parentEl = this.container.parentElement;
            if (parentEl) {
              const cmElement = this.codeMirror.getWrapperElement();
              const scroller = this.codeMirror.getScrollerElement();

              // Get the actual available height from parent
              const availableHeight = parentEl.clientHeight;

              if (availableHeight > 0) {
                // Set heights to fill available space without breaking layout
                this.container.style.height = `${availableHeight}px`;
                cmElement.style.height = `${availableHeight}px`;
                if (scroller) {
                  scroller.style.height = `${availableHeight}px`;
                }
              }
            }

            // Refresh and focus after layout is stable
            this.codeMirror.refresh();
            this.codeMirror.focus();
          }
        });
      } catch (error) {
        console.error("CodeMirror initialization failed:", error);
        this.codeMirror = null;
      }
    }

    // Fallback to textarea if CodeMirror failed or is not available
    if (!this.codeMirror) {
      this.textarea = document.createElement("textarea");
      this.textarea.className = "code-editor-textarea";
      this.textarea.value = this.currentCode;
      this.textarea.spellcheck = false;

      Object.assign(this.textarea.style, {
        fontFamily:
          "SF Mono, Monaco, Cascadia Code, Roboto Mono, Consolas, monospace",
        fontSize: "14px",
        lineHeight: "1.75",
        width: "100%",
        height: "100%",
        minHeight: "100%",
        background: "var(--bg-dark)",
        color: "var(--text-main)",
        border: "none",
        outline: "none",
        padding: "16px 0 16px 4rem",
        resize: "none",
        whiteSpace: "pre",
        overflowWrap: "normal",
        overflowX: "auto",
        overflowY: "auto",
        backgroundImage:
          "linear-gradient(to right, var(--bg-panel) 3.5rem, transparent 3.5rem)",
        backgroundAttachment: "local",
        tabSize: "4",
      });

      this.textarea.addEventListener("input", () => {
        this.currentCode = this.textarea.value; // Keep cache in sync
        if (this.onCodeChange) {
          this.onCodeChange(this.textarea.value);
        }
      });

      this.container.appendChild(this.textarea);
      this.textarea.focus();
    }
  }

  disableEditMode() {
    let code = "";
    if (this.codeMirror) {
      code = this.codeMirror.getValue();
      this.currentCode = code; // Update cache before destroying
      this.codeMirror.toTextArea();
      this.codeMirror = null;
      if (this.codeMirrorStyle) {
        this.codeMirrorStyle.remove();
        this.codeMirrorStyle = null;
      }
      this.container.innerHTML = "";
      this.textarea = null;
    } else if (this.textarea) {
      code = this.textarea.value;
      this.currentCode = code; // Update cache
      this.textarea.remove();
      this.textarea = null;
      this.container.innerHTML = "";
    } else {
      code = this.getCurrentCode();
      this.currentCode = code;
    }

    // Restore overflow settings for visual mode
    this.container.style.overflow = "auto";
    this.container.style.overflowX = "auto";
    this.container.style.overflowY = "auto";

    return code;
  }

  getCurrentCode() {
    // Always prefer the cached value if available and in edit mode
    if (this.isEditMode) {
      if (this.codeMirror) {
        const value = this.codeMirror.getValue();
        this.currentCode = value; // Keep cache updated
        return value;
      } else if (this.textarea) {
        const value = this.textarea.value;
        this.currentCode = value; // Keep cache updated
        return value;
      }
      // If we have cached code, use it
      if (this.currentCode) {
        return this.currentCode;
      }
    }
    // In visual mode, prefer cache, then reconstruct from lines
    if (this.currentCode) {
      return this.currentCode;
    }
    return this.lines.join("\n");
  }

  render(sourceCode, tokens) {
    // If in edit mode, don't overwrite user's current edits
    // Only update if editor is empty (initial load scenario)
    if (this.isEditMode) {
      if (this.codeMirror) {
        const currentValue = this.codeMirror.getValue();
        // Only update if editor is empty (initial load) or if explicitly requested
        // This prevents overwriting user input during paste/typing
        if (!currentValue || currentValue.trim() === "") {
          // Editor is empty, safe to set the value
          this.codeMirror.setValue(sourceCode || "");
          this.currentCode = sourceCode || "";
        }
        // Otherwise, keep user's current input - don't overwrite
      } else if (this.textarea) {
        const currentValue = this.textarea.value;
        // Only update if textarea is empty
        if (!currentValue || currentValue.trim() === "") {
          this.textarea.value = sourceCode || "";
          this.currentCode = sourceCode || "";
        }
        // Otherwise, keep user's current input - don't overwrite
      }
      // Update lines cache for getCurrentCode fallback
      if (sourceCode) {
        this.lines = sourceCode.split("\n");
      }
      return;
    }

    // In visual mode, always render the provided source code
    this.currentCode = sourceCode || "";

    this.container.innerHTML = "";
    this.tokenMap.clear();
    this.lines = sourceCode.split("\n");

    // Group tokens by line to avoid O(N^2) lookups
    const tokensByLine = new Array(this.lines.length).fill(0).map(() => []);
    tokens.forEach((t) => {
      const line = t.range.start[0];
      if (line >= 0 && line < this.lines.length) {
        tokensByLine[line].push(t);
      }
    });

    this.lines.forEach((lineContent, lineIndex) => {
      const lineEl = document.createElement("div");
      lineEl.className = "code-line";

      const lineTokens = tokensByLine[lineIndex] || [];
      lineTokens.sort((a, b) => a.range.start[1] - b.range.start[1]);

      let currentCol = 0;
      const lineLength = lineContent.length;

      lineTokens.forEach((token, tokenIndex) => {
        const startCol = Math.max(
          0,
          Math.min(token.range.start[1], lineLength)
        );
        const endCol = Math.max(
          startCol,
          Math.min(token.range.end[1], lineLength)
        );

        // 1. Text BEFORE token (using textContent for proper escaping)
        if (currentCol < startCol) {
          const textBefore = lineContent.slice(currentCol, startCol);
          if (textBefore.length > 0) {
            lineEl.appendChild(document.createTextNode(textBefore));
          }
        }

        // 2. The Token Span
        const span = document.createElement("span");
        const lexeme = lineContent.slice(startCol, endCol);

        // Use textContent to properly escape HTML entities (quotes, backslashes, etc.)
        span.textContent = lexeme;

        // Determine if this identifier is a function call
        let className = `token tk-${token.type}`;
        if (token.type === "IdentifierToken") {
          // Check if next token is an opening parenthesis
          const nextToken = lineTokens[tokenIndex + 1];
          if (nextToken && nextToken.type === "OpenParenthesisToken") {
            className += " function-call";
          }
        }

        span.className = className;

        // Store metadata for lookup
        span.dataset.key = `${lineIndex}:${startCol}`;
        span.dataset.line = lineIndex;
        span.dataset.col = startCol;
        span.dataset.endLine = token.range.end[0];
        span.dataset.endCol = token.range.end[1];
        span.dataset.tokenType = token.type;

        // EVENTS: Send FULL token object to app.js
        span.onmouseenter = () => this.onTokenHover(token);

        this.tokenMap.set(span.dataset.key, span);
        lineEl.appendChild(span);

        currentCol = endCol;
      });

      // 3. Text AFTER last token
      if (currentCol < lineLength) {
        const textAfter = lineContent.slice(currentCol);
        if (textAfter.length > 0) {
          lineEl.appendChild(document.createTextNode(textAfter));
        }
      }

      // Handle empty lines
      if (lineContent.length === 0) {
        lineEl.appendChild(document.createTextNode(" "));
      }

      this.container.appendChild(lineEl);
    });
  }

  highlightRange(range) {
    // Clear old highlights
    document
      .querySelectorAll(".token.highlighted")
      .forEach((el) => el.classList.remove("highlighted"));

    if (!range) return;

    const startLine = range.start[0];
    const startCol = range.start[1];
    const endLine = range.end[0];
    const endCol = range.end[1];

    // Highlight all tokens within the range
    let firstHighlighted = null;

    // Get all tokens and check if they fall within the range
    this.tokenMap.forEach((el, key) => {
      const tokenStartLine = parseInt(el.dataset.line);
      const tokenStartCol = parseInt(el.dataset.col);
      const tokenEndLine = parseInt(el.dataset.endLine);
      const tokenEndCol = parseInt(el.dataset.endCol);

      // Check if this token overlaps with the range
      let shouldHighlight = false;

      // Token overlaps if:
      // 1. Token starts before range ends AND token ends after range starts
      const tokenStartsBeforeRangeEnds =
        tokenStartLine < endLine ||
        (tokenStartLine === endLine && tokenStartCol < endCol);
      const tokenEndsAfterRangeStarts =
        tokenEndLine > startLine ||
        (tokenEndLine === startLine && tokenEndCol > startCol);

      if (tokenStartsBeforeRangeEnds && tokenEndsAfterRangeStarts) {
        shouldHighlight = true;
      }

      if (shouldHighlight) {
        el.classList.add("highlighted");
        if (!firstHighlighted) firstHighlighted = el;
      }
    });

    // Fallback: try to highlight by exact start position (for single token matches)
    if (!firstHighlighted) {
      const key = `${startLine}:${startCol}`;
      const exactMatch = this.tokenMap.get(key);
      if (exactMatch) {
        exactMatch.classList.add("highlighted");
        firstHighlighted = exactMatch;
      }
    }

    // Scroll to first highlighted element
    if (firstHighlighted) {
      firstHighlighted.scrollIntoView({ behavior: "smooth", block: "nearest" });
    }
  }
}
