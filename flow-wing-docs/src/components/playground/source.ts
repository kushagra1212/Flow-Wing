// Positions in the source. The compiler counts lines from 0 and columns in
// bytes of UTF-8; the editor counts UTF-16 code units from the start of the
// text. A line with "é" or "日本" in it is where the two differ.

export type Point = [line: number, column: number];
export type Range = { start: Point; end: Point };

// A compiler range as [start, end) offsets into the editor's text.
export type Span = { start: number; end: number };

export class SourceMap {
  private readonly lineStarts: number[] = [0];

  constructor(private readonly text: string) {
    for (let i = 0; i < text.length; i++) {
      if (text[i] === "\n") this.lineStarts.push(i + 1);
    }
  }

  get lineCount(): number {
    return this.lineStarts.length;
  }

  // The offset of byte `column` of line `line`. A byte inside a character
  // (the lexer can stop there) gives the character's own offset.
  offset([line, column]: Point): number {
    const start = this.lineStarts[Math.min(Math.max(line, 0), this.lineStarts.length - 1)];
    const end = line + 1 < this.lineStarts.length ? this.lineStarts[line + 1] - 1 : this.text.length;
    let bytes = 0;
    let i = start;
    while (i < end) {
      const code = this.text.codePointAt(i)!;
      const size = code < 0x80 ? 1 : code < 0x800 ? 2 : code < 0x10000 ? 3 : 4;
      if (bytes + size > column) break;
      bytes += size;
      i += code > 0xffff ? 2 : 1;
    }
    return i;
  }

  span(range: Range): Span {
    return { start: this.offset(range.start), end: this.offset(range.end) };
  }

  // The 0-based line an offset is on.
  lineOf(offset: number): number {
    let low = 0;
    let high = this.lineStarts.length - 1;
    while (low < high) {
      const mid = (low + high + 1) >> 1;
      if (this.lineStarts[mid] <= offset) low = mid;
      else high = mid - 1;
    }
    return low;
  }
}

// Human form of a compiler point: lines and columns from 1, columns in
// characters, as an editor shows them.
export function describePoint(map: SourceMap, point: Point): string {
  const offset = map.offset(point);
  const lineStart = map.offset([point[0], 0]);
  return `${point[0] + 1}:${offset - lineStart + 1}`;
}
