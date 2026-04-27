---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Declare and Define Functions

Functions are reusable blocks of code that perform a specific task. Define them, call them, pass by reference, return multiple values — it's all here.

## Function Definition

Define a function with a return type and a body:

### Example:

<CodeBlock code={
`fun add(x: int, y: int) -> int {
    return x + y
}

var result: int = add(2, 3)
`} language="fg"/>

### Properties:

- **Arguments**: Takes two `int` parameters.
- **Return Type**: Returns an `int`.


 ## Function with no return value

### Example:

<CodeBlock code={
`fun doNothing() -> nthg {
    /; This function returns nothing
}

fun doNothing2() -> nthg {
    if true {
        return :
    }
}

`} language="fg"/>

`doNothing` returns nothing. `return :` exits early from a `nthg` function. The `:` after `return` represents the absence of a value — it matches the `nthg` return type. Think of it as "return nothing, but return now."

### Early Return from Void Functions

For `nthg` (nothing) functions, use `return :` to bail out early:

<CodeBlock code={
`fun maybePrint(shouldPrint: bool) -> nthg {
    if (!shouldPrint) {
        return :
    }
    print("Hello")
}
`} language="fg"/>


## Only Function Declaration

Declare a function without defining its body — great for separating interface from implementation.

### Example:

<CodeBlock code={
`fun add(x: int, y: int) -> int decl
`} language="fg"/>

### Forward Declarations

Use `decl` when the body lives elsewhere — in a linked native library (`-l` flag) or another file loaded with `bring`:

<CodeBlock code={
`fun external_lib_func(x: int) -> int decl
fun add(x: int, y: int) -> int decl
`} language="fg"/>

## Function Call

Call a function by name with arguments. By default, arguments pass by value — the function gets a copy:

### Example:

<CodeBlock code={
`fun add(x: int, y: int) -> int {
    return x + y
}

var result: int = add(2, 3)

print(result)
`} language="fg"/>


 ## Function Parameters By Reference

Pass parameters by reference with `inout`. The function can modify the caller's variable directly — no copy, no ceremony.

### Example:

<CodeBlock code={
`fun add(inout x: int, y: int) -> int {
    x = 2
    return x + y
}

var x: int = 1
var result: int = add(x, 3)

print("x: ", x)
`} language="fg"/>

**Output:**
<CodeBlock code={
`x: 2
`} />

## Function With Default Value Parameters

Give parameters default values — callers can skip them and still get sensible behavior.

### Example:

<CodeBlock code={
`fun add(x: int = 2, y: int = 0) -> int {
    return x + y
}

var result: int = add()
print("Result: ", result)
`} language="fg"/>

**Output:**
<CodeBlock code={
`Result: 2
`} />


## Function Example with Multiple Return Values

Return multiple values from a single function — unpack them into multiple variables at the call site.

### Example:

<CodeBlock code={
`fun add(x: int, y: int) -> int, int {
    return x + y, x - y
}

var first: int, second: int = add(2, 3)

print("First: ", first)
print("\\nSecond: ", second)
`} language="fg"/>

**Output:**
<CodeBlock code={
`First:  5
Second:  -1
`} />

## Function Example with Container/Array Return Values and Parameters

Return containers and arrays from functions. Pass them by reference with `inout` to modify them in place.

### Example:

<CodeBlock code={
`fun add(x: int, y: int) -> int[2] {
    return [x + y, x - y]
}

fun update(inout x: int[2]) -> int[2] {
    x[0] = 2
    return x
}

type Person = {
    name: str,
}

var person: Person = { name: "Alice" }
var people: Person[2] = [person, { name: "Bob" }]

fun addPerson(inout people: Person[2], person: Person) -> Person[2] {
    people[1] = person
    return people
}

var result: int[2] = add(2, 3)
`} language="fg"/>


## Function Example with Object Return Values and Parameters

Return objects (types) from functions.

### Example:

<CodeBlock code={
`type Person = {
    name: str
}
fun add(x: int, y: int) -> Person {
    return {name: "Alice" }
}

`} language="fg"/>


## Function Example with Class Return Values and Parameters

Return class instances from functions. Use `new` to create them.

### Example:

<CodeBlock code={
`class Person {
    var name: str
    var age: int
    init(name: str, age: int) -> nthg {
        self.name = name
        self.age = age
    }
    toString() -> str {
        return "Name: " + self.name + ", Age: " + age
    }
}
fun add(x: int, y: int) -> Person {
    return new Person("Alice", 30)
}
var person: Person = add(2, 3)
print(person.toString())
`} language="fg"/>
Output: `Name: Alice, Age: 30`

## Function Example with Class as Parameter 

<CodeBlock code={
`type Person = {
    name: str
    age: int
}
var p: Person = {
    name: "a",
    age: 1
}
fun add(inout person: Person) -> nthg {
    person.age = 2
}
add(p)

`} language="fg"/>

When passing complex types (objects, arrays, class instances), use `inout` to avoid unnecessary copies. If you don't plan to modify the object, pass by value — the compiler handles the rest.






