#!/usr/bin/env sh
#
# fw-modules/mongo_module/merge_apple_static.sh
#
# Invoked as a POST_BUILD step from fw-modules/mongo_module/CMakeLists.txt
# on macOS. Merges libmongoc2.a and libbson2.a into the freshly-built
# libflowwing_mongo.a so a single archive is enough for the SDK / JIT link.
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
#   Second attempt (ar -x in one dir): same-basename .o files overwrote, so
#   either the mongoc-prefixed copies or the bson-prefixed copies were lost
#   and ld came back with `Undefined symbols: __mongoc_mcommon_b64_ntop ...`.
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

cd ..
rm -rf "$WORK_DIR"
