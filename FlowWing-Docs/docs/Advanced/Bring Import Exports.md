---
sidebar_position: 2
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Bring (import and exports)

## Start here

**`bring`** loads another **`.fg` file** into the **current** compilation. After **`bring "path.fg"`**, you can use **types**, **classes**, **functions**, and **variables** that the **other** file **exposes** to importers. Think of it as the **one**-file **import** for Flow-Wing: **`bring` = “include this file’s **exported** surface into my scope”**.

The **string** is a **path** resolved **relative to the file** that contains the **`bring`**, with **toolchain** rules for **system** / **lib** **modules** (for example **`bring vec`**). For **project** code, use **quoted** **paths** like **`"lib/util.fg"`** or, in these docs, the examples tree:

<CodeBlock code={
`bring "../examples/bring/choosy_lib.fg"
`} language="fg"/>

(Adjust for **your** project; doc snippets are compiled from a temp folder that can reach **`FlowWing-Docs/examples/…`**.)

**Use what the file exports:**

<CodeBlock code={
`bring "../examples/bring/choosy_lib.fg"
print(x)
callS(88)
`} language="fg"/>

The sample **`choosy_lib.fg`** uses **`expose`** on **`x`**, **`callS`**, **types**, **…** so those names are **visible** here. A file with **no** **`expose`** is still a normal **source** file; the story for **picking a subset** of names is *Choosy imports* in this section.

Here is **`choosy_lib.fg`** in full so you can see how a library file is structured:

<CodeBlock code={
`expose var x: int = 2

expose type TB = {
  s: str
}

expose type T = {
  a: int,
  b: TB[2]
}

expose var k: T = {}

expose var j: T[2]

expose class A {
  var x: int
  var y: T
  init(y: T) -> nthg {
    self.y = y
  }
  printY() -> nthg {
    print(self.y)
  }
}

expose fun callS(x: int) -> nthg {
  var aF: A = new A({b: [{s: "Hello"}]})
  print("Printing af ", aF.y)
  print("Printing k ", k)
  print("Print local x", x)
}
`} language="fg"/>

## “Whole file” vs choosy

- **Whole file (default story):** **`bring "file.fg"`** — you rely on the **other** file’s **expose** list (or the module / visibility rules in your build).
- **Choosy only:** **`bring { a, b } from "file.fg"`** — see **Choosy imports** for **`{ }`** and **requirements** on **`expose`**.

## More detail: `dependencies` + consumer (two-file pattern)

**`dependencies.fg`** (library side — no **`expose` required** in this *teaching* copy; in practice match what you **import**):

<CodeBlock code={
`var globalCount:int = 2

type StringWrapper = {
    value:str
}

type ComplexType = {
    id:int,
    data:StringWrapper[2]
}

var defaultComplexType:ComplexType = {}

var complexTypeArray:ComplexType[2]

class Printer {
    var count:int
    var complexData:ComplexType

    init(complexData:ComplexType) -> nthg {
        self.complexData = complexData
    }

    displayComplexData() -> nthg {
        print(self.complexData)
    }
}

fun handleData(input:int) -> nthg {
    var printerInstance:Printer = new Printer({data:[{value:"Hello"}]})
    print("Printer Instance Data: ", printerInstance.complexData)

    print("Global Default Complex Type: ", defaultComplexType)

    print("Input Value: ", input)
}
`} language="fg"/>

**`bring_example.fg` consumer** (uses **`choosy_lib`** in this **documentation** set so the snippet **verifies** end-to-end):

<CodeBlock code={
`bring "../examples/bring/choosy_lib.fg"
print(x)
print(k)
callS(88)
var p:T
p = {a:2}
print("print p ", p)
var g:A = new A({})
g.printY()
`} language="fg"/>

> **Heads-up:** the first block is a **template** of a **self-contained** library file. The second block is wired to the **real** **`choosy_lib.fg`** in **this** repo. When you **split** a real app into **`dependencies.fg` + `app.fg`**, add the right **`bring`** and **`expose`**s so names **match** your **binder** rules.

**Modules** ( **`module [name]`** ) are a **separate** **namespacing** feature—see *Creating and using modules*.

> **Circular imports:** avoid bringing files that (transitively) bring the file that started the chain — the binder will error on unresolved names. If you need shared types across files that reference each other, extract the shared types into a third file and bring that from both sides.

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **General `bring` and multi-file** | **`tests/fixtures/LatestTests/BringTests/`**, especially **`BringTestBasicTestAll/`** for basic **`bring` / path** / **expose**-style cases. |
| **Doc `choosy` library** | **`FlowWing-Docs/examples/bring/choosy_lib.fg`**. |
