import { fetchJSON } from "./utils.js";
import { CodeEditor } from "./editor.js";
import { TreeVisualizer } from "./tree.js"; // Reuse your existing tree logic
import { TokenTable } from "./tokenTable.js";
import { CodeHistory } from "./codeHistory.js";

class App {
  constructor() {
    this.state = {
      ast: null,
      tokens: null,
      sem: null,
      llvmIr: null,
      logs: null,
      activeView: "tokens",
      sourceCode: "",
      isEditMode: false,
      binaryPath: localStorage.getItem("flowWingBinaryPath") || "",
      showJsonEditor: false,
    };

    // JSON Editor instance
    this.jsonEditor = null;

    // UI Components
    this.detailsContent = document.getElementById("details-content");
    this.statusBar = document.getElementById("status-bar");
    this.outputPanel = document.getElementById("output-panel");
    this.outputContent = document.getElementById("output-content");

    // 1. Editor
    this.editor = new CodeEditor("code-editor", (token) =>
      this.handleSelection(token)
    );

    // Debounce timer for auto-save
    this.autoSaveTimer = null;
    this.autoSaveDelay = 500; // Save 500ms after user stops typing

    this.editor.onCodeChange = (code) => {
      this.state.sourceCode = code;
      // Auto-save to localStorage with debouncing
      this.autoSaveCode(code);
    };

    // 2. Tree Viz
    this.treeViz = new TreeVisualizer("viz-container", (nodeRaw) =>
      this.handleSelection(nodeRaw)
    );

    // 3. Token Table
    this.tokenTable = new TokenTable("viz-container", (token) =>
      this.handleSelection(token)
    );

    // 4. Code History Manager
    this.codeHistory = new CodeHistory();

    this.init();
  }

  async fetchSourceCode() {
    try {
      const res = await fetch("/api/source");
      if (!res.ok) throw new Error(res.statusText);
      return await res.text();
    } catch (e) {
      console.error("Failed to fetch source code:", e);
      return null;
    }
  }

  async fetchLLVMIR() {
    try {
      const res = await fetch("/api/llvm_ir.ll");
      if (!res.ok) {
        console.warn(
          `Failed to fetch LLVM IR: ${res.status} ${res.statusText}`
        );
        return null;
      }
      const text = await res.text();
      if (!text || text.trim() === "") {
        console.warn("LLVM IR file is empty");
        return null;
      }
      return text;
    } catch (e) {
      console.error("Failed to fetch LLVM IR:", e);
      return null;
    }
  }

  async fetchLogs() {
    try {
      const res = await fetch("/api/logs");
      if (!res.ok) {
        console.warn(`Failed to fetch logs: ${res.status} ${res.statusText}`);
        return null;
      }
      const data = await res.json();
      return data.logs || null;
    } catch (e) {
      console.error("Failed to fetch logs:", e);
      return null;
    }
  }

  async init() {
    // Load saved code from localStorage first (if available)
    const savedCode = this.loadSavedCode();

    // Show loading indicator while fetching initial data
    this.showLoading("Loading initial data...");

    // Fetch Data
    const [astData, tokenData, semData, llvmIrData, logsData, sourceCode] =
      await Promise.all([
        fetchJSON("ast.json"),
        fetchJSON("tokens.json"),
        fetchJSON("semantic_tree.json"),
        this.fetchLLVMIR(),
        this.fetchLogs(),
        this.fetchSourceCode(),
      ]);

    // Be defensive about data structure - only set if data actually exists
    if (
      tokenData &&
      tokenData.tokens &&
      Array.isArray(tokenData.tokens) &&
      tokenData.tokens.length > 0
    ) {
      this.state.tokens = tokenData.tokens;
      // Prefer saved code over server code if it exists
      this.state.sourceCode = savedCode || sourceCode || "";

      if (this.state.sourceCode) {
        this.editor.render(this.state.sourceCode, this.state.tokens);
      }
    } else {
      this.state.tokens = null;
    }

    if (astData && astData.tree !== null && astData.tree !== undefined) {
      this.state.ast = astData.tree;
    } else {
      this.state.ast = null;
    }

    if (semData && semData.sem !== null && semData.sem !== undefined) {
      this.state.sem = semData.sem;
      // Store semantic data for tree visualization
      this.treeViz.setSemanticData(semData.sem);
    } else {
      this.state.sem = null;
    }

    if (
      llvmIrData &&
      typeof llvmIrData === "string" &&
      llvmIrData.trim() !== ""
    ) {
      this.state.llvmIr = llvmIrData;
    } else {
      this.state.llvmIr = null;
    }

    if (logsData && typeof logsData === "string" && logsData.trim() !== "") {
      this.state.logs = logsData;
    } else {
      this.state.logs = null;
    }

    this.setupTabs();
    this.setupResizers();
    this.setupEditMode();
    this.setupSettings();
    this.setupRunButton();
    this.setupCodeHistory();
    this.setupResponsive();
    this.setupJsonToggle();
    this.updateTabVisibility();
    // Initialize pane responsive styles
    this.updatePaneResponsiveStyles();
    this.renderView();
  }

