// Where playground code is compiled. The page sees only PlaygroundCompiler,
// so a compiler that runs in the browser can sit next to the server one
// without changing the page.

export type CompileResult =
  | { ok: true; js: string; wasm: ArrayBuffer; diagnostics: string }
  | { ok: false; diagnostics: string };

export interface PlaygroundCompiler {
  compile(source: string, signal: AbortSignal): Promise<CompileResult>;
}

// playground/server: POST {source}, get back {ok, js, wasm (base64), diagnostics}.
export function serverCompiler(url: string): PlaygroundCompiler {
  return {
    async compile(source, signal) {
      let response: Response;
      try {
        response = await fetch(url, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ source }),
          signal,
        });
      } catch (error) {
        if (signal.aborted) {
          throw error;
        }
        return {
          ok: false,
          diagnostics: `Could not reach the compile server at ${url}.`,
        };
      }

      const body = await response.json().catch(() => null);
      if (!body || !body.ok) {
        return {
          ok: false,
          diagnostics:
            body?.diagnostics ?? `The compile server answered ${response.status}.`,
        };
      }
      return {
        ok: true,
        js: body.js,
        wasm: base64ToBytes(body.wasm).buffer,
        diagnostics: body.diagnostics ?? "",
      };
    },
  };
}

function base64ToBytes(base64: string): Uint8Array {
  const binary = atob(base64);
  const bytes = new Uint8Array(binary.length);
  for (let i = 0; i < binary.length; i++) {
    bytes[i] = binary.charCodeAt(i);
  }
  return bytes;
}
