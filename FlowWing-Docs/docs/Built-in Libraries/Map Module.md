---
sidebar_position: 3
title: Map module
sidebar_label: Map (map)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Map module (`map`)

## Start here

**`map::Map`** is a **string-keyed, dynamic-value** map: **keys** are **`str`**, and **values** are stored in the language's **dynamic** representation, so you can store numbers, text, and other values under different keys. Add **`bring map`**, then **`new map::Map()`**.

### A tiny program

<CodeBlock code={
`bring map

var m: map::Map = new map::Map()
m.set("a", 1)
m.set("b", "two")
println(m.get("a"))
println(m.get("b"))
println(m.size())
`} language="fg"/>

**Output:**
```
1
two
2
```

**Typical uses:** small **JSON-like** in-memory data, **config** keyed by name, and **caches** in scripts.

## Common operations (cheat sheet)

- **Read / write** — **`get`**, **`getOr`**, **`set`**, **`insert`** (alias for `set`)
- **Structure** — **`has`**, **`contains`** (alias for `has`), **`remove`**, **`size`**, **`isEmpty`**, **`clear`**

## More examples

### Using `getOr` with a fallback

<CodeBlock code={
`bring map

var m: map::Map = new map::Map()
m.set("x", 42)

var a = m.getOr("x", 0)
var b = m.getOr("missing", 0)
println(a)
println(b)
`} language="fg"/>

**Output:**
```
42
0
```

### Checking keys with `has`, removing entries, and clearing

<CodeBlock code={
`bring map

var m: map::Map = new map::Map()
m.set("key1", "value1")
m.set("key2", "value2")

println(m.has("key1"))
println(m.remove("key1"))
println(m.has("key1"))
println(m.size())

m.clear()
println(m.size())
println(m.isEmpty())
`} language="fg"/>

**Output:**
```
true
true
false
1
0
true
```

## Iteration over keys

Use a **`vec::Vec`** as a sidecar to track inserted keys, then iterate with a for-loop:

<CodeBlock code={
`bring map
bring vec

var m: map::Map = new map::Map()
var keys: vec::Vec = new vec::Vec()

m.set("a", 1)
keys.push("a")
m.set("b", 2)
keys.push("b")
m.set("c", 3)
keys.push("c")

for (var i: int = 0 to keys.size() - 1 : 1) {
    var k = keys.get(i)
    println(k, " = ", m.get(k))
}
`} language="fg"/>

**Output:**
```
a = 1
b = 2
c = 3
```

## More detail: keys, values, and `dyn`

`Map` stores values with the **`dyn`**-style value model for heterogeneous storage. For **type-safe** fixed shapes, the language's **`type`**, **objects**, and **classes** are often a better long-term design than a single unbounded **map**; use **`Map`** when flexibility matters more.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/map_module/map-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/MapModuleTests/`**. |
