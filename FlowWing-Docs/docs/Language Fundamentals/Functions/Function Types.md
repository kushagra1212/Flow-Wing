---
sidebar_position: 3
title: Function Types
sidebar_label: Function Types
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Function Types

Flow-Wing lets you pass functions as arguments using function type syntax.

## Syntax

```
[(param_types) -> return_type]
```

## Basic Callback

<CodeBlock code={
`fun greet(name: str) -> nthg {
    print("Hello, " + name)
}

fun runCallback(cb: [(str) -> nthg]) -> nthg {
    cb("World")
}

runCallback(greet)
`} language="fg"/>

Output: `Hello, World`

## Multi-Parameter Callbacks

<CodeBlock code={
`fun add(x: int, y: int) -> int {
    return x + y
}

fun apply(op: [(int, int) -> int], a: int, b: int) -> int {
    return op(a, b)
}

var result: int = apply(add, 3, 4)
print(result)
`} language="fg"/>

Output: `7`

## Limitations

Flow-Wing does not currently support anonymous functions (lambdas/closures). Functions must be declared with `fun` before being passed as callbacks.
