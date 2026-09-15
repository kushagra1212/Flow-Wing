#!/usr/bin/env bash
#
# FlowWing Compiler
# Copyright (C) 2023-2026 Kushagra Rathore
#
# Package the LLVM/Clang/LLD half of a built dependency prefix into a single
# release artifact.
#
# WHY ONLY LLVM
#
#   Measured on a cold CI run: the dependency build takes ~66 minutes, and
#   ~64 of those are LLVM. libuv, llhttp, mongo-c-driver, raylib and gtest
#   together finish in 1m45s. So LLVM is the only dependency worth shipping as
#   a prebuilt binary — the rest keep building from source, which also keeps
#   them easy to bump without republishing anything.
#
# WHY NOT THE OFFICIAL LLVM RELEASE
#
#   FlowWing builds LLVM with LLVM_ENABLE_RTTI=ON and LLVM_ENABLE_EH=ON.
#   The official llvm-project release tarballs are built with both OFF.
#   Publishing our own keeps the flags identical to a from-source build, so
#   downloading and building produce the same compiler.
#
# USAGE
#   scripts/package-llvm-artifact.sh <install-prefix> <output-dir> [build-type]
#
# EXAMPLE
#   scripts/package-llvm-artifact.sh .fw_dependencies/install dist Release
#
set -euo pipefail

PREFIX="${1:?usage: $0 <install-prefix> <output-dir> [build-type]}"
OUTDIR="${2:?usage: $0 <install-prefix> <output-dir> [build-type]}"
BUILD_TYPE="${3:-Release}"

if [ ! -d "$PREFIX/lib/cmake/llvm" ]; then
    echo "error: $PREFIX does not look like a built dependency prefix" >&2
    echo "       (no lib/cmake/llvm). Build the dependencies first." >&2
    exit 1
fi

# Read the version from LLVM's own config rather than hardcoding it here, so a
# version bump in deps_builder/CMakeLists.txt cannot drift out of sync with the
# artifact name.
LLVM_VERSION="$(sed -n 's/^set(LLVM_PACKAGE_VERSION \([0-9.]*\)).*/\1/p' \
    "$PREFIX/lib/cmake/llvm/LLVMConfig.cmake" | head -1)"
: "${LLVM_VERSION:?could not read LLVM_PACKAGE_VERSION from LLVMConfig.cmake}"

# The consumer (cmake/deps_builder/CMakeLists.txt) builds the artifact name
# from CMAKE_HOST_SYSTEM_NAME / CMAKE_HOST_SYSTEM_PROCESSOR. On Darwin and
# Linux those agree with uname. On Windows they do NOT — under Git Bash
# `uname -s` reports something like MINGW64_NT-10.0 where CMake says "Windows",
# and `uname -m` says x86_64 where CMake says AMD64. So allow an override, and
# Windows CI must set it:
#
#   FW_ARTIFACT_OS=Windows FW_ARTIFACT_ARCH=AMD64 scripts/package-llvm-artifact.sh ...
OS="${FW_ARTIFACT_OS:-$(uname -s)}"      # Darwin / Linux / Windows
ARCH="${FW_ARTIFACT_ARCH:-$(uname -m)}"  # arm64 / x86_64 / AMD64
NAME="llvm-${LLVM_VERSION}-${OS}-${ARCH}-${BUILD_TYPE}"
STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT

echo "--> packaging $NAME"
echo "    prefix: $PREFIX"

# ---------------------------------------------------------------------------
# What is NOT LLVM.
#
# The prefix is shared: every dependency installs into it. Rather than listing
# LLVM's thousands of files, list the handful that belong to the others and
# take everything else. Each entry is a path relative to the prefix.
#
# Keep this in step with cmake/deps_builder/CMakeLists.txt. If a new dependency
# is added there and not here, its files would be swept into the LLVM artifact
# — wasteful, and confusing when versions drift. The verification step at the
# bottom catches the common cases.
# ---------------------------------------------------------------------------
# Headers, CMake packages and pkg-config are named the same everywhere.
EXCLUDES=(
    # mongo-c-driver + libbson
    "include/mongoc-*"
    "include/bson-*"
    "lib/cmake/mongoc-*"
    "lib/cmake/bson-*"
    "share/mongo-c-driver"

    # libuv
    "include/uv.h"
    "include/uv"
    "lib/cmake/libuv"

    # llhttp
    "include/llhttp.h"
    "lib/cmake/llhttp"

    # raylib
    "include/raylib.h"
    "include/raymath.h"
    "include/rlgl.h"
    "lib/cmake/raylib"

    # googletest
    "include/gtest"
    "lib/cmake/GTest"

    # Every .pc file in the prefix belongs to a non-LLVM dependency; LLVM does
    # not install pkg-config files.
    "lib/pkgconfig"
)

