---
sidebar_position: 1
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# For Loop

Flow-Wing supports the `for` keyword to iterate over a sequence of values.

### Example Usage:

<CodeBlock code={
`for var i = 0 to 10  {
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`0 1 2 3 4 5 6 7 8 9 10
`} />

Here, the `for` keyword is used to iterate over a sequence of values. statment inside loop is executed 11 times. Since By Default, the steper is 1.

## With Steper

Flow-Wing supports the `for` keyword to iterate over a sequence of values with a steper.

### Example Usage:

<CodeBlock code={
`for var i = 0 to 10 : 2  {
    print(i + " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`0 2 4 6 8 10
`} />

Here, the `for` keyword is used to iterate over a sequence of values with a steper. statment inside loop is executed 6 times.

### For Loop with Array/Container

Flow-Wing supports the `for` keyword to iterate over a sequence of values with a steper.

### Example Usage:

<CodeBlock code={
`for var i = 0 to 5 : 1 {
    print(people[i].name + " ")
}
`} language="fg"/>
### Using Outside Variable

<CodeBlock code={
`var i: int = 0
for i = 0 to 5 : 1 {
    print(people[i].name + " ")
}
`} language="fg"/>