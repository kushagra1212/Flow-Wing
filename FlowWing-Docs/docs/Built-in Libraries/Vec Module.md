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
list.set(0, 99)
println(list.get(0))
list.removeAt(1)
`} language="fg"/>

**Output:**
```
3
10
99
```

**Typical uses:** building lists as you go (**`push` / `pop`**), looking up by index (**`get` / `set`**), and sometimes **sorting** or **reversing**.

## Common operations (cheat sheet)

- **Grow & shrink** — **`push`**, **`pop`**, **`insert`**, **`removeAt`**
- **Access** — **`get`**, **`set`**, **`size`**, **`isEmpty`**
- **Utility** — **`clear`**, **`indexOf`**, **`sort(ascending: bool)`**, **`reverse()`**
- You can **chain** calls in many styles the same as with other class APIs.

## Iteration

Use **`size()`** and **`get()`** in a for-loop to iterate over elements:

<CodeBlock code={
`bring vec

var list: vec::Vec = new vec::Vec()
list.push(10)
list.push(20)
list.push(30)

for (var i: int = 0 to list.size() - 1 : 1) {
    println("list[", i, "] = ", list.get(i))
}
`} language="fg"/>

**Output:**
```
list[0] = 10
list[1] = 20
list[2] = 30
```

## Performance

| Operation | Complexity |
|-----------|------------|
| `push()` | O(1) amortized |
| `pop()` | O(1) |
| `get()` | O(1) |
| `set()` | O(1) |
| `insert()` | O(n) |
| `removeAt()` | O(n) |
| `indexOf()` | O(n) |
| `size()` | O(1) |

## More detail: API and behavior

The public surface is the **`vec::Vec`** class. **Vec holds values of any type.** — one `Vec` holds mixed element types, unlike fixed `T[n]` arrays in the type system.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/vec_module/vec-module.fg`** in the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) repository. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/VecModuleTests/`** — how **`bring vec`**, method calls, and edge cases are exercised in the project's tests. |

Cloning the repo is **not** required to **use** **`vec::Vec`**; those paths are for people reading or contributing to the compiler.
