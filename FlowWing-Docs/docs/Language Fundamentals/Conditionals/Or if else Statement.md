---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Or if else Statements

Flow-Wing supports the `or` keyword to chain multiple `if` statements together. and use `else` to handle the case where none of the `if` statements are true.

### Example Usage:

<CodeBlock code={
`var x: int = 10
var y: int = 20

if x == 10 or y == 20 {
    print("x is 10 or y is 20")
} or if (x == 10 or y == 30) {
    print("x is 10 or y is 30")
} else {
    print("x is not 10 or y is not 20")
}
`} language="fg"/>

**Output:**

<CodeBlock code={
`x is 10 or y is 20
`}/>


Here, the `or` keyword is used to chain multiple `if` statements together.
