# FlowWing Programming Language Reference

FlowWing is a modern, statically-typed programming language with powerful dynamic features, designed for clarity, safety, and efficiency. This document provides a comprehensive overview of the language's syntax, features, and unique behaviors as found in the repository's test fixtures and compiler code.

## 1. File Extension
The standard file extension for FlowWing source files is `.fg`.

---

## 2. Basic Syntax and Types

### 2.1 Variables and Constants
FlowWing uses `var` for mutable variables and `const` for immutable constants.

```flow
var x: int = 10      // Typed variable
var y = 20           // Type inferred as int
const z: str = "Hi"  // Constant string
const PI = 3.14      // Constant float/deci
```

### 2.2 Primitive Types
- **`int`**: 64-bit signed integer (default for literal `1`).
- **`int8`, `int32`, `int64`**: Explicitly sized signed integers.
- **`deci`**: Double-precision floating point (default for literal `1.0`).
- **`deci32`**: Single-precision floating-point.
- **`float`**: Floating-point value (literal: `1.0f`).
- **`bool`**: Boolean (`true`, `false`).
- **`char`**: Single Unicode character (`'a'`).
- **`str`**: UTF-8 encoded string (`"hello"`).
- **`nthg`**: Represents "nothing" (used as return type for void functions).
- **`null`**: Represents the absence of a value (used for classes and optional results).

### 2.3 Comments
FlowWing uses `/;` for single-line comments.

```flow
var a = 5 /; This is a comment
```

---

## 3. Operators

- **Arithmetic**: `+`, `-`, `*`, `/`, `%`
- **Comparison**: `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Logical**: `&&`, `||`, `!`
- **Bitwise**: `&`, `|`, `^`, `~`, `<<`, `>>`
- **Assignment**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`
- **Ternary**: `condition ? true_expr : false_expr`

---

## 4. Control FlowWing

### 4.1 If Statements
```flow
if x > 10 {
  println("Greater")
} else if x == 10 {
  println("Equal")
} else {
  println("Smaller")
}
```

### 4.2 Switch Statements
Supports integers, booleans, and strings.

```flow
switch a {
  case 1: { println("One") }
  case 2: { println("Two") }
  default: { println("Other") }
}
```

### 4.3 For Loops
Traditional C-style for loops are supported.

```flow
for var i: int = 0; i < 10; i = i + 1 {
  println(i)
}
```

### 4.4 While Loops
```flow
while x < 10 {
  x = x + 1
}
```

---

## 5. Functions

### 5.1 Definition
Functions use the `fun` keyword and specify return types with `->`.

```flow
fun add(a: int, b: int) -> int {
  return a + b
}
```

### 5.2 Multi-Return
Functions can return multiple values, which can be captured into multiple variables.

```flow
fun getPoint() -> int, int {
  return 10, 20
}

var px, py = getPoint()
```

### 5.3 Inout Parameters
Pass-by-reference is achieved using the `inout` keyword.

```flow
fun increment(inout n: int) {
  n = n + 1
}

var a = 5
increment(a) /; a is now 6
```

---

## 6. Object-Oriented Programming

### 6.1 Classes and Initialization
Classes use `class` and have an `init` method for constructors.

```flow
class Person {
  var name: str
  fun init(name: str) -> nthg {
    self.name = name
  }
}

var p = new Person("Alice")
```

### 6.2 Inheritance
Uses `is` for inheritance. Subclasses call parent constructors using the parent class name or `super`.

```flow
class Student is Person {
  var id: int
  fun init(name: str, id: int) -> nthg {
    Person::init(name) /; Call parent init
    self.id = id
  }
}
```

---

## 7. Collections

### 7.1 Arrays
Fixed-size arrays with `type[size]` syntax. Supports multi-dimensional arrays.

```flow
var arr: int[5] = [1, 2, 3] /; Padded with zeros
var matrix: int[2][2] = [[1, 2], [3, 4]]
```

### 7.2 Vectors (`vec::Vec`)
Dynamic arrays from the `vec` module. Supports chaining.

```flow
bring vec
var v: vec::Vec = new vec::Vec()
v.push(10).push(20).reverse()
```

### 7.3 Maps (`map::Map`)
Key-value pairs from the `map` module.

```flow
bring map
var m: map::Map = new map::Map()
m.set("key", 100)
```

---

## 8. Modules and Imports

### 8.1 Bring Syntax
Used to import modules or specific symbols from other files.

```flow
bring vec
bring { symbol } from "other_file.fg"
```

---

## 9. Dynamic Typing
The `dyn` type allows for runtime type flexibility.

```flow
var d = 10
d = "String now" /; Legal


```

---

## 10. Built-in Modules and Helpers

### 10.1 `text::Text` (Bring via `bring text`)
Advanced string manipulation class.
- Methods: `getLength()`, `trim()`, `toUpper()`, `toLower()`, `reverse()`, `concat(s)`, `charAt(i)`, `equalsIgnoreCase(s)`, `clear()`, `isEmpty()`.

### 10.2 `Err` Module (Bring via `bring "Err-module.fg"`)
Standard error handling pattern using `Err::Result`.
- Functions: `Err::error(msg, code)`.
- Error Codes: `Err::CODE.NOT_FOUND`, `Err::CODE.INVALID_ARGUMENT`, etc.

### 10.3 Type Conversion Functions
`String(x)`, `Int(x)`, `Deci(x)`, `Bool(x)`, `Char(x)`, `Int8(x)`, `Int32(x)`, `Int64(x)`, `Decimal(x)`, `Decimal32(x)`.

---

## 11. Unique Language Features
- **Padded Arrays**: If an array literal is shorter than its declared size, it is padded with defaults (e.g., `0` for `int`, `""` for `str`).
- **Method Chaining**: Most methods in `vec`, `map`, and `text` return `self` to allow chaining.
- **Qualified Member Access**: Accessing static-like members or parent constructors using `::` (e.g., `Person::init`).
- **Void Equivalent**: `nthg` is the official keyword for "no return value".
- **Self keyword**: Used within classes to refer to the current instance.

---

## Documentation for LLM Code Generation
When generating FlowWing code:
1. Always use `bring` for necessary modules (`vec`, `map`, `text`).
2. Use `println()` for output.
3. Prefer explicit `var` declarations for clarity in complex logic.
4. Use `inout` for functions that need to modify their arguments.
5. Classes must have an `init` function if they require state initialization.
