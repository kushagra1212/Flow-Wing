#!/usr/bin/env bash
# Builds the Flow-Wing front end (lexer, parser, semantic analysis) for the
# browser, into build/wasm-frontend/flowwing-frontend.{js,wasm}:
#
#   make build-wasm-frontend
#
# See scripts/wasm/frontend/CMakeLists.txt. Needs emsdk: emcc on PATH, or
# $EMSDK, or ~/emsdk.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
OUT="${1:-$ROOT/build/wasm-frontend}"

fail() { echo "error: $*" >&2; exit 1; }

if ! command -v emcmake >/dev/null 2>&1; then
  EMSDK_DIR="${EMSDK:-$HOME/emsdk}"
  [ -f "$EMSDK_DIR/emsdk_env.sh" ] || fail "emcc not found. Install emsdk, or set EMSDK to its folder."
  # shellcheck disable=SC1091
  source "$EMSDK_DIR/emsdk_env.sh" >/dev/null 2>&1
fi

echo "   Compiling the Flow-Wing front end for the browser"
mkdir -p "$OUT"
emcmake cmake -S "$ROOT/scripts/wasm/frontend" -B "$OUT" -G Ninja \
  -DCMAKE_BUILD_TYPE=Release >"$OUT/configure.log" 2>&1 \
  || { cat "$OUT/configure.log"; fail "configure failed"; }
cmake --build "$OUT"

js="$OUT/flowwing-frontend.js"
wasm="$OUT/flowwing-frontend.wasm"
echo "    Finished $js ($(wc -c <"$wasm" | tr -d ' ') bytes of wasm)"
