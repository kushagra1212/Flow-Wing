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

**Illustration** of a “fat” library (many **`expose`**) — same **`choosy_lib`** idea, shown here as a **fictive** `dependencies.fg` style for teaching **structure**; your real file should **match** the names you list in **`bring { … }`**:

<CodeBlock code={
`expose var globalCount:int = 2

expose type StringWrapper = {
    value:str
}

expose type ComplexType = {
    id:int,
    data:StringWrapper[2]
}

expose var defaultComplexType:ComplexType = {}

expose var complexTypeArray:ComplexType[2]

expose class Printer {
    var count:int
    var complexData:ComplexType

    init(complexData:ComplexType) -> nthg {
        self.complexData = complexData
    }

    printData() -> nthg {
        print(self.complexData)
    }
}

expose fun handleData(input:int) -> nthg {
    var printerInstance:Printer = new Printer({data:[{value:"Hello"}]})
    print("Printer Instance Data: ", printerInstance.complexData)

    print("Global Default Complex Type: ", defaultComplexType)

    print("Input Value: ", input)
}
`} language="fg"/>

(That block is a **self-contained** pattern example; it is **not** the same text as **`choosy_lib.fg`** in this repo—use it as a **template** for your own **expose**s.)

## Source & tests (if you have the repository)

| What | Where |
|------|--------|
| **Choosy + `bring` / `expose` cases** | **`tests/fixtures/LatestTests/BringTests/BringTestBasicTestAllChoosy/`** and the wider **`tests/fixtures/LatestTests/BringTests/`** tree. |
| **Doc sample library** | **`FlowWing-Docs/examples/bring/choosy_lib.fg`**. |
