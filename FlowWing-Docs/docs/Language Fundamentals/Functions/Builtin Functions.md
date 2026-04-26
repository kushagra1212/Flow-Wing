---
sidebar_position: 2
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Built-In Functions 

## Print Function
The `print` function is used to print a message to the console.

### Example:
<CodeBlock code={
`print("Hello, World!")
print(2, 3, 4, "Hello")
print("Hello, World!\\nHello, Flow-Wing!")
`} language="fg"/>


## Superclass Reference
The `super` keyword is used to refer to the superclass of the current class.

### Example:
<CodeBlock code={
`class Dog extends Animal {
    init(age: int) -> nthg {
      super(age)
    }
}
`} language="fg"/>

## Input Function
The `input` function is used to read `input` from the user.

### Example:
<CodeBlock code={
`var name: str = input("Enter your name: ")
`} language="fg"/>

**Return Type: `str`**

**Properties:**
    - Usage: Read input from the user


## Integer Conversion
The `Int32` function is used to convert a value to a 32-bit integer.

### Example:
<CodeBlock code={
`var number: int = Int32("123")
`} language="fg"/>

## Decimal Conversion
The Decimal 64function is used to convert a value to a decimal 64-bit floating-point number.

### Example:
<CodeBlock code={
`var number: deci = Decimal("123.45")
`} language="fg"/>

## Decimal32 Conversion
The Decimal32 function is used to convert a value to a `32-bit decimal`.

### Example:
<CodeBlock code={
`var number: deci32 = Decimal32("123.45")
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