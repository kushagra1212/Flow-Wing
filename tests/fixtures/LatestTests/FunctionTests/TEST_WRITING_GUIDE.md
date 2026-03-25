# Test Writing Guide for Flow-Wing LatestTests

This guide documents how to write tests for the Flow-Wing compiler's `LatestTests` directory. Follow these conventions exactly when adding new tests.

---

## Directory Structure

All tests live in:

```
tests/fixtures/LatestTests/<Category>/<subcategory>/<test-name>.fg
tests/fixtures/LatestTests/<Category>/<subcategory>/<test-name>.expect
```

### Naming Conventions

- Use `snake_case` for filenames.
- Use descriptive names that reflect what is tested, e.g. `inout_int_increment`, `multi_return_two_vars`.
- Group related tests in subdirectories under a category (e.g. `FunctionTests/01_basic_void/`).
- Prefix subdirectories with two-digit numbers if ordering matters (e.g. `01_basic_void`, `02_return_types`).

---

## Test File Format

### Normal Tests (`.fg` + `.expect`)

**`.fg` file** — Flow-Wing source code:

```fg
fun add(a: int, b: int) -> int {
  return a + b
}

println(add(3, 7))
```

**`.expect` file** — Exact expected stdout output (newline terminated):

```
10
```

> **IMPORTANT:** The `.expect` file must exactly match what the program would print to stdout, including newlines. Use `println` which automatically appends a newline. Use `print` for no trailing newline.

---

### Error Tests (`.fg` only)

For compile-time errors, create **only** a `.fg` file. Do **NOT** create a `.expect` file.

Add a comment on line 1:

```fg
/; EXPECT_ERROR: ErrorName
fun add(a: int, b: int) -> int {
  return a + b
}
add(1)
```

---

## Known Error Names

These are the error names to use in the `/; EXPECT_ERROR:` comment:

| Error Name                               | When to Use                          |
| ---------------------------------------- | ------------------------------------ |
| `FunctionNotFound`                       | Calling an undeclared function       |
| `FunctionAlreadyDeclared`                | Defining the same function twice     |
| `FunctionArgumentCountMismatch`          | Too few or too many args passed      |
| `FunctionArgumentTypeMismatch`           | Arg type doesn't match param type    |
| `LiteralCannotBePassedToInoutParameter`  | Literal passed to inout param (use var) |
| `VariableNotFound`                       | Using an undeclared variable         |
| `AssignmentExpressionCountMismatch`      | Mismatched count in multi-assign     |
| `InvalidBinaryOperationWithTypes`        | Binary op not valid for types        |
| `InitializerExpressionTypeMismatch`      | Type mismatch on var initialization  |
| `InvalidUnaryOperator`                   | Unary op not valid for type          |
| `ContainerExpressionRankMismatch`        | Array rank mismatch                  |
| `EmptyContainerExpression`               | Empty `[]` container                 |
| `IndexingNonArrayTypeVariable`           | Indexing a non-array variable        |
| `IndexingMoreDimensionsThanArrayTypeHas` | Over-indexing an array               |
| `InvalidAssignmentToConstantVariable`    | Assigning to `const` variable        |
| `ExpectedAnIntegerForIndexing`           | Non-integer used as array index      |
| `FunctionNameConflictsWithBuiltin`       | Function name conflicts with builtin |
| `IncompatibleTypesForTernaryExpression`  | Ternary branches have different types |
| `FileContainsErrors`                     | Brought file fails semantic analysis (`bring "…"`) |
| `FileNotFound`                           | Brought path does not exist or is not a regular file |
| `ModuleAlreadyDeclared`                  | Two `module [name]` with the same name in one scope |
| `ModuleNotFound`                         | Reserved: module name in `name::x` not found (current binder often reports `VariableNotFound` for the module identifier first) |

---

## AST and semantic (bound) JSON dumps

To emit JSON for tooling, tests, or debugging (from the repo root after building `FlowWing`):

```sh
mkdir -p /tmp/fw-dump
./build/FlowWing path/to/file.fg -E ast -D -OD /tmp/fw-dump   # writes ast.json
./build/FlowWing path/to/file.fg -E sem -D -OD /tmp/fw-dump   # writes semantic_tree.json
```

`-D` / `--dump` enables dump passes; `-OD` / `--output-dir` sets the directory. Paths are per compilation (the main file’s directory is used for resolving relative `bring "…"` paths).

---

## Flow-Wing Data Types Reference

