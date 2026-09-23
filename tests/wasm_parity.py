#!/usr/bin/env python3
"""Runs fixtures as WebAssembly and checks their output against .expect.

Each fixture is built with `FlowWing --target=wasm32 --emit=exe`, run under
Node, and compared exactly as tests/runner.py compares native runs: stdout
then stderr, colour codes stripped, byte for byte against the .expect file.

It also runs them under the same environment: FW_GC_STRESS=1 for GcTests and
any `/; ENV:` header, both decided by tests/runner.py's own helpers.

A fixture with an `/; EXPECT_ERROR:` header and no .expect is a runtime-error
test. The native runner checks that the output names the error; here the
program must also exit non-zero, since printing the error and then exiting 0
is a failure mode native builds do not have.

A fixture lands in one of four buckets:

  PASS         same output as native
  FAIL         built and ran, but the output differs, or it crashed
  UNSUPPORTED  uses something wasm builds cannot do (a module the wasm
               runtime leaves out, or recursion deeper than the JavaScript
               engine allows); counted, not failed
  SKIP         a diagnostic fixture: it exists to fail compilation, which
               does not depend on the target

    make test-wasm                                  # needs emsdk
    make test-wasm ARGS="--dir tests/fixtures/LatestTests/ClassTests"
    python3 tests/wasm_parity.py --bin build/sdk/bin/FlowWing --filter Array

Exits 1 when anything FAILs.
"""
import argparse
import math
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

sys.path.insert(0, str(ROOT / "tests"))
# The native runner's rules for a fixture's environment, so the two agree.
from runner import (  # noqa: E402
    get_expected_error_code, get_test_env, test_forces_gc_stress)
ANSI = re.compile(r"\x1B(?:[@-Z\\-_]|\[[0-9;?]*[ -/]*[@-~])")

# wasm-ld naming a symbol from a module the wasm runtime does not include.
MISSING_MODULE = re.compile(r"undefined symbol: (\S+)")
# A native-only module (vortex, mongo, raylib), refused at its bring.
NATIVE_ONLY_MODULE = re.compile(r"\[Error:ModuleNotForTarget\].*'<?(\w+)>?' module works only in native builds")
# How node-host.js reports running out of stack. Every wasm call also uses
# the JavaScript engine's own stack, which Node limits to about 1 MB and a
# browser to a similar fixed size, so recursion stops at 10000 to 20000
# frames however large the program's stack is; a task also has its own.
# Native main gets 64 MB.
STACK_OVERFLOW = "Runtime Error: Stack Overflow."
EXPECT_ERROR = re.compile(r"/;\s*EXPECT_ERROR:\s*(.*)$")


def expected_error_text(fixture):
    """The whole EXPECT_ERROR header; runner.py keeps only its first word."""
    with open(fixture, encoding="utf-8", errors="replace") as f:
        for _ in range(5):
            match = EXPECT_ERROR.search(f.readline())
            if match:
                return match.group(1)
    return ""


def strip_ansi(text):
    return ANSI.sub("", text)


class StatusLine:
    """One line that rewrites itself while fixtures run, on a terminal only.

    Without it a clean run printed nothing for the whole minute it takes,
    since only failures are printed as they happen. A CI log is not a
    terminal, so it still gets just the failures and the summary."""

    CLEAR = "\r\033[K"

    def __init__(self, total):
        self.total = total
        self.live = sys.stdout.isatty()
        self.started = time.monotonic()

    def show(self, done, counts):
        if not self.live:
            return
        elapsed = time.monotonic() - self.started
        sys.stdout.write(f"{self.CLEAR}  {done}/{self.total} · {counts['PASS']} pass"
                         f" · {counts['FAIL']} fail · {counts['UNSUPPORTED']} unsupported"
                         f" · {elapsed:.0f}s")
        sys.stdout.flush()

    def clear(self):
        if self.live:
            sys.stdout.write(self.CLEAR)
            sys.stdout.flush()


# --minimal-env: what a program still needs to start.
MINIMAL_ENV = ("PATH", "HOME", "SYSTEMROOT", "TEMP", "TMP")


