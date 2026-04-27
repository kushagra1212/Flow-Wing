---
sidebar_position: 3
---

import CodeBlock from "@site/src/components/common/CodeBlock";


# Ternary Expression

The ternary operator `? :` picks one of two values based on a condition.

## Basic Usage

<CodeBlock code={
`println(true ? "Hello" : "World")
print(2 > 1 ? "Hello" : "World")
`} language="fg"/>

**Output:**
<CodeBlock code={
`Hello
Hello
`} />

When the condition before `?` is true, the left value is used. When false, the right value after `:` is used.

## Assignment

<CodeBlock code={
`var x: int = (43 == 43) ? 10 : 20
print(x)
`} language="fg"/>

**Output:**
<CodeBlock code={
`10
`} />

If the condition is true, `10` is assigned. Otherwise `20`.

Parentheses around the condition are optional. Use them for readability:

<CodeBlock code={
`var r = a > b ? a + 1 : b + 1        /; works
var r = (a > b) ? (a + 1) : (b + 1)  /; also works, clearer
`} language="fg"/>

## Returning from Functions

<CodeBlock code={
`fun max(a: int, b: int) -> int {
    return a > b ? a : b
}
print(max(10, 20))
`} language="fg"/>

**Output:**
<CodeBlock code={
`20
`} />

If `a > b` is true, `a` is returned. Otherwise, `b` is returned.