# LIBRARY FILENAMES ARE PLATFORM-SPECIFIC, and getting this wrong is silent.
#
# MSVC produces mongoc2.lib where Unix produces libmongoc2.a, and executables
# carry .exe. A Unix-only list simply matches nothing on Windows, so every
# non-LLVM library was copied into the zip — libuv, mongoc, bson, raylib,
# llhttp and gtest all shipped inside an artifact labelled "LLVM".
#
# Nothing warned, because the leak checks at the bottom were Unix-only too.
# Both lists have to name the platform's real files or neither works.
if [ "$OS" = "Windows" ]; then
    EXCLUDES+=(
        "bin/mongoc2-stat.exe"
        "lib/mongoc2.lib"
        "lib/bson2.lib"
        # libuv installs BOTH: libuv.lib is the static archive, uv.lib the
        # import library for uv.dll. Neither belongs here.
        "lib/libuv.lib"
        "lib/uv.lib"
        "lib/llhttp.lib"
        "lib/raylib.lib"
        "lib/gtest.lib"
        "lib/gtest_main.lib"
    )
else
    EXCLUDES+=(
        "bin/mongoc2-stat"
        "lib/libmongoc2.a"
        "lib/libbson2.a"
        "lib/libuv.a"
        "lib/libllhttp.a"
        "lib/libraylib.a"
        "lib/libgtest.a"
        "lib/libgtest_main.a"
    )
fi

TAR_EXCLUDE_ARGS=()
for e in "${EXCLUDES[@]}"; do
    TAR_EXCLUDE_ARGS+=(--exclude="./$e")
done

# ---------------------------------------------------------------------------
# Licence obligations.
#
# LLVM is Apache 2.0 WITH LLVM Exceptions. Section 4 of Apache 2.0 requires the
# licence text to travel with any redistribution, in source or binary form. The
# artifact is a binary redistribution, so the text ships inside it.
# ---------------------------------------------------------------------------
LIC_DIR="$STAGE/THIRD_PARTY_LICENSES"
mkdir -p "$LIC_DIR"

# Derived from the prefix, NOT hardcoded: a Debug prefix lives under
# .fw_dependencies_debug/ and a Release one under .fw_dependencies/, so a fixed
# path would silently package the Debug tree with the Release tree's licence —
# or, since a missing licence is fatal below, refuse to build Debug at all.
LLVM_SRC="$(cd "$PREFIX/.." && pwd)/build/llvm_external-prefix/src/llvm_external"
if [ -f "$LLVM_SRC/LICENSE.TXT" ]; then
    cp "$LLVM_SRC/LICENSE.TXT" "$LIC_DIR/LLVM-LICENSE.TXT"
else
    echo "error: LLVM LICENSE.TXT not found at $LLVM_SRC" >&2
    echo "       Refusing to build an artifact without it: Apache 2.0 section 4" >&2
    echo "       requires the licence to accompany a binary redistribution." >&2
    exit 1
fi

cat > "$LIC_DIR/README.md" <<EOF
# Third-party licences

This archive contains a compiled build of the LLVM Project
(LLVM, Clang and LLD), version ${LLVM_VERSION}.

| Component | Version | Licence | Upstream |
|---|---|---|---|
| LLVM / Clang / LLD | ${LLVM_VERSION} | Apache License 2.0 with LLVM Exceptions | https://github.com/llvm/llvm-project |

