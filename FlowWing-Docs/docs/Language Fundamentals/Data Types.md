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

- **Precision**: Can handle a wide range of decimal values
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
`var z: deci32 = 1.23
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

## 8. Nir Data Type (`Nir`)

The `Nir` datatype represents the null or Nirast value, often used as a return type for functions that can return null values.

### Example Usage:

<CodeBlock code={
`const val: Nir, err: Err::Result = File.read("file.txt","r")

if err != Nir {
  print(err.getMessage())
}
`} language="fg"/>

### Properties:

- **Usage**: Used to indicate that a function can return null values.
