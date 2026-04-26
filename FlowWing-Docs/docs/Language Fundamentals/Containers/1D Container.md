---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# 1D Container

Flow-Wing supports 1D containers.

## 1D Array

Flow-Wing supports 1D arrays.

### Example Usage:

<CodeBlock code={
`var arr: int[10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

for var i = 0 to 9 {
    print(arr[i])
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`1 2 3 4 5 6 7 8 9 10
`} />


### Example Usage: With Objects

<CodeBlock code={
`var arr: Person[10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

for var i = 0 to 9 {
    print(arr[i].name)
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`1 2 3 4 5 6 7 8 9 10
`} />