def classify(fixture, compiler, work, timeout, minimal_env=False):
    expected_error = get_expected_error_code(fixture)
    out_js = work / "prog.js"

    build = subprocess.run(
        [str(compiler), str(fixture), "--target=wasm32", "--emit=exe",
         f"--output-dir={work / 'build'}", "-o", str(out_js), "--progress=never"],
        capture_output=True, text=True, errors="replace", stdin=subprocess.DEVNULL)
    if build.returncode != 0:
        log = strip_ansi(build.stdout + build.stderr)
        native_only = NATIVE_ONLY_MODULE.findall(log)
        if native_only:
            return "UNSUPPORTED", "brings a native-only module: " + native_only[0]
        missing = MISSING_MODULE.findall(log)
        if missing:
            return "UNSUPPORTED", "links against a module not in the wasm runtime: " + missing[0]
        # The compiler rejected the program itself. That is what a diagnostic
        # fixture is for, and the native runner checks those.
        return "SKIP", "does not compile (diagnostic fixture)"

    env = ({k: v for k, v in os.environ.items() if k in MINIMAL_ENV}
           if minimal_env else dict(os.environ))
    if test_forces_gc_stress(fixture):
        env["FW_GC_STRESS"] = "1"
    env.update(get_test_env(fixture))
    try:
        run = subprocess.run(["node", str(out_js)], capture_output=True,
                             text=True, errors="replace", timeout=timeout,
                             stdin=subprocess.DEVNULL, cwd=str(fixture.parent),
                             env=env)
    except subprocess.TimeoutExpired:
        return "FAIL", f"timed out after {timeout}s"
    actual = strip_ansi(run.stdout + run.stderr)
    if STACK_OVERFLOW in actual:
        # A test that exists to overflow its stack did what it should.
        if expected_error and "Stack Overflow" in expected_error_text(fixture):
            return ("PASS", "") if run.returncode != 0 else (
                "FAIL", "reported the stack overflow but exited with status 0")
        return "UNSUPPORTED", "recursion deeper than WebAssembly allows"

    if expected_error:
        if expected_error not in actual:
            return "FAIL", (f"expected a runtime error naming {expected_error!r}, "
                            f"got {actual[-120:]!r}")
        if run.returncode == 0:
            return "FAIL", "printed the runtime error but exited with status 0"
        return "PASS", ""

    expected = fixture.with_suffix(".expect").read_text(encoding="utf-8", errors="replace")
    if actual == expected:
        return "PASS", ""
    first = next((i for i, (a, b) in enumerate(zip(actual, expected)) if a != b),
                 min(len(actual), len(expected)))
    return "FAIL", (f"output differs at byte {first}: "
                    f"expected {expected[first:first + 40]!r}, got {actual[first:first + 40]!r}")


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--bin", required=True, help="Path to FlowWing")
    parser.add_argument("--dir", action="append",
                        help="Fixture directory (repeatable). Default: all of LatestTests.")
    parser.add_argument("--filter", help="Regex on the fixture path")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 4)
    parser.add_argument("--timeout", type=int, default=20)
    parser.add_argument("--verbose", action="store_true", help="List every fixture")
    parser.add_argument(
        "--minimal-env", action="store_true",
        help="Run each program with almost no environment. Its strings live in "
             "the program's heap, so this moves everything after them: a memory "
             "bug that depends on where things land shows up in one layout and "
             "hides in the other.")
    args = parser.parse_args()

    if not shutil.which("node"):
        print("error: node not found; wasm builds run under Node.")
        return 2
    compiler = Path(args.bin).resolve()
    dirs = [Path(d) for d in (args.dir or ["tests/fixtures/LatestTests"])]
    fixtures = sorted(f for d in dirs for f in d.rglob("*.fg")
                      if f.with_suffix(".expect").exists() or get_expected_error_code(f))
    if args.filter:
        pattern = re.compile(args.filter)
        fixtures = [f for f in fixtures if pattern.search(str(f))]
    if not fixtures:
        print("No fixtures matched.")
        return 1

    work_root = Path(tempfile.mkdtemp(prefix="fw-wasm-parity-"))
    print(f"Running {len(fixtures)} fixtures as wasm32 under Node, "
          f"{args.jobs} at a time", flush=True)
    status = StatusLine(len(fixtures))

    def one(indexed):
        index, fixture = indexed
        work = work_root / str(index)
        work.mkdir()
        return fixture, *classify(fixture, compiler, work, args.timeout, args.minimal_env)

    counts = {"PASS": 0, "FAIL": 0, "UNSUPPORTED": 0, "SKIP": 0}
    unsupported = {}
    failures = []
    try:
        with ThreadPoolExecutor(max_workers=args.jobs) as pool:
            # as_completed, not pool.map: map yields in submission order, so
            # one slow fixture held back every result after it.
            running = [pool.submit(one, item) for item in enumerate(fixtures)]
            for done, future in enumerate(as_completed(running), start=1):
                fixture, verdict, reason = future.result()
                counts[verdict] += 1
                name = fixture.relative_to(ROOT) if fixture.is_relative_to(ROOT) else fixture
                if verdict == "FAIL":
                    failures.append((name, reason))
                elif verdict == "UNSUPPORTED":
                    unsupported[reason] = unsupported.get(reason, 0) + 1
                if args.verbose or verdict == "FAIL":
                    status.clear()
                    print(f"  [{verdict}] {name}" + (f"  {reason}" if reason else ""))
                status.show(done, counts)
    finally:
        status.clear()
        shutil.rmtree(work_root, ignore_errors=True)

    ran = counts["PASS"] + counts["FAIL"]
    print("-" * 60)
    print(f"{len(fixtures)} fixtures: {counts['PASS']} pass, {counts['FAIL']} fail, "
          f"{counts['UNSUPPORTED']} unsupported, {counts['SKIP']} diagnostic (skipped)")
    if ran:
        # Rounded down, so one failure among thousands never reads as 100.0%.
        parity = math.floor(1000.0 * counts["PASS"] / ran) / 10
        print(f"Parity with native: {parity:.1f}% of the "
              f"{ran} fixtures that build and run on wasm")
    for reason, count in sorted(unsupported.items(), key=lambda kv: -kv[1]):
        print(f"  unsupported x{count}: {reason}")
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
