---
sidebar_position: 4
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Assignment expressions

**Assignment operators:**

- **`=`** and **`<-`** (left arrow) are the **same** assignment in meaning: evaluate the right-hand side and store it in the target (variable, index, or member, where the language allows). The two tokens differ **only in syntax**—use whichever you prefer for **readability** or **style**; there is no separate “mode” in behavior between them.

## Compound assignment

**`+=`**, **`-=`**, **`*=`** and **`/=`** combine an operation with the store: **`x += e`** means **`x = x + e`**.

<CodeBlock code={
`var x: int = 10
x += 5
print(x, "\\n")
x -= 3
print(x, "\\n")
x *= 4
print(x, "\\n")

var d: deci = 10.0
d /= 4.0
print(d, "\\n")
`} language="fg"/>

Since **`+`** concatenates strings, **`+=`** appends:

<CodeBlock code={
`var s: str = "Hello"
s += " World"
print(s, "\\n")
`} language="fg"/>

They work on any assignable target — a variable, an array element, an object or class member, an **`inout`** parameter:

<CodeBlock code={
`var arr: int[3] = [1, 2, 3]
arr[1] += 10
print(arr, "\\n")

type T = { v: int }
var o: T = { v: 5 }
o.v *= 3
print(o.v, "\\n")
`} language="fg"/>

**The target is evaluated once.** In **`arr[next()] += 10`** the index expression runs a single time — writing it out as **`arr[next()] = arr[next()] + 10`** would call **`next()`** twice.

The usual home for these is a loop accumulator:

<CodeBlock code={
`var total: int = 0
var i: int = 0
while i < 5 {
    total += i
    i += 1
}
print(total, "\\n")

var joined: str = ""
for (var k: int = 0 to 3 : 1) {
    joined += String(k)
}
print(joined, "\\n")
`} language="fg"/>

Like **`=`**, a compound assignment is itself a **value**, so it composes with the chaining described below:

<CodeBlock code={
`var p: int = 2
var q: int = 0
q = p *= 5
print(q, "\\n")
print(p, "\\n")
`} language="fg"/>

Both print **`10`**.

### When a compound assignment is rejected

**`x op= e`** is valid exactly when **`x = x op e`** is. Two consequences worth knowing:

- **`/=`** on two **`int`** values is an **error**, because **`/`** produces a **`deci`** (**`1 / 2`** is **`0.5`**) and that does not fit back into an **`int`**. Use a **`deci`** target, or **`//=`**-style floor division written out as **`x = x // 2`**.
- Narrow integer targets follow the same promotion rules as ordinary arithmetic: **`int8 + int8`** produces an **`int`**, so **`i += j`** on **`int8`** is rejected just as **`i = i + j`** is.

A compound assignment also takes exactly **one** target — **`a, b += 1, 2`** is an error. Multi-target assignment is available with plain **`=`**.

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
