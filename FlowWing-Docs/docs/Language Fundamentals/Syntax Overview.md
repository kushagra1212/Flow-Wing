---
sidebar_position: 1
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Syntax Overview

Here's what Flow-Wing looks like:

<CodeBlock code={`print("Hello, World!")
`} language="fg"/>

Flow-Wing is **statically typed**, **case-sensitive**, and **whitespace-insensitive** — indentation is yours to choose.

## Basic Structure

<CodeBlock code={`/; Imports
bring someModule

/; Types
type Point = { x: int; y: int }

/; Functions
fun greet(name: str) -> nthg {
    print("Hello, " + name)
}

/; Entry point
fun fg_main() -> int {
    greet("World")
    return 0
}
`} language="fg"/>

## Quick Reference

| Element | Syntax |
|---------|--------|
| Variable | `var x: int = 42` |
| Constant | `const x: int = 100` |
| Function | `fun name(p: Type) -> RetType { }` |
| Type | `type Name = { field: Type }` |
| Class | `class Name { }` |
| If/Else | `if (cond) { } or if (cond) { } else { }` |
| While | `while (cond) { }` |
| For | `for (var i = 0 to 10 : 1) { }` |
| Switch | `switch val { case v: { } default: { } }` |
| Comment (line) | `/; comment` |
| Comment (block) | `/# comment #/` |
| Import | `bring "file.fg"` or `bring {a, b} from mod` |
