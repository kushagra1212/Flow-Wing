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

## Keep a function in a variable

A function is a value like any other: keep it in a variable, change it, call
it, pass it on. The variable needs its type written out.

<CodeBlock code={
`fun double(x: int) -> int {
    return x * 2
}

fun triple(x: int) -> int {
    return x * 3
}

var op: [(int) -> int] = double
println(op(5))
op = triple
println(op(5))
`} language="fg"/>

Output: `10`, then `15`

## Keep one in a field

A field of a class or an object type can hold a function. Call it as you
call a method: `box.op(x)`, `self.op(x)`, or `op(x)` inside the class.

<CodeBlock code={
`fun double(x: int) -> int {
    return x * 2
}

class Box {
    var op: [(int) -> int]
    init(op: [(int) -> int]) -> nthg {
        self.op = op
    }
    apply(x: int) -> int {
        return self.op(x)
    }
}

var box: Box = new Box(double)
println(box.apply(4))

type Handlers = {
    onValue: [(int) -> int]
}

var handlers: Handlers = { onValue: double }
println(handlers.onValue(21))
`} language="fg"/>

Output: `8`, then `42`

A function can also **return** a function (`-> [(int) -> int]`), and
`spawn f(x)` runs the function `f` holds.

## A function value that was never set

A variable or a field of a function type that no one set holds no function.
Calling it stops the program with a runtime error that names it:

```
Runtime Error: Cannot call 'op': no function was assigned to it.
```

## Limitations

- Flow-Wing does not currently support anonymous functions (lambdas/closures). Functions must be declared with `fun` before being passed as callbacks.
- A C function (one declared with `decl`) is not a function value: it takes and returns its values another way. Wrap it in a Flow-Wing function to pass it on.
- A method is not a function value (`box.apply` alone), and neither is a built-in such as `println`.
- Arrays of function values are not supported yet.
