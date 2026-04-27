---
sidebar_position: 2
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Data Types in Flow-Wing

## 1. Integer Data Type (`int`)

`int` stores a 32-bit signed integer — whole numbers, no fractional parts.

### Example Usage:

<CodeBlock code={
`var x: int = 42
`} language="fg"/>

### Properties:

- **Range**: -2,147,483,648 to 2,147,483,647
- **Default Value**: 0
- **Usage**: Counting, indexing, and simple arithmetic.

---

## 2. Decimal Data Type (`deci`)

`deci` stores floating-point numbers — values with a decimal point.

### Example Usage:

<CodeBlock code={
`var y: deci = 3.14
`} language="fg"/>

### Properties:

- **Precision**: `deci` is 64-bit (double precision). Use `deci32` (32-bit, single precision) only when memory is tight.
- **Usage**: Financial calculations, scientific computations, and anywhere decimal precision matters.

---

## 3. Boolean Data Type (`bool`)

`bool` holds one of two values: `true` or `false`. Think of it as an on/off switch with a name.

### Example Usage:

<CodeBlock code={
`var isActive: bool = true
`} language="fg"/>

### Properties:

- **Values**: `true` or `false`
- **Usage**: Conditions, flags, and toggles.

---

## 4. String Data Type (`str`)

`str` stores a sequence of characters — text, in other words.

### Example Usage:

<CodeBlock code={
`var name: str = "flowwing"
print(name, name[2])
`} language="fg"/>

### Properties:

- **Usage**: Text processing, messages, and any form of textual data.

### String Indexing

Strings are 0-indexed. `name[i]` returns a `char` at position `i`:

<CodeBlock code={
`var name: str = "Flow"
print(name[0])  // 'F'
print(name[3])  // 'w'
`} language="fg"/>

---

## 5. Nothing Data Type (`nthg`)

`nthg` marks the absence of a value. Use it as the return type for functions that don't return anything — no surprise, no data.

### Example Usage:

<CodeBlock code={
`fun doNothing() -> nthg {
    /; This function returns nothing
}
`} language="fg"/>

### Properties:

- **Usage**: Return type for procedures (functions with no return value).

---

## 6. 32-bit Decimal Data Type (`deci32`)

`deci32` is a 32-bit floating-point number — half the precision of `deci`, half the memory.

### Example Usage:

<CodeBlock code={
`var z: deci32 = 1.23f
`} language="fg"/>

### Properties:

- **Precision**: 32-bit (single precision) — lower than `deci`
- **Usage**: Memory-constrained contexts where full double precision isn't worth the cost.

---

## 7. 8-bit Integer Data Type (`int8`)

`int8` is a compact 8-bit signed integer — small numbers in a small footprint.

### Example Usage:

<CodeBlock code={
`var x: int8 = Int8(42)
`} language="fg"/>

### Properties:

- **Range**: -128 to 127
- **Usage**: Memory-tight contexts with values that fit in one byte. Convert from int with `Int8()`.

---

## 8. Null (`null`)

**`null`** is the keyword for "no value." Compare with **`== null`**, **`!= null`**, or assign **`null`** where a reference or optional value might be empty.

### Example usage

<CodeBlock code={
`var n = null
print(null == null, "\\n")
`} language="fg"/>

### Properties

- **Usage**: Absence of a value — object references, optional fields, and other nullable shapes.

See the [File Handling Module](../Built-in%20Libraries/File%20Handling%20Module) for real-world `null` and `Err` patterns.

---

## 9. 64-bit Integer Data Type (`int64`)

`int64` stores a 64-bit signed integer — for when 32 bits aren't enough. Append the **`l` suffix** to literals to explicitly create an `int64` value.

### Example Usage:

<CodeBlock code={
`var big: int64 = 10000000000l
var small: int64 = -42l
`} language="fg"/>

### Properties:

- **Range**: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
- **Default Value**: 0
- **Literal suffix**: `l` (e.g., `100l`, `-1l`)
- **Usage**: Large counters, timestamps, file sizes — anywhere 32 bits would overflow.

---

## 10. Character Data Type (`char`)

`char` holds a single **Unicode character**. Write it in single quotes — yes, even emojis.

### Example Usage:

<CodeBlock code={
`var letter: char = 'A'
var emoji: char = '🚀'
print(letter, " ", emoji)
`} language="fg"/>

### Properties:

- **Literal syntax**: Single-quoted: `'a'`, `'9'`, `'ñ'`, `'🚀'`
- **Escape sequences**: `\n`, `\t`, `\'`, `\\`
- **Conversion**: Use `Char(65)` to convert an integer codepoint, or `Char("X")` to grab the first character of a string.
- **Usage**: Individual characters, text processing, codepoint arithmetic.

---

## 11. Dynamic Type (`dyn` / `unknown`)

Declare a variable **without** a type annotation and Flow-Wing gives you a **dynamic** variable. The keyword `unknown` is the compile-time type for these values. A dynamic variable holds **any value** and can **change its type** at runtime — like a box that reshapes itself to fit whatever you put in.

### Example Usage:

<CodeBlock code={
`var x = 42       // x is dyn, currently holds int
print(x + 1)     // 43 — works, x acts as int
x = "hello"      // x now holds str
print(x + "world")  // helloworld — works, x acts as str
`} language="fg"/>

### Properties:

- **Declaration**: `var name = value` — no type annotation needed
- **All operations** work dynamically: `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `<=`, `>`, `>=`, `&&`, `||`, `!`, `~`
- **Type conversions**: Use `Int32()`, `String()`, `Decimal()`, `Bool()`, `Char()`, `Int64()`, `Int8()`, `Decimal32()` to explicitly convert
- **Usage**: Scripting-style code, heterogeneous collections, prototyping.
