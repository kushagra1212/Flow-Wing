---
sidebar_position: 3
title: Map module
sidebar_label: Map (map)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Map module (`map`)

## Start here

**`map::Map`** is a **string-keyed, dynamic-value** map: **keys** are **`str`**, and **values** are stored in the language’s **dynamic** representation, so you can store numbers, text, and other values under different keys. Add **`bring map`**, then **`new map::Map()`**.

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

**Typical uses:** small **JSON-like** in-memory data, **config** keyed by name, and **caches** in scripts.

## Common operations (cheat sheet)

- **Read / write** — **`get`**, **`getOr`**, **`set`**
- **Structure** — **`has`**, **`remove`**, **`size`**, **`clear`**

Exact **method** names and optional helpers follow the **`map`** module in your **SDK**; the surface can evolve between versions.

## More detail: keys, values, and `dyn`

`Map` is a **convenience** over **`map::...`**; values behave like the **`dyn`**-style value model for heterogeneous storage. For **type-safe** fixed shapes, the language’s **`type`**, **objects**, and **classes** are often a better long-term design than a single unbounded **map**; use **`Map`** when flexibility matters more.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source (reference)** | **`fw-modules/map_module/map-module.fg`**. |
| **Integration-style fixtures** | **`tests/fixtures/LatestTests/MapModuleTests/`**. |