The full licence text is in \`LLVM-LICENSE.TXT\`.

## Modifications

None. This is an unmodified build of the upstream \`llvmorg-${LLVM_VERSION}\`
tag. It differs from the binaries published by the LLVM project only in its
build configuration:

    LLVM_ENABLE_RTTI=ON          (upstream releases: OFF)
    LLVM_ENABLE_EH=ON            (upstream releases: OFF)
    LLVM_TARGETS_TO_BUILD=Native (upstream releases: all targets)

## Not an official LLVM release

This build is produced by the Flow-Wing project for its own use. It is not
endorsed by, affiliated with, or supported by the LLVM Project.
EOF

# ---------------------------------------------------------------------------
# Build the archive.
#
# FORMAT DIFFERS BY PLATFORM, and not for cosmetic reasons.
#
#   Unix    .tar.xz via `xz -9`. Debug archives are nearly all DWARF and
#           compress about 9x at -9 against 5.7x at -1. On a 10 GB debug
#           prefix that is the difference between fitting in one GitHub
#           release asset (2 GiB cap) and having to split it. tar also
#           preserves symlinks and the executable bit.
#
#   Windows .zip via 7-Zip. There is NO `xz` package on Chocolatey — a
#           `choco install xz` simply fails with "package was not found".
#           7zip is what .github/workflows/release.yml already installs and
#           uses to build the Windows release archive, so this follows a
#           path that is known to work on the runner. Nothing is lost:
#           Windows has no symlinks in the LLVM prefix and no exec bit.
# ---------------------------------------------------------------------------
mkdir -p "$OUTDIR"

# Absolute, BEFORE anything cds elsewhere.
#
# The Windows branch below runs 7z from inside the staging tree, so a relative
# $OUTDIR ("dist") resolved against that tree instead: the zip was written to
# <staging>/dist/... , the staging tree was then wiped by the EXIT trap, and
# verification failed with "The system cannot find the file specified" after a
# 2.5 hour build. The Unix branch never hit this because its redirection is
# evaluated in the original working directory.
OUTDIR="$(cd "$OUTDIR" && pwd)"

if [ "$OS" = "Windows" ]; then
    command -v 7z >/dev/null 2>&1 || {
        echo "error: 7z not found. Install it with: choco install 7zip -y" >&2
        exit 1
    }
    ARCHIVE="$OUTDIR/${NAME}.zip"
    ARCHIVE_NAME="${NAME}.zip"

    # 7z has no --exclude-from-a-directory-walk equivalent to tar's -C, so
    # stage the tree first, prune what does not belong, then zip the result.
    echo "--> staging (Windows) ..."
    STAGE_TREE="$STAGE/tree"
    mkdir -p "$STAGE_TREE"
    cp -R "$PREFIX"/. "$STAGE_TREE"/
    for e in "${EXCLUDES[@]}"; do
        rm -rf "$STAGE_TREE"/$e
    done
    cp -R "$STAGE/THIRD_PARTY_LICENSES" "$STAGE_TREE"/

    echo "--> compressing (7z, zip) ..."
    rm -f "$ARCHIVE"
    ( cd "$STAGE_TREE" && 7z a -tzip -mx=9 -r "$ARCHIVE" . >/dev/null )
else
    ARCHIVE="$OUTDIR/${NAME}.tar.xz"
    ARCHIVE_NAME="${NAME}.tar.xz"

    echo "--> compressing (xz -9, threaded) ..."
    tar -C "$PREFIX" "${TAR_EXCLUDE_ARGS[@]}" -cf - . \
        -C "$STAGE" THIRD_PARTY_LICENSES \
      | xz -9 -T0 > "$ARCHIVE"
fi

# ---------------------------------------------------------------------------
# Verify before anyone uploads it.
# ---------------------------------------------------------------------------
echo "--> verifying"
if [ "$OS" = "Windows" ]; then
    # 7z prints Windows-style paths ("lib\\cmake\\llvm\\LLVMConfig.cmake").
    # Translate to forward slashes so one set of patterns works everywhere —
    # without this every check below silently fails to match and the artifact
    # looks empty.
    MEMBERS="$(7z l -slt "$ARCHIVE" | sed -n 's/^Path = //p' | tr '\\\\' '/')"
else
    MEMBERS="$(tar -tJf "$ARCHIVE")"
fi

fail=0

# A here-string, NOT a pipe. `grep -q` stops at the first match and closes its
# input; with `set -o pipefail` that makes the writing end of a pipe die on
# SIGPIPE and the whole pipeline report failure — so every check would claim
# the file was missing when it was in fact present.
check_absent() {
    if grep -q "$1" <<< "$MEMBERS"; then
        echo "    LEAKED into the LLVM artifact: $1" >&2
        fail=1
    fi
}
check_present() {
    if ! grep -q "$1" <<< "$MEMBERS"; then
        echo "    MISSING from the LLVM artifact: $1" >&2
        fail=1
    fi
}

# Non-LLVM files must not be here. Libraries AND headers AND pkg-config: an
# earlier version of this script only checked the .a files, which would have
# let a whole include/mongoc-2.3.3 tree ride along unnoticed.
# Library names differ per platform, so a Unix-only list would never match on
# Windows and would report a clean artifact no matter what leaked into it.
if [ "$OS" = "Windows" ]; then
    check_absent "lib/uv\.lib"
    check_absent "lib/libuv\.lib"
    check_absent "lib/mongoc2\.lib"
    check_absent "lib/bson2\.lib"
    check_absent "lib/raylib\.lib"
    check_absent "lib/llhttp\.lib"
    check_absent "lib/gtest"
else
    check_absent "libuv\.a"
    check_absent "libmongoc2\.a"
    check_absent "libraylib\.a"
    check_absent "libllhttp\.a"
    check_absent "libbson2\.a"
    check_absent "libgtest"
fi
check_absent "include/mongoc-"
check_absent "include/bson-"
check_absent "include/gtest/"
check_absent "include/uv"
check_absent "include/llhttp\.h"
check_absent "include/raylib\.h"
check_absent "lib/pkgconfig"
check_absent "share/mongo-c-driver"

# The pieces the FlowWing build genuinely needs.
# File naming is platform-specific: MSVC produces LLVMCore.lib where Unix
# produces libLLVMCore.a, and executables carry a .exe suffix. Checking for
# the Unix names on Windows reported every required file as missing.
check_present "lib/cmake/llvm/LLVMConfig.cmake"
check_present "lib/clang/"          # clang's resource headers (stddef.h etc.)
check_present "THIRD_PARTY_LICENSES/LLVM-LICENSE.TXT"
if [ "$OS" = "Windows" ]; then
    check_present "lib/LLVMCore\.lib"
    check_present "bin/clang++\.exe"
else
    check_present "lib/libLLVMCore\.a"
    check_present "bin/clang++"
fi

if [ "$fail" -ne 0 ]; then
    echo "error: artifact failed verification; not writing a checksum" >&2
    rm -f "$ARCHIVE"
    exit 1
fi

# SHA-256, whichever tool this platform has.
#
#   macOS      ships `shasum` (Perl); no `sha256sum`.
#   Linux      ships `sha256sum` (coreutils).
#   Git Bash   ships `sha256sum` but NOT `shasum` — assuming `shasum` is what
#              made the Windows job fail with "missing required tool: shasum".
#
# Both print the same "<hash>  <filename>" format, so the .sha256 file is
# identical either way and `sha256sum -c` can verify it anywhere.
sha256_of() {
    if command -v sha256sum >/dev/null 2>&1; then
        sha256sum "$1"
    elif command -v shasum >/dev/null 2>&1; then
        shasum -a 256 "$1"
    else
        echo "error: no sha256sum or shasum on PATH" >&2
        return 1
    fi
}

( cd "$OUTDIR" && sha256_of "$ARCHIVE_NAME" > "${ARCHIVE_NAME}.sha256" )

SIZE="$(du -h "$ARCHIVE" | cut -f1)"
echo ""
echo "    $ARCHIVE  ($SIZE)"
echo "    $(cat "$OUTDIR/${NAME}.tar.xz.sha256")"
echo ""
echo "    GitHub caps a single release asset at 2 GiB."
