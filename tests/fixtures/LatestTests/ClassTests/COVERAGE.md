# Class test coverage (audit)

See also: **`CLASS_TEST_AUDIT.md`** (legacy mapping + cross-suite inventory) and **`CLASS_COMPATIBILITY.md`** (feature parity).

## 1. Have all tests under `tests/fixtures/Class` been copied to `LatestTests`?

**Yes — as a full mirror.** Legacy [`tests/fixtures/Class`](../../Class) has **88** `.fg` files. Every one exists under [`LatestTests/ClassTests/legacy_Class_fixtures/`](legacy_Class_fixtures/) with the **same relative path** and a matching **`.expect`** (re-verify with `find … | wc -l` or `diff -qr`).

**Additionally**, [`LatestTests/ClassTests`](.) has **~44** curated `.fg` files *outside* that mirror (`01_basic/`, `11_inheritance_basic/`, …) — those add focused scenarios and docs; they do **not** replace the 88-file mirror.

Older docs that said “only ~44 tests” were counting **curated** folders only and omitted `legacy_Class_fixtures/`.

## 2. What the compiler covers today (with `LatestTests/ClassTests`)

| Area | Status |
|------|--------|
| Methods without `fun` | Parser + `04_member_methods/method_without_fun_keyword.fg` |
| Multiple `init` overloads | `07_init_variants/init_overloads_zero_or_one_arg.fg` |
| Default parameters on `init` | `07_init_variants/init_default_second_param.fg` (+ IR default emission in `new`) |
| Implicit `self` | `05_member_access/implicit_self.fg` |
| `super(...)` in derived `init` | `11_inheritance_basic/super_in_derived_init.fg` |
| `extends` / fields | `11_inheritance_basic/simple_extends.fg`, `inherit_field_access.fg` |
| Subtyping (`Derived` where `Base` expected) | `11_inheritance_basic/virtual_dispatch_base_ref.fg` (and function-param variant if present) |
| Dynamic dispatch (base ref → overridden method) | `11_inheritance_basic/virtual_dispatch_base_ref.fg`, `virtual_dispatch_function_param.fg` |
| Nested / large type usage | `13_stress/large_type_graph.fg` (chained type aliases) |
| Cross-suite mirrors | `13_cross_suite/dynamic_class_null_branch.fg` (see `CLASS_TEST_AUDIT.md`) |

## 3. Class-related tests elsewhere under `tests/fixtures/`

These suites are primarily exercised by the **full** fixture tree (`tests/runner.py` over `tests/fixtures` or CI). Only **high-value** class-centric cases are **mirrored** under `LatestTests/ClassTests` (see `13_cross_suite/` and `CLASS_TEST_AUDIT.md`).

Examples: `DynamicType/`, `MiscellaneousTests/`, `MultipleAssignment/`, `InoutTest/`, `IndexTest/`, `ErrorTest/`, `WarningTest/`, `Z_ModuleTest/`, `Z_BringTest/`, …

## Curated folders (LatestTests-only)

| Folder | Purpose |
|--------|---------|
| `14_inference_and_external_mutate/` | Inferred field type (`var x`), `init` with/without param types, external function mutating `a.x` (int → str) |
| `15_errors/` | `ClassAlreadyDeclared`, `ParentClassNotFound`, `ParentClassIsNotAClass`, `SuperCallOutsideConstructor`, `FunctionAlreadyDeclared`, **`InvalidInitFunctionCall`** (no explicit `init()` / `self.init()` / `obj.init()` — only `new` invokes `init`), **`NewExpressionConstructorArgumentCountMismatch`** / **`NewExpressionConstructorArgumentTypeMismatch`** (clear `new Class(...)` / `init` messages), `FunctionArgumentTypeMismatch` (non-`new` calls), `MemberAccessOnNonObjectVariable`, `IndexingNonArrayTypeVariable`, runtime OOB (`EXPECT_ERROR: Runtime`) |
| `16_cross_feature/` | Class instances with `while`/`if`/`break`, `for`, `switch`, `or if`, nested `type` / object fields, multi-return `(int, A)`, default params on functions taking `A` |

There was **no** prior test mirroring the exact “`printA(new A(10))` with inferred `var x` then assign `"Hello2`” pair of programs; those live under **`14_inference_and_external_mutate/`**.

## 4. How to extend

1. Copy/adapt a legacy file into `LatestTests/ClassTests/**`.
2. Add `.expect` matching `println` output.
3. Run:

```bash
python3 tests/runner.py --bin build/FlowWing --dir tests/fixtures/LatestTests/ClassTests --mode jit
```

(On release builds, use `build/jit-release/FlowWing` if that is what your CI uses.)

4. For **full regression** across all suites (large), run the same runner on the whole tree, e.g.:

```bash
python3 tests/runner.py --bin build/FlowWing --dir tests/fixtures --mode jit
```

Use `--filter` or a subdirectory (e.g. `tests/fixtures/DynamicType`) to narrow scope.

_Last updated: legacy Class **88** `.fg`; LatestTests/ClassTests adds **15** new curated `.fg` under `14_`–`16_` (plus `15_errors` compile/runtime diagnostics). Re-count with `find tests/fixtures/LatestTests/ClassTests -name '*.fg' | wc -l`._
