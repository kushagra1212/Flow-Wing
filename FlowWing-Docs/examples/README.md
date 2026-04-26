# Flow-Wing-Docs example sources

These `.fg` files are **language examples** used by the documentation site. Some pages `bring` them by path. The path in a `bring "…"` is always **relative to the file that contains the `bring`**.

Doc snippet verification compiles from `FlowWing-Docs/.doc_snippet_tmp/`, so examples use paths like `../examples/bring/choosy_lib.fg`. In your own project, use a path relative to **your** source file (e.g. `bring "lib/utils.fg"`).

Do not point user-facing prose at the compiler’s internal `tests/fixtures/` tree; keep examples in this folder.

See **`../WRITING.md`** (documentation style for contributors).
