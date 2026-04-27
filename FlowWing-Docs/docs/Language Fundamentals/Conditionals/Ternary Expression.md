---
sidebar_position: 3
---

import Toast from "../../../src/components/common/Toast";
import CodeBlock from "../../../src/components/common/CodeBlock";


# Ternary Expression

Flow-Wing supports the `?` keyword to handle multiple cases.

### Example Usage:

<CodeBlock code={
`println(true ? "Hello" : "World")
print(false ? "Hello" : ("World" + "\n"))
print(2 > 1 ? "Hello" : "World")
`} language="fg"/>

**Output:**
<CodeBlock code={
`Hello
World
Hello
`} />



Here, if the first condition is true, `Hello` is printed. If the first condition is false, `World` is printed.

The `+` operator binds tighter than `?:`. Use parentheses to make intent explicit.

### Example Usage:

<CodeBlock code={
`var x: int = (43 == 43) ? 10 : 20
`} language="fg"/>

Here, if the first condition is true, `10` is assigned to `x`. If the first condition is false, `20` is assigned to `x`.
<Toast message="It is recommended to use `(` and `)` around the condition to get the expected results" title="Recommendation" type="info"/>

<CodeBlock code={
`/; Without parentheses — the + may bind inside the false branch
var r = a > b ? a + 1 : b + 1

/; With parentheses — explicit grouping
var r = (a > b) ? (a + 1) : (b + 1)
`} language="fg"/>

### Example Usage:


<CodeBlock code={
`fun max(a: int, b: int) -> int {
    return ((a > b) ? a : b )
}
print(max(10, 20))
`} language="fg"/>

**Output:**

<CodeBlock code={
`20
`}/>

If `a > b` is true, `a` is returned. Otherwise, `b` is returned.
