---
id: flow-wing-cli
title: Flow-Wing CLI Documentation
sidebar_label: Flow-Wing CLI
---

# Flow-Wing compiler command line

A full **SDK install** (installer, package, or release zip) usually ships **two** executables with the same options:

| You run | Role |
|--------|------|
| **`FlowWing`** / **`flowwing`** (Windows: `FlowWing.exe`) | **AOT** — compile `.fg` to a **native executable**; you run that file yourself. |
| **`FlowWing-jit`** / **`flowwing-jit`** (Windows: `FlowWing-jit.exe`) | **JIT** — **run the program directly**; no **`-o`** executable step and no second command to launch a binary. |

The usual invocation shape is the same; **`--help`** on **either** binary documents the full flag list for your build:

```text
flowwing <file.fg> [options]
flowwing-jit <file.fg> [options]
```

The input can be the first **positional** argument, or set with **`-F`** / **`--file=<path>`**.

Arguments after a **`--`** token are not parsed as compiler options; they are passed through as **runtime arguments** to your program (for example for the `sys` module and tests).

## Common options

| Option | Description |
|--------|-------------|
| `-h`, `--help` | Show help and exit. |
| `-V`, `--version` | Print compiler name and version. |
| `-F`, `--file=<path>` | Input `.fg` file (optional if the file is the first positional argument). |
| `-C`, `--code=<string>` | Source code as a string instead of a file. |
| `-FM`, `--format` | Format the **input file in place** (not compatible with `-FMP`). |
| `-FMP`, `--format-print` | Print formatted source to **stdout** (not compatible with `-FM`). |
| `-O0`, `-O1`, `-O2`, `-O3` | Optimization level; default is **`-O0`**. |
| `-e`, `--entry-point=<name>` | Entry symbol name (default follows your build; often **`fg_main`**-style for apps). |
| `-L <path>` | Add a **library search path** (may appear multiple times). |
| `-l <lib>` | Link a **system** library (may appear multiple times). |
| `--framework <name>` | **macOS:** link a framework (may appear multiple times). |
| `-S`, `--server` | Optional link hint for **Vortex** (HTTP). If you already **`bring vortex`**, you typically **do not** need this—`bring` records the right native library. |
| `--linker-warnings` | Pass **linker warnings** through where supported. |
| `-E`, `--emit=<kind>` | Select compiler output: **tokens**, **ast**, **sem**, **ir**, **obj**, **exe**, or **jit** (if your build supports the kind). |
| `-T`, `--target=<machine>` | Machine to generate code for: **`native`** (default) or **`wasm32`**. With `wasm32`, use `--emit=exe` for a program that runs in Node or a browser, or `--emit=ir` for its LLVM IR. See [Compiling to WebAssembly](../Advanced/Compiling%20to%20WebAssembly.md). |
| `-D`, `--dump` | With JSON/IR emit: also print to **stdout** when a pass runs. |
| `-OD`, `--output-dir=<path>` | Directory for generated files; default is often a **`build/`**-style directory under the project. |
| `-o`, `--output=<path>` | **AOT:** output path of the final executable. |
| `--progress=<mode>` | Build progress lines: **`auto`** (default) shows them only when the output is a terminal, **`always`** shows them everywhere (for example in CI logs), **`never`** hides them. See [Build progress](#build-progress). |

**AOT vs JIT:** For **AOT**, use **`flowwing`**, pass **`-o path`** when you want a named executable, then run that path. For **run without creating an app binary**, use **`flowwing-jit myapp.fg`** — the JIT program executes your `.fg` in one go (handy for quick iteration, similar to a script). If you only have **one** compiler binary (for example a **from-source** build that stages a single `build/sdk/bin/FlowWing`), that file is **either** AOT **or** JIT depending on which preset you built last, not both at once. Prefer a **packaged SDK** to get **`flowwing`** and **`flowwing-jit`** on `PATH` together.

## Build progress

When you build in a terminal, the compiler prints one line for each file it
compiles, then the link, then a summary:

```
   Compiling sys (std)
   Compiling lib/math-module.fg
   Compiling main.fg
     Linking build/bin/main
    Finished main in 0.57s (3 files, -0.11s vs last build ▼)
```

- Each file appears **once**, even when several files bring it.
- **`(std)`** marks a standard-library module.
- The last part compares this build with the **last successful build** of the
  same file, with the same `-O` level, target and output kind. It says
  `first build`, `same as last build` (a change under 50 ms or 5%), or how
  much slower (▲) or faster (▼) this build was. A compile-time regression is
  therefore visible in the build where it appears.
- The times are kept in `<output-dir>/.flowwing/build-times`. Deleting the
  file only resets the comparison.
- **JIT** builds print `Running main.fg` after `Finished`, and then your
  program's output. The `Finished` time does not include run time.

When the output is not a terminal (a pipe, a file, or a test runner), nothing
is printed, so scripts that read the compiler's output see no change. Use
`--progress=always` to keep the lines in a CI log.

## Examples

**Version**

```bash
flowwing --version
```

**AOT: compile, then run** (separate native executable on disk)

```bash
flowwing myapp.fg -o build/bin/myapp
./build/bin/myapp
```

**JIT: run the `.fg` directly** (no **`-o`** step; use the **JIT** binary from your SDK)

```bash
flowwing-jit myapp.fg
```

On Windows, if `flowwing-jit` is not on `PATH` yet, call the installed name, for example `FlowWing-jit.exe myapp.fg`. With **one** self-built `FlowWing` that was produced with a **JIT** preset, the same “run in one step” style is just:

```bash
./build/sdk/bin/FlowWing myapp.fg
```

(That only applies when that binary is the JIT build; for AOT, use **`-o`** and run the output.)

**From the compiler repo (developer workflow):** after `make build-jit-debug`, you can also use **`make run-jit-debug FILE=path/to/myapp.fg`**, which invokes the staged JIT the same way as `build/sdk/bin/FlowWing myapp.fg`.

**Format and print to stdout (does not rewrite the file in place)**

```bash
flowwing -FMP myapp.fg
```

**Pass arguments to your program**

```bash
flowwing myapp.fg -- --flag-for-program value
```

For a complete and accurate list, run **`flowwing --help`** or **`flowwing-jit --help`** (depending on which binary you are using). Different releases may add or rename options.
