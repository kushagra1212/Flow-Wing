// What is inside a .wasm file: its sections and their sizes, and what it
// imports and exports. Read from the bytes; nothing is run.

export type Section = { id: number; name: string; size: number; count: number | null };

export type WasmInfo = {
  size: number;
  sections: Section[];
  imports: WebAssembly.ModuleImportDescriptor[];
  exports: WebAssembly.ModuleExportDescriptor[];
};

const NAMES = [
  "custom", "type", "import", "function", "table", "memory", "global",
  "export", "start", "element", "code", "data", "data count", "tag",
];

// Sections that start with the number of entries they hold.
const COUNTED = new Set([1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 13]);

function leb(bytes: Uint8Array, at: number): [value: number, next: number] {
  let value = 0;
  let shift = 0;
  let i = at;
  for (;;) {
    const byte = bytes[i++];
    value += (byte & 0x7f) * 2 ** shift;
    if ((byte & 0x80) === 0) return [value, i];
    shift += 7;
  }
}

export async function inspectWasm(buffer: ArrayBuffer): Promise<WasmInfo> {
  const bytes = new Uint8Array(buffer);
  const sections: Section[] = [];
  let at = 8; // magic and version
  while (at < bytes.length) {
    const id = bytes[at];
    const [size, start] = leb(bytes, at + 1);
    let name = NAMES[id] ?? `unknown (${id})`;
    let count: number | null = null;
    if (id === 0) {
      const [length, text] = leb(bytes, start);
      name = `custom: ${new TextDecoder().decode(bytes.subarray(text, text + length))}`;
    } else if (COUNTED.has(id)) {
      count = leb(bytes, start)[0];
    }
    sections.push({ id, name, size, count });
    at = start + size;
  }
  // compile, not new WebAssembly.Module: browsers refuse to compile a large
  // module synchronously on the page's thread.
  const module = await WebAssembly.compile(buffer);
  return {
    size: bytes.length,
    sections,
    imports: WebAssembly.Module.imports(module),
    exports: WebAssembly.Module.exports(module),
  };
}
