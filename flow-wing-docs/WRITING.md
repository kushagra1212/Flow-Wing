# Writing Flow-Wing language documentation

This site documents the **Flow-Wing programming language** for people who write `.fg` code and use the **compiler and standard modules** shipped with a normal install (or a from-source build).

## Audience: language users, not the compiler repository

- **Do** explain syntax, `bring`, types, the CLI as users run it, and standard library modules.
- **Do** use `flowwing` / `FlowWing` (or `FlowWing.exe` on Windows) and “your `PATH`” when talking about the compiler. Mention install-specific names where helpful.
- **Do** keep self-contained `examples/` under `FlowWing-Docs/examples/` and reference them from docs with paths **relative to the snippet** (see `examples/README.md`).
- **Don’t** cite `src/…/.cpp` files, `LibUtils`, linker implementation details, or GitHub workflow YAML as the “source of truth” in user-facing pages.
- **Don’t** send readers to `tests/fixtures/`, `fw-modules/...` paths, or `docs/demo/` in the main compiler repo **unless** the page is explicitly “Building the compiler” or contributor-oriented.

## Where “building from source” belongs

- **Getting Started → Installation** and the main repo **README** / **AGENTS** may describe the `make` targets and `build/sdk/bin/FlowWing` for **contributors and advanced users** building the toolchain.
- For the rest of the docs, default to “compile with the Flow-Wing compiler you installed” and **`--help`** for flag details.

## Snippet checks

`verify_doc_snippets.py` compiles `<CodeBlock … language="fg" />` bodies. `bring` paths must resolve from `FlowWing-Docs/.doc_snippet_tmp/<name>.fg`, typically to files under `FlowWing-Docs/examples/`. Snippets that **AOT** too slowly or hang in this harness (e.g. **`bring vortex`**) are listed in **`SKIP_FG_SNIPPETS`** in that script—compile those examples manually or in CI with a different job if you need a guarantee.

## Touch points

- After changing the compiler CLI, update **Flow-Wing CLI** in sync with your build’s `FlowWing --help`.
- When standard modules change, update the **Built-in libraries** pages and, if needed, the files under `examples/`.
