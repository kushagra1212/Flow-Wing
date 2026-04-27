---
sidebar_position: 2
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Data Types in Flow-Wing

## 1. Integer Data Type (`int`)

The `int` datatype represents a 32-bit signed integer. It is used to store numeric values without any fractional components.

### Example Usage:

<CodeBlock code={
`var x: int = 42
`} language="fg"/>

### Properties:

- **Range**: -2,147,483,648 to 2,147,483,647
- **Default Value**: 0
- **Usage**: Commonly used for counting, indexing, and simple arithmetic operations.

---

## 2. Decimal Data Type (`deci`)

The `deci` datatype is used to store floating-point numbers with decimal points.

### Example Usage:

<CodeBlock code={
`var y: deci = 3.14
`} language="fg"/>

### Properties:

- **Precision**: `deci` is 64-bit (double precision). Use `deci32` (32-bit, single precision) only when memory is constrained.
- **Usage**: Commonly used for financial calculations, scientific computations, and anywhere precision with decimals is required.

---

## 3. Boolean Data Type (`bool`)

The `bool` datatype represents a boolean value, which can be either `true` or `false`.

### Example Usage:

<CodeBlock code={
`var isActive: bool = true
`} language="fg"/>

### Properties:

- **Values**: `true` or `false`
- **Usage**: Commonly used for conditional statements, flags, and toggles.

---

## 4. String Data Type (`str`)

The `str` datatype is used to store sequences of characters.

### Example Usage:

<CodeBlock code={
`var name: str = "flowwing"
print(name, name[2])
`} language="fg"/>

### Properties:

- **Usage**: Commonly used for text processing, displaying messages, and storing any form of textual data.

### String Indexing

Strings are 0-indexed. `name[i]` returns a `char` at position `i`:

<CodeBlock code={
`var name: str = "Flow"
print(name[0])  // 'F'
print(name[3])  // 'w'
`} language="fg"/>

---

## 5. Nothing Data Type (`nthg`)

The `nthg` datatype represents the absence of a value, often used as a return type for functions that do not return any value.

### Example Usage:

<CodeBlock code={
`fun doNothing() -> nthg {
    /; This function does not return anything
}
`} language="fg"/>

### Properties:

- **Usage**: Used to indicate no return value from a function.

---

## 6. 32-bit Decimal Data Type (`deci32`)

The `deci32` datatype represents a 32-bit floating-point number, used for storing decimal values with less precision compared to `deci`.

### Example Usage:

<CodeBlock code={
`var z: deci32 = 1.23f
`} language="fg"/>

### Properties:

- **Precision**: Lower precision compared to `deci`
- **Usage**: Suitable for scenarios where memory usage is a concern and high precision is not required.

---

## 7. 8-bit Integer Data Type (`int8`)

The `int8` datatype represents a 8-bit signed integer, used for storing small integer values.

### Example Usage:

<CodeBlock code={
`var x: int8 = Int8(42)
`} language="fg"/>

### Properties:

- **Range**: -128 to 127
- **Usage**: Suitable for scenarios where memory usage is a concern and high precision is not required.

---

## 8. Null (`null`)

**`null`** is the keyword and type name for the “no value” value. Use it in expressions and comparisons: **`== null`**, **`!= null`**, or assign **`null`** where a reference or optional value can be empty.

### Example usage

<CodeBlock code={
`var n = null
print(null == null, "\\n")
`} language="fg"/>

See the [File Handling Module](../Built-in%20Libraries/File%20Handling%20Module) for real-world `null` and `Err` patterns.

### Properties

- **Usage**: Absence of a value for object references, fields, and other nullable shapes. See the [File Handling Module](../Built-in%20Libraries/File%20Handling%20Module) for real-world `null` and `Err` patterns.

---

## 9. 64-bit Integer Data Type (`int64`)

The `int64` datatype represents a 64-bit signed integer. Use the **`l` suffix** on literals to explicitly create an `int64` value.

### Example Usage:

<CodeBlock code={
`var big: int64 = 10000000000l
var small: int64 = -42l
`} language="fg"/>

### Properties:

- **Range**: -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
- **Default Value**: 0
- **Literal suffix**: `l` (e.g., `100l`, `-1l`)
- **Usage**: When 32-bit integers are not enough—large counters, timestamps, file sizes.

---

## 10. Character Data Type (`char`)

The `char` datatype represents a single **Unicode character**, written with single quotes.

### Example Usage:

<CodeBlock code={
`var letter: char = 'A'
var emoji: char = '🚀'
print(letter, " ", emoji)
`} language="fg"/>

### Properties:

- **Literal syntax**: Single-quoted: `'a'`, `'9'`, `'ñ'`, `'🚀'`
- **Escape sequences**: `\n`, `\t`, `\'`, `\\`
- **Conversion**: Use `Char(65)` to convert an integer codepoint, or `Char("X")` to extract the first character of a string.
- **Usage**: Individual characters, text processing, codepoint arithmetic.

---

## 11. Dynamic Type (`dyn` / `unknown`)

When you declare a variable **without** a type annotation, it becomes a **dynamic** variable. The keyword `unknown` is the compile-time type for such values. A dynamic variable can hold **any value** and can **change its type** at runtime.

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