| Type     | Example Value  | Description              |
| -------- | -------------- | ------------------------ |
| `int`    | `42`           | 64-bit integer           |
| `int8`   | `42`           | 8-bit integer            |
| `int32`  | `42`           | 32-bit integer           |
| `int64`  | `42`           | 64-bit integer           |
| `deci`   | `3.14`         | 64-bit float (double)    |
| `deci32` | `2.5f`         | 32-bit float             |
| `str`    | `"hello"`      | String                   |
| `bool`   | `true`/`false` | Boolean                  |
| `char`   | `'a'`          | Character                |
| `nthg`   | —              | Void/nothing return type |

---

## Function Syntax

```fg
// Basic void function
fun name() {
  ...
}

// Function with return type
fun name(param: Type) -> ReturnType {
  return value
}

// Multiple return types
fun name(a: int) -> int, deci {
  return a, a * 1.5
}

// Default parameter value
fun greet(name: str = "World") -> str {
  return "Hello " + name
}

// Inout (pass by reference) parameter
fun increment(inout n: int) {
  n = n + 1
}

// Inout with string concatenation (modify in place)
fun append(inout s: str, t: str) {
  s = s + t
}

// Dynamic return (no annotation, body returns dynamic type)
fun getDynamic() {
  return 42
}
```

---

## Variable Declaration Patterns

```fg
// Static single var from function
var x: int = getValue()

// Static multi-var from multi-return function
var x: int, y: deci = getPoint()

// Dynamic var (type inferred from function return)
var z = getValue()

// Multi-var with mixed initializers (literals + function calls)
var s: str, n: int, d: deci = "label", getSingleInt(), getMultireturnFunc()

// Assignment (reassignment) from function
x = computeNewValue(x)
x, y = getPoint()
```

---

## Print Patterns

```fg
// Prints with newline
println(x)
println("Hello", " ", "World")

// Prints without newline
print(x)
print("\n")
```

---

## Limitations (LatestTests Only)

- **`while`** and **`for`** are supported. **`break`** and **`continue`** are implemented in IR generation for both while and for loops.
- **Functions can only be declared globally** (not inside other functions or blocks).
- **Scoped blocks `{ ... }`** are allowed for grouping variable declarations that shadow globals.

---

## Running Tests

```sh
make test-jit ARGS="--filter=LatestTests --keep-going --parallel"
```

To filter to just a specific subdirectory:

```sh
make test-jit ARGS="--filter=LatestTests/FunctionTests --keep-going --parallel"
```

---

## Checklist When Adding New Function Tests

- [ ] Think about what behavior to test
- [ ] Write the `.fg` file with the test code
- [ ] Manually trace the expected output and write the `.expect` file
  - **For error tests:** skip `.expect`, use `/; EXPECT_ERROR: ErrorName` on line 1
- [ ] Use descriptive filenames in `snake_case`
- [ ] Place files in the appropriate subdirectory
- [ ] Run `make test-jit ARGS="--filter=LatestTests --keep-going --parallel"` to verify
- [ ] Fix any mismatches (output may need adjustment based on actual compiler output)

---

## Test Categories for If Statements

| Category             | Subdirectory              | Coverage                                                                              |
| -------------------- | ------------------------- | ------------------------------------------------------------------------------------- |
| Basic                | `01_basic`                | Simple if, if-else, else if                                                           |
| Or if                | `02_or_if`                | `or if` syntax, multiple or-if, else branch                                           |
| Conditions           | `03_conditions`           | Bool, int, string, binary ops, logical and, function calls                             |
| Scope                | `04_scope`                | Variable shadowing, declarations in branches                                          |
| Complex              | `05_complex`              | Nested if, nested or-if, assignment in branches                                        |
| Dynamic              | `06_dynamic`              | Dynamic type conditions (truthy/falsy)                                                |
| Edge cases           | `07_edge_cases`           | Nir/null, deci, if without else                                                       |
| Object               | `08_object`               | Object as condition (non-null, null, uninitialized), or-if, nested                    |
| Array                | `09_array`                | Array as condition (non-null, uninitialized), or-if                                   |
| Dynamic edge         | `10_dynamic_edge`         | Dynamic string (empty/nonempty), bool false, deci zero, from function, or-if          |
| Errors               | `11_errors`               | VariableNotFound, FunctionNotFound, InvalidBinaryOperationWithTypes, InvalidUnaryOperator, etc. |

---

## Test Categories for While

