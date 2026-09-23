#!/usr/bin/env python3
"""Checks that every runtime function Flow-Wing calls has the same wasm32
signature on both sides of the call.

Native linkers never compare function types, so a declaration that disagrees
with its C definition links and runs natively: sometimes by luck, sometimes
by silently truncating a value. wasm-ld compares full types and rejects the
call ("function signature mismatch"). This audit finds every such mismatch at
once, instead of one link error at a time.

How it works:

  1. Compile the core C/C++ runtime to wasm32 LLVM IR with emcc.
  2. Emit wasm32 IR with Flow-Wing for every fixture and std module, which is
     the widest set of runtime calls the compiler actually makes.
  3. Lower both sides to wasm value types the way the WebAssembly backend
     does (i1/i8/i16/i32/ptr -> i32, i64, float -> f32, double -> f64,
     aggregates split into fields, aggregate returns into a hidden pointer,
     varargs into one extra i32), and compare by name.

Only declarations the module uses are compared: LLVM drops unused ones before
linking, so wasm-ld never sees them.

    make wasm-abi-audit                      # needs emsdk, found as the compiler finds it
    python3 scripts/wasm/abi_audit.py --bin build/sdk/bin/FlowWing

Exits 1 when any mismatch is found.
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# The runtime a browser build links. mongo, raylib, vortex and the libuv event
# loop are native-only for now.
RUNTIME_SOURCES = [
    "fw-modules/built_in_module/*.c",
    "fw-modules/dynamic/*.c",
    "fw-modules/gc/src/*.c",
    "fw-modules/file_module/*.cpp",
    "fw-modules/io_module/*.cpp",
    "fw-modules/js_module/*.c",
    "fw-modules/map_module/*.cpp",
    "fw-modules/text_module/*.c",
    "fw-modules/vec_module/*.cpp",
]
NATIVE_ONLY_MODULES = ("mongo", "raylib", "vortex")

SCALAR = {
    "i1": "i32", "i8": "i32", "i16": "i32", "i32": "i32", "ptr": "i32",
    "i64": "i64", "float": "f32", "double": "f64",
}
ATTRIBUTE = re.compile(
    r"\b(noundef|zeroext|signext|nonnull|noalias|nocapture|readonly|writeonly|"
    r"returned|inreg|immarg|nofree|dereferenceable(_or_null)?\(\d+\)|align \d+|"
    r"byval\([^)]*\)|sret\([^)]*\))\b")
LINKAGE = {"dso_local", "hidden", "internal", "weak", "weak_odr", "linkonce_odr",
           "local_unnamed_addr", "unnamed_addr", "extern_weak"}
FUNCTION = re.compile(r"^(define|declare)\b(.*?)@(\"[^\"]+\"|[\w.$-]+)\((.*)\)")
TYPEDEF = re.compile(r"^(%[\w.\"-]+) = type (<?\{.*\}>?)")


def split_top_level(text):
    parts, depth, current = [], 0, ""
    for ch in text:
        depth += ch in "{[<("
        depth -= ch in "}]>)"
        if ch == "," and depth == 0:
            parts.append(current.strip())
            current = ""
        else:
            current += ch
    if current.strip():
        parts.append(current.strip())
    return parts


def lower(ty, structs):
    """The wasm value types one LLVM value type becomes."""
    ty = ty.strip()
    if ty in SCALAR:
        return [SCALAR[ty]]
    if ty.startswith("%"):
        if ty not in structs:
            return ["?" + ty]
        ty = structs[ty]
    if ty.startswith("{") or ty.startswith("<{"):
        return [w for field in split_top_level(ty.strip("<>{} "))
                for w in lower(field, structs)]
    array = re.match(r"\[(\d+) x (.+)\]", ty)
    if array:
        return lower(array.group(2), structs) * int(array.group(1))
    return ["?" + ty]


def wasm_signature(prefix, params, structs):
    tokens = [t for t in ATTRIBUTE.sub("", prefix).split() if t not in LINKAGE]
    ret = tokens[-1] if tokens else "void"
    lowered_params = []
    for param in split_top_level(params):
        if param == "...":
            lowered_params.append("i32")  # pointer to the varargs buffer
            continue
        words = ATTRIBUTE.sub("", param).split()
        if words:
            lowered_params += lower(words[0], structs)
    if ret == "void":
        return tuple(lowered_params), ()
    lowered_ret = lower(ret, structs)
    if len(lowered_ret) > 1:
        # No multivalue: an aggregate return becomes a hidden pointer.
        return ("i32",) + tuple(lowered_params), ()
    return tuple(lowered_params), tuple(lowered_ret)


def collect(paths, kind):
    """name -> {signature: first source line} for `define` or `declare`."""
    found = defaultdict(dict)
    for path in paths:
        text = path.read_text(errors="replace")
        lines = text.splitlines()
        structs = {m.group(1): m.group(2)
                   for m in map(TYPEDEF.match, lines) if m}
        for line in lines:
            if not line.startswith(kind):
                continue
            match = FUNCTION.match(line)
            if not match:
                continue
            _, prefix, name, params = match.groups()
            name = name.strip('"')
            if kind == "declare" and sum(
                    text.count(f"@{name}{c}") for c in "(,)") < 2:
                continue  # declared, never used
            sig = wasm_signature(prefix, params, structs)
            found[name].setdefault(sig, f"{line.strip()[:140]}   ({path})")
    return found


def show(sig):
    params, ret = sig
    return f"({', '.join(params)}) -> {ret[0] if ret else 'void'}"


def compile_runtime(emcc, out_dir):
    uv_header = next(ROOT.glob("fw-modules/uv_module/**/fw_uv.h"), None)
    libuv = next(ROOT.glob(".fw_dependencies/install/include/uv.h"), None)
    includes = [f"-I{ROOT / 'fw-modules/gc/include'}", f"-I{ROOT / 'fw-modules'}"]
    includes += [f"-I{p.parent}" for p in (uv_header, libuv) if p]
    failures = []
    for pattern in RUNTIME_SOURCES:
        for source in sorted(ROOT.glob(pattern)):
            out = out_dir / (source.stem + ".ll")
            result = subprocess.run(
                [emcc, "-S", "-emit-llvm", "-O0", *includes, str(source),
                 "-o", str(out)], capture_output=True, text=True)
            if result.returncode != 0:
                failures.append(f"{source.relative_to(ROOT)}: "
                                f"{result.stderr.strip().splitlines()[-1]}")
    return failures


def emit_flowwing_ir(compiler, out_dir, jobs):
    inputs = sorted(ROOT.glob("tests/fixtures/LatestTests/**/*.fg"))
    inputs += [p for p in sorted(ROOT.glob("fw-modules/**/*-module.fg"))
               if not any(n in p.name for n in NATIVE_ONLY_MODULES)]

    def emit(indexed):
        index, source = indexed
        subprocess.run([str(compiler), str(source), "--target=wasm32",
                        "--emit=ir", f"--output-dir={out_dir / str(index)}"],
                       capture_output=True, stdin=subprocess.DEVNULL)

    with ThreadPoolExecutor(max_workers=jobs) as pool:
        list(pool.map(emit, enumerate(inputs)))
    # Fixtures that exist to fail compilation produce no IR, which is expected.
    return len(inputs)


def find_emcc(explicit):
    """emcc, looked for where the compiler looks: --emcc or FLOWWING_EMCC, then
    PATH, then $EMSDK, then ~/emsdk. Found through an emsdk folder, it also
    sets EMSDK_PYTHON, as emsdk_env.sh would: emcc needs a newer Python than
    some systems ship. So nobody has to source emsdk_env.sh, which on Linux
    breaks `make` (it puts a directory named cmake on PATH)."""
    for name in (explicit, os.environ.get("FLOWWING_EMCC")):
        if name:
            return shutil.which(name) or (name if Path(name).is_file() else None)
    on_path = shutil.which("emcc")
    if on_path:
        return on_path
    windows = os.name == "nt"
    for root in (os.environ.get("EMSDK"), str(Path.home() / "emsdk")):
        if not root:
            continue
        emcc = Path(root) / "upstream" / "emscripten" / ("emcc.bat" if windows else "emcc")
        if emcc.is_file():
            pythons = sorted((Path(root) / "python").glob(
                "*/python.exe" if windows else "*/bin/python3"))
            if pythons:
                os.environ.setdefault("EMSDK_PYTHON", str(pythons[0]))
            return str(emcc)
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--bin", required=True, help="Path to FlowWing")
    parser.add_argument("--emcc", help="emcc to compile the runtime with (default: found like the compiler finds it)")
    parser.add_argument("--work", default="build/wasm-abi-audit")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    args = parser.parse_args()

    emcc = find_emcc(args.emcc)
    if not emcc:
        print("error: emcc not found. Install emsdk, then put emcc on PATH, set "
              "EMSDK to the emsdk folder, or install it in ~/emsdk.")
        return 2
    compiler = Path(args.bin).resolve()
    work = Path(args.work).resolve()
    shutil.rmtree(work, ignore_errors=True)
    (work / "runtime").mkdir(parents=True)
    (work / "flowwing").mkdir(parents=True)

    failures = compile_runtime(emcc, work / "runtime")
    for failure in failures:
        print(f"warning: runtime source not audited: {failure}")
    count = emit_flowwing_ir(compiler, work / "flowwing", args.jobs)

    defined = collect(sorted((work / "runtime").glob("*.ll")), "define")
    declared = collect(sorted((work / "flowwing").rglob("llvm_ir.ll")), "declare")

    mismatches = []
    for name, signatures in sorted(declared.items()):
        if name not in defined:
            continue  # defined by Flow-Wing itself, libc, or an LLVM intrinsic
        c_sig, c_line = next(iter(defined[name].items()))
        for sig, fg_line in signatures.items():
            if sig != c_sig:
                mismatches.append((name, sig, fg_line, c_sig, c_line))

    checked = sum(1 for name in declared if name in defined)
    print(f"{count} Flow-Wing sources, {len(defined)} runtime definitions, "
          f"{checked} runtime functions called.")
    if not mismatches:
        print("No wasm32 signature mismatches.")
        return 0
    print(f"{len(mismatches)} wasm32 signature mismatch(es):")
    for name, sig, fg_line, c_sig, c_line in mismatches:
        print(f"\n  {name}")
        print(f"    Flow-Wing  {show(sig):32} {fg_line}")
        print(f"    C          {show(c_sig):32} {c_line}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
