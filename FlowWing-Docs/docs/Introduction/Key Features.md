---
sidebar_position: 2
---

High-level capabilities of **Flow-Wing** as a language:

- **Static typing** — built-in types such as `int` (32-bit by default in typical programs), `deci` / `deci32`, `str`, `bool`, and more; class types; `bring` for code and modules; `var` and containers with inference and reassignment as defined by the language.

  ```flowwing
  var x: int = 42
  var name: str = "Flow-Wing"
  var pi: deci = 3.14
  ```

- **Object-oriented programming** — classes, `extends`, `init`, methods; see *Language Fundamentals → Classes* and **Advanced** → *Inheritance*.

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

- **AOT and JIT** — a normal install may include an AOT compiler (compile to a native executable you run) and/or a JIT-style tool that runs a `.fg` file in one step. Which binary you have depends on your build or package. See *Flow-Wing CLI* and *Getting Started*.

- **Heap memory** — the runtime uses Boehm GC for ordinary heap allocation at the source level; you do not pair every allocation with a manual `free` in user code the way you would in C.

  ```flowwing
  var items: [int] = [1, 2, 3]
  items.push(4)
  ```

- **Modules and native linking** — `bring` for Flow-Wing modules; the compiler CLI supports `-L`, `-l`, and on macOS `--framework` for native libraries.

  ```flowwing
  bring sys
  bring io
  ```

- **Developer tooling** — in-editor support via a Flow-Wing extension, formatter flags (for example `-FMP`), and debug-style emits (`--emit=…`) for tokens, trees, and IR, where your compiler build enables them. Details are in *Flow-Wing CLI*.

- **Sample programs** — small games and demos are published with the project for learning; they are examples, not a separate product "engine."

For **building the compiler from source**, use *Getting Started → Installation* and the upstream repository. For **writing this documentation**, see **`WRITING.md`** in the `FlowWing-Docs` folder.
