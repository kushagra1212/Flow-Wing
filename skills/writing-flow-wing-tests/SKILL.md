---
name: writing-flow-wing-tests
description: Use when adding new test fixtures to the Flow-Wing LatestTests directory to verify compiler behavior.
---

# Writing Flow-Wing Tests

## Overview
This skill provides the standardized process for creating test cases in the `LatestTests` suite, ensuring correct directory structure, naming conventions, and error reporting.

## When to Use
- When adding new functionality tests.
- When verifying bug fixes.
- When adding regression tests for known issues.
- When testing compiler error diagnostics.

## Test Formats

### 1. Normal Tests (Success Cases)
Used when the code is expected to run and produce specific output.
- **Files required**: `<test-name>.fg` AND `<test-name>.expect`
- **`.fg` file**: Contains the Flow-Wing source code.
- **`.expect` file**: Contains the exact expected stdout (newline terminated).
- **Naming**: Use `snake_case`.
- **Example**:
  - `tests/fixtures/LatestTests/FunctionTests/01_basic/add_numbers.fg`
  - `tests/fixtures/LatestTests/FunctionTests/01_basic/add_numbers.expect`

### 2. Error Tests (Failure Cases)
Used when the code is expected to trigger a compiler diagnostic.
- **Files required**: `<test-name>.fg` ONLY.
- **Format**: The first line of the `.fg` file MUST be a comment specifying the error:
  `/; EXPECT_ERROR: ErrorName`
- **Naming**: Use `snake_case`.
- **Example**:
  - `tests/fixtures/LatestTests/FunctionTests/10_errors/missing_arg.fg`

## Directory & Naming Rules
- **Path**: `tests/fixtures/LatestTests/<Category>/<subcategory>/<test-name>.fg`
- **Naming**: Always use `snake_case`.
- **Subdirectories**: Use two-digit prefixes for ordering (e.g., `01_basic`, `02_return_types`).

## Common Error Names
| Error Name | Usage |
| :--- | :--- |
| `FunctionNotFound` | Calling an undeclared function |
| `VariableNotFound` | Using an undeclared variable |
| `FunctionArgumentCountMismatch` | Wrong number of arguments |
| `FunctionArgumentTypeMismatch` | Argument type mismatch |
| `InitializerExpressionTypeMismatch` | Type mismatch on variable initialization |
| `Runtime` | For runtime-specific errors (e.g., array OOB) |

## Checklist
- [ ] Is the filename in `snake_case`?
- [ ] Is the directory structure `Category/subcategory/`?
- [ ] For normal tests, is the `.expect` file present and exact?
- [ ] For error tests, is the first line `/; EXPECT_ERROR: <Name>`?
- [ ] Did you run `make test-jit ARGS="--filter=LatestTests ..."` to verify?
