---
sidebar_position: 2
title: Text module (text)
sidebar_label: Text (text)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Text / string utilities (`text`)

> **Name note:** this page is stored as **`Str Module.md`** in the docs tree, but the **module you import** is **`text`**, not `str`. Use **`bring text`**. (Plain **`str`** is a **type** in the language for string values.)

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

## When to use `text::Text`

Use **`text::Text`** for a **builder-style** or **in-place** buffer you mutate (for example call **`toUpper()`** on the object, then **`get()`** to read a **`str`**). Use plain **`str`** and **free functions** when you do not need a long-lived buffer.

**Mutable buffer example:**

<CodeBlock code={
`bring text

var t: text::Text = new text::Text("hello")
t.toUpper()
println(t.get())
`} language="fg"/>

## More detail: free functions and naming

**Free functions** in your install may include (names are not guaranteed every release—verify with the shipped module) **`text::length`**, **`text::concat`**, **`text::toUpper`**, **`text::toLower`**, **`text::trim`**, **`text::replace`**, **`text::reverse`**, **`text::indexOf`**, **`text::substring`**, and more. The **`text::Text`** class carries additional **methods** for in-place work. There is no separate legacy **`text::compare`** for ordering—**`==` / `!=`** cover equality; for sorting semantics, use what your program’s **types** and libraries provide.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/text_module/text-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/StrModuleTests/`** — **`bring`**, path helpers, **substring** / **indexOf** / **mutation** samples (file names use **“str”**; the import is still **`text`**). |
