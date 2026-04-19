# Ternary expression tests

Tests for the ternary operator `condition ? then_expr : else_expr`.  
Follows the [TEST_WRITING_GUIDE.md](../FunctionTests/TEST_WRITING_GUIDE.md).

## Structure

| Category              | Subdirectory            | Coverage                                                                 |
| --------------------- | ------------------------ | ------------------------------------------------------------------------- |
| Basic                 | `01_basic`               | Simple ternary, then/else branches, int/string results, truthy values     |
| Conditions            | `02_conditions`          | Bool, int/int8 zero/nonzero, string empty/nonempty, char, logical and/or/not, nested logical, arithmetic result, binary operators, func return str |
| Var decl and assignment | `03_var_decl_assignment` | Variable declaration and reassignment with ternary                        |
| Func return           | `04_func_return`         | Ternary with function calls (int and object return types)                 |
| Errors                | `05_errors`              | `IncompatibleTypesForTernaryExpression` (`.fg` only, no `.expect`)       |
| Dynamic               | `06_dynamic`             | Ternary with dynamic-typed condition (truthy/falsy)                       |
| Edge cases            | `07_edge_cases`          | Negative int, nir (null), chained and/or, deci small, str != "", nested ternary |
| Object                | `08_object`              | Condition with func return object and member access                       |
| Array                 | `09_array`               | Condition with array (nonempty, uninitialized)                             |

## Running tests

```sh
make test-jit ARGS="--filter=LatestTests/TernaryTests --keep-going --parallel"
```

Or with the runner directly:

```sh
python tests/runner.py --bin <path-to-flowwing> --dir tests/fixtures/LatestTests/TernaryTests
```
