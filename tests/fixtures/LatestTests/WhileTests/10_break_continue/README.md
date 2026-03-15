# Break and Continue Tests

These tests cover `break` and `continue` in `while` loops.

## Status

- **01_errors**: Diagnostic tests. Expect compiler to report an error (e.g. break/continue outside loop). These should pass once the runner matches the diagnostic output.
- **02_basic through 06_scope**: Runtime tests. They require **break and continue to be implemented in IR generation**. Currently the compiler asserts in `IRGenerator::visit(BoundBreakStatement*)` and `visit(BoundContinueStatement*)`. After implementing break/continue (branch to loop exit / loop condition block), these tests should pass.

## Layout

- **01_errors**: break/continue outside loop (block, if, function body, etc.)
- **02_basic**: simple break, simple continue, break on condition, continue skip, edge (immediate break/continue)
- **03_edge**: never entered, break after last iter, continue all but last
- **04_nested**: inner break only, outer break from inner, continue inner, deeply nested
- **05_complex**: break/continue with if-else, nested if, after assignment
- **06_scope**: loop inside function (break/continue), global vs local, block scope after break
