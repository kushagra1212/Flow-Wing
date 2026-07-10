#!/usr/bin/env sh
#
# fw-modules/mongo_module/merge_apple_static.sh
#
# Invoked as a POST_BUILD step from fw-modules/mongo_module/CMakeLists.txt
# on macOS **and Linux**. Merges libmongoc2.a and libbson2.a into the
# freshly-built libflowwing_mongo.a so a single archive is enough for the
# SDK / JIT link. Uses only POSIX `sh` + `ar` so the same script works on
# both platforms (BSD ar on macOS, GNU ar on Linux).
#
# Why this script exists, take 2:
#   mongo-c-driver 2.x bundles its internal "mongo-common" code (common-b64.c,
#   common-string.c, common-thread.c, common-md5.c, common-json.c, common-oid.c
#   ...) into BOTH libmongoc2.a and libbson2.a. The trick is that each archive
#   builds those .c files with a DIFFERENT symbol prefix (_mongoc_mcommon_*
#   inside libmongoc, _mcommon_* inside libbson) but the .o filenames are
#   identical.
#
#   First attempt (libtool -static): preserved every object verbatim, ld then
#   rejected with `duplicate symbol _kZeroObjectId` etc.
#   Second attempt (ar -x in one dir — what Linux was doing inline in
#   CMakeLists.txt until 2026-05-24): same-basename .o files overwrote, so
#   either the mongoc-prefixed copies or the bson-prefixed copies were lost
#   and ld came back with `undefined symbol: _mongoc_mcommon_string_*`,
#   `_mongoc_mcommon_b64_*`, etc.
#
# Real fix: extract each input archive into its own subdir, prefix every
# extracted .o file with the archive nickname so the basenames are unique,
# then archive them all together. Both prefix variants survive; ld picks
# whichever symbol the caller actually references.
#
# Args:
#   $1 = absolute path to libflowwing_mongo.a (the archive cmake just built)
#   $2 = absolute path to libmongoc2.a
#   $3 = absolute path to libbson2.a

set -eu

FLOWWING_MONGO_LIB="$1"
MONGOC_LIB="$2"
BSON_LIB="$3"

# Always print: CI logs gave us no signal whether this script ran on the
# Mac runner. With these lines, a missing merge becomes obvious in the log
# before the FlowWing link fails 100+ undefined-symbol errors later.
echo "merge_apple_static.sh: starting"
echo "  FLOWWING_MONGO_LIB=$FLOWWING_MONGO_LIB"
echo "  MONGOC_LIB=$MONGOC_LIB"
echo "  BSON_LIB=$BSON_LIB"
for f in "$FLOWWING_MONGO_LIB" "$MONGOC_LIB" "$BSON_LIB"; do
    if [ ! -f "$f" ]; then
        echo "merge_apple_static.sh: FATAL — input not found: $f" >&2
        exit 1
    fi
done

# Idempotency guard. The cmake invocation runs this script on every build
# (ALL custom target — not POST_BUILD — because POST_BUILD silently skips
# when ninja considers flowwing_mongo's target up-to-date, which is exactly
# what GitHub Actions cache restoration produces). Re-running the extract /
# rename / re-archive on an already-merged archive would dump duplicate .o
# files (every mongoc symbol appearing twice). Check for the marker symbol
# first; bail early if the archive is already merged.
if nm -gU "$FLOWWING_MONGO_LIB" 2>/dev/null | grep -Eq " T _?mongoc_client_destroy\$"; then
    echo "merge_apple_static.sh: archive already merged (mongoc_client_destroy present); skipping"
    exit 0
fi

# Diagnostic: does the INPUT mongoc archive actually expose the symbols we
# expect? CI Mac JIT showed "184 members" merged but linker still got
# `undefined symbol: mongoc_client_destroy` — either the input archive
# never had it (build-config issue / wrong arch cache), or something is
# stripping it. Print up front so the CI log answers the question.
#
# Symbol-name note: macOS Mach-O prepends `_` to every C symbol so nm
# prints `_mongoc_client_destroy`; Linux ELF nm prints `mongoc_client_destroy`
# bare. Match both with the regex prefix `_?` instead of pinning to one
# platform's convention (the first version of this check was Mach-O-only
# and false-FATAL'd a fully-working Linux merge).
echo "merge_apple_static.sh: probing input archives (nm -gU)"
echo "  MONGOC_LIB arch + member count: $(file "$MONGOC_LIB" | sed 's/^[^:]*: //'); $(ar -t "$MONGOC_LIB" | wc -l | tr -d ' ') members"
for sym in mongoc_client_destroy mongoc_client_new_from_uri bson_iter_init; do
    if nm -gU "$MONGOC_LIB" 2>/dev/null | grep -Eq " T _?$sym\$" \
       || nm -gU "$BSON_LIB"   2>/dev/null | grep -Eq " T _?$sym\$"; then
        echo "  found: $sym"
    else
        echo "  MISSING from inputs: $sym" >&2
    fi
