# Legacy `tests/fixtures/Class` mirror

This directory is a **1:1 copy** of every `.fg` file under `tests/fixtures/Class/`, preserving subdirectory layout (`ClassesTests/`, `InheritanceTest/`, …).

- **Count:** 88 `.fg` files — same as `find tests/fixtures/Class -name '*.fg' | wc -l`.
- Each file has a sibling **`.expect`** next to it for `tests/runner.py`.

### Regenerating all `.expect` files (match current compiler output)

From the repo root:

```bash
python3 tests/runner.py --bin build/FlowWing \
  --dir tests/fixtures/LatestTests/ClassTests/legacy_Class_fixtures \
  --mode jit --update --keep-going
```

This overwrites every sibling `.expect` with the **stdout+stderr** of `FlowWing` on that `.fg` file (JIT).

**Note:** Some legacy programs hit **undefined behavior** (e.g. bad prints, null calls). Their output can **vary between runs** (stack traces, garbage floats, UBSAN line numbers). After a bulk `--update`, a normal run `… --mode jit` without `--update` may still report mismatches on those until the runtime is fixed or the tests are narrowed. Curated tests under `01_basic/`, `11_inheritance_basic/`, etc. are the stable regression surface.

CI runs **`make test-jit ARGS="--filter=LatestTests …"`**, which includes this tree. The **original** `tests/fixtures/Class/` folder is the legacy harness location; **new work** should add or edit tests under `LatestTests/ClassTests/` (here or in curated folders like `01_basic/`) and follow [`../FunctionTests/TEST_WRITING_GUIDE.md`](../FunctionTests/TEST_WRITING_GUIDE.md).

To verify parity after edits:

```bash
diff -qr tests/fixtures/Class tests/fixtures/LatestTests/ClassTests/legacy_Class_fixtures
```

(Expect differences only if you intentionally diverge the mirror from legacy.)
