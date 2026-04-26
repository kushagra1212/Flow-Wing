---
sidebar_position: 4
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Assignment expressions

**Assignment operators:**

- **`=`** and **`<-`** (left arrow) are the **same** assignment in meaning: evaluate the right-hand side and store it in the target (variable, index, or member, where the language allows). The two tokens differ **only in syntax**—use whichever you prefer for **readability** or **style**; there is no separate “mode” in behavior between them.

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
