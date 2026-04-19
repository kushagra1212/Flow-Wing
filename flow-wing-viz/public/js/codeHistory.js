// Code History Manager with LRU Cache (max 10 items)
export class CodeHistory {
  constructor(storageKey = "flowWingCodeHistory") {
    this.storageKey = storageKey;
    this.maxItems = 10;
  }

  // Get all code history
  getAll() {
    try {
      const stored = localStorage.getItem(this.storageKey);
      if (!stored) return [];
      const history = JSON.parse(stored);
      return Array.isArray(history) ? history : [];
    } catch (e) {
      console.error("Error reading code history:", e);
      return [];
    }
  }

  // Save code to history (LRU - most recent at index 0)
  save(code) {
    if (!code || typeof code !== "string" || code.trim() === "") {
      return; // Don't save empty code
    }

    try {
      let history = this.getAll();
      
      // Remove duplicate if exists (move to front)
      history = history.filter((item) => item.code !== code);
      
      // Add new code at the beginning (most recent)
      const newItem = {
        code: code,
        timestamp: Date.now(),
        preview: this.getPreview(code),
      };
      history.unshift(newItem);
      
      // Keep only maxItems (remove oldest)
      if (history.length > this.maxItems) {
        history = history.slice(0, this.maxItems);
      }
      
      // Save to localStorage
      localStorage.setItem(this.storageKey, JSON.stringify(history));
      return history;
    } catch (e) {
      console.error("Error saving code history:", e);
      // If quota exceeded, remove oldest items
      if (e.name === "QuotaExceededError") {
        this.clear();
        // Try saving just this one
        try {
          localStorage.setItem(
            this.storageKey,
            JSON.stringify([
              {
                code: code,
                timestamp: Date.now(),
                preview: this.getPreview(code),
              },
            ])
          );
        } catch (e2) {
          console.error("Failed to save code after clearing:", e2);
        }
      }
    }
  }

  // Get preview of code (first line or first 50 chars)
  getPreview(code) {
    if (!code) return "";
    const lines = code.split("\n");
    const firstLine = lines[0] || "";
    if (firstLine.length <= 50) return firstLine;
    return firstLine.substring(0, 47) + "...";
  }

  // Get code by index
  get(index) {
    const history = this.getAll();
    if (index >= 0 && index < history.length) {
      return history[index];
    }
    return null;
  }

  // Get most recent code
  getLatest() {
    const history = this.getAll();
    return history.length > 0 ? history[0] : null;
  }

  // Clear all history
  clear() {
    try {
      localStorage.removeItem(this.storageKey);
    } catch (e) {
      console.error("Error clearing code history:", e);
    }
  }

  // Remove item by index
  remove(index) {
    try {
      let history = this.getAll();
      if (index >= 0 && index < history.length) {
        history.splice(index, 1);
        localStorage.setItem(this.storageKey, JSON.stringify(history));
        return history;
      }
    } catch (e) {
      console.error("Error removing code from history:", e);
    }
    return this.getAll();
  }

  // Format timestamp for display
  formatTimestamp(timestamp) {
    const date = new Date(timestamp);
    const now = new Date();
    const diffMs = now - date;
    const diffMins = Math.floor(diffMs / 60000);
    const diffHours = Math.floor(diffMs / 3600000);
    const diffDays = Math.floor(diffMs / 86400000);

    if (diffMins < 1) return "Just now";
    if (diffMins < 60) return `${diffMins}m ago`;
    if (diffHours < 24) return `${diffHours}h ago`;
    if (diffDays < 7) return `${diffDays}d ago`;
    return date.toLocaleDateString();
  }
}

