#!/usr/bin/env bash
#
# FlowWing Compiler
# Copyright (C) 2023-2026 Kushagra Rathore
#
# Verify cmake/deps_builder/deps.lock matches the versions actually pinned in
# cmake/deps_builder/CMakeLists.txt.
#
# WHY THIS EXISTS
#
#   The CI dependency cache key hashes deps.lock, not CMakeLists.txt, so that
#   editing a comment does not throw away an hour of build on three platforms.
#
#   That buys speed at the cost of a new failure mode: bump a version in
#   CMakeLists.txt, forget deps.lock, and the cache key does not change — so CI
#   silently restores and reuses the OLD dependencies. Nothing fails; you just
#   get a build of something you did not ask for, and it can persist for weeks.
#
#   Nothing reads deps.lock at build time (CMakeLists.txt remains the single
#   source of truth for what is fetched), so the drift cannot be caught by the
#   build itself. This check is what catches it.
#
# USAGE
#   scripts/check-deps-lock.sh
#
set -euo pipefail

CMAKE_FILE="cmake/deps_builder/CMakeLists.txt"
LOCK_FILE="cmake/deps_builder/deps.lock"

for f in "$CMAKE_FILE" "$LOCK_FILE"; do
    [ -f "$f" ] || { echo "error: $f not found (run from the repo root)" >&2; exit 1; }
done

# Windows runners ship Python as `python`, not `python3`, so pick whichever
# exists rather than assuming the POSIX name.
PY_BIN=""
for c in python3 python; do
    if command -v "$c" >/dev/null 2>&1; then PY_BIN="$c"; break; fi
done
[ -n "$PY_BIN" ] || { echo "error: neither python3 nor python found on PATH" >&2; exit 1; }

"$PY_BIN" - "$CMAKE_FILE" "$LOCK_FILE" <<'PY'
import re, sys

cmake_path, lock_path = sys.argv[1], sys.argv[2]
cmake = open(cmake_path).read()
lock  = open(lock_path).read()

def lock_value(name):
    m = re.search(rf'^{re.escape(name)}\s+(\S+)\s*$', lock, re.M)
    return m.group(1) if m else None

# Each entry: (lock key, human name, how to pull the version out of CMakeLists)
def llvm_version():
    m = re.search(r'set\(FW_LLVM_VERSION\s+"([^"]+)"\)', cmake)
    return f"llvmorg-{m.group(1)}" if m else None

def git_tag_after(project):
    # GIT_REPOSITORY ".../<project>.git"  ...  GIT_TAG "<value>"
    #
    # Comment lines may sit between the two — mongo-c-driver has a long one
    # explaining why it is pinned to 2.3.3. An earlier version of this regex
    # required them to be adjacent and so went blind to that dependency
    # entirely, which is exactly the silent drift this script exists to stop.
    m = re.search(
        rf'GIT_REPOSITORY\s+"[^"]*{re.escape(project)}[^"]*"'
        rf'(?:\s*(?:#[^\n]*)?\n)*'          # blank and comment lines
        rf'\s*GIT_TAG\s+"([^"]+)"',
        cmake)
    return m.group(1) if m else None

def url_capture(pattern):
    m = re.search(pattern, cmake)
    return m.group(1) if m else None

checks = [
    ("llvm",           "LLVM",             llvm_version()),
    ("raylib",         "raylib",           git_tag_after("raylib")),
    ("libuv",          "libuv",            git_tag_after("libuv")),
    ("llhttp",         "llhttp",           url_capture(r'llhttp/archive/refs/tags/(release/v[0-9.]+)\.tar\.gz')),
    ("mongo-c-driver", "mongo-c-driver",   git_tag_after("mongo-c-driver")),
    ("googletest",     "googletest",       url_capture(r'googletest/releases/download/(v[0-9.]+)/')),
]

# The artifact release tag is derived from FW_LLVM_VERSION, so it is checked
# against what CMake would actually build rather than read separately.
m = re.search(r'set\(FW_LLVM_VERSION\s+"([^"]+)"\)', cmake)
if m:
    checks.append(("llvm-artifact-release-tag", "LLVM artifact release tag",
                   f"deps-llvm-{m.group(1)}"))

fail = 0
for key, label, actual in checks:
    expected = lock_value(key)
    if actual is None:
        print(f"  ?? {label}: could not read the version from {cmake_path}")
        print(f"     This check needs updating — it is now blind to this dependency.")
        fail = 1
    elif expected is None:
        print(f"  !! {label}: missing from {lock_path} (CMakeLists has {actual})")
        fail = 1
    elif expected != actual:
        print(f"  !! {label}: deps.lock says {expected}, CMakeLists.txt says {actual}")
        fail = 1
    else:
        print(f"  ok {label}: {actual}")

if fail:
    print()
    print(f"error: {lock_path} is out of step with {cmake_path}.", file=sys.stderr)
    print("       The CI dependency cache key hashes deps.lock, so leaving these", file=sys.stderr)
    print("       out of step makes CI silently reuse the OLD dependencies.", file=sys.stderr)
    print("       Update deps.lock to match and re-run.", file=sys.stderr)
    sys.exit(1)

print()
print("deps.lock is in step with CMakeLists.txt")
PY
