# Flow-Wing documentation site (Docusaurus)

Published build: [flow-wing-docs.vercel.app](https://flow-wing-docs.vercel.app/) (see `docusaurus.config.ts`).

## For readers of the language

All **end-user** pages live under `docs/`. They describe **Flow-Wing the language**—not the C++ implementation—unless a page is clearly under *Getting Started* for **from-source** builds.

## For contributors to this site

- **`WRITING.md`** — tone, what to avoid (repo paths, `src/…` references in user pages), and how `examples/` ties into doc snippets.
- **`verify_doc_snippets.py`** — compiles every `<CodeBlock … language="fg" />` body; run from the repo root after `make build-aot-debug` so `build/sdk/bin/FlowWing` exists.
- **`examples/`** — small `.fg` libraries used in docs (for example `examples/bring/choosy_lib.fg`). `bring` paths in snippets are written for the verifier’s output folder; see `examples/README.md`.

The **authoritative** CLI and runtime behavior is always the **compiler you built or installed**—run **`--help`**. The upstream compiler repository is the place for C++ source, `make` targets, and `tests/`.

## Local dev server

```bash
cd FlowWing-Docs
yarn install
yarn start
```

Sidebar: `sidebars.ts`.
