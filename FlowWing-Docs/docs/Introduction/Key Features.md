---
sidebar_position: 2
---

High-level capabilities of **Flow-Wing** as a language:

- **Static typing** — built-in types: `int` (32-bit by default), `deci` / `deci32`, `str`, `bool`, and more. Class types, `bring` for modules, `var` with inference, and containers with reassignment.

  ```flowwing
  var x: int = 42
  var name: str = "Flow-Wing"
  var pi: deci = 3.14
  ```

- **Object-oriented programming** — classes, `extends`, `init`, methods. See *Language Fundamentals → Classes* and **Advanced** → *Inheritance*.

  ```flowwing
  class Animal {
      var name: str
  }

  class Dog extends Animal {
      fun bark() {
          print("Woof!")
      }
  }
  ```

- **AOT and JIT** — the AOT compiler produces a native executable you run directly. The JIT tool runs a `.fg` file in one step. Your build or package determines which binaries you get. See *Flow-Wing CLI* and *Getting Started*.

- **Heap memory** — the runtime uses Boehm GC for heap allocation. You never pair allocations with manual `free` in user code.

  ```flowwing
  var items: [int] = [1, 2, 3]
  items.push(4)
  ```

- **Modules and native linking** — `bring` loads Flow-Wing modules. The compiler CLI supports `-L`, `-l`, and on macOS `--framework` for native libraries.

  ```flowwing
  bring sys
  bring io
  ```

- **Developer tooling** — the Flow-Wing VS Code extension gives you in-editor support. Use formatter flags like `-FMP` and debug-style emits (`--emit=…`) for tokens, trees, and IR. Details are in *Flow-Wing CLI*.

- **Sample programs** — small games and demos ship with the project for learning. They are examples, not a separate product or "engine."

For **building the compiler from source**, use *Getting Started → Installation* and the upstream repository. For **writing this documentation**, see **`WRITING.md`** in the `FlowWing-Docs` folder.
