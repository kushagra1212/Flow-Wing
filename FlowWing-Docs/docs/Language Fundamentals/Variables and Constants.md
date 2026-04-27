---
sidebar_position: 3
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Variables and Constants Declaration

Everything you need to declare variables and constants in Flow-Wing, with examples.

## Variable Declaration

Declare a variable by giving it a type and a value.

### Example:
<CodeBlock code={
`var integer: int = 10
var decimal: deci = 5.5
var _string: str = "Hello, Flow-Wing!"
var _boolean: bool = true
var someThing = "Hello, Flow-Wing!"
`} language="fg"/>

`someThing` is a **dynamic type variable** — it can hold any value. Right now it holds `"Hello, Flow-Wing!"`, a `string`.


## Typed Variables

Give a variable an explicit type, then assign a value at runtime.

### Example:
<CodeBlock code={
`var number: int = 2
var string: str = "Hello, Flow-Wing!"
var boolean: bool = true
`} language="fg"/>

### Example with Complex Type:
<CodeBlock code={
`type Person = {
    name: str
    age: int
    height: deci
}
var person: Person = {
    name: "Alice",
    age: 30,
    height: 5.5
}
print(person)
`} language="fg"/>

### Example with Array Type:
<CodeBlock code={
`var numbers: int[5] = [1, 2, 3, 4, 5]
`} language="fg"/>

### Example with Default Value:

<CodeBlock code={
`var numbers: int[5]
`} language="fg"/>

Here numbers is an `array` of `int` with a default value of `[0, 0, 0, 0, 0]`.

### Variable Scope

Variables live inside the block `{ }` where you declare them:

<CodeBlock code={
`{
    var x: int = 10
    print(x)  /; 10
}
/; x is out of scope here — gone
`} language="fg"/>

Outer variables are visible inside inner blocks. Inner blocks can shadow outer variables by declaring the same name:

<CodeBlock code={
`var x: int = 10
{
    var x: int = 20  /; shadows outer x
    print(x)  /; 20
}
print(x)  /; 10
`} language="fg"/>

## Constant Declaration

Constants lock in a value at compile time. Use `const` for values that never change — the compiler optimizes them, and nobody accidentally reassigns them:

### Example:

<CodeBlock code={
`const maxUsers: int = 100
/; maxUsers = 200  /; Error: cannot reassign constant
`} language="fg"/>
