#!/usr/bin/env bash
# Builds a Flow-Wing program to WebAssembly and runs it with Node.
#
#   make run-wasm FILE=path/to/prog.fg
#   make run-wasm FILE=path/to/prog.fg ARGS=--html   # also a page for the browser
#
# A convenience around the compiler, which does the real work:
#
#   FlowWing prog.fg --target=wasm32 --emit=exe -o build/wasm/prog/prog.js
#
# The first run also builds the wasm runtime (make build-wasm-runtime).
# Programs that `spawn` build, but stop at the first task switch until the
# scheduler has a wasm backend.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
COMPILER="$ROOT/build/sdk/bin/FlowWing"

fail() { echo "error: $*" >&2; exit 1; }

source_file="${1:-}"
html=0
[ "${2:-}" = "--html" ] && html=1
[ -n "$source_file" ] || fail "usage: make run-wasm FILE=path/to/prog.fg [ARGS=--html]"
[ -f "$source_file" ] || fail "no such file: $source_file"
[ -x "$COMPILER" ] || fail "compiler not built: run make build-aot-release"

if [ ! -f "$ROOT/build/sdk/lib/wasm32-emscripten/libflowwing_rt.a" ]; then
  bash "$ROOT/scripts/wasm/build-runtime.sh" "$ROOT/build/sdk"
fi

stem="$(basename "${source_file%.*}")"
out="$ROOT/build/wasm/$stem"

"$COMPILER" "$source_file" --target=wasm32 --emit=exe -o "$out/$stem.js"
if [ "$html" = 1 ]; then
  "$COMPILER" "$source_file" --target=wasm32 --emit=exe -o "$out/web/$stem.html" --progress=never
  echo "     Browser: python3 -m http.server 8000 -d build/wasm/$stem/web"
  echo "              then open http://localhost:8000/$stem.html"
fi

echo "     Running $stem.wasm ($(wc -c <"$out/$stem.wasm" | tr -d ' ') bytes) with Node"
echo
node "$out/$stem.js"
