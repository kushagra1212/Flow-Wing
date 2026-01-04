// Convert compiler [line, col] range to linear string index for highlighting
export function getRangeIndices(sourceLines, startPos, endPos) {
  // startPos = [line, col], endPos = [line, col]
  // Note: Compiler lines seem to be 0-indexed based on your JSON

  // We don't strictly need linear index for HTML generation if we render line by line,
  // but useful for debugging.
  return {
    startLine: startPos[0],
    startCol: startPos[1],
    endLine: endPos[0],
    endCol: endPos[1],
  };
}

export async function fetchJSON(endpoint) {
  try {
    const res = await fetch(`/api/${endpoint}`);
    if (!res.ok) throw new Error(res.statusText);
    return await res.json();
  } catch (e) {
    console.error("Fetch error:", e);
    return null;
  }
}