done

WORK_DIR="$(dirname "$FLOWWING_MONGO_LIB")/_mongo_merge"
rm -rf "$WORK_DIR"
mkdir -p "$WORK_DIR/flowwing" "$WORK_DIR/mongoc" "$WORK_DIR/bson"

(cd "$WORK_DIR/flowwing" && ar -x "$FLOWWING_MONGO_LIB")
(cd "$WORK_DIR/mongoc"   && ar -x "$MONGOC_LIB")
(cd "$WORK_DIR/bson"     && ar -x "$BSON_LIB")

# Move into the staging root with a per-archive prefix so common-b64.c.o
# from mongoc does not clobber common-b64.c.o from bson (or vice versa).
cd "$WORK_DIR"
for f in flowwing/*.o; do mv "$f" "flowwing_$(basename "$f")"; done
for f in mongoc/*.o;   do mv "$f" "mongoc_$(basename "$f")";   done
for f in bson/*.o;     do mv "$f" "bson_$(basename "$f")";     done

# `common-oid.c.o` is the one mongo-common file that DOES carry the same
# symbols (_mcommon_oid_set_zero, _mcommon_oid_is_zero, _kZeroObjectId) in
# both archives — every other common-*.c.o is built with a distinct
# _mongoc_mcommon_* / _bson_mcommon_* prefix and must be kept twice.
# Drop the bson copy; mongoc's byte-identical copy satisfies references
# from both sides. Verified once via `nm` against libmongoc2.a + libbson2.a;
# revisit if the mongo-c-driver version bump brings in more collisions.
rm -f bson_common-oid.c.o

# Force a fresh archive — `ar -rcs` against an existing file appends.
rm -f "$FLOWWING_MONGO_LIB"
ar -rcs "$FLOWWING_MONGO_LIB" *.o

# `ar -rcs` includes `s` = build symbol index, but on macOS CI runners
# (Xcode-bundled `ar`) the index was silently omitted and ld64.lld failed
# with `archive has no index; run ranlib to add one`. Run ranlib
# unconditionally — it's a no-op if the index already exists.
ranlib "$FLOWWING_MONGO_LIB"

# Sanity check: mongoc + bson symbols MUST resolve from the merged archive,
# otherwise the FlowWing link silently fails later with hundreds of
# `undefined symbol: mongoc_*` / `bson_*` errors against
# libflowwing_mongo.cpp.o. Fail loudly here so the cause is visible in CI
# logs at the merge step, not 100s of lines deep in the linker output.
if ! ar -t "$FLOWWING_MONGO_LIB" | grep -q '^mongoc_'; then
    echo "merge_apple_static.sh: FATAL — merged archive $FLOWWING_MONGO_LIB" >&2
    echo "  is missing mongoc_*.o members. ar -t output:" >&2
    ar -t "$FLOWWING_MONGO_LIB" | sed 's/^/    /' >&2
    echo "  inputs were: MONGOC_LIB=$MONGOC_LIB BSON_LIB=$BSON_LIB" >&2
    exit 1
fi
if ! ar -t "$FLOWWING_MONGO_LIB" | grep -q '^bson_'; then
    echo "merge_apple_static.sh: FATAL — merged archive $FLOWWING_MONGO_LIB" >&2
    echo "  is missing bson_*.o members." >&2
    exit 1
fi

echo "merge_apple_static.sh: done; merged archive has $(ar -t "$FLOWWING_MONGO_LIB" | wc -l | tr -d ' ') members"

# Final symbol-level verification — `ar -t | grep '^mongoc_'` only proves
# the *.o file is in the archive, not that its global symbols survived.
# CI Mac JIT pass-2 had 184 members but still got `undefined symbol:
# mongoc_client_destroy`; this guards against that exact failure mode.
# Match `_?` prefix to cover both Mach-O (`_mongoc_*`) and ELF (`mongoc_*`).
for sym in mongoc_client_destroy bson_iter_init; do
    if ! nm -gU "$FLOWWING_MONGO_LIB" 2>/dev/null | grep -Eq " T _?$sym\$"; then
        echo "merge_apple_static.sh: FATAL — merged archive is missing global" >&2
        echo "  symbol $sym. Likely the input archive never exposed it" >&2
        echo "  (build-config / wrong-arch deps cache?)." >&2
        echo "  nm -gU $FLOWWING_MONGO_LIB | grep -c ' T ' = $(nm -gU "$FLOWWING_MONGO_LIB" 2>/dev/null | grep -c ' T ')" >&2
        exit 1
    fi
done
echo "merge_apple_static.sh: symbol verification passed"

cd ..
rm -rf "$WORK_DIR"
