---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Or if else Statements

Flow-Wing supports `or if` to chain multiple conditional branches together, and `else` to handle the case where none of the conditions are true.

### Example 1: First branch matches

<CodeBlock code={
`var x: int = 10
var y: int = 10

if (x == 10) {
    print("x is 10")
} or if (y == 20) {
    print("y is 20")
} else {
    print("neither condition matched")
}
`} language="fg"/>

**Output:**

<CodeBlock code={
`x is 10
`}/>

### Example 2: `or if` branch matches

<CodeBlock code={
`var a: int = 5

if (a > 10) {
    print("greater than 10")
} or if (a > 3) {
    print("a is between 4 and 10")
} else {
    print("a is 3 or less")
}
`} language="fg"/>

**Output:**

<CodeBlock code={
`a is between 4 and 10
`}/>

`or if` is Flow-Wing's equivalent of `else if` in other languages. Conditions evaluate top-to-bottom; the first matching branch runs. This is called "short-circuit" evaluation.
