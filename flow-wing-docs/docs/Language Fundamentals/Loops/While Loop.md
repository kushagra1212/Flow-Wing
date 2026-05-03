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

### Example Usage: Infinite Loop with Break

The `while true` pattern creates an infinite loop that exits via `break`:

<CodeBlock code={
`var i: int = 0

while true {
    print(i + " ")
    i = i + 1
    if i == 10 {
        break
    }
}

`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4 5 6 7 8 9
`} />

### Example Usage: Nested While Loop

<CodeBlock code={
`var i: int = 0

while i < 3 {
    var j: int = 0
    while j < 3 {
        print("(", i, ",", j, ") ")
        j = j + 1
    }
    i = i + 1
}

`} language="fg"/>

**Output:**
<CodeBlock code={
`(0,0) (0,1) (0,2) (1,0) (1,1) (1,2) (2,0) (2,1) (2,2)
`} />
