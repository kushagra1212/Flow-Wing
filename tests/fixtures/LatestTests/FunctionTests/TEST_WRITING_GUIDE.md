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

- **No loops** (`for`, `while`) — not supported in current LatestTests.
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
| Basic          | `01_basic`        | Switch on int, bool, str; case match; default branch                      |
| Default order  | `02_default_order`| Default first in source; match vs no match                                |
| Conditions     | `03_conditions`   | Case with expression, case with variable                                  |
| Nested         | `03_nested`       | Nested switch statements                                                  |
| Edge cases     | `04_edge_cases`   | No match uses default, deci/char, only default                             |
| Errors         | `05_errors`       | MultipleDefaultCaseStatements, CaseExpressionTypeMismatch                 |

**Switch syntax:** Use `case value:{` (no space between `:` and `{`) so the parser does not treat `:` as part of an expression.
