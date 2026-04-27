---
sidebar_position: 3
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Creating and using modules

## Start here

A **module** is a **named scope** in its **own** **`.fg`** file: you write **`module [name]`** at the top. Other files **attach** to it with **`bring "path-to-file.fg"`** (path is **relative to the file that contains the** **`bring`**). After that, use **`name::Type`**, **`name::function`**, and **`name::`…** to qualify items **declared in that module**.

**Convention:** name the file **`…-module.fg`** so it is obvious the file is a **module** in a project (not a hard syntax rule, but a strong habit in this project).

**Minimal module (types + shared state):**

<CodeBlock code={
`module [local]

type T = {
    a:int
}

var x:int
`} language="fg"/>

Inside the module file itself you can access members **directly** without **`local::`** — the **`local::`** prefix is needed only when accessing module members **from outside** the module file.

**Another file in the same project** brings it and uses **`local::`:**

<CodeBlock code={
`bring "../examples/modules/local-module.fg"
var localInstance: local::T = {}
`} language="fg"/>

(If you are following these docs, **`local-module.fg`** is the copy under **`FlowWing-Docs/examples/modules/`**; the **`bring`** string must match the path **from the current** **`.fg`** file. See *Getting Started* and **`WRITING.md`**, or use your own **folder layout**.)

## Classes inside a module (namespace)

A **class** in the same module can use **module** types; consumers still say **`local::A`**, **`local::T`**.

**`local-module.fg` (excerpt with a class):**

<CodeBlock code={
`module [local]

type T = {
    a:int
}

var x:int

class A {
    var x: local::T
    var u: int
    init() -> nthg {
    }
}
`} language="fg"/>

**`task.fg` (consumer):**

<CodeBlock code={
`bring "../examples/modules/local-module.fg"

var objectInstance: local::A = new local::A()

print(objectInstance.u)

objectInstance.x = {a:21}
print(objectInstance.x)
`} language="fg"/>

## More detail: `module`, `bring`, and `::`

- **`module [name]`** must match how you **qualify** — the bracket name is the **namespace** for **`name::`…**.
- **Relative** **`bring`** is from the **source** **`.fg`** path, not the shell **cwd** (unless you only have one file).
- The **standard library** ( **`bring vec`**, **`bring file`**, **…** ) is resolved by the **toolchain**; local **`bring "…" `** is for **your** project files. **`expose`** (on *Choosy* and **import** pages) is for **picking** names out of a file that **exports** them to **other** **`.fg` files**—a **plain** `module` file is **brought** as a **unit**; see *Bring* and *Choosy* in this section.

> **Module initialization:** top-level code in a module file runs **once** at program start (before **`fg_main`**). Use this for one-time setup like initializing shared state; the module is not re-executed on subsequent **`bring`** references.

> **Re-export pattern:** use **`bring "sub-module.fg"`** followed by **`expose`** in your module file to **re-export** symbols from a sub-module, so consumers only need to bring your module (not every transitive dependency).

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Module patterns and edge cases** | **`tests/fixtures/LatestTests/ModuleTests/`** in the [Flow-Wing](https://github.com/kushagra1212/Flow-Wing) tree—many real **`module` / `bring` / `::`** fixtures. |
| **Local sample** in this doc tree | **`FlowWing-Docs/examples/modules/local-module.fg`** (used by snippets when compiled from **`FlowWing-Docs/.doc_snippet_tmp/`**). |

Cloning the repo is **not** required to use **`module […]`**; the tests are for **readers and contributors** who want **more** real examples.
