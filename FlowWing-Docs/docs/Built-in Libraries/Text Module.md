---
sidebar_position: 2
title: Text module (text)
sidebar_label: Text (text)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Text / string utilities (`text`)

## Start here

**`text`** adds helpers for **working with `str` values and mutable text buffers**—**`text::length`**, **`text::trim`**, **`toUpper`**, **concatenation**, **substring** search, and a **`text::Text`** class when you want a **mutable** buffer. **String equality** in Flow-Wing is still **`==` / `!=`** on **`str`**.

### A tiny program

<CodeBlock code={
`bring text

var s: str = "  FlowWing  "
println(text::trim(s))
println(text::toUpper("abc"))
println(text::length("hi"))
`} language="fg"/>

**Output:**
```
FlowWing
ABC
2
```

## Free functions (complete list)

| Function | Returns | Description |
|----------|---------|-------------|
| `text::getLength(s)` | `int` | Length of the string |
| `text::length(s)` | `int` | Alias for `getLength` |
| `text::toUpper(s)` | `str` | Convert to uppercase |
| `text::toLower(s)` | `str` | Convert to lowercase |
| `text::reverse(s)` | `str` | Reverse the string |
| `text::trim(s)` | `str` | Remove leading/trailing whitespace |
| `text::replace(s, target, replacement)` | `str` | Replace all occurrences of `target` with `replacement` |
| `text::concat(first, second)` | `str` | Concatenate two strings |
| `text::charAt(s, index)` | `char` | Character at position `index` |
| `text::isEmpty(s)` | `bool` | True if the string is empty |
| `text::equalsIgnoreCase(a, b)` | `bool` | Case-insensitive equality check |
| `text::substring(source, start, end)` | `str` | Extract substring from `start` (inclusive) to `end` (exclusive) |
| `text::indexOf(source, target)` | `int` | First index of `target` in `source`, or `-1` if not found |

## Substring examples

<CodeBlock code={
`bring text

var s: str = "Hello World"
println(text::substring(s, 0, 5))
println(text::substring(s, 6, 11))
println(text::indexOf(s, "World"))
`} language="fg"/>

**Output:**
```
Hello
World
6
```

## When to use `text::Text`

Use **`text::Text`** for a **builder-style** or **in-place** buffer you mutate (for example call **`toUpper()`** on the object, then **`get()`** to read a **`str`**). Use plain **`str`** and **free functions** when you do not need a long-lived buffer.

**Mutable buffer example:**

<CodeBlock code={
`bring text

var t: text::Text = new text::Text("hello")
t.toUpper()
println(t.get())
`} language="fg"/>

**Output:**
```
HELLO
```

## More detail: free functions and naming

**Free functions** include **`text::length`**, **`text::concat`**, **`text::toUpper`**, **`text::toLower`**, **`text::trim`**, **`text::replace`**, **`text::reverse`**, **`text::indexOf`**, and more. The **`text::Text`** class carries additional **methods** for in-place work. There is no separate legacy **`text::compare`** for ordering—**`==` / `!=`** cover equality; for sorting semantics, use what your program's **types** and libraries provide.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/text_module/text-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/StrModuleTests/`** — **`bring`**, path helpers, **substring** / **indexOf** / **mutation** samples. |
