---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# 1D Container

Flow-Wing gives you fixed-size 1D arrays with compile-time bounds — think of them as tidy rows of boxes, each holding exactly one value of the same type.

## 1D Array

### Example Usage:

<CodeBlock code={
`var arr: int[10] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
for (var i: int = 0 to 9 : 1) {
    print(arr[i])
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`1 2 3 4 5 6 7 8 9 10
`} />

> **Note:** The `: 1` step is the default. You can write `for (var i: int = 0 to 9) { }`.

### Example Usage: With Objects

<CodeBlock code={
`type Person = {
    name: str
}
var arr: Person[10] = [
    {name: "1"},
    {name: "2"},
    {name: "3"},
    {name: "4"},
    {name: "5"},
    {name: "6"},
    {name: "7"},
    {name: "8"},
    {name: "9"},
    {name: "10"}
]
for (var i: int = 0 to 9 : 1) {
    print(arr[i].name, " ")
}
`} language="fg"/>

**Output:**
<CodeBlock code={
`1 2 3 4 5 6 7 8 9 10 
`} />
