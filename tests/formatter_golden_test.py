#!/usr/bin/env python3
"""Golden tests for `FlowWing --file=... --format-print` (formatted source on stdout)."""
import argparse
import difflib
import os
import subprocess
import sys
from pathlib import Path


class _Colors:
    """ANSI colors — same as tests/runner.py; disabled for non-TTY or NO_COLOR=1."""

    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    BOLD = "\033[1m"
    ENDC = "\033[0m"


def _term_colors() -> _Colors:
    c = _Colors()
    if not sys.stdout.isatty() or os.environ.get("NO_COLOR", "").strip():
        for name in (
            "HEADER",
            "OKBLUE",
            "OKGREEN",
            "WARNING",
            "FAIL",
            "BOLD",
            "ENDC",
        ):
            setattr(c, name, "")
    return c


def _in_ci() -> bool:
    return any(
        os.environ.get(v)
        for v in ("CI", "GITHUB_ACTIONS", "GITLAB_CI", "BUILD_BUILDID")
    )

SUBPROCESS_ENCODING = "utf-8"
SUBPROCESS_ERRORS = "replace"


def _run_format(bin_path: Path, fg_path: Path) -> tuple[int, str, str]:
    r = subprocess.run(
        [str(bin_path), f"--file={str(fg_path)}", "--format-print"],
        capture_output=True,
        text=True,
        encoding=SUBPROCESS_ENCODING,
        errors=SUBPROCESS_ERRORS,
    )
    return r.returncode, (r.stdout or ""), (r.stderr or "")


def main() -> int:
    p = argparse.ArgumentParser()
    p.add_argument("--bin", required=True, help="Path to FlowWing executable")
    p.add_argument(
        "--dir",
        type=Path,
        default=Path("tests/fixtures/FormatterTests"),
        help="Directory containing .fg and .expect pairs",
    )
    p.add_argument("--update", action="store_true", help="Write .expect from actual")
    p.add_argument(
        "--no-create-missing",
        action="store_true",
        help="Fail if .expect is missing (default: create it when not in CI)",
    )
    p.add_argument("--filter", type=str, default=None, help="Regex on stem name")
    args = p.parse_args()

    bin_path = Path(args.bin)
    d = args.dir
    C = _term_colors()
    if not bin_path.is_file():
        print(
            f"{C.FAIL}Compiler not found: {bin_path}{C.ENDC}",
            file=sys.stderr,
        )
        return 1
    if not d.is_dir():
        print(f"{C.FAIL}Not a directory: {d}{C.ENDC}", file=sys.stderr)
        return 1
    import re

    flt = re.compile(args.filter) if args.filter else None
    fgs = sorted(d.glob("*.fg"))
    if flt:
        fgs = [f for f in fgs if flt.search(f.stem)]
    if not fgs:
        print(f"{C.WARNING}No .fg files found.{C.ENDC}")
        return 0

    failed = 0
    for fg in fgs:
        ex = fg.with_suffix(".expect")
        rc, out, err = _run_format(bin_path, fg)
        if rc != 0:
            print(
                f"{C.FAIL}[FAIL (FORMAT)]{C.ENDC} {fg.name} exit {rc}\n{err}{out}"
            )
            failed += 1
            continue
        if err.strip():
            print(
                f"{C.FAIL}[FAIL (FORMAT)]{C.ENDC} {fg.name} unexpected stderr: {err!r}"
            )
            failed += 1
            continue
        if args.update:
            ex.write_text(out, encoding="utf-8")
            print(f"{C.OKBLUE}[UPDATED]{C.ENDC} {ex.name}")
            continue
        if not ex.is_file():
            if _in_ci() or args.no_create_missing:
                print(
                    f"{C.FAIL}[FAIL (MISSING EXPECT)]{C.ENDC} {fg.name} missing {ex.name} "
                    f"(commit the golden or run: {sys.argv[0]} --bin ... --update --filter ...)",
                    file=sys.stderr,
                )
                failed += 1
                continue
            ex.write_text(out, encoding="utf-8")
            print(
                f"{C.WARNING}[CREATED]{C.ENDC} {ex.name} (add to version control and commit)"
            )
            continue
        want = ex.read_text(encoding="utf-8")
        if out == want:
            print(f"{C.OKGREEN}[OK]{C.ENDC} {fg.name}")
        else:
            failed += 1
            print(f"{C.FAIL}[FAIL]{C.ENDC} {fg.name}")
            diff = difflib.unified_diff(
                want.splitlines(keepends=True),
                out.splitlines(keepends=True),
                fromfile=str(ex),
                tofile="actual",
            )
            sys.stdout.write("".join(diff))

    n = len(fgs)
    if not args.update and n:
        if failed:
            print(
                f"{C.FAIL}failed: {failed} of {n} formatter golden test(s).{C.ENDC}",
                file=sys.stderr,
            )
        else:
            print(
                f"{C.OKGREEN}All {n} formatter golden test(s) passed.{C.ENDC}"
            )

    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
