---
sidebar_position: 4
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Assignment expressions

**Assignment operators:**

- **`=`** and **`<-`** (left arrow) are the **same** assignment in meaning: evaluate the right-hand side and store it in the target (variable, index, or member, where the language allows). The two tokens differ **only in syntax**—use whichever you prefer for **readability** or **style**; there is no separate “mode” in behavior between them.

## An assignment is also a value

An assignment **produces a value**: the target it just stored into. So assignments **chain**, and they can appear anywhere a value is expected.

Chaining is **right-associative** — **`x = y = 3`** stores **`3`** into **`y`** first, then stores **`y`**’s new value into **`x`**:

<CodeBlock code={
`var x: int = 0
var y: int = 0
x = y = 3
print(x, "\\n")
print(y, "\\n")
`} language="fg"/>

Both print **`3`**. The same works with **`<-`** (**`x <- y <- 3`**), and the two can be mixed in one chain.

Because it is a value, an assignment also works inside a larger expression — a declaration’s initializer, a call argument, a condition, or an operand:

<CodeBlock code={
`var y: int = 0
var total: int = 1 + (y = 2)
print(total, "\\n")
print(y, "\\n")
`} language="fg"/>

**`total`** is **`3`** and **`y`** is **`2`**.

Objects and arrays chain too, and follow the same replacement rules as any other assignment:

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var p1: Person = { name: "", age: 0 }
var p2: Person = { name: "", age: 0 }
p1 = p2 = { name: "Alice", age: 30 }
print(p1, "\\n")
print(p2, "\\n")
`} language="fg"/>

### Multi-target assignments

When an assignment has **several** targets, its value is the **first (leftmost)** one:

<CodeBlock code={
`var a: int = 0
var b: int = 0
var x: int = 0
x = (a, b = 1, 2)
print(x, "\\n")
print(a, "\\n")
print(b, "\\n")
`} language="fg"/>

**`a`** becomes **`1`** and **`b`** becomes **`2`**, and **`x`** takes the **first** target’s value — **`1`**.

### Watch out: assignment in a condition

Since an assignment is a value and a number is truthy, **`if (x = 3)`** is **valid** — it **assigns** **`3`** to **`x`** and then tests it. That is an **assignment**, not the comparison **`x == 3`**:

<CodeBlock code={
`var x: int = 0
if (x = 3) {
    print("this runs\\n")
}
print(x, "\\n")
`} language="fg"/>

If you meant to **compare**, write **`==`**.

Omitted object fields in a **literal** are filled from **type defaults** (e.g. **`0`** for **`int`**, empty **`str`**, etc.), **not** from whatever was in the variable before. To change only one field, assign to that field:

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var person: Person = { name: "Alice", age: 30 }
person.name = "Bob"
print(person)
`} language="fg"/>

That keeps **`age: 30`** and updates **`name`**. By contrast, replacing the **whole** value with a **partial** literal overwrites the whole value with a new object where missing fields are defaults:

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var person: Person = { name: "Alice", age: 30 }
person = { name: "Bob" }
print(person)
`} language="fg"/>

You get **`age: 0`** (default for **`int`**) and **`name: "Bob"`** — not **`age: 30`**. The same happens if you write **`person <- { name: "Bob" }`**: the operator does not “merge” old field values. To keep **`age: 30`**, use a **field** assignment (first example) or a **full** new literal, not a partial one.

## Fixed-size array example

For **`Person[2]`**, assigning from an array **literal** with **fewer** elements than the fixed size still produces a value of the array type: remaining slots are set from **defaults**, not the previous array’s elements.

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var people: Person[2] = [
    { name: "Alice", age: 30 },
    { name: "Bob", age: 30 }
]
people = [{ name: "Charlie", age: 30 }]
print(people)
`} language="fg"/>

**Typical result:** the first entry matches the literal; the second is **default-initialized** (e.g. empty name, **age** **0**), **not** the old **`"Bob"`** row. You could write **`people <- [...]`** here with the same effect.

## Notes

- **`x <- 1`** and **`x = 1`**, **`person <- { name: "Bob" }`** and **`person = { name: "Bob" }`** are interchangeable; pick **`=`** or **`<-`** for taste.
- For **partial** object or array literals, the same **defaulting** rules apply: if you need old data preserved, do not rely on a partial literal; update fields explicitly or build a new full value.