| Category   | Subdirectory    | Coverage                                                                 |
| ---------- | --------------- | ------------------------------------------------------------------------- |
| Basic      | `01_basic`      | Simple while, print each iteration, zero iterations                      |
| Conditions | `02_conditions` | Bool, int nonzero, binary comparison, func return bool/int, logical, string, deci, char, unary not, arithmetic in condition |
| Scope      | `03_scope`      | Variable in body, shadow in body, outer/inner while, assign/decl from func, nested block, reassign outer |
| Complex    | `04_complex`    | While with if/else, factorial, nested while, condition from func, assign from func, deeply nested while/if, ternary in body, multi-var assign |
| Edge cases | `05_edge_cases` | Empty body, single iteration, int negative, deci small, many iterations, int zero stops, string empty immediate |
| Errors     | `06_errors`     | VariableNotFound, FunctionNotFound, InvalidBinaryOperationWithTypes (condition/void) |
| Dynamic    | `06_dynamic`    | Condition from dynamic func return, dynamic zero, dynamic truthy          |
| Object     | `07_object`     | Object nonnull/null as condition, member access in body                   |
| Array      | `08_array`      | Func return array, array index in body, accumulate array                  |
| Short-circuit | `09_short_circuit` | && / \|\| in condition (literals, vars, dynamic, chained, nested, with func calls) |
| Break/Continue | `10_break_continue` | Error tests (outside loop); basic/edge/nested/complex/scope tests (require break/continue IR gen) |

---

## Test Categories for For

| Category       | Subdirectory      | Coverage                                                                 |
| -------------- | ----------------- | ------------------------------------------------------------------------- |
| Basic          | `01_basic`        | Simple for with step, for without step (default 1), inclusive upper bound |
| Break/Continue | `02_break_continue` | break, continue, nested loops, loop inside function, break/continue with if |
| Errors         | `03_errors`       | break/continue outside loop (EXPECT_ERROR)                               |

**For syntax:** `for (var i: int = start to end : step) { body }` or `for (var i: int = start to end) { body }` (step defaults to 1). Use explicit `int` (or `int64`/`int8`) for the loop variable to avoid literal inference issues.

---

## Test Categories for Functions

| Category             | Subdirectory              | Coverage                                                                              |
| -------------------- | ------------------------- | ------------------------------------------------------------------------------------- |
| Basic void           | `01_basic_void`           | No-arg void functions, `nthg` return type                                             |
| Return types         | `02_return_types`         | `int`, `deci`, `deci32`, `str`, `bool`, `char`, `int8` returns                        |
| Parameters           | `03_parameters`           | All primitive param types (int, deci, str, bool, char, int8), multi-param, defaults   |
| Multi-return         | `04_multi_return`         | Multiple return values, mixed initializers                                            |
| Inout                | `05_inout`                | Pass-by-reference for int, bool, deci, deci32, str, char; dynamic inout; print/return |
| Var decl from func   | `06_var_decl_from_func`   | Static typed var decl from function call                                              |
| Dynamic vars         | `07_dynamic`              | `var x = func()` type inference                                                       |
| Assignment from func | `08_assignment_from_func` | Reassigning existing vars from func return; multi-assign from single/multi-return funcs; mixed literal+func; discard-then-reassign |
| Scope                | `09_scope`                | Local/global shadowing, intra-scope reassignment                                      |
| Errors               | `10_errors`               | Compile-time errors for functions                                                     |
| Return stmt          | `11_return_stmt`          | Return statement variations                                                           |
| Multi-decl mixed     | `12_multi_decl_mixed`     | Multi-assign with literals + single/multi-return funcs                                |

---

## Test Categories for Ternary

| Category                | Subdirectory              | Coverage                                                                 |
| ----------------------- | ------------------------- | ------------------------------------------------------------------------- |
| Basic                   | `01_basic`                | Simple ternary, then/else branches, int/string results, truthy values     |
| Conditions              | `02_conditions`           | Bool, int nonzero, binary operators (int and other types)                 |
| Var decl and assignment | `03_var_decl_assignment`  | Variable declaration and reassignment with ternary                        |
| Func return             | `04_func_return`          | Ternary with function calls (int and object return types)                  |
| Errors                  | `05_errors`               | `IncompatibleTypesForTernaryExpression` (`.fg` only, no `.expect`)        |

---

## Test Categories for Switch

