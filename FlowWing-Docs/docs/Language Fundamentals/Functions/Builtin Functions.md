---
sidebar_position: 2
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Built-In Functions

## `print`

Prints values to the console. Accepts any number of arguments. Does **not** append a newline.

### Example:
<CodeBlock code={
`print("Hello, World!")
print(2, 3, 4, "Hello")
print("Hello, World!\\nHello, Flow-Wing!")
`} language="fg"/>

## `println`

Prints values to the console. Accepts any number of arguments. Appends a newline after printing.

### Example:
<CodeBlock code={
`println("Hello, World!")
println(1, 2, 3)
println("The answer is", 42)
`} language="fg"/>

## Conversions (built-in callables)

Built-in conversion callables (provided by the language implementation) include **`Int8`**, **`Int32`**, **`Int64`**, **`Decimal`**, **`Decimal32`**, **`String`**, **`Bool`**, **`Char`**, with overloads for several source types. There is **no** standard `input()` console helper in the same set—use **`print`** / **`println`**, the **`file`** or **`sys`** modules, or your own I/O.

### Integer (default `int` is 32-bit)
<CodeBlock code={
`var n: int = Int32("123")
`} language="fg"/>

### `Int8`
<CodeBlock code={
`var b: int8 = Int8(65)
`} language="fg"/>

### `Int64`
<CodeBlock code={
`var big: int64 = Int64("9223372036854775807")
`} language="fg"/>

### `Char`
<CodeBlock code={
`var c: char = Char(65)
`} language="fg"/>

### `deci` (64-bit float) and `deci32`
<CodeBlock code={
`var x: deci = Decimal("123.45")
var y: deci32 = Decimal32("123.45")
`} language="fg"/>

## String Conversion
The String function is used to convert a value to a `string`.

### Example:
<CodeBlock code={
`var myStr: str = String(123)
`} language="fg"/>

## Boolean Conversion
The `Bool` function is used to convert a value to a boolean.

### Example:
<CodeBlock code={
`var flag: bool = Bool(1)
`} language="fg"/>
