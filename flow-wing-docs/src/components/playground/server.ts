// The Flow-Wing server: server.fg in the Flow-Wing repo
// (flowwing-explorer/flow-wing-website), the one behind
// flowwing.kushagrarathore.in.
//
//   POST /compile?target=wasm32|native&opt=N[&wat=1]    body: the program
//        ─▶ { ok, stage, compiler, log, diagnostics, ir, js, wasm, wat }
//   POST /run                                            body: {"code", "input"}
//        ─▶ { output, exitCode }        the program, run natively in a sandbox
//
// Both go as text/plain, a "simple" cross-origin request, so the browser sends
// them at once, without a CORS preflight.

export type Target = "wasm32" | "native";

export type BuildStep = { step: string; ms?: number; ok?: boolean; js?: number; wasm?: number };

export type Build = {
  ok: boolean;
  stage: string; // where it stopped: compile, link, sandbox, busy, ... or done
  compiler: string;
  target: Target;
  opt: number;
  log: BuildStep[];
  diagnostics: string;
  ir: string;
  js: string;
  wasm: ArrayBuffer | null;
  wat: string;
  watTruncated: boolean;
};

export type RunResult = { output: string; exitCode: number };

// What the page logs about each request.
export type Exchange<T> = { value: T; status: number; ms: number; bytes: number };

export class ServerUnreachable extends Error {}

function base64ToBytes(base64: string): ArrayBuffer {
  const binary = atob(base64);
  const bytes = new Uint8Array(binary.length);
  for (let i = 0; i < binary.length; i++) bytes[i] = binary.charCodeAt(i);
  return bytes.buffer;
}

export class PlaygroundServer {
  constructor(readonly base: string) {}

  get host(): string {
    try {
      return new URL(this.base).host;
    } catch {
      return this.base;
    }
  }

  private async post(path: string, body: string, signal: AbortSignal) {
    const started = performance.now();
    let response: Response;
    try {
      response = await fetch(this.base.replace(/\/$/, "") + path, {
        method: "POST",
        headers: { "Content-Type": "text/plain;charset=UTF-8" },
        body,
        signal,
      });
    } catch (error) {
      if (signal.aborted) throw error;
      throw new ServerUnreachable(`Could not reach the Flow-Wing server at ${this.host}.`);
    }
    const text = await response.text();
    return { text, status: response.status, ms: performance.now() - started, bytes: text.length };
  }

  async compile(
    source: string,
    options: { target: Target; opt: number; wat?: boolean },
    signal: AbortSignal,
  ): Promise<Exchange<Build>> {
    const query = `target=${options.target}&opt=${options.opt}${options.wat ? "&wat=1" : ""}`;
    const { text, status, ms, bytes } = await this.post(`/compile?${query}`, source, signal);
    let body: any = null;
    try {
      body = JSON.parse(text);
    } catch {
      // not the server's JSON: a proxy error page, or an older server
    }
    const value: Build = {
      ok: Boolean(body?.ok),
      stage: body?.stage ?? "server",
      compiler: body?.compiler ?? "",
      target: options.target,
      opt: options.opt,
      log: body?.log ?? [],
      diagnostics: body?.diagnostics ??
        (status === 404
          ? `The server at ${this.host} has no /compile yet. It needs a newer Flow-Wing server.`
          : `The server at ${this.host} answered ${status}.`),
      ir: body?.ir ?? "",
      js: body?.js ?? "",
      wasm: body?.wasm ? base64ToBytes(body.wasm) : null,
      wat: body?.wat ?? "",
      watTruncated: Boolean(body?.watTruncated),
    };
    return { value, status, ms, bytes };
  }

  async run(source: string, input: string, signal: AbortSignal): Promise<Exchange<RunResult>> {
    const { text, status, ms, bytes } = await this.post(
      "/run", JSON.stringify({ code: source, input }), signal);
    // The output keeps the compiler's colour codes raw, which JSON does not
    // allow in a string; escape them first, as the website's own page does.
    const safe = text.replace(/[\x00-\x1f]/g, (c) => "\\u" + c.charCodeAt(0).toString(16).padStart(4, "0"));
    let value: RunResult;
    try {
      const body = JSON.parse(safe);
      value = { output: body.output ?? "", exitCode: typeof body.exitCode === "number" ? body.exitCode : 0 };
    } catch {
      value = { output: `The server at ${this.host} answered ${status}.`, exitCode: -1 };
    }
    return { value, status, ms, bytes };
  }
}
