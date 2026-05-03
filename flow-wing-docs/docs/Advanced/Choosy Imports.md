---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Choosy imports

## Start here

**Choosy import** means: **`bring { name1, name2, … } from "path.fg"`** — you import **only** the symbols you list, not the whole file. The **target** file must **`expose`** those names (variables, types, functions, classes). The **path** is **relative to the** **`.fg`** file that contains the **`bring`**.

**Minimal use** (library lives under **`FlowWing-Docs/examples/`** when you follow this site’s layout; adjust the path for **your** tree):

<CodeBlock code={
`bring {x, k, callS} from "../examples/bring/choosy_lib.fg"

print(x)
callS(99)
`} language="fg"/>

Only **`x`**, **`k`**, and **`callS`** are in scope here—other **`expose`**d names in that file stay **out** of this unit unless you add them to **`{ … }`**.

## Why use choosy imports?

- **Smaller** visible namespace—easier to see what a file **depends** on.
- **Avoids** accidental use of **hidden** globals from a **big** library file.
- Pairs with a **well-`expose`d** library: one **`.fg`** can offer many **exports**; each **consumer** picks what it needs.

## Bigger example (many symbols from one library)

<CodeBlock code={
`bring {x, k, j, callS, A, T, TB} from "../examples/bring/choosy_lib.fg"

print(x)
print(k)
print(j)
callS(88)
var p:T
p = {a:2 }
print("print p ", p)
var g:A = new A({})
g.printY()
`} language="fg"/>

## More detail: `expose` and the library file

Everything you list in **`{ … }`** must appear as **`expose var`**, **`expose type`**, **`expose class`**, or **`expose fun`** in the **brought** file. **Order** in **`{ ... }`** does not matter. You **cannot** choosy-import a name the library does **not** **expose** (you would get a **binder** error).

For a **self-contained library example** (with many **`expose`** declarations) see the **`choosy_lib.fg`** listing and the **`dependencies.fg`** pattern on the *Bring (import and exports)* page — they show the full file structure.

> **Same-named symbols across files:** if two brought files both **`expose`** a function or variable with the same name, the binder will report an ambiguity. Use **choosy imports** to pick the specific name from the file you intend, or qualify names under a **`module [name]`** namespace.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Choosy + `bring` / `expose` cases** | **`tests/fixtures/LatestTests/BringTests/BringTestBasicTestAllChoosy/`** and the wider **`tests/fixtures/LatestTests/BringTests/`** tree. |
| **Doc sample library** | **`FlowWing-Docs/examples/bring/choosy_lib.fg`**. |
