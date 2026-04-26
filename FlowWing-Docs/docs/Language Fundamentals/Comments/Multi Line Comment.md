---
sidebar_position: 2
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Multi Line Comment

Flow-Wing supports multi line comments. They start with `/#` and end with `#/`.


### Example Usage:

<CodeBlock code={
`/# This is a multi line comment
   Commented on line 1
   Commented on line 2
   #/

   print("Hello, World!")
`} language="fg"/>

**Output:**
<CodeBlock code={
`Hello, World!
`} />

