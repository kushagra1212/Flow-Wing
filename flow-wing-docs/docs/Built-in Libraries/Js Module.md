---
sidebar_position: 11
title: JavaScript module (js)
sidebar_label: JavaScript (js)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# JavaScript module (`js`)

## Start here

**`bring js`** gives a program built for the browser any JavaScript value:
read and set its properties, call its methods, create objects, await
promises, and listen to events. The [dom module](./Dom%20Module.md) is built
on it; use `js` for what `dom` does not cover (local storage, the canvas, the
clipboard, any browser API).

It works in **WebAssembly builds only** (`--target=wasm32`).

<CodeBlock code={
`bring js

var window: js::Value = js::global()
var storage: js::Value = window.get("localStorage")
storage.callWith("setItem", js::args().addStr("theme").addStr("dark"))
println(storage.callWith("getItem", js::args().addStr("theme")).toStr())

var now: js::Value = window.get("Date").construct(js::args())
println(now.call("getFullYear").toInt())
`} language="fg"/>

## How values are held

A JavaScript value cannot live in WebAssembly memory, so a `js::Value` holds a
**handle** to it. When the `js::Value` is collected, the handle is released
and JavaScript can collect the value too. `release()` does it at once.

An **exception** JavaScript throws ends the program with a runtime error that
quotes it, as a Flow-Wing error would. The `try` versions return it as an
`Err::Result` instead:

<CodeBlock code={
`bring js
bring Err

var value: js::Value, err: Err::Result = js::tryEval("JSON.parse('not json')")
if !err.isOk() {
  println("could not parse: " + err.message)
}
`} language="fg"/>

## Values

| Function | Returns | Description |
|---|---|---|
| `js::global()` | `js::Value` | `globalThis`: `window` in a page |
| `js::fromStr(s)`, `js::fromNum(n)`, `js::fromInt(n)`, `js::fromBool(b)` | `js::Value` | A Flow-Wing value as a JavaScript one |
| `js::nullValue()`, `js::undefinedValue()`, `js::array()` | `js::Value` | |
| `js::args()` | `js::ArgList` | Arguments for a call: `js::args().addStr("a").addInt(2).add(value)` |
| `js::eval(code)`, `js::tryEval(code)` | `js::Value` | Run JavaScript source in the page's global scope |
| `js::log(text)` | | `console.log` |

## A value's methods

| Method | Description |
|---|---|
| `get(name)`, `getStr(name)`, `getNum(name)`, `getInt(name)`, `getBool(name)` | Read a property, as a value or converted |
| `set(name, value)`, `setStr`, `setNum`, `setInt`, `setBool` | Set a property; they return the value, so calls chain |
| `at(index)`, `length()` | Elements of an array, or of anything indexable |
| `call(method)`, `callWith(method, args)`, `tryCall(method, args)` | Call a method |
| `invoke(args)` | Call the value itself, as a function |
| `construct(args)` | `new Value(...args)`, for a constructor such as `Date` or `URL` |
| `toStr()`, `toNum()`, `toInt()`, `toBool()` | Convert, as JavaScript's `String`, `Number` and truthiness do |
| `typeOf()` | `typeof`, except `"null"` for null and `"array"` for an array |
| `isUndefined()`, `isNull()`, `same(other)` | Tests; `same` is `===` |
| `release()` | Let JavaScript collect the value now |

## Events, timers and promises

| Function | Description |
|---|---|
| `js::listen(target, event, handler, flags)` | Call `handler.handle(event)` for every `event` on `target`. `flags`: `0`, or `js::PREVENT_DEFAULT` / `js::STOP_PROPAGATION` added together. Returns an id |
| `js::after(ms, handler)`, `js::every(ms, handler)` | A timer, once or repeating |
| `js::unlisten(id)` | Stop a listener or a timer |
| `js::await(promise)` | The promise's value, and an `Err::Result` for a rejection. Waits without blocking the page; run it in a handler or a spawned task |
| `js::stop()` | Stop handling events, so the program can end |

A handler extends `js::Handler` and overrides `handle(event: js::Value)`. The
event value is valid only while `handle` runs.

## Source & tests (if you have the repository)

| What | Where |
|---|---|
| **Module source** | `fw-modules/js_module/`: `js-module.fg`, `js_bridge.c` (the C half), `js-bridge.js` (the JavaScript half) |
| **Tests** | `tests/fixtures/WebTests/js_*`, run with `make test-web` |
