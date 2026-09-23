---
sidebar_position: 10
title: Web page module (dom)
sidebar_label: Web page (dom)
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Web page module (`dom`)

## Start here

**`bring dom`** lets a Flow-Wing program run a web page: find elements, change
them, and handle clicks, typing, timers and network requests. You write only
Flow-Wing; the JavaScript that connects it to the page ships with the
compiler.

It works in **WebAssembly builds only**. A native build that brings `dom`
stops with `ModuleNotForTarget`: a native program has no page.

```
 index.html ──<script src="app.js">──▶ app.js (made by the compiler) ──▶ app.wasm (your program)
                                          ▲                                  │
                                          └──── clicks, timers, fetch ◀──────┘ dom::query, setText, on
```

### A counter

`index.html`:

```html
<!doctype html>
<html>
  <body>
    <button id="add">+</button>
    <span id="count">0</span>
    <script src="app.js"></script>
  </body>
</html>
```

`app.fg`:

<CodeBlock code={
`bring dom

class Increment extends dom::Handler {
  var count: int
  init() -> nthg {
    self.count = 0
  }
  handle(event: dom::Event) -> nthg {
    self.count = self.count + 1
    dom::query("#count").setText(String(self.count))
  }
}

dom::query("#add").on("click", new Increment())
`} language="fg"/>

Build it next to the page, and serve the folder (browsers do not load
WebAssembly from a `file://` address):

```bash
flowwing app.fg --target=wasm32 -o app.js
python3 -m http.server 8000     # then open http://localhost:8000
```

Put the `<script>` tag at the end of `<body>`, so the elements exist when the
program starts.

## How events work

- A **handler** is an object: extend `dom::Handler` and override `handle`.
  Because it is an object, it can keep what it needs, such as the row of a
  list it belongs to.
- Events are handled **one at a time, in order**. Between them the program
  sleeps, and the page stays responsive.
- The program **keeps running while anything listens**, and ends by itself
  when nothing does. `dom::stop()` ends it sooner.
- The browser acts on some events (following a link, submitting a form) as
  soon as its own listeners return, before your handler runs. Pass
  `dom::PREVENT_DEFAULT` to `onWith` to stop that: it is done for you, in the
  listener.

<CodeBlock code={
`bring dom

class RemoveRow extends dom::Handler {
  var row: dom::Element
  init(row: dom::Element) -> nthg {
    self.row = row
  }
  handle(event: dom::Event) -> nthg {
    self.row.remove()
  }
}

class Submitted extends dom::Handler {
  init() -> nthg {
  }
  handle(event: dom::Event) -> nthg {
    var input: dom::Element = dom::query("#item")
    var row: dom::Element = dom::create("li").setText(input.value())
    var remove: dom::Element = dom::create("button").setText("x")
    remove.on("click", new RemoveRow(row))
    dom::query("#list").append(row.append(remove))
    input.setValue("")
  }
}

dom::query("#form").onWith("submit", new Submitted(), dom::PREVENT_DEFAULT)
`} language="fg"/>

## Finding elements

| Function | Returns | Description |
|---|---|---|
| `dom::query(selector)` | `dom::Element` | The first element matching a CSS selector, or `null` |
| `dom::queryAll(selector)` | `dom::ElementList` | Every element matching it |
| `dom::byId(id)` | `dom::Element` | The element with this id, or `null` |
| `dom::create(tag)` | `dom::Element` | A new element, not yet in the page |
| `dom::body()` | `dom::Element` | `document.body` |
| `dom::title()`, `dom::setTitle(text)` | | The page's title |
| `dom::document()`, `dom::window()` | `js::Value` | For anything else, through the [js module](./Js%20Module.md) |

## Elements

Methods that change an element return it, so calls chain:
`dom::create("li").addClass("row").setText("milk")`.

| Method | Description |
|---|---|
| `text()`, `setText(text)` | The text inside. `setText` never parses markup |
| `html()`, `setHtml(html)` | The markup inside. Never pass text a user typed |
| `value()`, `setValue(text)` | A form field's value |
| `checked()`, `setChecked(bool)` | A checkbox's state |
| `attr(name)`, `setAttr(name, value)`, `removeAttr(name)`, `hasAttr(name)` | Attributes; `attr` gives `""` when unset |
| `addClass(name)`, `removeClass(name)`, `toggleClass(name)`, `hasClass(name)` | Classes |
| `setStyle(property, value)`, `style(property)` | One CSS property, by its CSS name: `setStyle("background-color", "red")` |
| `append(child)`, `prepend(child)` | Add a child last or first |
| `remove()` | Take the element out of the page |
| `clear()` | Remove every child |
| `parent()` | The parent element, or `null` |
| `query(selector)`, `queryAll(selector)` | Search inside this element |
| `focus()` | Give it the keyboard focus |
| `on(event, handler)` | Call `handler` for every `event` (`"click"`, `"input"`, `"keydown"`, ...). Returns an id for `dom::cancel` |
| `onWith(event, handler, flags)` | As `on`, with `dom::PREVENT_DEFAULT` and/or `dom::STOP_PROPAGATION` |
| `js()` | The JavaScript element, as a `js::Value` |

`dom::ElementList` has `length()` and `at(index)`.

## Events

| Method | Description |
|---|---|
| `kind()` | The event's type: `"click"`, `"input"`, ... (`""` for a timer) |
| `target()` | The element it happened on |
| `value()` | The value of the form field it happened on |
| `key()` | A keyboard event's key: `"Enter"`, `"a"`, `"ArrowUp"`, ... |
| `js()` | The JavaScript event, as a `js::Value` |

## Timers and the network

| Function | Description |
|---|---|
| `dom::after(ms, handler)` | Call `handler` once, after `ms` milliseconds. Returns an id |
| `dom::every(ms, handler)` | Call it every `ms` milliseconds |
| `dom::cancel(id)` | Stop a listener or a timer |
| `dom::fetchText(url)` | GET `url` and return the body, and an `Err::Result`: a network error, or a status that is not 2xx, is the error |
| `dom::log(text)` | `console.log` |
| `dom::stop()` | Stop handling events, so the program can end |

`fetchText` waits without blocking the page. Call it from a handler or from a
function you `spawn`:

<CodeBlock code={
`bring dom
bring Err

class Load extends dom::Handler {
  init() -> nthg {
  }
  handle(event: dom::Event) -> nthg {
    var body: str, err: Err::Result = dom::fetchText("/data.txt")
    if err.isOk() {
      dom::query("#data").setText(body)
    } else {
      dom::query("#data").setText("Could not load: " + err.message)
    }
  }
}

dom::query("#load").on("click", new Load())
`} language="fg"/>

## Source & tests (if you have the repository)

| What | Where |
|---|---|
| **Module source** | `fw-modules/dom_module/dom-module.fg` |
| **Tests** | `tests/fixtures/WebTests/`, run in a simulated page with `make test-web` |
