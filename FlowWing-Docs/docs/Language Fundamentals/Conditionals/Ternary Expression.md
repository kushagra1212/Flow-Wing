---
sidebar_position: 3
---

import Toast from "../../../src/components/common/Toast";
import CodeBlock from "../../../src/components/common/CodeBlock";


# Ternary Expression

Flow-Wing supports the `?` keyword to handle multiple cases.

### Example Usage:

<CodeBlock code={
`print(true ? "Hello" : "World", "\\n")
print(false ? "Hello" : "World", "\\n")
print(2 > 1 ? "Hello" : "World")  
`} language="fg"/>

**Output:**
<CodeBlock code={
`Hello
World
Hello
`} />



Here, if first condition is true, `Hello` is printed. If first condition is false, `World` is printed.

### Example Usage:

<CodeBlock code={
`var x: int = (43 == 43) ? 10 : 20
`} language="fg"/>

Here, if first condition is true, `10` is assigned to `x`. If first condition is false, `20` is assigned to `x`.
<Toast message="It is recommended to use `(` and `)` around the condition to get expected results" title="Recommendation" type="info"/>
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

Here, if first condition is true, `10` is returned. If first condition is false, `20` is returned. 
<Toast message="It is recommended to use `(` and `)` around the condition to get expected results" title="Recommendation" type="info"/>
