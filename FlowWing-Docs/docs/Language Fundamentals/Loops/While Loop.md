---
sidebar_position: 2
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# While Loop

Flow-Wing supports the `while` keyword to iterate over a sequence of values.

### Example Usage:

<CodeBlock code={
`var i: int = 0

while i < 10 {
    print(i + " ")
    i = i + 1
}

`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4 5 6 7 8 9
`} />

### Example Usage: With Break

<CodeBlock code={
`var i: int = 0

while i < 10 {
    if i == 5 {
        break
    }
    print(i + " ")
    i = i + 1
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4
`} />

### Example Usage: With Continue

<CodeBlock code={
`var i: int = 0

while i < 10 {
    if i == 5 {
        i = i + 1
        continue
    }
    print(i + " ")
    i = i + 1
}

`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4 6 7 8 9
`} />