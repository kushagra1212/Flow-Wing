---
name: writing-flow-wing
description: Use when writing code in the Flow-Wing (.fg) programming language, especially when dealing with class instantiation, loop syntax, or complex type declarations.
---

# Writing Flow-Wing (.fg)

## Overview
Flow-Wing is a programming language combining static and dynamic typing. This skill provides the correct syntax patterns for writing valid `.fg` code.

## When to Use
- Writing new `.fg` source files.
- Refactoring existing Flow-Wing code.
- Debugging syntax errors in Flow-Wing.

**REQUIRED REFERENCE:** Always consult [docs/FlowWing_Documentation.md](docs/FlowWing_Documentation.md) for full technical details.

## Core Patterns

### Class Instantiation
**Incorrect:** `var a: A = A(10)`
**Correct:** `var a: A = new A(10)`

### For Loops
**Incorrect:** `for (var i = 0 to 10) { ... }`
**Correct:** `for (var i: int = 0 to 10 : 1) { ... }`

## Quick Reference

| Feature | Syntax Example |
|---------|---------------|
| **Constants** | `const PI: deci = 3.14` |
| **Functions** | `fun add(a: int, b: int) -> int { return a + b }` |
| **Arrays** | `var arr: int[5] = [1, 2, 3]` |
| **Printing** | `println("Hello")` or `print(1, "\n")` |

## Common Mistakes

- **Missing `new`**: Forgetting to use `new` when instantiating a class.
- **Loop Syntax**: Omitting the type or the step in a `for` loop.
- **Type Mismatch**: Attempting invalid binary operations between incompatible types (e.g., `true + 1`).
- **Scope**: Forgetting to use `self.` when accessing class members within a method.
