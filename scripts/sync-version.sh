#!/usr/bin/env bash
#
# Single-source-of-truth version sync. Reads the top-level VERSION.txt file
# and rewrites every package.json / package-lock.json that ships the
# FlowWing extension so they match.
#
# CMake reads VERSION.txt directly via file(STRINGS ...) in CMakeLists.txt
# and propagates it to src/common/version.h via cmake/version.cmake, so this
# script only needs to handle the Node/VS Code side.
#
# NOTE: file is VERSION.txt, not VERSION. The repo root is on the C++
# include path and macOS/Windows are case-insensitive, so a bare VERSION
# collides with the C++20 standard header <version>.
#
# Usage:
#   ./scripts/sync-version.sh              # interactive prompt (or re-sync if blank)
#   ./scripts/sync-version.sh 1.2.3        # explicit (also rewrites VERSION.txt)
#   CI=1 ./scripts/sync-version.sh         # non-interactive, re-sync from VERSION.txt
#
# Requirements: jq.

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$REPO_ROOT"

VERSION_FILE="VERSION.txt"

if [[ ! -f "$VERSION_FILE" ]]; then
    echo "error: $VERSION_FILE missing at repo root" >&2
    exit 1
fi

CURRENT_VERSION="$(tr -d '[:space:]' < "$VERSION_FILE")"

if [[ $# -ge 1 ]]; then
    NEW_VERSION="$1"
elif [[ -t 0 && -z "${CI:-}" ]]; then
    printf "Current version: %s\nNew version (Enter to keep): " "$CURRENT_VERSION" >&2
    read -r NEW_VERSION
    NEW_VERSION="${NEW_VERSION:-$CURRENT_VERSION}"
else
    NEW_VERSION="$CURRENT_VERSION"
fi

NEW_VERSION="$(printf '%s' "$NEW_VERSION" | tr -d '[:space:]')"
if [[ -z "$NEW_VERSION" ]]; then
    echo "error: version cannot be empty" >&2
    exit 1
fi
if ! [[ "$NEW_VERSION" =~ ^[0-9]+\.[0-9]+\.[0-9]+([-+.][0-9A-Za-z.-]+)?$ ]]; then
    echo "error: '$NEW_VERSION' is not a valid semver" >&2
    exit 1
fi

if [[ "$NEW_VERSION" != "$CURRENT_VERSION" ]]; then
    echo "$NEW_VERSION" > "$VERSION_FILE"
fi

if ! command -v jq >/dev/null 2>&1; then
    echo "error: jq is required" >&2
    exit 1
fi

echo "Syncing FlowWing version to $NEW_VERSION"

PACKAGES=(
    src/lsp/package.json
    src/lsp/client/package.json
    src/lsp/server/package.json
    flow-wing-docs/package.json
    flow-wing-viz/package.json
)

for pkg in "${PACKAGES[@]}"; do
    if [[ ! -f "$pkg" ]]; then
        echo "  skip (missing): $pkg"
        continue
    fi
    tmp="$(mktemp)"
    jq --arg v "$NEW_VERSION" '.version = $v' "$pkg" > "$tmp"
    mv "$tmp" "$pkg"
    echo "  updated: $pkg"
done

# Lockfiles record the package's own version in two spots ("version" at the
# root and packages.[""].version). Patch both with jq instead of running
# `npm install --package-lock-only` so we don't trigger a network fetch /
# dependency resolve just to bump a single number.
LOCKFILES=(
    src/lsp/package-lock.json
    src/lsp/client/package-lock.json
    src/lsp/server/package-lock.json
)

for lock in "${LOCKFILES[@]}"; do
    if [[ ! -f "$lock" ]]; then
        echo "  skip (missing): $lock"
        continue
    fi
    tmp="$(mktemp)"
    jq --arg v "$NEW_VERSION" '
        .version = $v
        | (.packages[""].version) |= (if . == null then . else $v end)
    ' "$lock" > "$tmp"
    mv "$tmp" "$lock"
    echo "  updated: $lock"
done

echo "Done. CMake picks up the new version on the next configure."
