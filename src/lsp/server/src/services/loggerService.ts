/**
 * Logger service for Flow-Wing LSP.
 * - Verbose logging when FLOWWING_LSP_DEBUG=1 (opt-in, works even during tests)
 * - Silent during tests unless FLOWWING_LSP_DEBUG=1
 */

const isTest =
  process.env.NODE_ENV === "test" ||
  process.env.MOCHA_WORKER_ID !== undefined;

const isDebugEnabled = (): boolean =>
  process.env.FLOWWING_LSP_DEBUG === "1" || process.env.FLOWWING_LSP_DEBUG === "true";

function formatMessage(level: string, tag: string, ...args: unknown[]): string {
  const timestamp = new Date().toISOString();
  const prefix = `[${timestamp}] [${level}] [${tag}]`;
  const parts = args.map((a) =>
    typeof a === "object" && a !== null ? JSON.stringify(a) : String(a)
  );
  return `${prefix} ${parts.join(" ")}`;
}

export const logger = {
  /** Fine-grained trace (completion flow, token parsing) */
  trace(tag: string, ...args: unknown[]): void {
    if (isDebugEnabled()) {
      console.log(formatMessage("TRACE", tag, ...args));
    }
  },

  /** Debug-level (symbol resolution, type inference) */
  debug(tag: string, ...args: unknown[]): void {
    if (isDebugEnabled()) {
      console.log(formatMessage("DEBUG", tag, ...args));
    }
  },

  /** Info-level (general flow) */
  info(tag: string, ...args: unknown[]): void {
    if (isDebugEnabled()) {
      console.log(formatMessage("INFO", tag, ...args));
    }
  },

  /** Warnings (always logged unless in test) */
  warn(tag: string, ...args: unknown[]): void {
    if (!isTest) {
      console.warn(formatMessage("WARN", tag, ...args));
    }
  },

  /** Errors (always logged) */
  error(tag: string, ...args: unknown[]): void {
    console.error(formatMessage("ERROR", tag, ...args));
  },

  /** Check if debug logging is enabled (for conditional logic) */
  isEnabled(): boolean {
    return isDebugEnabled();
  },
};
