# Class fixtures audit (`tests/fixtures/Class` → `LatestTests`)

## Counts (re-run anytime)

```bash
find tests/fixtures/Class -name '*.fg' | wc -l
find tests/fixtures/LatestTests/ClassTests -name '*.fg' | wc -l
```

| Location | `.fg` files |
|----------|-------------|
| `tests/fixtures/Class` | **88** |
| `tests/fixtures/LatestTests/ClassTests/legacy_Class_fixtures` | **88** (1:1 path mirror + `.expect`) |
| `tests/fixtures/LatestTests/ClassTests` (total) | **~132** (88 mirror + ~44 curated outside mirror) |

**All 88 legacy files are present** under `legacy_Class_fixtures/`. Curated tests elsewhere in `ClassTests/` add **extra** coverage (clearer names, inheritance/dispatch focus, cross-suite mirrors) without removing the mirror.

## Mapping strategy

1. **Full mirror:** Keep `legacy_Class_fixtures/` in sync with `tests/fixtures/Class` (88 files). See [`legacy_Class_fixtures/README.md`](legacy_Class_fixtures/README.md).
2. **Curated tests:** Optionally **cluster** by theme and add clearer scenarios under `01_basic/`, `11_inheritance_basic/`, etc.
3. Add a **new** curated `.fg` + `.expect` when you want a **named** regression separate from a long legacy filename.
4. When authoring new tests, follow LatestTests syntax (`println`, optional `fun` on methods, `extends`, init-only `super(...)`).

## Legacy `tests/fixtures/Class` — cluster → `LatestTests/ClassTests`

| Legacy cluster | Count (approx.) | Covered by LatestTests (examples) | Notes |
|----------------|-----------------|-----------------------------------|--------|
| `ClassesTests/` — equality, logical not | several | `01_basic/class_equality.fg`, `10_class_operators/class_logical_not.fg` | Legacy `ClassEqualityOperator`, `LogicalNotForClass` |
| `ClassesTests/` — init / defaults / prints | many | `03_init/*`, `07_init_variants/*` | Legacy `ClassInit*`, `DefaultInitilizer*` → overloads + defaults; multi-return-heavy legacy files may stay **out of scope** until multi-return parity is explicit |
| `ClassesTests/` — implicit self / print chains | many | `05_member_access/implicit_self.fg`, `04_member_methods/*` | `InsideClassPrint*`, `PrintNice*` |
| `ClassesTests/` — return/pass class | several | `06_object_from_function/*`, `09_class_with_functions/*` | `ReturnClassObjectFromFunction*`, `CreatingObjectFromFunction*` |
| `InheritanceTest/` — `super(y)` in ctor | many | `11_inheritance_basic/super_in_derived_init.fg`, `inherit_field_access.fg` | Long filenames share one scenario |
| `InheritanceTest/` — base ref + dynamic dispatch | many | `11_inheritance_basic/virtual_dispatch_base_ref.fg`, `virtual_dispatch_function_param.fg` + **all** `InheritanceTest/*.fg` in `legacy_Class_fixtures/` | Curated tests are shorter; long legacy names remain in the mirror |
| `ClassPrintTest/` | few | `03_init/init_with_print.fg` + mirror under `legacy_Class_fixtures/ClassPrintTest/` | Variadic/print specifics |

**Note:** Multi-return + class and long inheritance smoke files **are** in the mirror (`legacy_Class_fixtures/`). Curated `virtual_dispatch_*` tests are **additional** clarity, not a substitute for deleting mirror files.

## Class-related tests in other `tests/fixtures/**` suites

| Suite | Role | Mirrored in LatestTests? |
|-------|------|---------------------------|
| `IndexTest/` | e.g. array field + `self` | Yes — `12_integration/index_member_array.fg` |
| `DynamicType/` | class + `null` / dynamic | Yes — `13_cross_suite/dynamic_class_null_branch.fg` (minimal mirror of `DynamicType/Class.fg`) |
| `InoutTest/` | `inout` + class | **Harness only** (see `classesWithInout.fg`); inout semantics are suite-specific |
| `MultipleAssignment/` | MA + class | **Harness only** unless a class-only regression is needed |
| `MiscellaneousTests/` | broad snippets | **Harness only** |
| `ErrorTest/` | diagnostics | **Harness only** (expected failures) |
| `Z_ModuleTest/`, `Z_BringTest/` | modules + class | **Harness only** |

**CI:** `.github/workflows` and Docker use **`--filter=LatestTests`** — that includes **all** of `ClassTests/` (mirror + curated). For extra regression, run the full `tests/fixtures` tree locally or in a broader job.

## How to extend

1. **Updating legacy class tests:** Edit **`tests/fixtures/Class`** and **copy/sync** the same file into `LatestTests/ClassTests/legacy_Class_fixtures/` (keep paths aligned), then refresh the `.expect` (run the program and capture stdout).
2. **New curated tests:** Add under `LatestTests/ClassTests/<topic>/` (or `13_cross_suite/`, `13_stress/`).
3. Add matching `.expect` unless the test uses `EXPECT_ERROR` in-file.
4. Run:  
   `python3 tests/runner.py --bin build/FlowWing --dir tests/fixtures/LatestTests/ClassTests --mode jit`