  setupJsonToggle() {
    const jsonToggle = document.getElementById("json-toggle");
    const jsonCopyBtn = document.getElementById("json-copy-btn");
    const jsonFormatBtn = document.getElementById("json-format-btn");
    const jsonCollapseBtn = document.getElementById("json-collapse-btn");
    const jsonExpandBtn = document.getElementById("json-expand-btn");
    const jsonSearchInput = document.getElementById("json-search-input");

    if (!jsonToggle) {
      console.warn("JSON toggle button not found");
      return;
    }

    // Update toggle visibility based on current view
    const updateToggleVisibility = () => {
      const view = this.state.activeView;
      // Only show for tokens, ast, and semantic views
      const showToggle = ["tokens", "ast", "semantic"].includes(view);
      jsonToggle.style.display = showToggle ? "flex" : "none";
    };

    // Initial visibility update
    updateToggleVisibility();

    // Update visibility when tabs change
    const originalSetupTabs = this.setupTabs.bind(this);
    this.setupTabs = () => {
      // Not calling original since setupTabs is already done
    };

    // Listen for tab clicks to update JSON toggle visibility
    document.querySelectorAll(".tab-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        // Small delay to allow state update
        setTimeout(() => {
          updateToggleVisibility();
          // Hide JSON view if switching to a non-supported tab
          if (!["tokens", "ast", "semantic"].includes(this.state.activeView)) {
            this.state.showJsonEditor = false;
            this.updateJsonEditorVisibility();
          }
        }, 10);
      });
    });

    // Toggle JSON view
    jsonToggle.addEventListener("click", () => {
      this.state.showJsonEditor = !this.state.showJsonEditor;
      jsonToggle.classList.toggle("active", this.state.showJsonEditor);
      this.updateJsonEditorVisibility();
    });

    // Copy JSON button
    if (jsonCopyBtn) {
      jsonCopyBtn.addEventListener("click", () => {
        const json = this.getCurrentViewJson();
        if (json) {
          navigator.clipboard.writeText(JSON.stringify(json, null, 2)).then(() => {
            this.showNotification("JSON copied to clipboard!");
          }).catch((err) => {
            console.error("Failed to copy:", err);
            this.showNotification("Failed to copy JSON");
          });
        }
      });
    }

    // Format JSON button
    if (jsonFormatBtn) {
      jsonFormatBtn.addEventListener("click", () => {
        if (this.jsonEditor) {
          const content = this.jsonEditor.getValue();
          try {
            const parsed = JSON.parse(content);
            this.jsonEditor.setValue(JSON.stringify(parsed, null, 2));
          } catch (e) {
            console.error("Failed to format JSON:", e);
          }
        }
      });
    }

    // Collapse all button
    if (jsonCollapseBtn) {
      jsonCollapseBtn.addEventListener("click", () => {
        if (this.jsonEditor) {
          this.jsonEditor.execCommand("foldAll");
        }
      });
    }

    // Expand all button
    if (jsonExpandBtn) {
      jsonExpandBtn.addEventListener("click", () => {
        if (this.jsonEditor) {
          this.jsonEditor.execCommand("unfoldAll");
        }
      });
    }

    // Search in JSON
    if (jsonSearchInput) {
      let searchTimeout = null;
      jsonSearchInput.addEventListener("input", (e) => {
        if (searchTimeout) clearTimeout(searchTimeout);
        searchTimeout = setTimeout(() => {
          this.searchInJson(e.target.value);
        }, 200);
      });
    }
  }

  getCurrentViewJson() {
    const view = this.state.activeView;
    switch (view) {
      case "tokens":
        return { tokens: this.state.tokens };
      case "ast":
        return { tree: this.state.ast };
      case "semantic":
        return this.state.sem;
      default:
        return null;
    }
  }

  updateJsonEditorVisibility() {
    const vizContainer = document.getElementById("viz-container");
    const jsonEditorContainer = document.getElementById("json-editor-container");
    const jsonToggle = document.getElementById("json-toggle");
    const title = document.getElementById("viz-title");

    if (!vizContainer || !jsonEditorContainer) return;

    if (this.state.showJsonEditor) {
      vizContainer.style.display = "none";
      jsonEditorContainer.style.display = "flex";
      jsonToggle?.classList.add("active");
      
      // Update title to indicate JSON view
      if (title) {
        const viewName = this.getViewDisplayName(this.state.activeView);
        title.textContent = `${viewName} (JSON)`;
      }
      
      this.renderJsonEditor();
    } else {
      vizContainer.style.display = "";
      jsonEditorContainer.style.display = "none";
      jsonToggle?.classList.remove("active");
      
      // Restore original title
      if (title) {
        title.textContent = this.getViewDisplayName(this.state.activeView);
      }
      
      // Cleanup JSON editor
      if (this.jsonEditor) {
        const editorElement = this.jsonEditor.getWrapperElement();
        if (editorElement && editorElement.parentNode) {
          editorElement.parentNode.removeChild(editorElement);
        }
        this.jsonEditor = null;
      }
    }
  }

  getViewDisplayName(view) {
    switch (view) {
      case "tokens": return "Token List";
      case "ast": return "Abstract Syntax Tree";
      case "semantic": return "Semantic Tree";
      case "llvm-ir": return "LLVM IR";
      case "logs": return "Compiler Logs";
      default: return view;
    }
  }

  renderJsonEditor() {
    const jsonEditorDiv = document.getElementById("json-editor");
    if (!jsonEditorDiv) return;

    // Clear previous editor
    if (this.jsonEditor) {
      const editorElement = this.jsonEditor.getWrapperElement();
      if (editorElement && editorElement.parentNode) {
        editorElement.parentNode.removeChild(editorElement);
      }
      this.jsonEditor = null;
    }
    jsonEditorDiv.innerHTML = "";

    const jsonData = this.getCurrentViewJson();
    if (!jsonData) {
      jsonEditorDiv.innerHTML = '<div class="empty-state">No JSON data available for this view</div>';
      return;
    }

    const jsonString = JSON.stringify(jsonData, null, 2);

    // Create CodeMirror editor for JSON
    this.jsonEditor = CodeMirror(jsonEditorDiv, {
      value: jsonString,
      mode: { name: "javascript", json: true },
      theme: "monokai",
      readOnly: true,
      lineNumbers: true,
      lineWrapping: true,
      foldGutter: true,
      gutters: ["CodeMirror-linenumbers", "CodeMirror-foldgutter"],
      matchBrackets: true,
      autoCloseBrackets: true,
      indentUnit: 2,
      tabSize: 2,
      extraKeys: {
        "Ctrl-F": "findPersistent",
        "Cmd-F": "findPersistent",
      },
    });

    // Refresh editor after a short delay to ensure proper sizing
    setTimeout(() => {
      if (this.jsonEditor) {
        this.jsonEditor.refresh();
      }
    }, 100);

    // Setup resize observer
    if (window.ResizeObserver) {
      const jsonResizeObserver = new ResizeObserver(() => {
        if (this.jsonEditor) {
          this.jsonEditor.refresh();
        }
      });
      jsonResizeObserver.observe(jsonEditorDiv);
      this.jsonResizeObserver = jsonResizeObserver;
    }
  }

  searchInJson(query) {
    const searchCountSpan = document.getElementById("json-search-count");
    
    if (!this.jsonEditor || !query.trim()) {
      if (searchCountSpan) searchCountSpan.textContent = "";
      // Clear any existing search highlights
      if (this.jsonEditor) {
        this.jsonEditor.getAllMarks().forEach(mark => mark.clear());
      }
      return;
    }

    // Clear previous marks
    this.jsonEditor.getAllMarks().forEach(mark => mark.clear());

    const content = this.jsonEditor.getValue();
    const regex = new RegExp(query.replace(/[.*+?^${}()|[\]\\]/g, '\\$&'), 'gi');
    let match;
    let count = 0;
    let firstMatch = null;

    while ((match = regex.exec(content)) !== null) {
      count++;
      const from = this.jsonEditor.posFromIndex(match.index);
      const to = this.jsonEditor.posFromIndex(match.index + match[0].length);
      
      this.jsonEditor.markText(from, to, {
        className: "json-search-highlight",
      });

      if (!firstMatch) {
        firstMatch = from;
      }
    }

    if (searchCountSpan) {
      searchCountSpan.textContent = count > 0 ? `${count} match${count !== 1 ? 'es' : ''}` : 'No matches';
    }

    // Scroll to first match
    if (firstMatch) {
      this.jsonEditor.scrollIntoView(firstMatch, 100);
    }
  }

  showNotification(message) {
    // Create or reuse notification element
    let notification = document.querySelector(".copy-notification");
    if (!notification) {
      notification = document.createElement("div");
      notification.className = "copy-notification";
      document.body.appendChild(notification);
    }

    notification.textContent = message;
    notification.classList.add("show");

    setTimeout(() => {
      notification.classList.remove("show");
    }, 2000);
  }

  setupEditMode() {
    const editToggle = document.getElementById("edit-toggle");
    if (!editToggle) {
      console.error("Edit toggle button not found");
      return;
    }

    const updateToggleUI = () => {
      editToggle.classList.toggle("active", this.state.isEditMode);
      const icon = editToggle.querySelector("span");
      if (icon) {
        icon.textContent = this.state.isEditMode ? "👁️" : "✏️";
      }
      editToggle.title = this.state.isEditMode
        ? "Switch to View Mode"
        : "Switch to Edit Mode";
    };

    editToggle.addEventListener("click", async () => {
      // Prevent multiple rapid clicks
      if (editToggle.disabled) return;
      editToggle.disabled = true;

      try {
        if (this.state.isEditMode) {
          // Switching from edit to view mode
          // Get the latest code from editor before switching
          const code = this.editor.getCurrentCode();
          // Update state with the latest code
          this.state.sourceCode = code;

          // Save to localStorage immediately when switching modes
          this.autoSaveCode(code);

          // Update state first
          this.state.isEditMode = false;
          this.editor.setEditMode(false);

          // Render immediately with existing tokens using the code we just got
          this.editor.render(code, this.state.tokens || []);
          this.updateStatus("View Mode");

          // Save and optionally recompile in background
          this.saveAndRecompile(code).catch((err) => {
            console.error("Background recompile failed:", err);
          });
        } else {
          // Switching from view to edit mode
          // Ensure we have the latest source code in state
          const currentCode = this.editor.getCurrentCode();
          if (currentCode) {
            this.state.sourceCode = currentCode;
            // Save to localStorage when switching to edit mode
            this.autoSaveCode(currentCode);
          }

          this.state.isEditMode = true;
          this.editor.setEditMode(true);
          this.updateStatus("Edit Mode");
        }

        updateToggleUI();
      } catch (error) {
        console.error("Error toggling edit mode:", error);
        this.updateStatus("Error switching modes");
      } finally {
        editToggle.disabled = false;
      }
    });

    // Initialize UI state
    updateToggleUI();
  }

  async saveAndRecompile(code) {
    // Save the code
    try {
      await fetch("/api/save-source", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ code }),
      });

      // If we have binary path, recompile to get fresh tokens
      if (this.state.binaryPath) {
        this.updateStatus("Recompiling...");
        try {
          const compileRes = await fetch("/api/compile", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ binaryPath: this.state.binaryPath }),
          });

          if (compileRes.ok) {
            await this.reloadData();
            this.updateStatus("View Mode - Code updated");
          } else {
            this.updateStatus(
              "View Mode - Recompile to update syntax highlighting"
            );
          }
        } catch (error) {
          this.updateStatus(
            "View Mode - Recompile to update syntax highlighting"
          );
        }
      }
    } catch (error) {
      console.error("Failed to save code:", error);
    }
  }

  setupSettings() {
    const settingsBtn = document.getElementById("settings-btn");
    const settingsModal = document.getElementById("settings-modal");
    const settingsClose = document.getElementById("settings-close");
    const settingsCancel = document.getElementById("settings-cancel");
    const settingsSave = document.getElementById("settings-save");
    const binaryPathInput = document.getElementById("binary-path");

    // Load saved path
    binaryPathInput.value = this.state.binaryPath;

    settingsBtn.addEventListener("click", () => {
      settingsModal.style.display = "flex";
      binaryPathInput.value = this.state.binaryPath;
    });

    const closeModal = () => {
      settingsModal.style.display = "none";
    };

    settingsClose.addEventListener("click", closeModal);
    settingsCancel.addEventListener("click", closeModal);

    settingsSave.addEventListener("click", () => {
      const path = binaryPathInput.value.trim();
      if (path) {
        this.state.binaryPath = path;
        localStorage.setItem("flowWingBinaryPath", path);
        this.updateStatus("Binary path saved");
        closeModal();
      } else {
        alert("Please enter a valid binary path");
      }
    });

    // Close on outside click
    settingsModal.addEventListener("click", (e) => {
      if (e.target === settingsModal) {
        closeModal();
      }
    });
  }

  setupRunButton() {
    const runBtn = document.getElementById("run-btn");
    runBtn.addEventListener("click", () => {
      this.runCode();
    });

    // Setup output panel resizer
    this.setupOutputResizer();
    this.setupScrollToBottom();

    // Setup output close button
    const outputClose = document.getElementById("output-close");
    if (outputClose) {
      outputClose.addEventListener("click", () => {
        this.outputPanel.style.display = "none";
      });
    }
  }

  setupCodeHistory() {
    // Add history button to editor controls
    const editorControls = document.querySelector(".editor-controls");
    if (!editorControls) return;

    // Create history button
    const historyBtn = document.createElement("button");
    historyBtn.id = "code-history-btn";
    historyBtn.className = "icon-btn";
    historyBtn.title = "Code History";
    historyBtn.innerHTML = "<span>📋</span>";

    // Insert before run button
    const runBtn = document.getElementById("run-btn");
    if (runBtn && runBtn.parentElement) {
      runBtn.parentElement.insertBefore(historyBtn, runBtn);
    } else {
      editorControls.appendChild(historyBtn);
    }

    // Create history dropdown
    const historyDropdown = document.createElement("div");
    historyDropdown.id = "code-history-dropdown";
    historyDropdown.className = "code-history-dropdown";
    historyDropdown.style.display = "none";
    document.body.appendChild(historyDropdown);

    // Toggle dropdown
    historyBtn.addEventListener("click", (e) => {
      e.stopPropagation();
      const isVisible = historyDropdown.style.display !== "none";
      if (isVisible) {
        historyDropdown.style.display = "none";
      } else {
        this.showCodeHistory(historyDropdown);
      }
    });

    // Close dropdown when clicking outside
    document.addEventListener("click", (e) => {
      if (
        !historyDropdown.contains(e.target) &&
        !historyBtn.contains(e.target)
      ) {
        historyDropdown.style.display = "none";
      }
    });

    // Setup paste detection in editor
    this.setupPasteDetection();
  }

  setupPasteDetection() {
    // Detect paste events in the editor
    const editorContainer = document.getElementById("code-editor");
    if (!editorContainer) return;

    editorContainer.addEventListener("paste", (e) => {
      // Small delay to let paste complete
      setTimeout(() => {
        const code = this.editor.getCurrentCode();
        if (code && code.trim()) {
          this.codeHistory.save(code);
          this.updateStatus("Code saved to history");
        }
      }, 100);
    });
  }

  showCodeHistory(dropdown) {
    const history = this.codeHistory.getAll();

    if (history.length === 0) {
      dropdown.innerHTML = `
        <div class="code-history-empty">
          <p>No code history yet</p>
          <small>Paste code to save it here</small>
        </div>
      `;
    } else {
      const historyList = history
        .map((item, index) => {
          const time = this.codeHistory.formatTimestamp(item.timestamp);
          return `
            <div class="code-history-item" data-index="${index}">
              <div class="code-history-preview">${this.escapeHtml(
                item.preview
              )}</div>
              <div class="code-history-meta">
                <span class="code-history-time">${time}</span>
                <button class="code-history-delete" data-index="${index}" title="Delete">×</button>
              </div>
            </div>
          `;
        })
        .join("");

      dropdown.innerHTML = `
        <div class="code-history-header">
          <span>Code History (${history.length}/10)</span>
          <button class="code-history-clear" title="Clear All">Clear</button>
        </div>
        <div class="code-history-list">${historyList}</div>
      `;

      // Position dropdown near the button
      const historyBtn = document.getElementById("code-history-btn");
      if (historyBtn) {
        const rect = historyBtn.getBoundingClientRect();
        dropdown.style.top = `${rect.bottom + 5}px`;
        dropdown.style.right = `${window.innerWidth - rect.right}px`;
      }

      // Setup item click handlers
      dropdown.querySelectorAll(".code-history-item").forEach((item) => {
        item.addEventListener("click", (e) => {
          if (e.target.classList.contains("code-history-delete")) {
            e.stopPropagation();
            const index = parseInt(e.target.dataset.index);
            this.codeHistory.remove(index);
            this.showCodeHistory(dropdown);
            return;
          }
          const index = parseInt(item.dataset.index);
          const historyItem = this.codeHistory.get(index);
          if (historyItem) {
            this.loadCodeFromHistory(historyItem.code);
            dropdown.style.display = "none";
          }
        });
      });

      // Clear all button
      const clearBtn = dropdown.querySelector(".code-history-clear");
      if (clearBtn) {
        clearBtn.addEventListener("click", (e) => {
          e.stopPropagation();
          if (confirm("Clear all code history?")) {
            this.codeHistory.clear();
            this.showCodeHistory(dropdown);
          }
        });
      }
    }

    dropdown.style.display = "block";
  }

  loadCodeFromHistory(code) {
    // Switch to edit mode if not already
    if (!this.state.isEditMode) {
      this.state.isEditMode = true;
      this.editor.setEditMode(true);
    }

    // Set the code in editor
    if (this.editor.codeMirror) {
      this.editor.codeMirror.setValue(code);
      this.editor.currentCode = code;
    } else if (this.editor.textarea) {
      this.editor.textarea.value = code;
      this.editor.currentCode = code;
    }

    // Update state
    this.state.sourceCode = code;

    // Save to history again to move it to front (LRU - make it most recent)
    this.codeHistory.save(code);

    // Also save to current code storage
    this.autoSaveCode(code);

    this.updateStatus("Code loaded from history");
  }

  escapeHtml(text) {
    const div = document.createElement("div");
    div.textContent = text;
    return div.innerHTML;
  }

  setupOutputResizer() {
    const outputPanel = this.outputPanel;
    const resizer = document.getElementById("output-resizer");
    if (!resizer || !outputPanel) return;

    let isResizing = false;
    let startY = 0;
    let startHeight = 0;

    resizer.addEventListener("mousedown", (e) => {
      isResizing = true;
      startY = e.clientY;
      startHeight = parseInt(window.getComputedStyle(outputPanel).height, 10);
      resizer.classList.add("active");
      document.body.style.cursor = "row-resize";
      document.body.style.userSelect = "none";
      // Disable transition during resize for smooth dragging
      outputPanel.style.transition = "none";
      e.preventDefault();
    });

    document.addEventListener("mousemove", (e) => {
      if (!isResizing) return;

      const deltaY = startY - e.clientY; // Inverted because we're resizing from top
      const newHeight = Math.max(
        100,
        Math.min(window.innerHeight * 0.8, startHeight + deltaY)
      );
      outputPanel.style.height = `${newHeight}px`;
    });

    document.addEventListener("mouseup", () => {
      if (isResizing) {
        isResizing = false;
        resizer.classList.remove("active");
        document.body.style.cursor = "";
        document.body.style.userSelect = "";
        // Re-enable transition after resize
        outputPanel.style.transition = "";
      }
    });
  }

  setupScrollToBottom() {
    const scrollBtn = document.getElementById("scroll-to-bottom-btn");
    const outputContent = this.outputContent;
    if (!scrollBtn || !outputContent) return;

    // Function to check if user is near bottom
    const checkScrollPosition = () => {
      if (
        !outputContent ||
        outputContent.parentElement.style.display === "none"
      ) {
        scrollBtn.classList.remove("visible");
        return;
      }

      const { scrollTop, scrollHeight, clientHeight } = outputContent;
      const isNearBottom = scrollHeight - scrollTop - clientHeight < 50; // 50px threshold

      if (isNearBottom) {
        scrollBtn.classList.remove("visible");
      } else {
        scrollBtn.classList.add("visible");
      }
    };

    // Show/hide button on scroll
    outputContent.addEventListener("scroll", checkScrollPosition);

    // Check on content change
    const observer = new MutationObserver(() => {
      checkScrollPosition();
    });
    observer.observe(outputContent, { childList: true, subtree: true });

    // Scroll to bottom on button click
    scrollBtn.addEventListener("click", () => {
      outputContent.scrollTo({
        top: outputContent.scrollHeight,
        behavior: "smooth",
      });
    });

    // Initial check
    checkScrollPosition();
  }

  async runCode() {
    if (!this.state.binaryPath) {
      alert("Please configure the Flow-Wing binary path in Settings first.");
      return;
    }

    const runBtn = document.getElementById("run-btn");
    runBtn.disabled = true;

    // Reset all state except code editor
    this.resetAllState();

    this.updateStatus("Running...");
    this.showOutput("", "Running code...\n");

    try {
      // 1. Save current code
      const code = this.editor.getCurrentCode();
      const saveRes = await fetch("/api/save-source", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ code }),
      });

      if (!saveRes.ok) {
        throw new Error("Failed to save source code");
      }

      // 2. Compile and generate artifacts
      this.updateStatus("Compiling...");
      this.showOutput("", "Compiling and generating artifacts...\n");
      this.showLoading("Compiling code...");

      const compileRes = await fetch("/api/compile", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ binaryPath: this.state.binaryPath }),
      });

      const compileData = await compileRes.json();
      const compilationFailed = !compileRes.ok || !compileData.success;

      if (compilationFailed) {
        // Show complete compilation error logs
        let errorMessage = "Compilation failed\n\n";
        if (!compileRes.ok) {
          errorMessage += `HTTP Status: ${compileRes.status} ${compileRes.statusText}\n\n`;
        }
        if (compileData.results) {
          compileData.results.forEach((result, index) => {
            if (!result.success) {
              errorMessage += `--- ${result.emit.toUpperCase()} Compilation Error ---\n`;
              if (result.stderr) {
                errorMessage += `STDERR:\n${result.stderr}\n`;
              }
              if (result.stdout) {
                errorMessage += `STDOUT:\n${result.stdout}\n`;
              }
              errorMessage += `Exit Code: ${result.exitCode}\n\n`;
            }
          });
        } else if (compileData.error) {
          errorMessage += `Error: ${compileData.error}\n`;
        }
        this.showOutput(errorMessage, "error");
        this.updateStatus("Compilation failed");

        // Clear data that shouldn't exist after failed compilation
        // Keep tokens/logs as they might be available even on failure
        this.state.ast = null;
        this.state.sem = null;
        this.state.llvmIr = null;
        if (this.treeViz) {
          this.treeViz.setSemanticData(null);
        }

        // Destroy LLVM IR CodeMirror editor if it exists
        if (this.llvmIrEditor) {
          const editorElement = this.llvmIrEditor.getWrapperElement();
          if (editorElement && editorElement.parentNode) {
            editorElement.parentNode.removeChild(editorElement);
          }
          this.llvmIrEditor = null;
        }

        // Explicitly disable IR tab immediately since compilation failed
        const irTab = document.querySelector('.tab-btn[data-view="llvm-ir"]');
        if (irTab) {
          irTab.disabled = true;
          irTab.classList.add("disabled");
          irTab.setAttribute(
            "title",
            "No LLVM IR available. Compile your code successfully to generate IR."
          );
          irTab.classList.remove("active");
        }

        // If currently viewing IR tab, clear the container immediately
        if (this.state.activeView === "llvm-ir") {
          const container = document.getElementById("viz-container");
          if (container) {
            container.innerHTML = "";
          }
        }
      }

      // 3. Reload artifacts (even on failure - to load any partial data like logs/tokens)
      this.updateStatus(
        compilationFailed ? "Loading available data..." : "Reloading data..."
      );
      await this.reloadData(compilationFailed);

      // Stop here if compilation failed
      if (compilationFailed) {
        return;
      }

      // 4. Run the code
      this.updateStatus("Executing...");
      const runRes = await fetch("/api/run", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ binaryPath: this.state.binaryPath }),
      });

      if (!runRes.ok) {
        const errorData = await runRes.json().catch(() => ({
          error: `HTTP ${runRes.status}: ${runRes.statusText}`,
        }));
        let errorMessage = `Request failed\n\nHTTP Status: ${runRes.status} ${runRes.statusText}\n`;
        if (errorData.error) {
          errorMessage += `Error: ${errorData.error}\n`;
        }
        this.showOutput(errorMessage, "error");
        this.updateStatus("Execution failed");
        return;
      }

      const runData = await runRes.json();
      if (runData.success) {
        // Show complete output including both stdout and stderr (warnings might be in stderr)
        let output = "";
        if (runData.stdout) {
          output += runData.stdout;
        }
        if (runData.stderr) {
          if (output) output += "\n";
          output += "--- STDERR (Warnings/Info) ---\n";
          output += runData.stderr;
        }
        if (!output) {
          output = "Program executed successfully (no output)";
        }
        this.showOutput(output, "success");
        this.updateStatus("Execution completed");
      } else {
        // Show complete error log with all available information
        let errorMessage = "Execution failed\n\n";
        if (runData.exitCode !== undefined) {
          errorMessage += `Exit Code: ${runData.exitCode}\n\n`;
        }
        if (runData.stderr) {
          errorMessage += `--- STDERR ---\n${runData.stderr}\n\n`;
        }
        if (runData.stdout) {
          errorMessage += `--- STDOUT ---\n${runData.stdout}\n\n`;
        }
        if (runData.error) {
          errorMessage += `--- ERROR ---\n${runData.error}\n`;
        }
        if (errorMessage === "Execution failed\n\n") {
          errorMessage = "Execution failed (no error details available)";
        }
        this.showOutput(errorMessage, "error");
        this.updateStatus("Execution failed");
      }
    } catch (error) {
      // Show complete error information including stack trace if available
      let errorMessage = `Error: ${error.message}`;
      if (error.stack) {
        errorMessage += `\n\nStack Trace:\n${error.stack}`;
      }
      this.showOutput(errorMessage, "error");
      this.updateStatus("Error occurred");

      // Clear data that shouldn't exist after an error (AST, semantic, IR)
      // Keep tokens/logs as they might be available
      this.state.ast = null;
      this.state.sem = null;
      this.state.llvmIr = null;
      if (this.treeViz) {
        this.treeViz.setSemanticData(null);
      }

      // Destroy LLVM IR CodeMirror editor if it exists
      if (this.llvmIrEditor) {
        const editorElement = this.llvmIrEditor.getWrapperElement();
        if (editorElement && editorElement.parentNode) {
          editorElement.parentNode.removeChild(editorElement);
        }
        this.llvmIrEditor = null;
      }

      // If currently viewing IR tab, clear the container immediately
      if (this.state.activeView === "llvm-ir") {
        const container = document.getElementById("viz-container");
        if (container) {
          container.innerHTML = "";
        }
      }

      // Try to reload any available data (only tokens/logs) and update tab visibility
      try {
        await this.reloadData(true); // Pass true to skip fetching AST/semantic/IR
      } catch (reloadError) {
        // If reload also fails, at least update tab visibility to remove loading state
        this.updateTabVisibility();
      }
    } finally {
      runBtn.disabled = false;
    }
  }

  async reloadData(compilationFailed = false) {
    // Show loading indicator
    this.showLoading("Fetching compilation results...");

    // If compilation failed, only fetch tokens and logs (skip AST, semantic, IR)
    // These files might contain stale data from previous successful runs
    if (compilationFailed) {
      const [tokenData, logsData] = await Promise.all([
        fetchJSON("tokens.json"),
        this.fetchLogs(),
      ]);

      // Update state with new data (or null if not available)
      // Be more defensive about data structure
      this.state.tokens =
        tokenData &&
        tokenData.tokens &&
        Array.isArray(tokenData.tokens) &&
        tokenData.tokens.length > 0
          ? tokenData.tokens
          : null;
      this.state.logs =
        logsData && typeof logsData === "string" && logsData.trim() !== ""
          ? logsData
          : null;

      // Ensure AST, semantic, and IR remain null (already cleared before reloadData)
      this.state.ast = null;
      this.state.sem = null;
      this.state.llvmIr = null;

      // Explicitly disable IR tab immediately since compilation failed
      const irTab = document.querySelector('.tab-btn[data-view="llvm-ir"]');
      if (irTab) {
        irTab.disabled = true;
        irTab.classList.add("disabled");
        irTab.setAttribute(
          "title",
          "No LLVM IR available. Compile your code successfully to generate IR."
        );
        irTab.classList.remove("active");
      }
    } else {
      // Fetch all data on successful compilation
      const [astData, tokenData, semData, llvmIrData, logsData] =
        await Promise.all([
          fetchJSON("ast.json"),
          fetchJSON("tokens.json"),
          fetchJSON("semantic_tree.json"),
          this.fetchLLVMIR(),
          this.fetchLogs(),
        ]);

      // Update state with new data (or null if not available)
      // Be more defensive about data structure
      this.state.tokens =
        tokenData &&
        tokenData.tokens &&
        Array.isArray(tokenData.tokens) &&
        tokenData.tokens.length > 0
          ? tokenData.tokens
          : null;
      this.state.ast =
        astData && astData.tree !== null && astData.tree !== undefined
          ? astData.tree
          : null;
      this.state.sem =
        semData && semData.sem !== null && semData.sem !== undefined
          ? semData.sem
          : null;
      this.state.llvmIr =
        llvmIrData && typeof llvmIrData === "string" && llvmIrData.trim() !== ""
          ? llvmIrData
          : null;
      this.state.logs =
        logsData && typeof logsData === "string" && logsData.trim() !== ""
          ? logsData
          : null;
    }

    // Update semantic data in tree visualizer
    this.treeViz.setSemanticData(this.state.sem);

    // Re-render editor if not in edit mode and we have tokens
    if (!this.state.isEditMode && this.state.tokens) {
      this.editor.render(this.state.sourceCode, this.state.tokens);
    }

    // Update tab visibility based on available data
    this.updateTabVisibility();

    // Re-render current view
    this.renderView();
  }

  showOutput(content, type = "") {
    this.outputPanel.style.display = "flex";
    this.outputContent.textContent = content;
    this.outputContent.className = `output-content ${type}`;

    // Check scroll position after content update
    // Use setTimeout to ensure DOM is updated
    setTimeout(() => {
      const scrollBtn = document.getElementById("scroll-to-bottom-btn");
      if (scrollBtn && this.outputContent) {
        const { scrollTop, scrollHeight, clientHeight } = this.outputContent;
        const isNearBottom = scrollHeight - scrollTop - clientHeight < 50;
        if (isNearBottom) {
          scrollBtn.classList.remove("visible");
        } else {
          scrollBtn.classList.add("visible");
        }
      }
    }, 0);
  }

  updateStatus(message) {
    this.statusBar.textContent = message;
  }

  setupResizers() {
    const resizers = document.querySelectorAll(".resizer");
    const panes = document.querySelectorAll(".pane");

    let isResizing = false;
    let currentResizer = null;
    let startX = 0;
    let startWidths = [];
    let leftPane = null;
    let rightPane = null;

    // Only enable resizers on desktop
    const updateResizerVisibility = () => {
      const isMobile = window.innerWidth <= 1024;
      resizers.forEach((resizer) => {
        resizer.style.display = isMobile ? "none" : "";
      });
    };

    updateResizerVisibility();

    resizers.forEach((resizer) => {
      resizer.addEventListener("mousedown", (e) => {
        // Don't allow resizing on mobile
        if (window.innerWidth <= 1024) {
          e.preventDefault();
          return;
        }

        isResizing = true;
        currentResizer = resizer;
        startX = e.clientX;
        resizer.classList.add("active");

        // Find the panes this resizer is between
        const resizerPane = resizer.parentElement;
        const paneIndex = Array.from(panes).indexOf(resizerPane);

        if (paneIndex >= 0 && paneIndex < panes.length - 1) {
          leftPane = panes[paneIndex];
          rightPane = panes[paneIndex + 1];
        }

        // Store initial widths
        startWidths = Array.from(panes).map((pane) => pane.offsetWidth);

        document.body.style.cursor = "col-resize";
        document.body.style.userSelect = "none";
        e.preventDefault();
      });
    });

    document.addEventListener("mousemove", (e) => {
      if (!isResizing || !currentResizer || !leftPane || !rightPane) return;

      const deltaX = e.clientX - startX;
      const leftIndex = Array.from(panes).indexOf(leftPane);
      const rightIndex = Array.from(panes).indexOf(rightPane);

      const minWidth = 200;
      const maxWidth = window.innerWidth - minWidth * 2;

      const newLeftWidth = Math.max(
        minWidth,
        Math.min(maxWidth, startWidths[leftIndex] + deltaX)
      );
      const newRightWidth = Math.max(
        minWidth,
        Math.min(maxWidth, startWidths[rightIndex] - deltaX)
      );

      // Only resize if both panes stay within bounds
      if (newLeftWidth >= minWidth && newRightWidth >= minWidth) {
        leftPane.style.flex = `0 0 ${newLeftWidth}px`;
        rightPane.style.flex = `0 0 ${newRightWidth}px`;
      }
    });

    document.addEventListener("mouseup", () => {
      if (isResizing) {
        isResizing = false;
        if (currentResizer) {
          currentResizer.classList.remove("active");
        }
        currentResizer = null;
        leftPane = null;
        rightPane = null;
        document.body.style.cursor = "";
        document.body.style.userSelect = "";

        // Trigger responsive updates after resize
        this.updatePaneResponsiveStyles();
      }
    });

    // Update resizer visibility on resize
    window.addEventListener("resize", updateResizerVisibility);

    // Setup ResizeObserver for panes to handle dynamic responsive updates
    this.setupPaneResizeObserver();
  }

  setupPaneResizeObserver() {
    if (!window.ResizeObserver) return;

    const panes = document.querySelectorAll(".pane");
    const observer = new ResizeObserver((entries) => {
      entries.forEach((entry) => {
        const pane = entry.target;
        this.updatePaneResponsiveStyles(pane);
      });
    });

    panes.forEach((pane) => {
      observer.observe(pane);
    });

    this.paneResizeObserver = observer;
  }

  updatePaneResponsiveStyles(pane = null) {
    const panesToUpdate = pane ? [pane] : document.querySelectorAll(".pane");

    panesToUpdate.forEach((p) => {
      const width = p.offsetWidth;

      // Remove existing responsive classes
      p.classList.remove("pane-narrow", "pane-medium", "pane-wide");

      // Add appropriate class based on width
      if (width < 300) {
        p.classList.add("pane-narrow");
      } else if (width < 500) {
        p.classList.add("pane-medium");
      } else {
        p.classList.add("pane-wide");
      }

      // Update editor if this is the source pane
      if (
        p.classList.contains("source-pane") &&
        this.editor &&
        this.editor.codeMirror
      ) {
        setTimeout(() => {
          this.editor.codeMirror.refresh();
        }, 100);
      }

      // Update LLVM IR editor if visible
      if (p.classList.contains("viz-pane") && this.llvmIrEditor) {
        setTimeout(() => {
          this.llvmIrEditor.refresh();
        }, 100);
      }

      // Force reflow for logs header to ensure proper layout
      if (p.querySelector(".logs-header")) {
        const logsHeader = p.querySelector(".logs-header");
        // Trigger reflow to ensure CSS updates apply
        logsHeader.offsetHeight;
      }
    });
  }

  setupResponsive() {
    let resizeTimer;
    const handleResize = () => {
      clearTimeout(resizeTimer);
      resizeTimer = setTimeout(() => {
        // Update pane responsive styles based on new sizes
        this.updatePaneResponsiveStyles();

        // Refresh CodeMirror editors on resize
        if (this.editor && this.editor.codeMirror) {
          this.editor.codeMirror.refresh();
        }
        if (this.llvmIrEditor) {
          this.llvmIrEditor.refresh();
        }

        // Refresh tree visualization
        if (this.treeViz && this.treeViz.render) {
          const currentView = this.state.activeView;
          if (currentView === "ast" || currentView === "semantic") {
            // Trigger a re-render by calling renderView
            this.renderView();
          }
        }

        // Update output panel if visible
        if (this.outputPanel && this.outputPanel.style.display !== "none") {
          const outputContent = document.getElementById("output-content");
          if (outputContent) {
            // Trigger scroll position check
            outputContent.dispatchEvent(new Event("scroll"));
          }
        }
      }, 150);
    };

    window.addEventListener("resize", handleResize);
    window.addEventListener("orientationchange", () => {
      // Delay to allow orientation change to complete
      setTimeout(() => {
        handleResize();
        // Force a full refresh after orientation change
        if (this.editor && this.editor.codeMirror) {
          setTimeout(() => this.editor.codeMirror.refresh(), 100);
        }
        if (this.llvmIrEditor) {
          setTimeout(() => this.llvmIrEditor.refresh(), 100);
        }
      }, 200);
    });

    // Initial check
    handleResize();
  }

  setupTabs() {
    document.querySelectorAll(".tab-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        // Don't allow clicking disabled tabs
        if (btn.disabled || btn.classList.contains("disabled")) {
          return;
        }

        const view = btn.dataset.view;

        document
          .querySelectorAll(".tab-btn")
          .forEach((b) => b.classList.remove("active"));
        e.target.classList.add("active");
        this.state.activeView = view;
        this.renderView();
      });
    });
  }

  // Update tab visibility based on available data - disable tabs without data instead of hiding
  updateTabVisibility() {
    const tabs = document.querySelectorAll(".tab-btn");
    let hasEnabledTab = false;
    let firstEnabledTab = null;
    let currentTabEnabled = false;

    // Remove loading shimmer from all tabs first
    this.hideLoading();

    tabs.forEach((tab) => {
      const view = tab.dataset.view;
      let hasData = false;
      let tooltipMessage = "";

      switch (view) {
        case "tokens":
          hasData =
            this.state.tokens &&
            Array.isArray(this.state.tokens) &&
            this.state.tokens.length > 0;
          tooltipMessage =
            "No token data available. Run your code to generate tokens.";
          break;
        case "ast":
          hasData = this.state.ast !== null && this.state.ast !== undefined;
          tooltipMessage =
            "No AST data available. Compile your code successfully to generate AST.";
          break;
        case "semantic":
          hasData = this.state.sem !== null && this.state.sem !== undefined;
          tooltipMessage =
            "No semantic tree data available. Compile your code successfully to generate semantic tree.";
          break;
        case "llvm-ir":
          // More strict check - must be non-null, non-undefined, non-empty string
          hasData =
            this.state.llvmIr !== null &&
            this.state.llvmIr !== undefined &&
            typeof this.state.llvmIr === "string" &&
            this.state.llvmIr.trim() !== "";
          tooltipMessage =
            "No LLVM IR available. Compile your code successfully to generate IR.";
          break;
        case "logs":
          hasData =
            this.state.logs !== null &&
            this.state.logs !== undefined &&
            typeof this.state.logs === "string" &&
            this.state.logs.trim() !== "";
          tooltipMessage =
            "No compiler logs available. Run your code to generate logs.";
          break;
        default:
          hasData = true;
      }

      // Ensure tab is visible (not hidden)
      tab.style.removeProperty("display");
      tab.style.removeProperty("visibility");

      if (hasData) {
        // Enable tab - remove disabled state
        tab.disabled = false;
        tab.classList.remove("disabled");
        tab.removeAttribute("title");
        tab.removeAttribute("data-tooltip");

        if (!firstEnabledTab) {
          firstEnabledTab = view;
        }
        hasEnabledTab = true;
        if (view === this.state.activeView) {
          currentTabEnabled = true;
        }
      } else {
        // Disable tab - mark as disabled and add tooltip
        tab.disabled = true;
        tab.classList.add("disabled");
        tab.setAttribute("title", tooltipMessage);
        tab.setAttribute("data-tooltip", tooltipMessage);
        tab.classList.remove("active");
      }
    });

    // If current tab is disabled, switch to first enabled tab
    if (!currentTabEnabled && firstEnabledTab) {
      // If switching away from IR tab, destroy the editor
      if (this.state.activeView === "llvm-ir" && this.llvmIrEditor) {
        const editorElement = this.llvmIrEditor.getWrapperElement();
        if (editorElement && editorElement.parentNode) {
          editorElement.parentNode.removeChild(editorElement);
        }
        this.llvmIrEditor = null;
      }

      this.state.activeView = firstEnabledTab;
      tabs.forEach((tab) => {
        if (tab.dataset.view === firstEnabledTab) {
          tab.classList.add("active");
        }
      });
      this.renderView();
    }

    // If no enabled tabs, show a message in the viz container
    if (!hasEnabledTab) {
      const container = document.getElementById("viz-container");
      const title = document.getElementById("viz-title");
      if (container && title) {
        title.textContent = "No Data";
        container.innerHTML = `
          <div class="empty-state" style="padding: 40px;">
            <p>No data available yet.</p>
            <p style="font-size: 0.9em; color: var(--text-muted); margin-top: 10px;">
              Run your code to generate tokens, AST, semantic tree, IR, and logs.
            </p>
          </div>
        `;
      }
    }
  }

  // Reset all state except code editor when Run is clicked
  resetAllState() {
    // Clear all compilation data
    this.state.ast = null;
    this.state.tokens = null;
    this.state.sem = null;
    this.state.llvmIr = null;
    this.state.logs = null;

    // Reset active view to tokens (default)
    this.state.activeView = "tokens";

    // Clear semantic data from tree visualizer
    if (this.treeViz) {
      this.treeViz.setSemanticData(null);
      // Clear any highlights in tree visualizer
      if (this.treeViz.clearHighlights) {
        this.treeViz.clearHighlights();
      }
    }

    // Clear editor highlights (but keep the code)
    if (this.editor && this.editor.highlightRange) {
      this.editor.highlightRange(null);
    }

    // Destroy LLVM IR CodeMirror editor if it exists
    if (this.llvmIrEditor) {
      const editorElement = this.llvmIrEditor.getWrapperElement();
      if (editorElement && editorElement.parentNode) {
        editorElement.parentNode.removeChild(editorElement);
      }
      this.llvmIrEditor = null;
    }

    // Clear visualization container
    const container = document.getElementById("viz-container");
    const title = document.getElementById("viz-title");
    if (container) {
      container.innerHTML = "";
    }
    if (title) {
      title.textContent = "";
    }

    // Clear details panel
    if (this.detailsContent) {
      this.detailsContent.innerHTML = `
        <div class="empty-state">
          Hover over code or tree nodes to see details
        </div>
      `;
    }

    // Clear output panel content (but keep panel visible for new output)
    if (this.outputContent) {
      this.outputContent.textContent = "";
      this.outputContent.className = "output-content";
    }

    // Reset tab selection to tokens (default)
    // Ensure all tabs are visible (not hidden) - they'll be disabled by updateTabVisibility() if no data
    document.querySelectorAll(".tab-btn").forEach((tab) => {
      tab.classList.remove("active");
      tab.classList.remove("tab-loading");
      tab.classList.remove("disabled");
      tab.disabled = false;
      tab.style.removeProperty("display");
      tab.style.removeProperty("visibility");
      tab.removeAttribute("title");
      tab.removeAttribute("data-tooltip");
      if (tab.dataset.view === "tokens") {
        tab.classList.add("active");
      }
    });

    // updateTabVisibility() will be called after data loads to enable/disable tabs appropriately
  }

  // Clear all compilation data
  clearData() {
    this.state.ast = null;
    this.state.tokens = null;
    this.state.sem = null;
    this.state.llvmIr = null;
    this.state.logs = null;

    // Clear semantic data from tree visualizer
    if (this.treeViz) {
      this.treeViz.setSemanticData(null);
    }

    // Destroy LLVM IR CodeMirror editor if it exists
    if (this.llvmIrEditor) {
      const editorElement = this.llvmIrEditor.getWrapperElement();
      if (editorElement && editorElement.parentNode) {
        editorElement.parentNode.removeChild(editorElement);
      }
      this.llvmIrEditor = null;
    }

    // Destroy JSON editor if it exists
    if (this.jsonEditor) {
      const editorElement = this.jsonEditor.getWrapperElement();
      if (editorElement && editorElement.parentNode) {
        editorElement.parentNode.removeChild(editorElement);
      }
      this.jsonEditor = null;
    }

    // Reset JSON editor visibility
    this.state.showJsonEditor = false;
    this.updateJsonEditorVisibility();

    // If currently viewing IR tab, clear the container
    if (this.state.activeView === "llvm-ir") {
      const container = document.getElementById("viz-container");
      if (container) {
        container.innerHTML = "";
      }
    }

    // Don't call updateTabVisibility here - let showLoading handle showing tabs with shimmer
    // updateTabVisibility will be called after data is loaded
  }

  // Show loading indicator in viz container and tabs
  showLoading(message = "Loading data...") {
    const container = document.getElementById("viz-container");
    const title = document.getElementById("viz-title");
    if (container && title) {
      title.textContent = "Loading";
      container.innerHTML = `
        <div class="loading-container">
          <div class="loading-spinner"></div>
          <div class="loading-text">${message}</div>
        </div>
      `;
    }

    // Add shimmer effect to all tabs and ensure they're visible
    const tabs = document.querySelectorAll(".tab-btn");
    if (tabs.length === 0) {
      console.warn("No tabs found when trying to show loading state");
      return;
    }

    tabs.forEach((tab) => {
      // Remove any inline display styles that might hide the tab
      tab.style.removeProperty("display");
      tab.style.removeProperty("visibility");
      // Temporarily enable all tabs for loading shimmer
      tab.disabled = false;
      tab.classList.remove("disabled");
      tab.classList.add("tab-loading");
    });
  }

  // Hide loading indicator and remove shimmer from tabs
  hideLoading() {
    document.querySelectorAll(".tab-btn").forEach((tab) => {
      tab.classList.remove("tab-loading");
    });
  }

  renderView() {
    const title = document.getElementById("viz-title");
    const container = document.getElementById("viz-container");
    const jsonToggle = document.getElementById("json-toggle");

    // Update JSON toggle visibility based on current view
    const supportsJsonView = ["tokens", "ast", "semantic"].includes(this.state.activeView);
    if (jsonToggle) {
      jsonToggle.style.display = supportsJsonView ? "flex" : "none";
    }

    // If switching to a view that doesn't support JSON, hide the JSON editor
    if (!supportsJsonView && this.state.showJsonEditor) {
      this.state.showJsonEditor = false;
      this.updateJsonEditorVisibility();
    }

    // If JSON editor is visible, re-render it with the new view's data
    if (this.state.showJsonEditor && supportsJsonView) {
      // Update title for JSON view
      if (title) {
        title.textContent = `${this.getViewDisplayName(this.state.activeView)} (JSON)`;
      }
      this.renderJsonEditor();
      return; // Don't render the normal view
    }

    // Cleanup virtualized logs when switching away from logs tab
    if (this.state.activeView !== "logs") {
      this.cleanupVirtualizedLogs();
    }

    container.innerHTML = ""; // Clear current view

    // Check if current view has data, if not, find first available view
    let viewToRender = this.state.activeView;
    let hasData = false;

    switch (viewToRender) {
      case "tokens":
        hasData = this.state.tokens && this.state.tokens.length > 0;
        break;
      case "ast":
        hasData = this.state.ast !== null && this.state.ast !== undefined;
        break;
      case "semantic":
        hasData = this.state.sem !== null && this.state.sem !== undefined;
        break;
      case "llvm-ir":
        // More strict check - must be non-null, non-undefined, non-empty string
        hasData =
          this.state.llvmIr !== null &&
          this.state.llvmIr !== undefined &&
          typeof this.state.llvmIr === "string" &&
          this.state.llvmIr.trim() !== "";
        break;
      case "logs":
        hasData =
          this.state.logs !== null &&
          this.state.logs !== undefined &&
          this.state.logs.trim() !== "";
        break;
      default:
        hasData = true;
    }

    // If current view has no data, find first available view
    if (!hasData) {
      if (this.state.tokens && this.state.tokens.length > 0) {
        viewToRender = "tokens";
      } else if (this.state.ast !== null && this.state.ast !== undefined) {
        viewToRender = "ast";
      } else if (this.state.sem !== null && this.state.sem !== undefined) {
        viewToRender = "semantic";
      } else if (
        this.state.logs !== null &&
        this.state.logs !== undefined &&
        this.state.logs.trim() !== ""
      ) {
        viewToRender = "logs";
      } else {
        // No data available, show empty state
        if (title) title.textContent = "No Data";
        container.innerHTML = `
          <div class="empty-state" style="padding: 40px;">
            <p>No data available yet.</p>
            <p style="font-size: 0.9em; color: var(--text-muted); margin-top: 10px;">
              Run your code to generate tokens, AST, semantic tree, IR, and logs.
            </p>
          </div>
        `;
        return;
      }

      // Update active view and tab if we switched
      this.state.activeView = viewToRender;
      document.querySelectorAll(".tab-btn").forEach((tab) => {
        tab.classList.remove("active");
        if (tab.dataset.view === viewToRender) {
          tab.classList.add("active");
        }
      });
    }

    // Render the appropriate view
    if (viewToRender === "ast" && this.state.ast) {
      title.textContent = "Abstract Syntax Tree";
      this.treeViz.render(this.state.ast);
    } else if (viewToRender === "semantic" && this.state.sem) {
      title.textContent = "Semantic Tree";
      this.treeViz.render(this.state.sem.tree);
    } else if (viewToRender === "tokens" && this.state.tokens) {
      title.textContent = "Token List";
      this.tokenTable.render(this.state.tokens);
    } else if (viewToRender === "llvm-ir" && this.state.llvmIr) {
      title.textContent = "LLVM IR";
      this.renderLLVMIR();
    } else if (viewToRender === "logs") {
      title.textContent = "Compiler Logs";
      this.renderLogs();
    }
  }

  renderLLVMIR() {
    const container = document.getElementById("viz-container");
    container.innerHTML = "";

    // Always destroy existing editor first, even if IR is null
    // This ensures old content doesn't persist
    if (this.llvmIrEditor) {
      const editorElement = this.llvmIrEditor.getWrapperElement();
      if (editorElement && editorElement.parentNode) {
        editorElement.parentNode.removeChild(editorElement);
      }
      this.llvmIrEditor = null;
    }

    if (!this.state.llvmIr) {
      const empty = document.createElement("div");
      empty.className = "empty-state";
      empty.style.padding = "20px";
      empty.style.textAlign = "center";
      empty.innerHTML = `
        <p>No LLVM IR available.</p>
        <p style="font-size: 0.9em; color: var(--text-muted); margin-top: 10px;">
          Compile your code to generate LLVM IR. The file should be generated as <code>llvm_ir.ll</code> in the build directory.
        </p>
      `;
      container.appendChild(empty);
      return;
    }

    // Create CodeMirror editor for LLVM IR (read-only with syntax highlighting)
    const editorContainer = document.createElement("div");
    editorContainer.id = "llvm-ir-editor";
    editorContainer.style.width = "100%";
    editorContainer.style.height = "100%";
    editorContainer.style.minHeight = "400px";
    container.appendChild(editorContainer);

    this.llvmIrEditor = CodeMirror(editorContainer, {
      value: this.state.llvmIr,
      mode: "llvm",
      theme: "monokai",
      readOnly: true,
      lineNumbers: true,
      lineWrapping: true,
      indentUnit: 2,
      tabSize: 2,
    });

    // Setup resize observer for LLVM IR editor
    if (window.ResizeObserver && this.llvmIrEditor) {
      const llvmResizeObserver = new ResizeObserver(() => {
        if (this.llvmIrEditor && this.state.activeView === "llvm-ir") {
          this.llvmIrEditor.refresh();
        }
      });
      llvmResizeObserver.observe(container);
      // Store observer for cleanup if needed
      this.llvmIrResizeObserver = llvmResizeObserver;
    }

    // Refresh the editor to ensure proper sizing
    setTimeout(() => {
      if (this.llvmIrEditor) {
        this.llvmIrEditor.refresh();
      }
    }, 100);
  }

  renderLogs() {
    const container = document.getElementById("viz-container");

    // Cleanup previous virtualized state
    this.cleanupVirtualizedLogs();

    container.innerHTML = "";

    if (!this.state.logs || this.state.logs.trim() === "") {
      const empty = document.createElement("div");
      empty.className = "logs-empty";
      empty.innerHTML = `
        <div class="logs-empty-icon">📋</div>
        <div class="logs-empty-title">No compiler logs available</div>
        <div class="logs-empty-desc">
          Run your code to generate compiler debug logs. Make sure the compiler was built with <code>ENABLE_LOGGING</code>.
        </div>
      `;
      container.appendChild(empty);
      return;
    }

    // Parse logs first to get stats
    const parsedLogs = this.parseLogs(this.state.logs);
    const stats = this.calculateLogStats(parsedLogs);

    // Create logs container
    const logsContainer = document.createElement("div");
    logsContainer.className = "logs-container";

    // Create header with stats
    const header = document.createElement("div");
    header.className = "logs-header";

    // Stats section
    const statsDiv = document.createElement("div");
    statsDiv.className = "logs-stats";

    const logTypes = [
      "binder",
      "codegen",
      "lexer",
      "parser",
      "linking",
      "info",
      "debug",
      "CLI Parser",
    ];
    logTypes.forEach((type) => {
      if (stats[type.toUpperCase()] && stats[type.toUpperCase()] > 0) {
        const stat = document.createElement("div");
        stat.className = "logs-stat";
        stat.innerHTML = `
          <span class="logs-stat-dot ${type}"></span>
          <span class="logs-stat-count">${stats[type.toUpperCase()]}</span>
          <span>${type.charAt(0).toUpperCase() + type.slice(1)}</span>
        `;
        statsDiv.appendChild(stat);
      }
    });

    // Actions section
    const actionsDiv = document.createElement("div");
    actionsDiv.className = "logs-actions";

    // Expand/Collapse all button
    const expandAllBtn = document.createElement("button");
    expandAllBtn.className = "logs-action-btn";
    expandAllBtn.innerHTML = "⬇ Expand All";
    expandAllBtn.addEventListener("click", () => {
      const entries = logsContainer.querySelectorAll(".log-entry");
      const allExpanded = [...entries].every((e) =>
        e.classList.contains("expanded")
      );
      entries.forEach((e) => {
        if (allExpanded) {
          e.classList.remove("expanded");
        } else {
          e.classList.add("expanded");
        }
      });
      expandAllBtn.innerHTML = allExpanded ? "⬇ Expand All" : "⬆ Collapse All";
      expandAllBtn.classList.toggle("active", !allExpanded);
    });

    // Copy all logs button
    const copyAllBtn = document.createElement("button");
    copyAllBtn.className = "logs-action-btn";
    copyAllBtn.innerHTML = "📋 Copy";
    copyAllBtn.addEventListener("click", () => {
      this.copyLogsToClipboard(parsedLogs);
    });

    // Export logs button
    const exportBtn = document.createElement("button");
    exportBtn.className = "logs-action-btn";
    exportBtn.innerHTML = "💾 Export";
    exportBtn.addEventListener("click", () => {
      this.exportLogs(parsedLogs);
    });

    actionsDiv.appendChild(expandAllBtn);
    actionsDiv.appendChild(copyAllBtn);
    actionsDiv.appendChild(exportBtn);

    header.appendChild(statsDiv);
    header.appendChild(actionsDiv);

    // Create toolbar
    const toolbar = document.createElement("div");
    toolbar.className = "logs-toolbar";

    // Filter group
    const filterGroup = document.createElement("div");
    filterGroup.className = "logs-toolbar-group";

    const filterLabel = document.createElement("span");
    filterLabel.className = "logs-toolbar-label";
    filterLabel.textContent = "Filter";

    const filterSelect = document.createElement("select");
    filterSelect.className = "logs-filter-select";
    filterSelect.innerHTML = `
      <option value="all">All Types</option>
      <option value="BINDER">Binder</option>
      <option value="CODEGEN">CodeGen</option>
      <option value="LEXER">Lexer</option>
      <option value="PARSER">Parser</option>
      <option value="LINKING">Linking</option>
      <option value="INFO">Info</option>
      <option value="DEBUG">Debug</option>
      <option value="CLI PARSER">Cli Parser</option>
    `;

    filterGroup.appendChild(filterLabel);
    filterGroup.appendChild(filterSelect);

    // Search input
    const searchInput = document.createElement("input");
    searchInput.type = "text";
    searchInput.placeholder = "Search logs by message, file, or type...";
    searchInput.className = "logs-search-input";

    // Count badge
    const countBadge = document.createElement("span");
    countBadge.className = "logs-count-badge";
    countBadge.textContent = `${parsedLogs.length} logs`;

    toolbar.appendChild(filterGroup);
    toolbar.appendChild(searchInput);
    toolbar.appendChild(countBadge);

    // Logs content area
    const logsContent = document.createElement("div");
    logsContent.className = "logs-content";

    // Store references for filtering
    this.logsData = {
      parsedLogs,
      logsContent,
      countBadge,
      filterSelect,
      searchInput,
    };

    // Render logs
    this.renderParsedLogs(logsContent, parsedLogs);

    // Event listeners
    filterSelect.addEventListener("change", () => {
      this.applyLogFilters();
    });

    searchInput.addEventListener("input", () => {
      this.applyLogFilters();
    });

    logsContainer.appendChild(header);
    logsContainer.appendChild(toolbar);
    logsContainer.appendChild(logsContent);
    container.appendChild(logsContainer);
  }

  calculateLogStats(logs) {
    const stats = {};
    logs.forEach((log) => {
      const type = log.type.toUpperCase();
      stats[type] = (stats[type] || 0) + 1;
    });
    return stats;
  }

  applyLogFilters() {
    if (!this.logsData) return;

    const { parsedLogs, logsContent, countBadge, filterSelect, searchInput } =
      this.logsData;
    const filterType = filterSelect.value;
    const searchTerm = searchInput.value.toLowerCase();

    const filteredLogs = this.filterLogs(parsedLogs, filterType, searchTerm);
    this.renderParsedLogs(logsContent, filteredLogs);
    countBadge.textContent = `${filteredLogs.length} / ${parsedLogs.length} logs`;
  }

  copyLogsToClipboard(logs) {
    const text = logs
      .map((log, i) => {
        let str = `[${log.type}] ${log.file} => ${log.message}`;
        if (log.location) str += `\n  ${log.location}`;
        return str;
      })
      .join("\n\n");

    navigator.clipboard
      .writeText(text)
      .then(() => {
        this.showCopyNotification("Logs copied to clipboard");
      })
      .catch((err) => {
        console.error("Failed to copy logs:", err);
      });
  }

  exportLogs(logs) {
    const data = {
      exportedAt: new Date().toISOString(),
      totalLogs: logs.length,
      stats: this.calculateLogStats(logs),
      logs: logs,
    };

    const blob = new Blob([JSON.stringify(data, null, 2)], {
      type: "application/json",
    });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = `flowwing-logs-${Date.now()}.json`;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);

    this.showCopyNotification("Logs exported successfully");
  }

  showCopyNotification(message) {
    // Remove existing notification
    const existing = document.querySelector(".copy-notification");
    if (existing) existing.remove();

    const notification = document.createElement("div");
    notification.className = "copy-notification";
    notification.textContent = message;
    document.body.appendChild(notification);

    // Trigger animation
    requestAnimationFrame(() => {
      notification.classList.add("show");
    });

    // Remove after delay
    setTimeout(() => {
      notification.classList.remove("show");
      setTimeout(() => notification.remove(), 300);
    }, 2000);
  }

  parseLogs(logsText) {
    const logs = [];
    // Strip ANSI escape codes
    const cleanText = logsText.replace(/\x1b\[[0-9;]*m/g, "");
    const lines = cleanText.split("\n");

    let currentLog = null;

    for (let i = 0; i < lines.length; i++) {
      const line = lines[i];

      // Match log header: [DEBUG] [[TYPE]] File.cpp  => Message => Details
      const headerMatch = line.match(
        /^\[DEBUG\]\s*(?:\[\[([^\]]+)\]\])?\s*([^\s]+)\s*=>\s*(.+)$/
      );

      if (headerMatch) {
        // Save previous log
        if (currentLog) {
          logs.push(currentLog);
        }

        const [, type, file, message] = headerMatch;
        currentLog = {
          type: type || "DEBUG",
          file: file.trim(),
          message: message.trim(),
          location: "",
          details: [],
          timestamp: Date.now() + i, // Use index to preserve order
        };
      } else if (currentLog && line.startsWith("/")) {
        // Location line (file path with line number and function)
        currentLog.location = line.trim();
      } else if (currentLog && line.trim() && !line.startsWith("[DEBUG]")) {
        // Additional details
        currentLog.details.push(line.trim());
      }
    }

    // Don't forget the last log
    if (currentLog) {
      logs.push(currentLog);
    }

    return logs;
  }

  renderParsedLogs(container, logs) {
    container.innerHTML = "";

    if (logs.length === 0) {
      const noLogs = document.createElement("div");
      noLogs.className = "logs-empty";
      noLogs.innerHTML = `
        <div class="logs-empty-icon">🔍</div>
        <div class="logs-empty-title">No matching logs</div>
        <div class="logs-empty-desc">Try adjusting your filter or search criteria.</div>
      `;
      container.appendChild(noLogs);
      return;
    }

    // Use virtualized rendering for better performance with large logs
    this.setupVirtualizedLogs(container, logs);
  }

  // Virtual scrolling configuration
  getLogItemHeight() {
    return 85; // Estimated height of each log entry in pixels
  }

  setupVirtualizedLogs(container, logs) {
    const ITEM_HEIGHT = this.getLogItemHeight();
    const BUFFER_SIZE = 5; // Number of items to render above/below viewport

    // Create virtualized container structure
    const virtualContainer = document.createElement("div");
    virtualContainer.className = "logs-virtual-container";
    virtualContainer.style.position = "relative";
    virtualContainer.style.height = `${logs.length * ITEM_HEIGHT}px`;
    virtualContainer.style.minHeight = "100%";

    const viewportEl = document.createElement("div");
    viewportEl.className = "logs-virtual-viewport";
    viewportEl.style.position = "absolute";
    viewportEl.style.top = "0";
    viewportEl.style.left = "0";
    viewportEl.style.right = "0";

    virtualContainer.appendChild(viewportEl);
    container.appendChild(virtualContainer);

    // Store virtualization state
    this.virtualLogsState = {
      logs,
      container,
      virtualContainer,
      viewportEl,
      ITEM_HEIGHT,
      BUFFER_SIZE,
      lastStartIndex: -1,
      lastEndIndex: -1,
      renderedElements: new Map(), // Cache for rendered elements
    };

    // NEW: Handle window/pane resizing
    const resizeObserver = new ResizeObserver(() => {
      this.updateVirtualizedLogs();
    });
    resizeObserver.observe(container);
    this.virtualLogsResizeObserver = resizeObserver; // Store for cleanup

    // Initial render - wrapped in rAF to ensure clientHeight is calculated
    requestAnimationFrame(() => {
      this.updateVirtualizedLogs();
    });

    // Setup scroll listener with throttling
    let scrollTimeout;
    const scrollHandler = () => {
      if (scrollTimeout) return;
      scrollTimeout = requestAnimationFrame(() => {
        this.updateVirtualizedLogs();
        scrollTimeout = null;
      });
    };

    // Remove old scroll listener if exists
    if (this.logsScrollHandler) {
      container.removeEventListener("scroll", this.logsScrollHandler);
    }
    this.logsScrollHandler = scrollHandler;
    container.addEventListener("scroll", scrollHandler, { passive: true });
  }

  updateVirtualizedLogs() {
    if (!this.virtualLogsState) return;

    const {
      logs,
      container,
      viewportEl,
      ITEM_HEIGHT,
      BUFFER_SIZE,
      lastStartIndex,
      lastEndIndex,
      renderedElements,
    } = this.virtualLogsState;

    const scrollTop = container.scrollTop;
    const viewportHeight = container.clientHeight;

    // Calculate visible range
    const startIndex = Math.max(
      0,
      Math.floor(scrollTop / ITEM_HEIGHT) - BUFFER_SIZE
    );
    const endIndex = Math.min(
      logs.length - 1,
      Math.ceil((scrollTop + viewportHeight) / ITEM_HEIGHT) + BUFFER_SIZE
    );

    // Skip if the range hasn't changed significantly
    if (startIndex === lastStartIndex && endIndex === lastEndIndex) {
      return;
    }

    this.virtualLogsState.lastStartIndex = startIndex;
    this.virtualLogsState.lastEndIndex = endIndex;

    // Clear viewport and re-render visible items
    viewportEl.innerHTML = "";

    // Position the viewport at the correct scroll position
    viewportEl.style.transform = `translateY(${startIndex * ITEM_HEIGHT}px)`;

    // Render visible items
    const fragment = document.createDocumentFragment();
    for (let i = startIndex; i <= endIndex; i++) {
      const log = logs[i];
      if (!log) continue;

      // Create or reuse cached element
      let logEntry;
      if (renderedElements.has(i)) {
        logEntry = renderedElements.get(i);
      } else {
        logEntry = this.createLogEntry(log, i);
        // Cache the element for reuse (limit cache size)
        if (renderedElements.size < 200) {
          renderedElements.set(i, logEntry);
        }
      }

      fragment.appendChild(logEntry);
    }

    viewportEl.appendChild(fragment);
  }

  // Cleanup virtualized logs when switching tabs
  cleanupVirtualizedLogs() {
    if (this.logsScrollHandler && this.virtualLogsState?.container) {
      this.virtualLogsState.container.removeEventListener(
        "scroll",
        this.logsScrollHandler
      );
    }

    if (this.virtualLogsResizeObserver) {
      this.virtualLogsResizeObserver.disconnect();
      this.virtualLogsResizeObserver = null;
    }

    this.logsScrollHandler = null;
    this.virtualLogsState = null;
  }

  createLogEntry(log, index) {
    const entry = document.createElement("div");
    entry.className = `log-entry log-type-${log.type.toLowerCase()}`;
    entry.dataset.type = log.type;
    entry.dataset.index = index;

    // Main content wrapper
    const main = document.createElement("div");
    main.className = "log-entry-main";

    // Header with type badge, file, index, and actions
    const header = document.createElement("div");
    header.className = "log-entry-header";

    const typeBadge = document.createElement("span");
    typeBadge.className = `log-type-badge log-badge-${log.type.toLowerCase()}`;
    typeBadge.textContent = log.type;

    const fileName = document.createElement("span");
    fileName.className = "log-file-name";
    fileName.textContent = log.file;

    const indexSpan = document.createElement("span");
    indexSpan.className = "log-entry-index";
    indexSpan.textContent = `#${index + 1}`;

    // Actions (copy single entry)
    const actions = document.createElement("div");
    actions.className = "log-entry-actions";

    const copyBtn = document.createElement("button");
    copyBtn.className = "log-entry-action";
    copyBtn.textContent = "Copy";
    copyBtn.addEventListener("click", (e) => {
      e.stopPropagation();
      const text = `[${log.type}] ${log.file} => ${log.message}${
        log.location ? "\n" + log.location : ""
      }`;
      navigator.clipboard.writeText(text).then(() => {
        this.showCopyNotification("Log entry copied");
      });
    });

    actions.appendChild(copyBtn);

    // Expand indicator
    const expandIndicator = document.createElement("span");
    expandIndicator.className = "log-expand-indicator";
    expandIndicator.textContent = "▶";
    expandIndicator.title = "Click to expand/collapse";

    header.appendChild(expandIndicator);
    header.appendChild(typeBadge);
    header.appendChild(fileName);
    header.appendChild(indexSpan);
    header.appendChild(actions);

    // Message content
    const messageContainer = document.createElement("div");
    messageContainer.className = "log-message-container";

    // Parse message for key => value pairs
    const messageParts = log.message.split(" => ");
    messageParts.forEach((part, i) => {
      const span = document.createElement("span");
      if (i % 2 === 0) {
        span.className = "log-message-key";
      } else {
        span.className = "log-message-value";
      }
      span.textContent = part;
      messageContainer.appendChild(span);

      if (i < messageParts.length - 1) {
        const arrow = document.createElement("span");
        arrow.className = "log-message-arrow";
        arrow.textContent = " → ";
        messageContainer.appendChild(arrow);
      }
    });

    main.appendChild(header);
    main.appendChild(messageContainer);
    entry.appendChild(main);

    // Location (collapsible)
    if (log.location) {
      const locationContainer = document.createElement("div");
      locationContainer.className = "log-location";

      // Extract file path and function name
      const locMatch = log.location.match(/^(.+):(\d+)\s+in\s+(.+)$/);
      if (locMatch) {
        const [, filePath, lineNum, funcName] = locMatch;

        const pathSpan = document.createElement("span");
        pathSpan.className = "log-location-path";
        pathSpan.textContent = filePath;

        const lineSpan = document.createElement("span");
        lineSpan.className = "log-location-line";
        lineSpan.textContent = `:${lineNum}`;

        const funcSpan = document.createElement("span");
        funcSpan.className = "log-location-func";
        funcSpan.textContent = ` in ${funcName}`;

        locationContainer.appendChild(pathSpan);
        locationContainer.appendChild(lineSpan);
        locationContainer.appendChild(funcSpan);
      } else {
        locationContainer.textContent = log.location;
      }

      entry.appendChild(locationContainer);
    }

    // Toggle location visibility on click
    entry.addEventListener("click", (e) => {
      // Don't toggle if clicking on action buttons
      if (e.target.closest(".log-entry-actions")) return;
      entry.classList.toggle("expanded");
    });

    return entry;
  }

  filterLogs(logs, filterType, searchTerm) {
    return logs.filter((log) => {
      // Type filter
      if (filterType !== "all" && log.type !== filterType) {
        return false;
      }

      // Search filter
      if (searchTerm) {
        const searchableText =
          `${log.type} ${log.file} ${log.message} ${log.location}`.toLowerCase();
        if (!searchableText.includes(searchTerm)) {
          return false;
        }
      }

      return true;
    });
  }

  // --- Unified Handler for Selection (Hover) ---
  handleSelection(data) {
    if (!data) return;

    // 1. Highlight in Editor (if range exists)
    if (data.range) {
      this.editor.highlightRange(data.range);
    }

    // 2. Highlight in Tree (if active view is tree)
    if (this.state.activeView !== "tokens") {
      // Check if this is type info (from semantic type node)
      const typeId = data.typeId !== undefined ? data.typeId : data.type_id;
      if (typeId !== undefined && data.kind && !data.range) {
        // This is a type info object, highlight by typeId
        this.treeViz.highlightNodeByTypeId(typeId);
      } else {
        // Check if this is symbol info (from semantic symbol node)
        const symbolId =
          data.symbolId !== undefined ? data.symbolId : data.symbol_id;
        if (symbolId !== undefined && data.kind && !data.range) {
          // This is a symbol info object, highlight by symbolId
          this.treeViz.highlightNodeBySymbolId(symbolId);
        } else if (data.range) {
          // Regular node with range
          this.treeViz.highlightNodeByRange(data.range);
        }
      }
    }

    // 3. Render Details Sidebar
    this.renderDetails(data);
  }

  renderDetails(data) {
    this.detailsContent.innerHTML = "";

    if (!data) {
      const empty = document.createElement("div");
      empty.className = "empty-state";
      empty.textContent = "Hover over code or tree nodes to see details";
      this.detailsContent.appendChild(empty);
      return;
    }

    // Special handling for range - show visually
    if (data.range) {
      this.renderRangeVisual(data.range);
    }

    // Helper to resolve type/symbol ID to name
    const resolveTypeName = (typeId) => {
      if (
        this.state.sem &&
        this.state.sem.types &&
        this.state.sem.types[typeId]
      ) {
        const typeInfo = this.state.sem.types[typeId];
        return typeInfo.name || typeInfo.kind || `Type ${typeId}`;
      }
      return `Type ${typeId}`;
    };

    const resolveSymbolName = (symbolId) => {
      if (
        this.state.sem &&
        this.state.sem.symbols &&
        this.state.sem.symbols[symbolId]
      ) {
        const symbolInfo = this.state.sem.symbols[symbolId];
        return symbolInfo.name || symbolInfo.kind || `Symbol ${symbolId}`;
      }
      return `Symbol ${symbolId}`;
    };

    // Recursive helper to render JSON object nicely - more compact version
    const createProp = (key, val, depth = 0) => {
      // Handle special ID keys: type_id, _type_id, type_ids, _type_ids, symbol_id, _symbol_id, symbol_ids, _symbol_ids
      // Also handle exact matches: type_id, symbol_id (without underscore prefix)
      if (
        (key === "type_id" || key.endsWith("_type_id")) &&
        typeof val === "number"
      ) {
        const row = document.createElement("div");
        row.className = depth === 0 ? "prop-row-main" : "prop-row";

        const kSpan = document.createElement("span");
        kSpan.className = "prop-key";
        kSpan.textContent = key + ": ";
        row.appendChild(kSpan);

        const vSpan = document.createElement("span");
        vSpan.className = "prop-value";
        vSpan.style.color = "#ff7b72"; // Type color
        vSpan.style.fontWeight = "600";
        vSpan.textContent = `${val} (${resolveTypeName(val)})`;
        vSpan.style.cursor = "pointer";
        vSpan.title = "Click to view type details";
        vSpan.addEventListener("click", () => {
          this.navigateToType(val);
        });
        row.appendChild(vSpan);
        return row;
      }

      if (
        (key === "type_ids" || key.endsWith("_type_ids")) &&
        Array.isArray(val)
      ) {
        const row = document.createElement("div");
        row.className = depth === 0 ? "prop-row-main" : "prop-row";

        const kSpan = document.createElement("span");
        kSpan.className = "prop-key";
        kSpan.textContent = key + ": ";
        row.appendChild(kSpan);

        const container = document.createElement("div");
        container.style.display = "flex";
        container.style.flexWrap = "wrap";
        container.style.gap = "6px";
        container.style.marginTop = "4px";

        val.forEach((typeId) => {
          const badge = document.createElement("span");
          badge.className = "type-pill";
          badge.style.cursor = "pointer";
          badge.style.color = "#ff7b72";
          badge.style.borderColor = "#ff7b72";
          badge.textContent = `${typeId} (${resolveTypeName(typeId)})`;
          badge.title = "Click to view type details";
          badge.addEventListener("click", () => {
            this.navigateToType(typeId);
          });
          container.appendChild(badge);
        });

        row.appendChild(container);
        return row;
      }

      if (
        (key === "symbol_id" || key.endsWith("_symbol_id")) &&
        typeof val === "number"
      ) {
        const row = document.createElement("div");
        row.className = depth === 0 ? "prop-row-main" : "prop-row";

        const kSpan = document.createElement("span");
        kSpan.className = "prop-key";
        kSpan.textContent = key + ": ";
        row.appendChild(kSpan);

        const vSpan = document.createElement("span");
        vSpan.className = "prop-value";
        vSpan.style.color = "#79c0ff"; // Symbol color
        vSpan.style.fontWeight = "600";
        vSpan.textContent = `${val} (${resolveSymbolName(val)})`;
        vSpan.style.cursor = "pointer";
        vSpan.title = "Click to view symbol details";
        vSpan.addEventListener("click", () => {
          this.navigateToSymbol(val);
        });
        row.appendChild(vSpan);
        return row;
      }

      if (
        (key === "symbol_ids" || key.endsWith("_symbol_ids")) &&
        Array.isArray(val)
      ) {
        const row = document.createElement("div");
        row.className = depth === 0 ? "prop-row-main" : "prop-row";

        const kSpan = document.createElement("span");
        kSpan.className = "prop-key";
        kSpan.textContent = key + ": ";
        row.appendChild(kSpan);

        const container = document.createElement("div");
        container.style.display = "flex";
        container.style.flexWrap = "wrap";
        container.style.gap = "6px";
        container.style.marginTop = "4px";

        val.forEach((symbolId) => {
          const badge = document.createElement("span");
          badge.className = "type-pill";
          badge.style.cursor = "pointer";
          badge.style.background = "rgba(121, 192, 255, 0.15)";
          badge.style.borderColor = "#79c0ff";
          badge.style.color = "#79c0ff";
          badge.textContent = `${symbolId} (${resolveSymbolName(symbolId)})`;
          badge.title = "Click to view symbol details";
          badge.addEventListener("click", () => {
            this.navigateToSymbol(symbolId);
          });
          container.appendChild(badge);
        });

        row.appendChild(container);
        return row;
      }

      // For top-level important properties, use compact inline format
      if (
        depth === 0 &&
        (key === "kind" || key === "type" || key === "value" || key === "name")
      ) {
        const compactRow = document.createElement("div");
        compactRow.className = "prop-row-compact";

        const keyBadge = document.createElement("span");
        keyBadge.className = "prop-key-badge";
        keyBadge.textContent = key;

        const valueSpan = document.createElement("span");
        valueSpan.className = "prop-value-inline";
        valueSpan.textContent = String(val);

        compactRow.appendChild(keyBadge);
        compactRow.appendChild(valueSpan);
        return compactRow;
      }

      const row = document.createElement("div");
      row.className = depth === 0 ? "prop-row-main" : "prop-row";

      const kSpan = document.createElement("span");
      kSpan.className = "prop-key";
      kSpan.textContent = key + ": ";

      row.appendChild(kSpan);

      if (typeof val === "object" && val !== null) {
        // If Array
        if (Array.isArray(val)) {
          // Special handling for range arrays - show compact format
          if (key === "start" || key === "end") {
            const compactValue = `L${val[0] + 1}:C${val[1] + 1}`;
            const vSpan = document.createElement("span");
            vSpan.className = "prop-value range-compact";
            vSpan.textContent = compactValue;
            row.appendChild(vSpan);
            return row;
          }

          // Check if array contains objects (likely node objects with kind)
          const hasNodeObjects = val.some(
            (v) =>
              typeof v === "object" && v !== null && (v.kind || v.raw?.kind)
          );

          if (hasNodeObjects) {
            // Render as a list of clickable items showing Node Kind
            const container = document.createElement("div");
            container.className = "children-section";
            container.style.marginTop = "8px";

            const header = document.createElement("div");
            header.className = "children-header";
            header.textContent = `${
              key.charAt(0).toUpperCase() + key.slice(1)
            } (${val.length})`;
            container.appendChild(header);

            const list = document.createElement("div");
            list.className = "children-list";

            val.forEach((item, index) => {
              const itemEl = document.createElement("div");
              itemEl.className = "child-item";
              itemEl.style.padding = "8px 12px";
              itemEl.style.margin = "4px 0";
              itemEl.style.border = "1px solid rgba(255, 255, 255, 0.1)";
              itemEl.style.borderRadius = "4px";
              itemEl.style.backgroundColor = "rgba(255, 255, 255, 0.03)";
              itemEl.style.transition = "all 0.2s ease";
              itemEl.style.cursor = "pointer";

              // Hover effect
              itemEl.addEventListener("mouseenter", () => {
                itemEl.style.backgroundColor = "rgba(255, 255, 255, 0.08)";
                itemEl.style.borderColor = "rgba(121, 192, 255, 0.5)";
              });
              itemEl.addEventListener("mouseleave", () => {
                itemEl.style.backgroundColor = "rgba(255, 255, 255, 0.03)";
                itemEl.style.borderColor = "rgba(255, 255, 255, 0.1)";
              });

              // Click handler to navigate to item
              if (typeof item === "object" && item !== null) {
                itemEl.addEventListener("click", (e) => {
                  e.stopPropagation();
                  this.navigateToNode(item);
                });
              }

              // Display item info
              const itemInfo = document.createElement("div");
              itemInfo.style.display = "flex";
              itemInfo.style.alignItems = "center";
              itemInfo.style.gap = "8px";

              const indexBadge = document.createElement("span");
              indexBadge.style.padding = "2px 6px";
              indexBadge.style.backgroundColor = "rgba(121, 192, 255, 0.2)";
              indexBadge.style.borderRadius = "3px";
              indexBadge.style.fontSize = "0.75em";
              indexBadge.style.color = "#79c0ff";
              indexBadge.textContent = `[${index}]`;
              itemInfo.appendChild(indexBadge);

              // Show Node Kind if available
              if (typeof item === "object" && item !== null) {
                const kind = item.kind || item.raw?.kind || "Object";
                const kindSpan = document.createElement("span");
                kindSpan.style.color = "#79c0ff";
                kindSpan.style.fontWeight = "600";
                kindSpan.textContent = kind;
                itemInfo.appendChild(kindSpan);

                // Show additional info if available (name, value, etc.)
                if (item.name) {
                  const nameSpan = document.createElement("span");
                  nameSpan.style.color = "rgba(255, 255, 255, 0.7)";
                  nameSpan.textContent = `: ${item.name}`;
                  itemInfo.appendChild(nameSpan);
                } else if (
                  item.value !== undefined &&
                  typeof item.value !== "object"
                ) {
                  const valueSpan = document.createElement("span");
                  valueSpan.style.color = "rgba(255, 255, 255, 0.7)";
                  valueSpan.textContent = `: ${String(item.value)}`;
                  itemInfo.appendChild(valueSpan);
                } else if (item.raw?.name) {
                  const nameSpan = document.createElement("span");
                  nameSpan.style.color = "rgba(255, 255, 255, 0.7)";
                  nameSpan.textContent = `: ${item.raw.name}`;
                  itemInfo.appendChild(nameSpan);
                }
              } else {
                // Primitive value
                const valueSpan = document.createElement("span");
                valueSpan.style.color = "rgba(255, 255, 255, 0.7)";
                valueSpan.textContent = String(item);
                itemInfo.appendChild(valueSpan);
              }

              itemEl.appendChild(itemInfo);
              list.appendChild(itemEl);
            });

            container.appendChild(list);
            row.appendChild(container);
          } else {
            // For primitive arrays or arrays without node objects, show inline
            if (val.length <= 5) {
              const inlineValue = val.map((v) => String(v)).join(", ");
              const vSpan = document.createElement("span");
              vSpan.className = "prop-value";
              vSpan.textContent = `[${inlineValue}]`;
              row.appendChild(vSpan);
            } else {
              // Show count badge
              const badge = document.createElement("span");
              badge.className = "array-badge";
              badge.textContent = `Array[${val.length}]`;
              row.appendChild(badge);

              // Show first few items inline
              const preview = val
                .slice(0, 3)
                .map((v) => String(v))
                .join(", ");
              const vSpan = document.createElement("span");
              vSpan.className = "prop-value";
              vSpan.textContent = ` [${preview}...]`;
              row.appendChild(vSpan);
            }
          }
        } else {
          // Nested Object - make ALL nested objects clickable
          const entries = Object.entries(val).filter(
            ([k]) =>
              k !== "statements" && k !== "children" && k !== "declarators"
          );

          if (entries.length <= 3 && depth < 2) {
            // Show inline for small objects - make clickable
            const inlineParts = entries
              .map(([k, v]) => {
                if (typeof v === "object") return `${k}: {...}`;
                return `${k}: ${String(v)}`;
              })
              .join(", ");
            const vSpan = document.createElement("span");
            vSpan.className = "prop-value";
            vSpan.style.cursor = "pointer";
            vSpan.style.color = "#79c0ff";
            vSpan.style.textDecoration = "underline";
            vSpan.title = "Click to view this object's details";
            vSpan.addEventListener("click", (e) => {
              e.stopPropagation();
              e.preventDefault();
              console.log("Clicked on inline nested object:", key, val);
              this.navigateToNode(val);
            });
            vSpan.textContent = `{${inlineParts}}`;
            row.appendChild(vSpan);
          } else {
            // Show as nested for larger objects - make the key clickable
            // Make ALL nested object keys clickable
            kSpan.classList.add("clickable-nested-key");
            kSpan.style.cursor = "pointer";
            kSpan.style.color = "#79c0ff";
            kSpan.style.fontWeight = "600";
            kSpan.style.textDecoration = "underline";
            kSpan.style.position = "relative";
            kSpan.style.zIndex = "10";
            kSpan.title = "Click to view this object's details";

            // Add a visual indicator
            const clickIndicator = document.createElement("span");
            clickIndicator.style.color = "#79c0ff";
            clickIndicator.style.fontSize = "0.8em";
            clickIndicator.style.marginLeft = "4px";
            clickIndicator.style.pointerEvents = "none";
            kSpan.appendChild(clickIndicator);

            // Make the key span clickable - bind to the App instance
            const appInstance = this;
            const handleClick = function (e) {
              e.stopPropagation();
              e.preventDefault();
              console.log("Clicked on nested object:", key, val);
              appInstance.navigateToNode(val);
              return false;
            };

            kSpan.addEventListener("click", handleClick, true); // Use capture phase
            kSpan.addEventListener(
              "mousedown",
              (e) => {
                e.stopPropagation();
              },
              true
            );

            // Also make the entire row clickable as a fallback
            row.addEventListener(
              "click",
              function (e) {
                // Only trigger if clicking on the row itself, the key, or the indicator
                const target = e.target;
                if (
                  target === row ||
                  target === kSpan ||
                  target === clickIndicator ||
                  kSpan.contains(target) ||
                  (target.closest && target.closest(".prop-key") === kSpan)
                ) {
                  e.stopPropagation();
                  e.preventDefault();
                  console.log("Clicked on nested object row:", key, val);
                  appInstance.navigateToNode(val);
                  return false;
                }
              },
              true
            ); // Use capture phase

            // Also make the row hoverable
            row.classList.add("clickable-nested-object");

            const container = document.createElement("div");
            container.className = "prop-obj-compact";
            // Don't let container block clicks to the key
            container.style.pointerEvents = "auto";
            entries.forEach(([k, v]) => {
              container.appendChild(createProp(k, v, depth + 1));
            });
            row.appendChild(container);
          }
        }
      } else {
        // Primitive - inline
        const vSpan = document.createElement("span");
        vSpan.className = "prop-value";
        vSpan.textContent = String(val);
        row.appendChild(vSpan);
      }
      return row;
    };

    // Special handling for typeId/type_id and symbolId/symbol_id - show linked data
    const typeId = data.typeId !== undefined ? data.typeId : data.type_id;
    if (
      typeId !== undefined &&
      typeId !== null &&
      this.state.sem &&
      this.state.sem.types
    ) {
      const typeInfo = this.state.sem.types[typeId];
      if (typeInfo) {
        const typeCard = document.createElement("div");
        typeCard.className = "semantic-link-card type-link-card clickable-link";
        typeCard.style.cursor = "pointer";
        typeCard.innerHTML = `
          <div class="semantic-link-header">
            <span class="semantic-link-icon">🔗</span>
            <span class="semantic-link-title">Type Reference</span>
          </div>
          <div class="semantic-link-content">
            <div class="semantic-link-id">type_id: <span class="semantic-link-value">${typeId}</span></div>
            <div class="semantic-link-name">${
              typeInfo.name || typeInfo.kind || "Unknown"
            }</div>
          </div>
        `;
        typeCard.addEventListener("click", () => {
          this.navigateToType(typeId);
        });
        this.detailsContent.appendChild(typeCard);
      }
    }

    const symbolId =
      data.symbolId !== undefined ? data.symbolId : data.symbol_id;
    if (
      symbolId !== undefined &&
      symbolId !== null &&
      this.state.sem &&
      this.state.sem.symbols
    ) {
      const symbolInfo = this.state.sem.symbols[symbolId];
      if (symbolInfo) {
        const symbolCard = document.createElement("div");
        symbolCard.className =
          "semantic-link-card symbol-link-card clickable-link";
        symbolCard.style.cursor = "pointer";
        const symbolTypeId =
          symbolInfo.typeId !== undefined
            ? symbolInfo.typeId
            : symbolInfo.type_id;
        symbolCard.innerHTML = `
          <div class="semantic-link-header">
            <span class="semantic-link-icon">🔗</span>
            <span class="semantic-link-title">Symbol Reference</span>
          </div>
          <div class="semantic-link-content">
            <div class="semantic-link-id">symbol_id: <span class="semantic-link-value">${symbolId}</span></div>
            <div class="semantic-link-name">${
              symbolInfo.name || symbolInfo.kind || "Unknown"
            }</div>
            ${
              symbolTypeId !== undefined && symbolTypeId !== null
                ? `<div class="semantic-link-type">type_id: <span class="semantic-link-value clickable-link-value" data-type-id="${symbolTypeId}">${symbolTypeId}</span></div>`
                : ""
            }
          </div>
        `;
        symbolCard.addEventListener("click", () => {
          this.navigateToSymbol(symbolId);
        });
        // Make typeId clickable within symbol card
        const typeIdSpan = symbolCard.querySelector(".clickable-link-value");
        if (typeIdSpan && symbolTypeId !== undefined && symbolTypeId !== null) {
          typeIdSpan.style.cursor = "pointer";
          typeIdSpan.style.textDecoration = "underline";
          typeIdSpan.addEventListener("click", (e) => {
            e.stopPropagation();
            this.navigateToType(symbolTypeId);
          });
        }
        this.detailsContent.appendChild(symbolCard);
      }
    }

    if (
      data.symbolIds &&
      Array.isArray(data.symbolIds) &&
      this.state.sem &&
      this.state.sem.symbols
    ) {
      const symbolIdsCard = document.createElement("div");
      symbolIdsCard.className = "semantic-link-card symbol-link-card";
      const header = document.createElement("div");
      header.className = "semantic-link-header";
      header.innerHTML =
        '<span class="semantic-link-icon">🔗</span><span class="semantic-link-title">Symbol References</span>';
      symbolIdsCard.appendChild(header);

      const content = document.createElement("div");
      content.className = "semantic-link-content";
      data.symbolIds.forEach((sid) => {
        const symbolInfo = this.state.sem.symbols[sid];
        if (symbolInfo) {
          const symbolItem = document.createElement("div");
          symbolItem.className = "semantic-link-item clickable-link";
          symbolItem.style.cursor = "pointer";
          symbolItem.innerHTML = `
            <div class="semantic-link-id">symbolId: <span class="semantic-link-value">${sid}</span></div>
            <div class="semantic-link-name">${
              symbolInfo.name || symbolInfo.kind || "Unknown"
            }</div>
          `;
          symbolItem.addEventListener("click", () => {
            this.navigateToSymbol(sid);
          });
          content.appendChild(symbolItem);
        }
      });
      symbolIdsCard.appendChild(content);
      this.detailsContent.appendChild(symbolIdsCard);
    }

    // Special handling for children, statements, and declarators arrays
    const renderChildrenArray = (key, children) => {
      if (!Array.isArray(children) || children.length === 0) return null;

      const section = document.createElement("div");
      section.className = "children-section";

      const header = document.createElement("div");
      header.className = "children-header";
      header.textContent = `${key.charAt(0).toUpperCase() + key.slice(1)} (${
        children.length
      })`;
      section.appendChild(header);

      const list = document.createElement("div");
      list.className = "children-list";

      children.forEach((child, index) => {
        if (!child || typeof child !== "object") return;

        const childItem = document.createElement("div");
        childItem.className = "child-item";
        childItem.style.padding = "8px 12px";
        childItem.style.margin = "4px 0";
        childItem.style.border = "1px solid rgba(255, 255, 255, 0.1)";
        childItem.style.borderRadius = "4px";
        childItem.style.backgroundColor = "rgba(255, 255, 255, 0.03)";
        childItem.style.transition = "all 0.2s ease";

        // Hover effect
        childItem.addEventListener("mouseenter", () => {
          childItem.style.backgroundColor = "rgba(255, 255, 255, 0.08)";
          childItem.style.borderColor = "rgba(121, 192, 255, 0.5)";
        });
        childItem.addEventListener("mouseleave", () => {
          childItem.style.backgroundColor = "rgba(255, 255, 255, 0.03)";
          childItem.style.borderColor = "rgba(255, 255, 255, 0.1)";
        });

        // Click handler to navigate to child
        childItem.addEventListener("click", () => {
          this.navigateToNode(child);
        });

        // Display child info
        const childInfo = document.createElement("div");
        childInfo.style.display = "flex";
        childInfo.style.alignItems = "center";
        childInfo.style.gap = "8px";

        const indexBadge = document.createElement("span");
        indexBadge.textContent = `[${index}]`;
        indexBadge.style.color = "#8b949e";
        indexBadge.style.fontSize = "12px";
        indexBadge.style.minWidth = "30px";

        const kindBadge = document.createElement("span");
        kindBadge.textContent = child.kind || "Unknown";
        kindBadge.style.color = "#79c0ff";
        kindBadge.style.fontWeight = "600";
        kindBadge.style.fontSize = "13px";

        childInfo.appendChild(indexBadge);
        childInfo.appendChild(kindBadge);

        // Add range info if available
        if (child.range) {
          const rangeInfo = document.createElement("span");
          rangeInfo.textContent = `L${child.range.start[0] + 1}:C${
            child.range.start[1] + 1
          }`;
          rangeInfo.style.color = "#8b949e";
          rangeInfo.style.fontSize = "11px";
          rangeInfo.style.marginLeft = "auto";
          childInfo.appendChild(rangeInfo);
        }

        childItem.appendChild(childInfo);
        list.appendChild(childItem);
      });

      section.appendChild(list);
      return section;
    };

    // Render children arrays if they exist
    if (
      data.children &&
      Array.isArray(data.children) &&
      data.children.length > 0
    ) {
      const childrenSection = renderChildrenArray("children", data.children);
      if (childrenSection) {
        this.detailsContent.appendChild(childrenSection);
      }
    }

    if (
      data.statements &&
      Array.isArray(data.statements) &&
      data.statements.length > 0
    ) {
      const statementsSection = renderChildrenArray(
        "statements",
        data.statements
      );
      if (statementsSection) {
        this.detailsContent.appendChild(statementsSection);
      }
    }

    if (
      data.declarators &&
      Array.isArray(data.declarators) &&
      data.declarators.length > 0
    ) {
      const declaratorsSection = renderChildrenArray(
        "declarators",
        data.declarators
      );
      if (declaratorsSection) {
        this.detailsContent.appendChild(declaratorsSection);
      }
    }

    if (
      data.expression &&
      typeof data.expression === "object" &&
      data.expression !== null
    ) {
      const expressionSection = renderChildrenArray("expression", [
        data.expression,
      ]);
      if (expressionSection) {
        this.detailsContent.appendChild(expressionSection);
      }
    }

    // Root properties - prioritize important ones
    const importantKeys = ["kind", "type", "value", "name", "lexeme"];
    const otherKeys = [];

    Object.keys(data).forEach((key) => {
      if (
        key === "range" ||
        key === "typeId" ||
        key === "type_id" || // Also exclude snake_case
        key === "symbolId" ||
        key === "symbol_id" || // Also exclude snake_case
        key === "symbolIds" ||
        key === "symbol_ids" || // Also exclude snake_case
        key === "statements" ||
        key === "expression" ||
        key === "declarators" ||
        key === "children"
      )
        return;

      if (importantKeys.includes(key)) {
        importantKeys.splice(importantKeys.indexOf(key), 1);
        importantKeys.push(key);
      } else {
        otherKeys.push(key);
      }
    });

    // Render important properties first
    importantKeys.forEach((key) => {
      if (data.hasOwnProperty(key)) {
        this.detailsContent.appendChild(createProp(key, data[key]));
      }
    });

    // Render other properties (but skip typeId/type_id and symbolId/symbol_id as they're handled specially above)
    otherKeys.forEach((key) => {
      // Skip if already handled specially
      if (
        key === "typeId" ||
        key === "type_id" ||
        key === "symbolId" ||
        key === "symbol_id"
      ) {
        return;
      }
      this.detailsContent.appendChild(createProp(key, data[key]));
    });
  }

  renderRangeVisual(range) {
    const rangeCard = document.createElement("div");
    rangeCard.className = "range-visual-card";

    const header = document.createElement("div");
    header.className = "range-header";
    const icon = document.createElement("span");
    icon.className = "range-icon";
    icon.textContent = "📍";
    const title = document.createElement("span");
    title.className = "range-title";
    title.textContent = "Code Location";
    header.appendChild(icon);
    header.appendChild(title);

    const rangeGrid = document.createElement("div");
    rangeGrid.className = "range-grid";

    // Start position
    const startCard = document.createElement("div");
    startCard.className = "range-position-card start";
    const startLabel = document.createElement("div");
    startLabel.className = "range-label";
    startLabel.textContent = "Start";
    const startLine = document.createElement("div");
    startLine.className = "range-line";
    startLine.innerHTML = `<span class="range-value">Line ${
      range.start[0] + 1
    }</span>`;
    const startCol = document.createElement("div");
    startCol.className = "range-col";
    startCol.innerHTML = `<span class="range-value">Col ${
      range.start[1] + 1
    }</span>`;
    startCard.appendChild(startLabel);
    startCard.appendChild(startLine);
    startCard.appendChild(startCol);

    // End position
    const endCard = document.createElement("div");
    endCard.className = "range-position-card end";
    const endLabel = document.createElement("div");
    endLabel.className = "range-label";
    endLabel.textContent = "End";
    const endLine = document.createElement("div");
    endLine.className = "range-line";
    endLine.innerHTML = `<span class="range-value">Line ${
      range.end[0] + 1
    }</span>`;
    const endCol = document.createElement("div");
    endCol.className = "range-col";
    endCol.innerHTML = `<span class="range-value">Col ${
      range.end[1] + 1
    }</span>`;
    endCard.appendChild(endLabel);
    endCard.appendChild(endLine);
    endCard.appendChild(endCol);

    rangeGrid.appendChild(startCard);
    rangeGrid.appendChild(endCard);
    rangeCard.appendChild(header);
    rangeCard.appendChild(rangeGrid);

    this.detailsContent.appendChild(rangeCard);
  }

  navigateToType(typeId) {
    if (!this.state.sem || !this.state.sem.types || !typeId) return;

    const typeInfo = this.state.sem.types[typeId];
    if (!typeInfo) return;

    // Switch to semantic view if not already
    if (this.state.activeView !== "semantic") {
      document.querySelectorAll(".tab-btn").forEach((btn) => {
        if (btn.dataset.view === "semantic") {
          btn.classList.add("active");
        } else {
          btn.classList.remove("active");
        }
      });
      this.state.activeView = "semantic";
      this.renderView();
    }

    // Highlight in tree
    const foundNode = this.treeViz.highlightNodeByTypeId(typeId);

    // Show type details
    this.renderDetails(typeInfo);

    // Highlight in editor if type has a range
    if (typeInfo.range) {
      this.editor.highlightRange(typeInfo.range);
    }
  }

  navigateToNode(nodeData) {
    if (!nodeData) return;

    // Find the node in the tree and navigate to it
    const found = this.treeViz.navigateToNode(nodeData);

    if (found) {
      // Show the node's details
      this.renderDetails(nodeData);

      // Highlight in editor if node has a range
      if (nodeData.range) {
        this.editor.highlightRange(nodeData.range);
      }
    } else {
      // If not found in tree, still show details
      this.renderDetails(nodeData);

      if (nodeData.range) {
        this.editor.highlightRange(nodeData.range);
      }
    }
  }

  navigateToSymbol(symbolId) {
    if (!this.state.sem || !this.state.sem.symbols || symbolId === undefined)
      return;

    const symbolInfo = this.state.sem.symbols[symbolId];
    if (!symbolInfo) return;

    // Switch to semantic view if not already
    if (this.state.activeView !== "semantic") {
      document.querySelectorAll(".tab-btn").forEach((btn) => {
        if (btn.dataset.view === "semantic") {
          btn.classList.add("active");
        } else {
          btn.classList.remove("active");
        }
      });
      this.state.activeView = "semantic";
      this.renderView();
    }

    // Highlight in tree
    const foundNode = this.treeViz.highlightNodeBySymbolId(symbolId);

    // Show symbol details
    this.renderDetails(symbolInfo);

    // Highlight in editor if symbol has a range
    if (symbolInfo.range) {
      this.editor.highlightRange(symbolInfo.range);
    }
  }

  // Auto-save current code to localStorage with debouncing
  autoSaveCode(code) {
    // Clear existing timer
    if (this.autoSaveTimer) {
      clearTimeout(this.autoSaveTimer);
    }

    // Set new timer to save after delay
    this.autoSaveTimer = setTimeout(() => {
      try {
        localStorage.setItem("flowWingCurrentCode", code);
        // Optionally show a subtle indicator (but don't spam the status bar)
        // this.updateStatus("Code auto-saved");
      } catch (e) {
        console.error("Failed to auto-save code:", e);
        // If quota exceeded, try to clear old data
        if (e.name === "QuotaExceededError") {
          console.warn("LocalStorage quota exceeded, clearing old code");
          try {
            localStorage.removeItem("flowWingCurrentCode");
            localStorage.setItem("flowWingCurrentCode", code);
          } catch (e2) {
            console.error("Failed to save after clearing:", e2);
          }
        }
      }
    }, this.autoSaveDelay);
  }

  // Load saved code from localStorage
  loadSavedCode() {
    try {
      const saved = localStorage.getItem("flowWingCurrentCode");
      return saved || null;
    } catch (e) {
      console.error("Error loading saved code:", e);
      return null;
    }
  }

  // Clear saved code (useful for resetting)
  clearSavedCode() {
    try {
      localStorage.removeItem("flowWingCurrentCode");
    } catch (e) {
      console.error("Error clearing saved code:", e);
    }
  }
}

new App();
