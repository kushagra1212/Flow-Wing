---
sidebar_position: 3
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Variables and Constants Declaration

This document provides examples of how to declare variables and constants in Flow-Wing.

## Variable Declaration

Variables in Flow-Wing can be declared with a specific data type and assigned a value.

### Example:
<CodeBlock code={
`var integer: int = 10
var decimal: deci = 5.5
var _string: str = "Hello, Flow-Wing!"
var _boolean: bool = true
var someThing = "Hello, Flow-Wing!"
`} language="fg"/>

Here variable someThing is a `Dynamic Type Variable` that can be assigned any value. but its current value is `"Hello, Flow-Wing!"` which is a `string`.


## Dynamically Allocated Variables

Variables in Flow-Wing can be `dynamically allocated`. This means that they can be assigned a value at runtime.

### Example:
<CodeBlock code={
`var number: int  = new 2
var string: str = new "Hello, Flow-Wing!"
var boolean: bool = new true
`} language="fg"/>

### Example with Complex Type:
<CodeBlock code={
`type Person = {
    name: str,
    age: int,
    height: deci
}

var person: Person = { name: "Alice", age: 30, height: 5.5 }
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

## Constant Declaration

Constants are immutable and cannot be changed after being assigned.

### Example:
<CodeBlock code={
`const x: int = 2
`} language="fg"/>
