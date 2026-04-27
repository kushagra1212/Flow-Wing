---
sidebar_position: 1
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# For Loop

Flow-Wing supports the `for` keyword to iterate over a sequence of values.

### Example Usage:

<CodeBlock code={
`for var i: int = 0 to 10  {
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4 5 6 7 8 9 10
`} />

Here, the `for` keyword is used to iterate over a sequence of values. The statement inside the loop is executed 11 times. The step `: 1` is the default. Writing `for (var i = 0 to 10)` without `: 1` is equivalent.

## With Step

Flow-Wing supports the `for` keyword to iterate over a sequence of values with a step.

### Example Usage:

<CodeBlock code={
`for (var i: int = 0 to 10 : 2)  {
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`0 2 4 6 8 10
`} />

Here, the `for` keyword is used to iterate over a sequence of values with a step. The statement inside the loop is executed 6 times.

## Descending Loop

Flow-Wing supports descending loops by using a negative step value.

### Example Usage:

<CodeBlock code={
`// Count down from 10 to 0
for (var i: int = 10 to 0 : -1) {
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`10 9 8 7 6 5 4 3 2 1 0
`} />

## Break and Continue

Flow-Wing supports `break` and `continue` control flow statements inside a `for` loop.

### Example Usage:

<CodeBlock code={
`// Skip even numbers
for (var i: int = 0 to 10 : 1) {
    if (i % 2 == 0) {
        continue
    }
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`1 3 5 7 9
`} />

### For Loop with Array/Container

Flow-Wing supports the `for` keyword to iterate over a sequence of values with a step.

### Example Usage:

<CodeBlock code={
`type Person = {
    name: str
}
var people: Person[6] = [
    {name: "a"},
    {name: "b"},
    {name: "c"},
    {name: "d"},
    {name: "e"},
    {name: "f"}
]
for (var i: int = 0 to 5 : 1) {
    print(people[i].name + " ")
}
`} language="fg"/>
### Using a variable from the outer scope (bounds)

The loop control variable is introduced in the `for` head (`var i: int = ...`). You can still read other outer variables in the *bounds* and *step*:

<CodeBlock code={
`type Person = {
    name: str
}
var people: Person[6] = [
    {name: "a"},
    {name: "b"},
    {name: "c"},
    {name: "d"},
    {name: "e"},
    {name: "f"}
]
var last: int = 5
for (var i: int = 0 to last : 1) {
    print(people[i].name + " ")
}

`} language="fg"/>