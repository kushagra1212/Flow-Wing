#!/usr/bin/env python3
"""Compile and run every Flow-Wing example in the documentation.

The docs show code with <CodeBlock code={`...`} language="fg"/> (a block with
no language shows output or a syntax outline, and is skipped). The code is a
JavaScript template literal, so what a reader sees is the literal after JS
unescaping (`\\n` shows as \\n, a lone `\\n` becomes a line break). This script
applies the same rules, then builds each example and runs it, and writes a
report that puts each example's real output next to the text that follows it
on the page, where the docs state what it prints.

    python3 tests/docs_examples.py                     # every page
    python3 tests/docs_examples.py --filter 'Json'     # pages whose path matches
    python3 tests/docs_examples.py --report /tmp/r.md  # where the report goes

An example that brings `dom` or `js` needs a web page, so it is only compiled
for wasm32. Exit status is 0 when every example compiled; a failure to compile
or to run is listed in the report either way, since some examples are meant to
fail (a diagnostic, a runtime error) and the page says so.
"""

import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ANSI = re.compile(r"\x1b\[[0-9;]*[A-Za-z]")
OPEN = re.compile(r"<CodeBlock\s+code=\{\s*`")


def js_template_unescape(raw):
    """What a JS template literal evaluates to (untagged, so no raw access)."""
    out = []
    i = 0
    simple = {"n": "\n", "t": "\t", "r": "\r", "b": "\b", "f": "\f", "v": "\v", "0": "\0"}
    while i < len(raw):
        c = raw[i]
        if c != "\\":
            out.append(c)
            i += 1
            continue
        nxt = raw[i + 1] if i + 1 < len(raw) else ""
        if nxt in simple:
            out.append(simple[nxt])
            i += 2
        elif nxt == "\n":  # line continuation
            i += 2
        elif nxt == "x":
            out.append(chr(int(raw[i + 2:i + 4], 16)))
            i += 4
        elif nxt == "u" and raw[i + 2:i + 3] == "{":
            end = raw.index("}", i)
            out.append(chr(int(raw[i + 3:end], 16)))
            i = end + 1
        elif nxt == "u":
            out.append(chr(int(raw[i + 2:i + 6], 16)))
            i += 6
        else:  # \\ \` \$ \' \" and any other character stand for themselves
            out.append(nxt)
            i += 2
    return "".join(out)


def extract(md_path):
    """Yield (line, code, text_after) for each CodeBlock in a page."""
    text = md_path.read_text(encoding="utf-8")
    for m in OPEN.finditer(text):
        start = m.end()
        i = start
        while True:
            j = text.index("`", i)
            backslashes = 0
            k = j - 1
            while text[k] == "\\":
                backslashes += 1
                k -= 1
            if backslashes % 2 == 0:
                break
            i = j + 1
        raw = text[start:j]
        line = text.count("\n", 0, m.start()) + 1
        close = text.index("/>", j) + 2
        # A block with no language="fg" shows output or a syntax outline, not
        # a program.
        if 'language="fg"' not in text[j:close]:
            continue
        after_lines = [l for l in text[close:].splitlines() if l.strip()][:6]
        yield line, js_template_unescape(raw), "\n".join(after_lines)


def run(cmd, timeout, cwd=None, env=None):
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout,
                           cwd=cwd, env=env, stdin=subprocess.DEVNULL,
                           encoding="utf-8", errors="replace")
        return p.returncode, ANSI.sub("", (p.stdout or "") + (p.stderr or ""))
    except subprocess.TimeoutExpired as e:
        out = e.stdout or b""
        if isinstance(out, bytes):
            out = out.decode("utf-8", "replace")
        return None, ANSI.sub("", out)


def check(example, compiler, work, run_timeout):
    page, index, line, code, after = example
    d = Path(work) / f"{re.sub(r'[^A-Za-z0-9]+', '_', page)}_{index}"
    d.mkdir(parents=True, exist_ok=True)
    src = d / "example.fg"
    src.write_text(code, encoding="utf-8")
    result = {"page": page, "index": index, "line": line, "code": code,
              "after": after}

    if re.search(r"^\s*bring\s+(dom|js)\b", code, re.M):
        status, out = run([compiler, str(src), "--target=wasm32",
                           "-o", str(d / "app.js")], 300, cwd=d)
        result.update(target="wasm32", compile_status=status,
                      compile_output=out.strip(), run_status="not run",
                      output="")
        return result

    exe = d / "example"
    status, out = run([compiler, str(src), "-o", str(exe)], 300, cwd=d)
    result.update(target="native", compile_status=status,
                  compile_output=out.strip())
    if status != 0 or not exe.exists():
        result.update(run_status="not run", output="")
        return result
    status, out = run([str(exe)], run_timeout, cwd=d)
    result.update(run_status="timeout" if status is None else status,
                  output=out)
    return result


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--bin", default=str(ROOT / "build/sdk/bin/FlowWing"))
    ap.add_argument("--docs", default=str(ROOT / "flow-wing-docs/docs"))
    ap.add_argument("--filter", default="", help="regex on the page path")
    ap.add_argument("--report", default="docs-examples-report.md")
    ap.add_argument("--json", default="", help="also write results as JSON")
    ap.add_argument("--jobs", type=int, default=6)
    ap.add_argument("--timeout", type=int, default=10,
                    help="seconds an example may run")
    args = ap.parse_args()

    docs = Path(args.docs)
    pattern = re.compile(args.filter) if args.filter else None
    examples = []
    for md in sorted(docs.rglob("*.md")):
        page = str(md.relative_to(docs))
        if pattern and not pattern.search(page):
            continue
        for index, (line, code, after) in enumerate(extract(md), 1):
            examples.append((page, index, line, code, after))

    work = tempfile.mkdtemp(prefix="fw-docs-")
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = list(pool.map(
            lambda e: check(e, args.bin, work, args.timeout), examples))

    lines = ["# Documentation examples", ""]
    counts = {}
    for r in results:
        if r["compile_status"] != 0:
            key = "compile failed"
        elif r["target"] == "wasm32":
            key = "compiled for wasm32 (not run)"
        elif r["run_status"] == "timeout":
            key = "still running after the timeout"
        elif r["run_status"] != 0:
            key = "run failed"
        else:
            key = "ran"
        r["summary"] = key
        counts[key] = counts.get(key, 0) + 1
    lines.append(", ".join(f"{v} {k}" for k, v in sorted(counts.items())))
    lines.append("")

    current = None
    for r in results:
        if r["page"] != current:
            current = r["page"]
            lines += [f"## {current}", ""]
        lines.append(f"### Example {r['index']} (line {r['line']}): {r['summary']}")
        lines += ["", "```fg", r["code"].rstrip(), "```", ""]
        if r["compile_status"] != 0:
            lines += ["Compiler said:", "", "```", r["compile_output"][-3000:], "```", ""]
        elif r["target"] == "native":
            lines += [f"Output (exit {r['run_status']}):", "", "```",
                      r["output"][-3000:].rstrip(), "```", ""]
        lines += ["The page goes on:", "", "```", r["after"], "```", ""]
    Path(args.report).write_text("\n".join(lines), encoding="utf-8")
    if args.json:
        Path(args.json).write_text(json.dumps(results, indent=1), encoding="utf-8")

    print(f"{len(results)} examples: " +
          ", ".join(f"{v} {k}" for k, v in sorted(counts.items())))
    print(f"report: {args.report}  (work dir {work})")
    return 1 if counts.get("compile failed") else 0


if __name__ == "__main__":
    sys.exit(main())
