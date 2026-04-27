---
sidebar_position: 8
title: JSON module (json)
sidebar_label: JSON (json)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# JSON module (`json`)

## Start here

**`bring json`** lets you **build**, **parse**, and **serialize** JSON data. The module provides a **`json::JsonNode`** class with a fluent API for constructing nested objects and arrays.

### A tiny program

<CodeBlock code={
`bring json

var obj: json::JsonNode = json::newObject()
obj.put("name", json::newString("FlowWing"))
obj.put("year", json::newNumber(2024))
obj.put("active", json::newBool(true))

var jsonStr: str = json::stringify(obj)
println(jsonStr)
`} language="fg"/>

**Output:**
```
{"name": "FlowWing", "year": 2024, "active": true}
```

## Building JSON

Create nodes with the factory functions, then chain calls to build your structure:

### Objects

<CodeBlock code={
`bring json

var user: json::JsonNode = json::newObject()
    .put("name", json::newString("Alice"))
    .put("age", json::newNumber(30))

var address = json::newObject()
    .put("city", json::newString("New York"))
    .put("zip", json::newString("10001"))

user.put("address", address)
println(json::stringify(user))
`} language="fg"/>

### Arrays

<CodeBlock code={
`bring json

var arr: json::JsonNode = json::newArray()
    .push(json::newNumber(1))
    .push(json::newNumber(2))
    .push(json::newNumber(3))

println(json::stringify(arr))

/; Access by index
println("Index 1: ", arr.getAt(1).numVal)
`} language="fg"/>

## Parsing JSON

Parse a JSON string into a `JsonNode` tree:

<CodeBlock code={
`bring json

var raw: str = '{"x":10,"y":[1,2,3],"ok":true}'
var root: json::JsonNode = json::parse(raw)

println("x = ", root.get("x").numVal)
println("y[0] = ", root.get("y").getAt(0).numVal)
`} language="fg"/>

> **Note on string literals:** Single quotes (`'...'`) can be used for JSON string literals to avoid escaping double quotes. Both `'{"key":"val"}'` and `"{\\"key\\":\\"val\\"}"` are valid.

## Factory functions

| Function | Returns | Description |
|----------|---------|-------------|
| `json::newObject()` | `json::JsonNode` | Creates an empty JSON object `{}` |
| `json::newArray()` | `json::JsonNode` | Creates an empty JSON array `[]` |
| `json::newString(s)` | `json::JsonNode` | Creates a JSON string node |
| `json::newNumber(n)` | `json::JsonNode` | Creates a JSON number node |
| `json::newBool(b)` | `json::JsonNode` | Creates a JSON boolean node |
| `json::newNull()` | `json::JsonNode` | Creates a JSON null node |

## Serialization & parsing

| Function | Returns | Description |
|----------|---------|-------------|
| `json::stringify(node)` | `str` | Serializes a node to a JSON string |
| `json::parse(str)` | `json::JsonNode` | Parses a JSON string into a node tree |

## Accessing values

| Property / Method | Type / Returns | Description |
|-------------------|----------------|-------------|
| `.strVal` | `str` | String value of a node |
| `.numVal` | `deci` | Numeric value of a node |
| `.boolVal` | `bool` | Boolean value of a node |
| `.get(key)` | `json::JsonNode` | Get value by key in an object |
| `.getAt(index)` | `json::JsonNode` | Get item by index in an array (out-of-bounds returns `null`) |
| `.put(key, val)` | `json::JsonNode` | Set/update a key in an object (returns self) |
| `.push(val)` | `json::JsonNode` | Append to an array (returns self) |

## Supported JSON features

- **Nested structures** — objects inside objects, arrays inside arrays
- **Method chaining** — `.put().put().push()` style
- **Key overwriting** — calling `.put(key, ...)` on an existing key updates it
- **Escaped characters** — `\n`, `\t`, `\"` in strings
- **Malformed JSON** — `json::parse()` on invalid input returns an empty object `{}`

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source** | `fw-modules/json_module/json-module.fg` |
| **Integration fixtures** | `tests/fixtures/LatestTests/JsonModuleTests/` |
