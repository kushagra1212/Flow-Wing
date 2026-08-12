---
sidebar_position: 1
title: Comments
sidebar_label: Comments
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Comments

Flow-Wing supports two comment styles.

## Single-Line Comments

Use `/;` to comment out the rest of a line:

<CodeBlock code={
`/; This is a comment
print("Hello")  /; Everything after /; on this line is a comment
`} language="fg"/>

`/;` can appear anywhere on a line. Everything after it becomes a comment.

## Multi-Line Comments

Use `/#` to start and `#/` to end a comment block:

<CodeBlock code={
`/#
This entire
block is a comment.
It can span multiple lines.
#/
print("Hello")
`} language="fg"/>

Multi-line comments **cannot nest**. A `/#` inside a multi-line comment is treated as text, not as a new comment start.

## Comments and the formatter

`flowwing --format-print` keeps a comment where you put it. The rule is the one you would expect:

- A comment **on a line with code** describes the code before it, and stays on that line.
- A comment **on a line by itself** describes the code that follows, and keeps its own line (re-indented to match the surrounding block).

<CodeBlock code={
`var total: int = 0   /; running total
total += 5   /; add five
/; this comment is on its own line
println(total)
`} language="fg"/>

Formatting that gives back:

<CodeBlock code={
`var total: int = 0 /; running total
total += 5 /; add five
/; this comment is on its own line
println(total)
`} language="fg"/>

Runs of spaces before an end-of-line comment are normalised to one. This holds in every position that can end a line — after a declaration, an assignment, a call, a `return`, a type field, an opening `{` or a closing `}`.
