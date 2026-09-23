// A program in the page's address, so a link opens it: #code=<data>, where
// data is the UTF-8 source, deflated when the browser can, as base64url.
// "z" or "p" in front says which.

function toBase64Url(bytes: Uint8Array): string {
  let binary = "";
  for (const byte of bytes) binary += String.fromCharCode(byte);
  return btoa(binary).replace(/\+/g, "-").replace(/\//g, "_").replace(/=+$/, "");
}

function fromBase64Url(text: string): Uint8Array {
  const binary = atob(text.replace(/-/g, "+").replace(/_/g, "/"));
  return Uint8Array.from(binary, (c) => c.charCodeAt(0));
}

async function pipe(bytes: Uint8Array, stream: TransformStream<Uint8Array, Uint8Array>): Promise<Uint8Array> {
  const body = new Blob([bytes]).stream().pipeThrough(stream);
  return new Uint8Array(await new Response(body).arrayBuffer());
}

export async function encodeSource(source: string): Promise<string> {
  const bytes = new TextEncoder().encode(source);
  if (typeof CompressionStream !== "undefined") {
    return "z" + toBase64Url(await pipe(bytes, new CompressionStream("deflate-raw")));
  }
  return "p" + toBase64Url(bytes);
}

export async function decodeSource(data: string): Promise<string | null> {
  try {
    const bytes = fromBase64Url(data.slice(1));
    if (data[0] === "z") {
      return new TextDecoder().decode(await pipe(bytes, new DecompressionStream("deflate-raw")));
    }
    if (data[0] === "p") return new TextDecoder().decode(bytes);
  } catch {
    // a damaged link: fall through
  }
  return null;
}

export function sourceFromHash(hash: string): string | null {
  const match = /(?:^#|&)code=([^&]+)/.exec(hash);
  return match ? match[1] : null;
}
