---
sidebar_position: 1
title: Vec module
sidebar_label: Vec (vec)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Vec module (`vec`)

## Start here

**`vec::Vec`** is a **dynamic list**—you can store **different kinds of values** in the same list (for example a number, then a string, then a decimal). In source you write **`bring vec`**, then **`new vec::Vec()`**. You do not manage raw memory in Flow-Wing the way you do in C; the runtime looks after the storage.

### A tiny program

<CodeBlock code={
`bring vec

var list: vec::Vec = new vec::Vec()
list.push(10)
list.push("FlowWing")
list.push(3.14159)
println(list.size())
println(list.get(0))
`} language="fg"/>

**Typical uses:** building lists as you go (**`push` / `pop`**), looking up by index (**`get` / `set`**), and sometimes **sorting** or **reversing** when you have that API on your build.

## Common operations (cheat sheet)

- **Grow & shrink** — **`push`**, **`pop`**, **`insert`**, **`removeAt`**
- **Access** — **`get`**, **`set`**, **`size`**, **`isEmpty`**
- **Utility** — **`clear`**, **`indexOf`**, **`sort(ascending: bool)`**, **`reverse()`** (name your compiler’s module surface when in doubt)
- You can **chain** calls in many styles the same as with other class APIs.

## More detail: API and behavior

The public surface is the **`vec::Vec`** class. The exact set of **methods** can grow between compiler releases; for the authoritative list, use **`--help`**, editor completion, or the **standard library** that ships in **`lib/modules`** with your **SDK**. This module is **dynamically typed** at the value level: one **`Vec` holds mixed** element types, unlike fixed **`T[n]`** arrays in the type system.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/vec_module/vec-module.fg`** in the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) repository. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/VecModuleTests/`** — how **`bring vec`**, method calls, and edge cases are exercised in the project’s tests. |

Cloning the repo is **not** required to **use** **`vec::Vec`**; those paths are for people reading or contributing to the compiler.

## Longer example

<CodeBlock code={
`bring vec

var list: vec::Vec = new vec::Vec()
list.push(10)
list.push("FlowWing")
list.push(3.14159)
println(list.size())
println(list.get(0))
list.set(0, 99)
println(list.get(0))
list.removeAt(1)
`} language="fg"/>
