---
sidebar_position: 9
title: MongoDB module (mongo)
sidebar_label: MongoDB (mongo)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# MongoDB module (`mongo`)

## Start here

**`bring mongo`** connects Flow-Wing programs to a **MongoDB** server via the official `libmongoc` C driver. The module exposes three classes — **`mongo::Client`**, **`mongo::Collection`**, and **`mongo::Cursor`** — plus a free **`mongo::lastError()`** for diagnostics. Documents go in and out as **JSON strings**, so it pairs naturally with the [`json` module](./Json%20Module.md).

> **Prerequisites:** a reachable `mongod` (default `mongodb://127.0.0.1:27017`) and a Flow-Wing build with the bundled `libmongoc` dependency.

### A tiny program

<CodeBlock code={
`bring mongo

var uri: str = "mongodb://127.0.0.1:27017"
var mc: mongo::Client = new mongo::Client(uri)
if !mc.isOk() {
    println("connect failed: ", mongo::lastError())
    return :
}

var events: mongo::Collection = mc.getCollection("app", "events")
var doc: str = "{\\"k\\":\\"hi\\",\\"n\\":1}"
var ok: bool = events.insertOne(doc)
println("inserted: ", ok)

mc.close()
`} language="fg"/>

> **Note on string literals:** Flow-Wing uses double quotes for strings. Escape inner double quotes with backslash when embedding JSON: `"{\"key\":\"val\"}"`.

## Connecting

<CodeBlock code={
`bring mongo

var mc: mongo::Client = new mongo::Client("mongodb://127.0.0.1:27017")
if !mc.isOk() {
    println("connect failed: ", mongo::lastError())
    return :
}
/; ... use mc ...
mc.close()
`} language="fg"/>

`new mongo::Client(uri)` parses the URI eagerly. `isOk()` returns `false` when the URI is invalid or the handle table is full — read `mongo::lastError()` for the message. **Always call `close()`** when done; it destroys the client *and* every collection/cursor handle the program has opened (the v1 driver uses a single shared handle table).

## Getting a collection

<CodeBlock code={
`bring mongo

var mc: mongo::Client = new mongo::Client("mongodb://127.0.0.1:27017")
var users: mongo::Collection = mc.getCollection("app", "users")
var events: mongo::Collection = mc.getCollection("app", "events")
`} language="fg"/>

`getCollection(db, coll)` is cheap and does not round-trip to the server — collections are created lazily on first write.

## Inserting

### One document

<CodeBlock code={
`bring mongo

var coll: mongo::Collection = mc.getCollection("app", "events")
var doc: str = "{\\"k\\":\\"signup\\",\\"n\\":1}"
var ok: bool = coll.insertOne(doc)
if !ok {
    println("insertOne failed: ", mongo::lastError())
}
`} language="fg"/>

### Many documents

Pass a **JSON array** of documents — each element must be an object.

<CodeBlock code={
`bring mongo

var batch: str = "[{\\"k\\":\\"a\\",\\"n\\":1},{\\"k\\":\\"b\\",\\"n\\":2}]"
var ok: bool = coll.insertMany(batch)
if !ok {
    println("insertMany failed: ", mongo::lastError())
}
`} language="fg"/>

## Counting

<CodeBlock code={
`bring mongo

var n: int64 = coll.count("{\\"k\\":\\"signup\\"}")
println("matched: ", n)

/; count all documents — empty filter "" is treated as {}
var total: int64 = coll.count("")
`} language="fg"/>

Returns `-1` on error; check `mongo::lastError()`.

## Reading

### Single document

<CodeBlock code={
`bring mongo

var hit: str = coll.findOne("{\\"k\\":\\"signup\\"}")
if hit == "" {
    var err: str = mongo::lastError()
    if err != "" {
        println("findOne error: ", err)
    } else {
        println("no match")
    }
} else {
    println("found: ", hit)
}
`} language="fg"/>

`findOne` returns the document as a JSON string in **relaxed extended JSON** form, or `""` for either *no match* or *error* — distinguish the two by checking `mongo::lastError()`.

### Cursor

For multiple results, open a cursor with `find(filterJson, limit)` (pass `limit = 0` for no limit). Read with `next()` until it returns `""`, then `close()`.

<CodeBlock code={
`bring mongo

var cur: mongo::Cursor = coll.find("{\\"k\\":\\"signup\\"}", 100)
var s: str = cur.next()
while s != "" {
    println(s)
    s = cur.next()
}
cur.close()
`} language="fg"/>

> **Always `close()` cursors** to release the server-side cursor and the local handle slot. `mc.close()` also clears every open cursor as a safety net.

## Error handling

There are no exceptions. Every operation reports failure through its return value (`false`, `0`, `-1`, or `""`) and writes a thread-local string readable via `mongo::lastError()`. The last-error slot is **cleared at the start of every call**, so read it immediately after a failing call.

<CodeBlock code={
`bring mongo

var ok: bool = coll.insertOne("not json")
if !ok {
    println("insert failed: ", mongo::lastError())
}
`} language="fg"/>

## `mongo::Client`

| Method | Returns | Description |
|--------|---------|-------------|
| `new mongo::Client(uri)` | `mongo::Client` | Opens a client from a MongoDB connection URI |
| `.isOk()` | `bool` | `true` when the handle is valid |
| `.getCollection(db, coll)` | `mongo::Collection` | Borrows a collection handle from this client |
| `.close()` | — | Destroys this client and every open collection/cursor |

## `mongo::Collection`

| Method | Returns | Description |
|--------|---------|-------------|
| `.insertOne(json)` | `bool` | Inserts one JSON document |
| `.insertMany(jsonArr)` | `bool` | Inserts each element of a JSON array of documents |
| `.findOne(filterJson)` | `str` | First match as JSON, or `""` for none/error |
| `.find(filterJson, limit)` | `mongo::Cursor` | Opens a cursor; `limit = 0` means unlimited |
| `.count(filterJson)` | `int64` | Document count; `-1` on error; `""` filter = `{}` |

## `mongo::Cursor`

| Method | Returns | Description |
|--------|---------|-------------|
| `.next()` | `str` | Next document as JSON; `""` at end-of-stream or error |
| `.close()` | — | Releases the cursor handle |

## Module function

| Function | Returns | Description |
|----------|---------|-------------|
| `mongo::lastError()` | `str` | Most recent error message (thread-local); `""` when none |

## Limits & gotchas

- **Single-threaded model** — handle tables are global; safe for Flow-Wing's single-thread runtime, not for sharing handles across threads.
- **Handle caps** — up to **64** clients, **256** collections, **256** cursors per process.
- **`mc.close()` is "close-all"** — it destroys every open collection and cursor along with the client.
- **JSON in, JSON out** — documents cross the FFI as relaxed extended JSON strings; use the [`json` module](./Json%20Module.md) to build or parse them.
- **`limit = 0`** on `find` returns the full result set; on `count` the filter `""` is treated as `{}`.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module source** | `fw-modules/mongo_module/mongo-module.fg` |
| **Native bridge** | `fw-modules/mongo_module/libflowwing_mongo.cpp` |
| **Local smoke test** | `tests/local/mongo_test.fg` |