| Category       | Subdirectory      | Coverage                                                                 |
| -------------- | ----------------- | ------------------------------------------------------------------------- |
| Basic          | `01_basic`        | Switch on int, int8, int64, bool, str, deci, deci32, char; case match; default |
| Default order  | `02_default_order`| Default first in source; match vs no match                                |
| Conditions     | `03_conditions`   | Case with expression, variable, function call, binary expr               |
| Nested         | `03_nested`       | Nested switch statements                                                  |
| Edge cases     | `04_edge_cases`   | No match, deci/char, only default, return in switch; int zero/negative; first match wins; empty str |
| Errors         | `05_errors`       | MultipleDefaultCaseStatements, CaseExpressionTypeMismatch                 |
| Scope          | `06_scope`        | Variable declaration/assignment in case; shadowing; nested block; decl from func |
| Complex        | `07_complex`      | Empty case block; func return in case body; switch on func call; deeply nested switch |
| Dynamic        | `08_dynamic`      | Switch on dynamic from function (int, str)                                |
| Array          | `09_array`        | Switch on array element; case with array index                           |
| Object         | `10_object`       | Object decl in case; func return object in case; object member access   |

**Switch syntax:** Use `case value:{` (no space between `:` and `{`) so the parser does not treat `:` as part of an expression.

---

## Test categories for Class

| Category | Subdirectory | Coverage |
| -------- | ------------ | -------- |
| Inference + mutation | `14_inference_and_external_mutate/` | Inferred `var x`, `init(s)` / `init(s: str)`, external `fun` mutating `a.x` |
| Errors | `15_errors/` | `ClassAlreadyDeclared`, `ParentClassNotFound`, `ParentClassIsNotAClass`, `SuperCallOutsideConstructor`, `FunctionAlreadyDeclared`, **`InvalidInitFunctionCall`** (explicit `init()` / `self.init()` / `obj.init()`), **`NewExpressionConstructorArgumentCountMismatch`** / **`NewExpressionConstructorArgumentTypeMismatch`** for bad `new Class(...)` (preferred over generic function mismatch), `MemberAccessOnNonObjectVariable`, `IndexingNonArrayTypeVariable`, runtime OOB (`EXPECT_ERROR: Runtime`) |
| Cross-feature | `16_cross_feature/` | `while`/`for`/`switch`/`or if`, `type` + object field, multi-return, default params |

## Class tests (`ClassTests`)

Class fixtures live under `tests/fixtures/LatestTests/ClassTests/` with the same **`.fg` + `.expect`** rules as above (`println` / stdout, exact newlines in `.expect`).

**Follow this guide** for naming, structure, and expectations. Class-specific behavior and legacy migration notes are in:

- [`tests/fixtures/LatestTests/ClassTests/CLASS_COMPATIBILITY.md`](../ClassTests/CLASS_COMPATIBILITY.md) — feature parity (vtable dispatch, `super`, etc.)
- [`tests/fixtures/LatestTests/ClassTests/COVERAGE.md`](../ClassTests/COVERAGE.md) — what is tested vs `tests/fixtures/Class`

**`fun` inside classes:** For member methods and `init`, the `fun` keyword is **optional**. The parser accepts `name(` … `)` the same as `fun name(` … `)`. Use whichever style fits the test:

- Omit `fun` when the scenario is specifically **fun-less** method syntax (see `04_member_methods/method_without_fun_keyword.fg`).
- Use `fun` when you want to mirror top-level function style or stress the explicit keyword — both are valid.

**Legacy `tests/fixtures/Class`:** All **88** `.fg` files from that tree are **already mirrored** under [`ClassTests/legacy_Class_fixtures/`](../ClassTests/legacy_Class_fixtures/) with the **same relative paths** and a matching `.expect` each (so CI’s `--filter=LatestTests` still runs them). **Additionally**, curated tests live in `01_basic/`, `11_inheritance_basic/`, etc. — those consolidate or extend behavior without replacing the mirror. See `COVERAGE.md` / `CLASS_TEST_AUDIT.md`.

**Cross-suite class usage** (e.g. `DynamicType/`, `InoutTest/`) is mostly covered by the **full** `tests/runner.py --dir tests/fixtures` run; high-value cases are **mirrored** under `ClassTests/12_integration/` and `ClassTests/13_cross_suite/` as documented in `CLASS_TEST_AUDIT.md`.

**Newer curated suites:** `ClassTests/14_inference_and_external_mutate/` (inferred fields + external mutation), `ClassTests/15_errors/` (compile + runtime `EXPECT_ERROR`), `ClassTests/16_cross_feature/` (classes combined with control flow, `type`/`object`, multi-return). See `ClassTests/COVERAGE.md`.

