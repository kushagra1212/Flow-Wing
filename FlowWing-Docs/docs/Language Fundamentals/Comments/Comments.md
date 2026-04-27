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
