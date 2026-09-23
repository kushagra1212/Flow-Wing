#!/usr/bin/env bash
# Compiles the Flow-Wing runtime to wasm32, once, into the SDK:
#
#   <sdk>/lib/wasm32-emscripten/libflowwing_rt.a
#   <sdk>/lib/wasm32-emscripten/node-host.js
#
# FlowWing --target=wasm32 --emit=exe links every program against these.
# Needs emsdk: emcc on PATH, or $EMSDK, or ~/emsdk.
#
#   make build-wasm-runtime
#
# Not in the runtime: mongo, raylib and vortex, which need sockets, a window
# or a database. Bringing one of those fails at link time with the missing
# symbol named. The file module is in; it reads synchronously on wasm.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SDK_DIR="${1:-$ROOT/build/sdk}"
OUT="$SDK_DIR/lib/wasm32-emscripten"

fail() { echo "error: $*" >&2; exit 1; }

if ! command -v emcc >/dev/null 2>&1; then
  EMSDK_DIR="${EMSDK:-$HOME/emsdk}"
  [ -f "$EMSDK_DIR/emsdk_env.sh" ] || fail "emcc not found. Install emsdk, or set EMSDK to its folder."
  # shellcheck disable=SC1091
  source "$EMSDK_DIR/emsdk_env.sh" >/dev/null 2>&1
fi

M="$ROOT/fw-modules"
C_SOURCES=(
  "$M"/built_in_module/*.c
  "$M"/dynamic/*.c
  "$M"/gc/src/*.c
  "$M"/text_module/*.c
)
CXX_SOURCES=(
  "$M"/vec_module/*.cpp
  "$M"/map_module/*.cpp
  "$M"/io_module/*.cpp
  "$M"/file_module/*.cpp
)
INCLUDES=(-I"$M/gc/include" -I"$M")

objects="$OUT/objects"
rm -rf "$objects"
mkdir -p "$objects"

echo "   Compiling the Flow-Wing runtime for wasm32"
for src in "${C_SOURCES[@]}"; do
  emcc -c -O2 "${INCLUDES[@]}" "$src" -o "$objects/$(basename "${src%.*}").o"
done
for src in "${CXX_SOURCES[@]}"; do
  em++ -c -O2 -std=c++17 "${INCLUDES[@]}" "$src" -o "$objects/$(basename "${src%.*}").o"
done

rm -f "$OUT/libflowwing_rt.a"
emar rcs "$OUT/libflowwing_rt.a" "$objects"/*.o
rm -rf "$objects"
cp "$ROOT/scripts/wasm/node-host.js" "$OUT/node-host.js"

count=$(( ${#C_SOURCES[@]} + ${#CXX_SOURCES[@]} ))
echo "    Finished $OUT/libflowwing_rt.a ($count sources)"