**Class compile-time errors:** Use `/; EXPECT_ERROR: ErrorName` on line 1 (same as other LatestTests). Class-specific names that appear in compiler output include `ParentClassNotFound`, `ParentClassIsNotAClass`, `SuperCallOutsideConstructor`, `MemberAccessOnNonObjectVariable`, `ClassAlreadyDeclared`, **`NewExpressionConstructorArgumentCountMismatch`**, **`NewExpressionConstructorArgumentTypeMismatch`** (for `new Class(...)` / constructor `init` issues — clearer than `FunctionArgument*`), plus `FunctionAlreadyDeclared`, `FunctionArgumentTypeMismatch`, `IndexingNonArrayTypeVariable`. For **runtime** failures (e.g. array OOB on a member array), use `/; EXPECT_ERROR: Runtime` — the runner matches the substring `Runtime` in stdout/stderr (same pattern as `ArrayTests/runtime_errors/`).

**Comments:** Prefer no leading `//` as the first line of a `.fg` file if the compiler pipeline rejects it; keep programs starting with `class`, `type`, `fun`, or `var` as in other LatestTests. For error tests, the first line may be `/; EXPECT_ERROR: ...`.

---

## Module tests (`ModuleTests`)

| Category | Subdirectory | Coverage |
| -------- | ------------ | -------- |
| Basic | `01_basic/` | `module [m]`, module-level `var`, `println(m::x)` |
| Functions | `02_functions/` | `fun` in module, `m::func()` |
| Errors | `11_errors/` | Unknown module in `name::x` (often `VariableNotFound` today) |

**Syntax:** A file that starts with `module [name]` treats the rest of the file (until EOF) as module members. Use `name::symbol` for qualified access (including from inside the same module).

---

## Bring tests (`BringTests`)

| Category | Subdirectory | Coverage |
| -------- | ------------ | -------- |
| OK | `01_ok/` | `bring "sibling.fg"` resolves **relative to the main file’s directory**; sub-file must compile cleanly; use **direct** `bring` of each file you need (symbols from a nested `bring` in another file are **not** visible) |
| Errors | `11_errors/` | Missing file (`FileNotFound`), broken lib (`FileContainsErrors` / lexer errors), **duplicate** `bring` of the same file (`VariableAlreadyDeclared` / other “already declared”), **circular** `bring` (`CircularReference`), **transitive** use of a name only imported deeper in the chain (`VariableNotFound` / `IdentifierNotFoundInFileOrModule`) |
| Support libs | `support_*` siblings (e.g. `support_dup_lib/`, `support_circular_bring/`, `include_for_nested_chain/`) | `.fg` files used only as `bring` targets; keep them **outside** `01_ok/` and `11_errors/` so `tests/runner.py` (which uses `rglob("*.fg")`) does not treat them as standalone tests |

**Semantics:** `bring` type-checks the referenced file (nested semantic analysis). On success, only globals **defined** in that file are merged (not symbols that file obtained via its own nested `bring`). `bring {a,b} from "f.fg"` lists names among those **direct** exports; `bring "f.fg"` bulk-imports them. Built-ins and compiler-internal `fg_*` helpers from the nested compile are skipped. Choosy imports must list every name the main file uses, including **type** aliases (e.g. `T`, `TB`).

**Circular dependency:** A cycle (e.g. A→B→A or `bring "self.fg"`) is a **compile error** (`CircularReference`), not supported.

### Legacy Z mirrors (full corpus)

The **entire** trees from `tests/fixtures/Z_BringTest/BringTest` and `tests/fixtures/Z_ModuleTest/ModuleTest` are mirrored under LatestTests:

| Mirror | Path |
| ------ | ---- |
| Z Bring | `BringTests/legacy_Z_BringTest/` |
| Z Module | `ModuleTests/legacy_Z_ModuleTest/` |

These are **skipped by default** when running `tests/runner.py` on a broad `--dir` (e.g. all of `LatestTests`) so CI stays green. To run them:

```sh
FLOWWING_RUN_LEGACY_Z=1 python3 tests/runner.py --bin build/FlowWing --dir tests/fixtures/LatestTests --mode jit
# or point --dir at a legacy mirror folder only
python3 tests/runner.py --bin build/FlowWing --dir tests/fixtures/LatestTests/BringTests/legacy_Z_BringTest --mode jit
```

See each mirror’s `README.md` for details.

---
