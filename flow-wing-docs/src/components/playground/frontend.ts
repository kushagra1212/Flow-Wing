// Live analysis while you type: the compiler's front end, in a Web Worker
// (static/playground/frontend-worker.js). Nothing leaves the browser.
//
// At most one request waits behind the one running: a newer edit replaces it,
// so typing fast never builds a backlog.

export type Emit = "tokens" | "ast" | "sem";

export type StageResult = { emit: Emit; ok: boolean; ms: number; json: any; output: string };

export type Analysis =
  | { source: string; stages: StageResult[] }
  | { source: string; unavailable: string };

type Request = { source: string; target: string; resolve: (analysis: Analysis | null) => void };

export class FrontendAnalyzer {
  private worker: Worker | null = null;
  private running: Request | null = null;
  private queued: Request | null = null;
  private nextId = 0;

  constructor(private readonly url: string) {}

  // Resolves with the analysis, or null if a newer request replaced this one.
  // target: the build to check the program for, "wasm32" or "native".
  analyse(source: string, target: string): Promise<Analysis | null> {
    return new Promise((resolve) => {
      const request = { source, target, resolve };
      if (this.running) {
        this.queued?.resolve(null);
        this.queued = request;
      } else {
        this.start(request);
      }
    });
  }

  dispose(): void {
    this.worker?.terminate();
    this.worker = null;
  }

  private start(request: Request): void {
    this.running = request;
    const worker = this.ensureWorker();
    worker.postMessage({ id: ++this.nextId, source: request.source, target: request.target });
  }

  private ensureWorker(): Worker {
    if (this.worker) return this.worker;
    const worker = new Worker(this.url);
    worker.onmessage = ({ data }) => {
      const done = this.running;
      this.running = null;
      done?.resolve(data.unavailable
        ? { source: done.source, unavailable: data.unavailable }
        : { source: done.source, stages: data.stages });
      this.next();
    };
    worker.onerror = (event) => {
      event.preventDefault();
      const done = this.running;
      this.running = null;
      // A crashed worker is replaced by a fresh one for the next request.
      this.worker?.terminate();
      this.worker = null;
      done?.resolve({ source: done.source, unavailable: event.message || "The analysis worker stopped." });
      this.next();
    };
    this.worker = worker;
    return worker;
  }

  private next(): void {
    const request = this.queued;
    this.queued = null;
    if (request) this.start(request);
  }
}
