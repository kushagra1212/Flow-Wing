# FlowWing Consolidated Documentation

## Lines 1 - 2123

# FlowWing Technical Documentation

This documentation covers the fundamental operations, data types, and array manipulations available in the FlowWing programming language, based on the provided test suite.

## 1. Basic Output Operations

FlowWing provides two primary functions for outputting data to the console: `print` and `println`.

### `print`

The `print` function outputs the provided arguments. It does not automatically append a newline character unless explicitly provided as a string argument.

```flowwing
print("Hello, World!")
print(1, "\n")
```

### `println`

The `println` function outputs the provided arguments followed by a newline character. It can accept multiple arguments, which are printed sequentially.

```flowwing
println(1)
println("hello", " ", "world")
```

---

## 2. Boolean Logic and Comparisons

FlowWing supports a wide range of comparison and logical operators.

### Comparison Operators

The following operators can be used for comparing various types (Int32, Double, Float, String, Char, and Boolean):

- `==` (Equality)
- `!=` (Inequality)
- `>` (Greater Than)
- `<` (Less Than)
- `>=` (Greater Than or Equal)
- `<=` (Less Than or Equal)

```flowwing
print(true == false, "\n")
print(1.0 == 1.0, "\n")
print("Hello" > "World", "\n")
print('a' < 'b', "\n")
```

### Logical Operators

Logical operations are performed using:

- `&&` (Logical AND)
- `||` (Logical OR)

```flowwing
print(true && false, "\n")
print(true || false, "\n")
```

### Type Safety in Operations

FlowWing enforces strict type checking. Attempting to perform invalid binary operations between incompatible types (e.g., dividing a boolean by a double or comparing a string to an integer) will result in an `InvalidBinaryOperationWithTypes` error.

```flowwing
/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(true/1.0)

/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
print(2 == "2")
```

---

## 3. Character Handling

The `char` type represents individual characters. FlowWing supports standard ASCII and extended UTF-8 characters, including emojis.

### Character Literals and Escape Sequences

Characters are defined using single quotes. Escape sequences like `\n` (newline), `\t` (tab), and `\\` (backslash) are supported.

```flowwing
print('a', "\n")
print('🚀', "\n")
print("Tab:", '\t', "End\n")
```

---

## 4. Type Conversion

The `String()` function is used to convert various data types into their string representations.

```flowwing
print(String(1), "\n")
print(String(1.0f), "\n")
print(String('a'), "\n" )
print(String(true), "\n")
```

---

## 5. Arithmetic Operations

### Decimal Arithmetic (Double and Float)

FlowWing supports arithmetic for `Double` and `Float` types, including mixed-type arithmetic (e.g., adding an `Int32` to a `Double`).

```flowwing
print(1.3 + 1, "\n")
print(1.3f * 1.2f, "\n")
print(1.3 / 1.2, "\n")
```

### Integer Arithmetic (Int32)

Integer-specific operations include:

- `+`, `-`, `*` (Standard arithmetic)
- `//` (Integer division)
- `%` (Modulus)
- `&`, `|`, `^` (Bitwise AND, OR, XOR)

```flowwing
print(1 // 2, "\n")
print(1 % 2, "\n")
print(1 & 1, "\n")
```

### String Concatenation

The `+` operator is used to concatenate strings. FlowWing allows concatenating strings with numbers, booleans, and characters.

```flowwing
print("Hello" + "World", "\n")
print("Hello" + 2, "\n")
print("Hello" + true, "\n")
print("Hello" + 'a', "\n")
```

---

## 6. Unary Operators

Unary operators are applied to a single operand.

- `!` (Bang): Negates a boolean or checks truthiness.
- `-` (Minus): Negates a numeric value.
- `+` (Plus): Unary plus for numeric values.
- `~` (Tilde): Bitwise NOT (tilting) for integers.

```flowwing
print(!true, "\n")
print(-1.0, "\n")
print(~1, "\n")
```

---

## 7. Arrays

FlowWing supports fixed-size arrays, including multidimensional arrays.

### Array Declaration and Initialization

Arrays can be partially initialized; any unassigned elements are automatically set to their type's default value (e.g., `0` for `int`, `false` for `bool`, `""` for `str`).

```flowwing
var a:int[2] = [1, 2]
var b:int[5] = [1, 2]  // Results in [1, 2, 0, 0, 0]
var c:int[5][2] = [[1, 2], [3, 4]]
```

### Multidimensional Arrays and Slicing

Accessing a single dimension of a multidimensional array returns a "slice" (a view of that dimension). Modifying an element within a slice modifies the original array.

```flowwing
var a:int[2][2] = [[1, 2], [3, 4]]
var p:int[2] = a[1]
p[0] = 11
/; 'a' is now [[1, 2], [11, 4]]
```

### Mixed-Type Arrays

In certain contexts, FlowWing allows arrays to hold mixed types (dynamic-like behavior), though strict typing is generally preferred.

```flowwing
var x:[2] = [2, "Hello"]
x[1] = 2.4
```

---

## 8. Array Errors and Runtime Issues

FlowWing provides several error checks to ensure array safety.

### Common Errors

- `ExpectedAnIntegerForIndexing`: Occurs when a non-integer is used as an index.
- `EmptyContainerExpression`: Occurs when attempting to initialize an array with an empty literal when a size is expected.
- `IndexingMoreDimensionsThanArrayTypeHas`: Occurs when attempting to access more dimensions than the array possesses.
- `ContainerExpressionRankMismatch`: Occurs when the nested structure of an initializer does not match the declared dimensions.

```flowwing
/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var a:int[2] = [1, 2]
print(a[x])

/; EXPECT_ERROR: ContainerExpressionRankMismatch
var a:int[5] = [1, [2, 3]]
```

### Runtime Errors

- `Runtime Error: Array Index Out of Bounds`: Occurs when accessing an index outside the declared range.
- `Runtime Error: Cannot cast Dynamic value to Int32`: Occurs when a dynamic/mixed-type value cannot be safely cast to a specific type.

```flowwing
/; EXPECT_ERROR: Runtime Error: Array Index Out of Bounds.
var a:int[2][2] = [[1, 2], [3, 4]]
println(a[0][3])

/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var x:int = 5
var y = "Hello"
var a:int[5] = [x, y]
```

## Lines 2124 - 4243

# Array Type Conversion and Initialization

FlowWing allows for the conversion of mixed-type elements into specific array types during initialization. When an array is initialized with fewer elements than its defined size, the remaining slots are padded with default values (e.g., `0` for numeric types or `""` for strings).

### Mixed Type Conversion to `deci32`

When initializing a `deci32` array with mixed integer and float values, the elements are converted to the `deci32` type.

```flowwing
var x = 5
var y = 2.2f
var z = 3.2f

var a:deci32[5] = [x, y, z]
print(a)
/; Output: [ 5, 2.2, 3.2, 0, 0 ]
```

### Mixed Type Conversion to `str`

Arrays of type `str` can be initialized with various types (integers, floats, booleans). These values are converted to their string representations. If the array size exceeds the provided elements, the remaining slots are filled with empty strings.

```flowwing
var x = 5
var y = "Hello"
var z = 3.2f
var w:bool = true

var a:str[5] = [x, y, z, w]
print(a)
/; Output: [ "5", "Hello", "3.2", "true", "" ]
```

### 3D Array Initialization with Variables

Multi-dimensional arrays can be initialized using variables. If the nested structures provided do not fully populate the array dimensions, the remaining space is padded with zeros.

```flowwing
var x:int = 10
var a:int[5][3][2] = [[[1, 2], [3, 4]], [[x], [7, 8]], [[9, 10], [11, 12]]]
print(a)
/; Output: [ [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ] ], [ [ 10, 0 ], [ 7, 8 ], [ 0, 0 ] ], [ [ 9, 10 ], [ 11, 12 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ], [ [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ] ]
```

# Boolean Literal Operations

Boolean literals support logical and comparison operations.

### Logical Expressions

FlowWing supports complex boolean logic using `&&` (AND), `||` (OR), and parentheses for grouping.

```flowwing
print((true && true) || false) /; true
print((true || false) && true) /; true
print((true && false) || (false && true)) /; false
```

### Comparison Operators

Boolean values can be compared using equality (`==`), inequality (`!=`), and relational operators (`>`, `>=`, `<`, `<=`).

```flowwing
print(true == true)   /; true
print(true == false)  /; false
print(true > false)    /; true
print(false >= false) /; true
```

# Character Literal Operations

Characters in FlowWing can interact with integers, booleans, and other characters.

### Character Arithmetic and Concatenation

Adding a boolean or an integer to a character results in a new character. Adding two characters results in a string.

```flowwing
print('A' + true)      /; B
print('A' + 1)         /; B
print('a' + 'b')        /; ab (returns string)
print(1.0 + 'a')       /; b
```

### Character Comparison

Characters can be compared using standard relational operators based on their underlying values.

```flowwing
print('a' > 'A')       /; true
print('0' > '9')       /; false
print('a' == 'a')       /; true
```

# Decimal (Floating Point) Operations

FlowWing provides two decimal types: `deci32` (32-bit float) and `deci64` (64-bit double).

### `deci32` Arithmetic

The `deci32` type supports addition, subtraction, multiplication, and division.

```flowwing
print(1.5f + 1.5f)     /; 3
print(6.0f / 2.0f)     /; 3
print(3.14f * 2.0f)     /; 6.2800002
```

### `deci64` Precision and Arithmetic

The `deci64` type offers higher precision for scientific and large-scale calculations.

```flowwing
print(3.14159265359 + 2.71828182846) /; 5.85987448205
print(1.0 / 4.0)                     /; 0.25
```

# Integer Operations

Integer operations are handled via `int32` and `int64` types.

### `int32` Operations

`int32` supports standard arithmetic, bitwise operations, and modulo. Note that division between two integers can return a decimal value.

```flowwing
print(128 & 128)       /; 128 (Bitwise AND)
print(1000 / 3)         /; 333.3333435 (Division returns decimal)
print(1000 // 3)        /; 333 (Integer division)
print(128 % 10)        /; 8 (Modulo)
```

### `int64` and the `l` Suffix

For very large integers, `int64` is used. Literals can be explicitly defined as `int64` using the `l` suffix.

```flowwing
print(3000000000 + 3000000000) /; 6000000000
print(10000l + 10000l)         /; 20000
```

# Error Handling and Invalid Operations

FlowWing enforces type safety during binary operations. Attempting invalid operations will result in an `InvalidBinaryOperationWithTypes` error.

### Invalid Type Combinations

Certain operations, such as adding booleans or performing bitwise operations on characters or decimals, are prohibited.

```flowwing
print(true + true)           /; Error: InvalidBinaryOperationWithTypes
print('a' & 'b')             /; Error: InvalidBinaryOperationWithTypes
print(3.14 & 2.0)            /; Error: InvalidBinaryOperationWithTypes
print("Hello" / "World")       /; Error: InvalidBinaryOperationWithTypes
```

### Integer Overflow

Providing a literal that exceeds the capacity of the integer type will trigger a `NumberTooLargeForInt` error.

```flowwing
print(99999999999999999999999999999999999999999) /; Error: NumberTooLargeForInt
```

## Lines 4244 - 6371

# FlowWing Technical Documentation: Binary Operations, Imports, and Classes

This documentation covers the behavior of binary operations across various literal types, the `bring` keyword for module imports, and the implementation of classes.

## Binary Operations with Literals

FlowWing supports a wide range of binary operations including arithmetic, bitwise, and comparison operators across different integer and floating-point types.

### Int64 Suffix Operations

The `l` suffix is used to denote `int64` literals. These literals support standard arithmetic, including hexadecimal notation.

```flowwing
print(0xFFl + 0x10l, "\n")
/; EXPECT: 271

print(10000000000l // 3l, "\n")
/; EXPECT: 3333333333
```

Large multiplications and mixed-type operations with `int64` are also supported:

```flowwing
print(0x10000l * 0x10000l, "\n")
/; EXPECT: 4294967296

print(10000l * 10000, "\n")
/; EXPECT: 100000000
```

### Int8 Operations

`int8` types support arithmetic, bitwise, and comparison operations. Note that division between `int8` literals can result in decimal values.

**Arithmetic and Modulo:**

```flowwing
print(5 * 3, "\n")
print(100 / 7, "\n")
print(100 % 7, "\n")
```

**Bitwise Operations:**
FlowWing supports bitwise AND (`&`), OR (`|`), and XOR (`^`) for `int8`.

```flowwing
print(5 & 3, "\n")
print(5 | 3, "\n")
print(5 ^ 3, "\n")
```

**Comparisons:**

```flowwing
print(127 > -128, "\n")
print(0 <= 0, "\n")
print(1 != 0, "\n")
```

### Mixed Type Operations

#### Integer and Decimal Mixing

Operations between integers (`int8`, `int32`, `int64`) and decimal types (`float`, `double`) result in decimal values.

```flowwing
print(1000 + 1.5, "\n")
print(1000 / 1.5, "\n")
print(1.5f + 1.5, "\n")
```

#### String and Character Concatenation

Strings can be concatenated with characters (`char`) and other types. Concatenating a string with a character or an integer results in a new string.

```flowwing
print('H' + "ello", "\n")
print("Hello" + 42, "\n")
print("Value: " + true, "\n")
```

#### String Comparisons

Strings are compared lexicographically.

```flowwing
print("abc" < "abd", "\n")
print("a" > "A", "\n")
print("Hello" == "Hello", "\n")
```

### Nir (Null) Operations

The `null` value (referred to as `nir`) can be compared using equality and inequality operators.

```flowwing
print(null == null, "\n")
print(null != null, "\n")
```

---

## The `bring` Keyword

The `bring` keyword is used to import symbols (variables, types, functions, or classes) from other files.

### Basic and Selective Import

You can bring an entire file or select specific symbols using curly braces. To make symbols available for `bring`, they must be marked with the `expose` keyword in the source file.

```flowwing
/; In the source file
expose var x:int = 2

/; In the importing file
bring {x} from "source_file.fg"
```

### Error Handling in `bring`

The compiler enforces several rules regarding imports:

- **CircularReference**: Occurs when two or more files import each other in a cycle.
- **FileNotFound**: Occurs when the specified file does not exist.
- **IdentifierNotFoundInFileOrModule**: Occurs when attempting to bring a symbol that is not `exposed`.
- **VariableAlreadyDeclared**: Occurs when importing the same file multiple times into the same scope.

```flowwing
/; EXPECT_ERROR: CircularReference
bring "../support_circular_bring/bring_circular_pair_b.fg"

/; EXPECT_ERROR: FileNotFound
bring "file_not_exist_9f3a2c1d.fg"
```

---

## Class Definitions and Usage

FlowWing provides a robust class system including initialization, field access, and methods.

### Class Structure and Initialization

Classes are defined using the `class` keyword. The `init` function serves as the constructor. Use `self` to access instance members within the class.

```flowwing
class A {
  var x: int
  var b: str
  fun init(x: int, b: str) -> nthg {
    self.x = x
    self.b = b
  }
}

var a: A = new A(10, "Nice")
```

### Member Access and Methods

Fields can be accessed directly via dot notation. Methods can be defined to mutate state or return values.

**Direct Field Access:**

```flowwing
class A {
  var x: int
}

var a: A = new A()
println(a.x)
```

**Getters, Setters, and Mutation:**

```flowwing
class A {
  var x: int
  fun setX(val: int) -> nthg {
    self.x = val
  }
  fun doubleX() -> nthg {
    self.x = self.x * 2
  }
}
```

### Class Equality

By default, comparing two different instances of a class using `==` returns `false`, even if their internal fields are identical.

```flowwing
class A {
  var x: int
}

println((new A()) == (new A()))
/; EXPECT: false
```

## Lines 6372 - 8494

# FlowWing Class and Object Documentation

This documentation covers the implementation, usage, and error handling of classes, objects, inheritance, and advanced member access in FlowWing.

## Class Members and Methods

FlowWing allows classes to define fields (variables) and methods (functions). Methods can mutate the state of the object, return values, or return nothing (`nthg`).

### Method Mutation and Return Types

Methods can modify the internal fields of a class. A method can return a specific type or use the `nthg` type to indicate it returns nothing (void).

```flowwing
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
  fun doubleX() -> int {
    return x * 2
  }
  fun printX() -> nthg {
    println(self.x)
  }
}
```

### Method Arguments

Methods can accept multiple arguments of various types.

```flowwing
class Calculator {
  var result: int
  fun init() -> nthg {
    self.result = 0
  }
  fun add(a: int, b: int) -> int {
    self.result = a + b
    return self.result
  }
}
```

### Implicit and Explicit `self`

Within a class method, `self` can be used to explicitly reference the current instance, or it can be omitted when accessing fields directly.

```flowwing
class A {
  var x: int
  fun init(val: int) -> nthg {
    self.x = val
  }
  fun getX() -> int {
    return x
  }
}
```

### Method Syntax Variations

FlowWing supports defining methods with or without the `fun` keyword.

```flowwing
class A {
  var x: int
  fun init(v: int) -> nthg {
    self.x = v
  }
  doubleX() -> int {
    return x * 2
  }
}
```

## Initialization (`init`)

The `init` function is a special method used to initialize class instances.

### Default Field Values

If no `init` function is provided, or if fields are not explicitly assigned, they default to zero-values (e.g., `0` for `int`, `""` for `str`, `false` for `bool`).

```flowwing
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
}

var obj: A = new A()
/; obj.a is 0, obj.b is "", obj.d is 0.0, obj.e is false
```

### Overloading `init`

FlowWing supports overloading the `init` function with different parameter signatures.

```flowwing
class A {
  var x: int
  var y: int
  fun init() -> nthg {
    self.x = 0
    self.y = 0
  }
  fun init(a: int) -> nthg {
    self.x = a
    self.y = a
  }
}
```

### Default Parameters in `init`

Parameters in an `init` function can have default values.

```flowwing
class A {
  var a: int
  var b: int
  init(x: int, y: int = 100) -> nthg {
    self.a = x
    self.b = y
  }
}
```

## Functions and Class Interaction

### Passing and Returning Classes

Classes can be passed as arguments to functions and returned from functions.

```flowwing
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun createA() -> A {
  return new A(42)
}

var a: A = createA()
```

### Reassignment and Modification

Functions can modify a class instance before returning it, or a variable can be reassigned to a new instance returned by a function.

```flowwing
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

fun getA() -> A {
  var d: A = new A(100)
  d.x = 21
  return d
}

var a: A = getA()
```

## Operators and Truthiness

### Reference Equality

The equality operators `==` and `!=` compare the memory references of class instances, not their internal field values.

```flowwing
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)
var b: A = new A(2)

if (a == b) {
  /; This will be false because they are different instances
}
```

### Nullability and Truthiness

Class instances can be `null`. An instance is considered "truthy" if it is not `null`.

```flowwing
class A {
  var x: int
  fun init(x: int) -> nthg {
    self.x = x
  }
}

var a: A = new A(2)

if (a) {
  println("a is not null")
}

if (a == null) {
  println("a is null")
}
```

## Inheritance and Polymorphism

### Field and Method Inheritance

A class can extend another class using the `extends` keyword, inheriting all its fields and methods.

```flowwing
class Animal {
  var name: str
  var age: int
  fun init(name: str, age: int) -> nthg {
    self.name = name
    self.age = age
  }
}

class Dog extends Animal {
  var breed: str
  fun init(name: str, age: int, breed: str) -> nthg {
    self.name = name
    self.age = age
    self.breed = breed
  }
}
```

### Using `super` in Derived Classes

Derived classes can call the parent class's `init` function using `super`.

```flowwing
class Base {
  var tag: int
  fun init(x: int) -> nthg {
    self.tag = x
  }
}

class Child extends Base {
  var extra: int
  fun init(y: int) -> nthg {
    super(y)
    self.extra = y + 10
  }
}
```

### Virtual Dispatch (Polymorphism)

FlowWing supports dynamic dispatch. If a derived class overrides a method, the derived version is called even when the object is referenced by a base class type.

```flowwing
class Base {
  fun tag() -> nthg {
    println("Base")
  }
}

class Derived extends Base {
  fun tag() -> nthg {
    println("Derived")
  }
}

var b: Base = new Derived()
b.tag() /; Prints "Derived"
```

## Advanced Types and Integration

### Custom Type Fields

Classes can contain fields of custom `type` definitions (struct-like objects).

```flowwing
type T = {
  a: int
}

class A {
  var obj: T
  fun init(obj: T) -> nthg {
    self.obj = obj
  }
}
```

### Array Members

Class fields can be arrays of specific types.

```flowwing
class A {
  var x: int[2]
  fun init(x: int[2]) -> nthg {
    self.x[1] = x[1]
  }
}
```

### Mutation: `inout` vs By-Value

When passing a class to a function, it is passed by value (the reference is copied). To mutate the original variable (e.g., reassigning the instance), the `inout` keyword must be used.

```flowwing
class A {
  var x: int
  incrementX() -> nthg {
    x = x + 1
  }
}

fun mutable(inout a: A) -> nthg {
  a.x = a.x + 1
}

fun immutable(a: A) -> nthg {
  a.x = a.x + 1
}
```

## Control Flow with Class Members

Class members can be used within standard control flow structures like `if/else`, `switch`, `for`, and `while`.

### Switch on Member Fields

The `switch` statement can evaluate the value of a class field.

```flowwing
class Mode {
  var k: int
  fun init(v: int) -> nthg {
    self.k = v
  }
}

var m: Mode = new Mode(2)
switch (m.k) {
  case 1: { println(10) }
  case 2: { println(20) }
  default: { println(99) }
}
```

## Error Handling

FlowWing provides several compile-time and runtime errors related to class usage.

### Common Compilation Errors

- **`FunctionNotFound`**: Attempting to call a method that does not exist.
- **`ClassAlreadyDeclared`**: Defining a class with a name that is already in use.
- **`ParentClassIsNotAClass`**: Attempting to extend a `type` instead of a `class`.
- **`NewExpressionConstructorArgumentCountMismatch`**: Providing the wrong number of arguments to `new`.

```flowwing
/; EXPECT_ERROR: FunctionNotFound
class A {
  fun init() -> nthg {}
}

var a: A = new A()
println(a.missing())
```

### Runtime Errors

- **`Array Index Out of Bounds`**: Accessing an array index that does not exist.

```flowwing
class A {
  var arr: int[2]
  fun init() -> nthg {
    self.arr[0] = 1
    self.arr[1] = 2
  }
}
var a: A = new A()
println(a.arr[5]) /; Runtime Error
```

## Modules

The `bring` keyword is used to import modules, allowing access to classes defined within them.

```flowwing
bring "support_cnt_module.fg"

class Holder {
  var c: cnt::Counter
  fun init() -> nthg {
    self.c = new cnt::Counter(0)
  }
}
```

## Lines 8495 - 10615

# FlowWing Class and Inheritance Documentation

This documentation covers the behavior of classes, inheritance, constructor mechanics, variable initialization, and scope management within the FlowWing programming language, based on the provided test suite.

## Class Inheritance and Constructors

FlowWing supports class inheritance using the `extends` keyword. When a class is instantiated, its constructor (`init`) is called. In a hierarchy, constructors are executed from the base class down to the derived class.

### Basic Inheritance

Derived classes can define their own variables and methods, which may shadow or extend those of the parent class.

```flowwing
class C {
  var z:deci
  var v:str
  init() -> nthg {
    z  = 22.2
    v ="Hello"
    print("C Constructor is Called",z)
    self.z = z+2.2
  }
  init(x:int) -> nthg {
    print("Called super",x)
  }
  printW() -> nthg {
    print("world")
  }
}

class B extends C {
  var z:int
  var j:deci
  init() -> nthg  {
    z =1
    print(j,"\nB Constructor is Called",self.z)
  }

  printFromB()-> nthg {
    print("Print from B\n")
  }

  getZ() -> int {
    return z+2
  }
  getS() -> deci {
    return 2.4
  }
}

class A extends B {
  var x: int
  var y: deci
  init(y:deci ) -> nthg {
    self.y = y
    print("\nA Constructor is Called",self.z)
    print(v)
  }
}
```

### Using `super()`

The `super()` keyword is used within a derived class's `init` method to explicitly call a constructor from the parent class, allowing for controlled initialization of the base class.

```flowwing
class Animal {
  var age:int
  var species:str
  var t:T
  init(age:int) -> nthg {
    self.age = age
    self.t = {d:"Hi",x:12}
  }
}

class Dog extends Animal {
   var breed:str

  init(age:int) -> nthg {
    super(age)
  }

  getAge() ->int {
    return 7*self.age
  }
}
```

## Variable Initialization and Default Values

FlowWing provides default values for class members when they are not explicitly initialized during declaration or within the `init` method.

### Default Values for Primitives and Complex Types

When a class is instantiated, primitive types and complex types (structs and arrays) are initialized to their zero/empty equivalents:

- `int`: `0`
- `deci`: `0`
- `str`: `""`
- `bool`: `false`
- `struct/type`: All fields are initialized to their respective zero values.
- `array`: All elements are initialized to their respective zero values.

```flowwing
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  type X = {
    x1: str,
    x2: int
  }
  var obj: X
  type Complex = {
    a:int[3],
    j:X[2]
  }
  var arr:X[2]

  init() -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
  }
}
```

## Scope and the `self` Keyword

The `self` keyword is critical for distinguishing between local variables (parameters or variables declared within a function/method) and class members.

### `self` vs. Local Scope

In an `init` method or any class method, assigning a value to a name without `self` may target a local variable rather than the class member, especially if the parameter name matches the member name.

```flowwing
class A {
  var a: int
  var b: str
  var d: deci

  init(a:int,b:str,yesD:deci) -> nthg {
    var obj:X
    print("Pinting u: ")
    print(obj)
    print(a)
    a = a      /; This does not update the class member 'a'
    b = b      /; This does not update the class member 'b'
    d = yesD   /; This does not update the class member 'd'
  }
}
```

### Correct Member Assignment

To correctly update a class member from within a method, the `self` prefix must be used.

```flowwing
class A {
  var a: int
  var b: str
  var d: deci

  init(a:int,b:str,yesD:deci) -> nthg {
    self.a = a
    self.b = b
    d = yesD    /; This is a local assignment to the parameter 'd'
    self.d = yesD /; This is the correct way to update the class member
  }
}
```

### Assignment Caveat in Methods

A significant edge case occurs when attempting to update a class member using an argument of the same name without `self`. The assignment will only affect the local scope of the method.

```flowwing
class A {
  var arr: Complex[2]

  /; This fails to update the class member 'arr'
  updateComplex(arr:Complex[2]) -> nthg {
    arr = arr
  }

  /; This correctly updates the class member 'arr'
  updateComplexCorrect(arr:Complex[2]) -> nthg {
    self.arr = arr
  }
}
```

## Complex Types and Structs

FlowWing allows for the definition of custom types (structs) and the use of arrays of these types.

### Struct Definition and Usage

Structs can be passed as arguments, returned from functions, and nested within other types or classes.

```flowwing
type T = {
    a:int,
    b:str
}

class A {
  var x:int
  var s:str
  var t:T
  var g:T[2]

  init(s: str) -> nthg{
    self.s = s
  }

  getT() -> T {
    return t
  }
}
```

### Nested and Array-based Complex Types

Complex types can include arrays of other complex types, creating deep hierarchies.

```flowwing
type X = {
    x1: str,
    x2: int
}
type Complex = {
    a: int[3],
    j: X[2]
}

class A {
  var arr: Complex[2]

  updateComplex(arr:Complex[2]) -> nthg {
    self.arr = arr
  }
}
```

## Lines 10616 - 12735

# FlowWing Technical Documentation: Class Structures and Inheritance

This documentation covers advanced class mechanics in FlowWing, including member access, complex type manipulation, logical operations on instances, function scoping, and inheritance.

## Class Member Access and Initialization

In FlowWing, class members can be accessed within class methods using either the `self` keyword or by direct name access. During initialization, the `init` method is used to set the initial state of the object.

```flowwing
class A {
  var a: int
  var b: str
  var d: deci
  var e: bool
  var obj: X
  var arr: Complex[2]
  var obj2: Complex
  init(a: int, b: str, yesD: deci, obj: X ) -> nthg {
    print("initCalled")
    self.a = a
    self.b = b
    d = yesD
    self.obj = obj
  }

  updateA() -> nthg {
    a = 100
    self.d = 2.2
    b = "Nice"
  }
}
```

## Complex Type Manipulation within Classes

FlowWing classes can store complex, nested data structures such as arrays of structs or objects containing arrays. These can be updated via methods, and the language supports deep manipulation of these structures.

```flowwing
type X = {
  x1: str,
  x2: int
}
type Complex = {
  a: int[3],
  j: X[2]
}

class A {
  /; ...
  var arr: Complex[2]

  updateComplex(ar: Complex[2]) -> nthg {
    arr = ar
  }

  printAll() -> nthg {
    print(self.arr[0].j[0].x2)
    arr[0].j[0].x2= 2
    /; ...
    obj2 = {
      j: [{
        x2: 2,
        x1: "Ge"
      }],
      a: [2 fill 1]
    }
    print(self.obj2)
    /; ...
  }
}
```

## Logical Operations on Class Instances

The logical NOT operator (`!`) can be applied directly to class instances, allowing for truthiness checks in conditional statements.

```flowwing
class A {
  var x:int
  init(x:int) -> nthg {
      self.x = x
    }
}

var a:A = new A(2)

if(!a){
  print("A")
}or if(a){
    print("or A")
  }
```

## Function Scope and Visibility within Class Methods

Methods defined within a class have access to both global functions and other methods defined within the same class. A method can call a global function directly, or call a class method using `self`.

```flowwing
fun printNice() -> nthg {
    print("Not Nice")
  }

fun outsidefun()-> nthg {
      print("Outsidefunction")
    }

class A {
  /; ...
  printAll() -> nthg {
    /; ...
    printNice()      /; Calls the global function
    self.printNice() /; Calls the class method
    outsidefun()      /; Calls the global function
  }

  printNice() -> nthg {
      print("Nice")
    }
}
```

## Returning Class Objects from Functions

Functions in FlowWing can return instances of a class. When a class object is returned, it maintains its state, and subsequent modifications to the returned object are reflected accordingly.

```flowwing
type T = {
  a:int
}

class A{
  var obj:T

  init(obj:T) -> nthg {
    self.obj = obj
  }
}

fun getA() -> A {
  var d:A= new A({a:100})
  d.obj.a = 21
  return d
}

var a:A =  getA()
a.obj = {a:32}
print(a.obj)
```

## Class Inheritance and the `super` Keyword

FlowWing supports inheritance via the `extends` keyword. Subclasses can call the parent class's constructor or methods using the `super` keyword.

```flowwing
class A {
  type T3A = {
    u:str,
  }
  var x:T1
  var a:T3A
  init(x:T1) -> nthg {
    self.x = x
    a = {u:"Nice"}
  }
}

class B extends A  {
  init(y:T1) -> nthg {
    super(y)
  }
}
```

### Polymorphism and Base Class References

A significant caveat in FlowWing inheritance is how method resolution behaves when using a base class reference. If a variable is declared with the type of the base class, even if it holds an instance of a child class, only the methods defined in the base class are accessible through that variable.

```flowwing
class A {
  /; ...
  printX() -> nthg {
      print(self.x)
    }
}

class B extends A  {
  /; ...
  printX()-> nthg {
      print("Not printing it ")
    }
}

/; Even though 'b' is an instance of B, it is typed as A.
/; Therefore, b.printX() will execute the implementation in class A.
var b:A = new B({a:2})
b.printX()
```

## Lines 12736 - 14856

# FlowWing Technical Documentation

## Inheritance and Dynamic Method Dispatch

FlowWing supports class inheritance, allowing a child class to extend a base class. This enables **Dynamic Method Dispatch**, where a method call on a base class reference is resolved at runtime to the implementation provided by the actual object type.

In the following example, the `Dog` class extends `Animal`. When `printAge` is called with a `Dog` object, it uses the overridden `getAge` method from the `Dog` class rather than the base `Animal` class.

```flowwing
class Animal {
  var age:int
  var species:str
  init(age:int) -> nthg {
    self.age = age
  }
  getAge() -> int {
    return self.age
  }
  printSpecies() -> nthg {
    print("Species: ",species)
  }
}

class Dog extends Animal {
   var breed:str

  init(age:int) -> nthg {
    super(age)
  }

  getAge() ->int {
    return 7*self.age
  }
  printBreed() -> nthg {
    print("breed "+breed)
  }
}

fun printAge(a: Animal) ->nthg{
  print("I'm "+a.getAge()+" years old!\n")
}

fun main2() -> nthg {
  var animal:Animal = new Animal(2)
  var  dog:Dog = new Dog(2)

  printAge(animal)
  printAge(dog)
}

main2()
```

## Algorithmic Patterns: Recursion and Iteration

FlowWing provides robust support for mathematical and logical algorithms using both recursive and iterative approaches.

### Recursive Implementations

Recursion is commonly used for mathematical functions like factorials, Fibonacci sequences, and Greatest Common Divisor (GCD).

```flowwing
fun factorial(n: int) -> int {
  if (n == 0) {
    return 1
  }
  return n * factorial(n - 1)
}

fun gcd(a: int, b: int) -> int {
  if (b == 0) {
    return a
  }
  return gcd(b, a % b)
}
```

### Iterative Implementations

Iterative patterns utilize `for` loops with range syntax `(var i: int = start to end : step)` to perform repetitive tasks.

```flowwing
fun fibonacci(n: int) -> int {
  if (n <= 1) {
    return n
  }
  var a: int = 0
  var b: int = 1
  var c: int = 0
  for (var i: int = 2 to n : 1) {
    c = a + b
    a = b
    b = c
  }
  return b
}
```

## Comment Syntax

FlowWing supports both single-line and multi-line comments to document code.

### Multi-line Comments

Multi-line comments are enclosed between `/#` and `#/`.

```flowwing
/# Calulate sum  of natural number
fun main() {
    var num = 10
    var sum = 0
    var i = 1
    for (i to num) {
        sum = sum + i
        i = i - 1
    }

    print("Sum = "+ sum + sum)
}

main()
#/
```

### Single-line Comments

Single-line comments are initiated with `/;`.

```flowwing
print(5)
/; print(2) print(3)
```

## Constant Declarations and Type Safety

The `const` keyword is used to declare immutable variables. Constants are type-safe and can be initialized from literals or expressions.

### Constant Types and Scope

Constants can be declared for all primitive types, including `int`, `deci`, `str`, `bool`, and `char`. They respect scoping rules, allowing for global or local access.

```flowwing
const i:int = 42
const d:deci = 3.14
const s:str = "hello"
const b:bool = true
const c:char = 'A'

const MAX:int = 100
{
    var x:int = MAX + 1
    println(x)
}
println(MAX)
```

### Constraints and Errors

Attempting to reassign a value to a constant will result in an `InvalidAssignmentToConstantVariable` error. Additionally, FlowWing enforces strict type checking during initialization.

```flowwing
/; EXPECT_ERROR: InvalidAssignmentToConstantVariable
const x:int = 5
x = 10

/; EXPECT_ERROR: InitializerExpressionTypeMismatch
const x:int = 5.5
```

## Array Containers and Multi-dimensional Structures

Arrays in FlowWing can be fixed-size or dynamic. They support various types and can be nested to create multi-dimensional structures.

### Uninitialized Arrays

When an array is declared without explicit values, it is initialized with default values based on the type (e.g., `0` for `int`, `false` for `bool`, `""` for `str`).

```flowwing
var x:bool[2]
println(x) /; Output: [ false, false ]

var x:str[2]
println(x) /; Output: [ "", "" ]
```

### Multi-dimensional Arrays and Padding

Multi-dimensional arrays are padded with default values if the provided initialization does not fill the entire structure.

```flowwing
var a:int[5][2] = [[1, 2], [3, 4]]
print(a)
/; Output: [ [ 1, 2 ], [ 3, 4 ], [ 0, 0 ], [ 0, 0 ], [ 0, 0 ] ]
```

### Dynamic Typing and Casting

Arrays can hold dynamic values, but assigning them to a typed array requires successful casting. If a dynamic value cannot be cast to the target type, a runtime error occurs.

```flowwing
var x:int = 5
var y = "Hello"

/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var a:int[5] = [x, y]
```

## Lines 14857 - 16976

# FlowWing Documentation: Containers and Dynamic Variables

This documentation covers the behavior of multi-dimensional arrays, dynamic arrays, dynamic variable types, and the error-handling module.

## Multi-dimensional Arrays

Multi-dimensional arrays in FlowWing allow for complex data structures. They support nested indexing and can be modified at various levels, including entire rows.

### Reading and Modifying Multi-dimensional Arrays

You can access elements using chained indices. Modifying a single element or replacing an entire row is supported.

```flowwing
var x:int[2][3] = [[1, 2, 3], [4, 5, 6]]
x[1] = [9, 8, 7]
x[1][1] = 100
# Resulting x: [ [ 1, 2, 3 ], [ 9, 100, 7 ] ]
```

### Nested Access and Triple Dimensions

FlowWing supports deep nesting, allowing for three or more dimensions.

```flowwing
var a:int[2][2][3] = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
println(a[1][1][1]) # Output: 11
```

## Dynamic Arrays

Dynamic arrays (declared without a specific type, e.g., `[N]`) can hold mixed types and exhibit specific behaviors regarding initialization and padding.

### Mixed Type Support and Padding

When a dynamic array is initialized with fewer elements than its declared size, the remaining slots are padded with zero-initialized values.

```flowwing
var k:[3] = [2, "Some", "Test"]
var x:[2][3] = [k, ["test2", 5]]
# x becomes: [ [ 2, "Some", "Test" ], [ "test2", 5, 0 ] ]
```

### Array Indexing Errors

Several errors can occur during array operations:

- `EmptyContainerExpression`: Initializing an array with `[]`.
- `IndexingMoreDimensionsThanArrayTypeHas`: Attempting to index a dimension that does not exist.
- `IndexingNonArrayTypeVariable`: Attempting to index a non-array variable.
- `ContainerExpressionRankMismatch`: Providing an initializer with a different rank than the declared type.

```flowwing
/; EXPECT_ERROR: ContainerExpressionRankMismatch
var a:int[5] = [1, [2,3]]

/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var a:int[2] = [1, 2]
println(a[0][2])
```

## Dynamic Variables

Dynamic variables do not have a fixed type at declaration, allowing them to change types during reassignment.

### Declaration and Reassignment

A variable can be initialized as one type and later reassigned to another.

```flowwing
var x = 10
x = "now a string"
x = false
```

### Scope and Shadowing

Variables declared within a block `{ ... }` are local to that block. If a local variable has the same name as a global variable, it shadows the global one.

```flowwing
var x = 100
{
    var x = 200
    println(x) # Prints 200
}
println(x) # Prints 100
```

## Dynamic Variable Operations

### Binary and Unary Operations

Dynamic variables support standard arithmetic, bitwise, and logical operations.

```flowwing
var x = 5
var y = x + 3
var z = x & 3
var w = !true
```

### Type Conversion Functions

FlowWing provides built-in functions to convert dynamic values into specific primitive types.

```flowwing
var _int = 100000222222
println(Bool(_int))      # true
println(Decimal(_int))    # 100000222222
println(Int32(_int))       # 1000002
println(String(_int))     # "100000222222"
```

**Note:** Attempting to cast a dynamic value to an incompatible type (e.g., a string to an integer) will result in a `Runtime Error`.

```flowwing
/; EXPECT_ERROR: Runtime Error: Cannot cast Dynamic value to Int32.
var _str = "Hello"
println(Int32(_str))
```

## Edge Cases

### Zero-Initialization

When a variable is declared without an explicit value, it is initialized to its type's zero value (e.g., `0` for `int`, `false` for `bool`, and empty strings/chars).

```flowwing
var x:int
println(x) # 0

var b:bool
println(b) # false
```

### Chained Indexing and Members

FlowWing supports accessing members of an object and then immediately indexing into an array within that object.

```flowwing
type T = { vals:int[3] }
var obj:T = { vals:[10,20,30] }
println(obj.vals[0]) # 10
```

## The `Err` Module

The `Err` module provides a robust way to handle errors using a `Result` type, which can be brought into scope using `bring Err`.

### Using Result Types

Functions can return a value alongside an `Err::Result`.

```flowwing
bring Err

fun parseStatus(flag: bool) -> str, Err::Result {
  if flag {
    return "ready", Err::ok("everything is fine")
  }
  return "", Err::error("failed", Err::CODE.INVALID_ARGUMENT, "flag was false")
}

var status: str, err: Err::Result = parseStatus(true)
println(err.isOk()) # true
```

## Lines 16977 - 19098

# FlowWing Technical Documentation

This documentation covers the File System module, `for` loop constructs, and Function definitions based on the provided test suite.

---

## File System Module (`file`)

The `file` module provides both static functions for quick file manipulation and a stateful `File` class for stream-like operations.

### Static File Operations

Static functions allow for immediate reading, writing, and appending of text. These functions return `Err::Result` to handle potential I/O errors.

```flowwing
var writeOk: bool, writeErr: Err::Result = file::writeText(testPath, "Hello, FlowWing File System!\n")
var appOk: bool, appErr: Err::Result = file::appendText(testPath, "This is an appended line.\n")
var content: str, readErr: Err::Result = file::readText(testPath)
```

### File Existence and Deletion

You can check if a file exists or attempt to delete a file using the following functions:

```flowwing
println("Does test file exist? " + String(file::exists(testPath)))
var delFakeOk: bool, delFakeErr: Err::Result = file::delete("missing_file_404.txt")
```

### Stateful Line-by-Line Reading (`file::File`)

For more complex processing, the `file::File` class allows you to open a file in a specific mode and read it line by line.

**Modes:**

- `"r"`: Read mode.
- `"w"`: Write mode.
- `"a"`: Append mode.

```flowwing
var lineFile: file::File = new file::File(testPath)
var openErr: Err::Result = lineFile.open("r")

if openErr.isOk() {
  while true {
    var line: str, eofErr: Err::Result = lineFile.readLine()
    if eofErr.isErr() {
      break
    }
    println(line)
  }
  lineFile.close()
}
```

### File System Edge Cases and Error Handling

The file system handles several edge cases:

- **Empty Files:** Reading a line from an empty file via the `File` class results in an `EOF` error.
- **Invalid Paths:** Writing to an empty path string will fail.
- **Misuse of `File` Class:** Attempting to read before opening, using an invalid mode (e.g., `"z"`), or reading after closing will trigger errors.
- **Append Behavior:** Using `appendText` on a non-existent file will successfully create the file and append the text.

```flowwing
/; Read line on empty file
var emptyFile: file::File = new file::File(emptyTestPath)
emptyFile.open("r")
var emptyLine: str, emptyLineErr: Err::Result = emptyFile.readLine()
if emptyLineErr.isErr() {
  println("Expected Error Caught (Read line on empty file): " + emptyLineErr.getMessage())
}
```

---

## For Loops

The `for` loop in FlowWing allows for iteration over a range of values with a specified step.

### Basic Syntax and Types

The loop syntax follows `for (var i = start to end : step)`. The loop variable can be explicitly typed (e.g., `int`, `int64`, `int8`).

```flowwing
for (var i: int = 0 to 3 : 1) {
  println(i)
}

/; Negative step
for (var i: int = 3 to 0 : -1) {
  println(i)
}

/; Default step (no step provided)
for (var i: int = 0 to 2) {
  println(i)
}
```

### Loop Control: `break` and `continue`

- `break`: Immediately terminates the loop.
- `continue`: Skips the remainder of the current iteration and moves to the next.

```flowwing
for (var i: int = 0 to 5 : 1) {
  if (i == 5) {
    break
  }
  if (i == 2) {
    continue
  }
  println(i)
}
```

### Advanced Loop Usage

Loops can incorporate complex logic within their bodies, including ternary operators, `switch` statements, and nested loops.

```flowwing
for (var i: int = 0 to 3 : 1) {
  switch i {
    case 0:{
      println("zero")
    }
    default:{
      println("other")
    }
  }
}

for (var i: int = 0 to 1 : 1) {
  for (var j: int = 0 to 1 : 1) {
    println(i)
    println(j)
  }
}
```

### Loop Errors

The compiler enforces strict rules to prevent invalid loop states:

- `break` and `continue` cannot be used outside of a loop.
- The `step` must be of a compatible numeric type.
- The upper bound must be a compatible numeric type.
- The loop variable cannot be a `bool` or `str`.

```flowwing
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
fun foo() {
  if (true) {
    break
  }
}
```

### Function Integration

Bounds and steps in a `for` loop can be determined by function calls.

```flowwing
fun getBound() -> int {
  return 5
}

for (var i: int = 0 to getBound() : 1) {
  println(i)
}
```

---

## Functions

Functions in FlowWing support various return types, parameter configurations, and mutation capabilities.

### Return Types

Functions can return various types, including `nthg` (representing "nothing" or `void`), `bool`, `char`, `deci`, `deci32`, `int`, `int8`, and `str`.

```flowwing
fun getBool() -> bool {
  return true
}

fun getDeci32() -> deci32 {
  return 2.5f
}

fun noRet() {
  println(42)
}
```

### Parameters and Default Values

Parameters can be passed by value or by reference using the `inout` keyword. Functions also support default parameter values.

```flowwing
/; Standard parameters
fun describe(a: int, b: deci, c: str, d: bool) -> str {
  return c
}

/; Default parameters
fun greet(name: str = "World") -> str {
  return "Hello " + name
}

/; Inout parameter (pass-by-reference)
fun setFlag(inout flag: bool) -> bool {
  flag = !flag
  return flag
}
```

### Multi-Return Functions

FlowWing allows functions to return multiple values simultaneously. These can be assigned to multiple variables or partially discarded.

```flowwing
fun quad() -> int, int, int, int {
  return 1, 2, 3, 4
}

var a: int, b: int, c: int, d: int = quad()

/; Using inout with multi-return
fun test2(inout a: int, b: str = "Hello") -> int, deci {
  a = 20
  return 1, 3.5
}
```

### Variable Declaration from Functions

Variables can be declared and initialized directly from the result of a function call, including multi-return functions.

```flowwing
fun getPoint() -> int, deci {
  return 10, 3.14
}

var x: int, y: deci = getPoint()
```

### Dynamic Type Inference

FlowWing supports dynamic type inference when assigning function results to variables without explicit type annotations.

```flowwing
fun num() -> int {
  return 42
}

var x = num()
println(x)
```

## Lines 19099 - 21220

# FlowWing Technical Documentation: Functions, Scope, and Complex Types

This documentation covers the behavior of functions, variable assignment patterns, scoping rules, error handling, and the manipulation of arrays and complex objects in FlowWing.

## 1. Function Returns and Dynamic Assignment

FlowWing supports dynamic variable initialization and type inference based on function return values. Variables can be assigned the result of a function call directly, and the compiler can infer the type.

### Type Inference from Returns

Variables can be declared without explicit types when assigned from a function return.

```flowwing
fun getStr() -> str {
  return "dynamic"
}

var s = getStr()
println(s)
```

### Multi-Value Returns

Functions can return multiple values, which can be assigned to multiple variables in a single statement.

```flowwing
fun flags() -> bool, char {
  return true, 'X'
}

var ok: bool = false
var ch: char = ' '
ok, ch = flags()
```

## 2. Advanced Assignment Patterns

FlowWing provides flexible syntax for assigning values to multiple variables, allowing for a mix of function calls and literals.

### Mixed Assignments

You can combine function calls and literal values within a single assignment statement.

```flowwing
fun mid() -> int { return 5 }

var a: int = 0
var b: int = 0
var c: int = 0
a, b, c = 1, mid(), 9
```

### Sequential and Multi-Function Assignment

Multiple variables can be populated by calling multiple functions in a single line.

```flowwing
fun p1() -> int, int { return 1, 2 }
fun p2() -> int, int { return 3, 4 }

var a: int = 0
var b: int = 0
var c: int = 0
var d: int = 0
a, b, c, d = p1(), p2()
```

## 3. Variable Scoping and Shadowing

FlowWing implements block-level scoping. Variables declared within a block `{ ... }` are local to that block.

### Variable Shadowing

Declaring a variable with the same name as a global variable within a block will "shadow" the global variable for the duration of that block.

```flowwing
var a: int = 1
var b: str = "global"
{
  var a: int, b: str = 88, "block"
  println(a)
  println(b)
}
println(a)
println(b)
```

### Global Variable Modification via `inout`

While block-level variables shadow globals, functions can modify global variables if they are passed using the `inout` keyword.

```flowwing
fun addOne(inout n: int) {
  n = n + 1
}

var g: int = 10
addOne(g)
println(g) /; Outputs 11
```

## 4. Error Handling and Constraints

The FlowWing compiler enforces strict rules regarding types, argument counts, and reserved keywords.

### Type and Argument Mismatches

The following errors are triggered when function calls do not match their definitions:

- `FunctionArgumentTypeMismatch`: Passing a type that does not match the parameter.
- `FunctionArgumentCountMismatch`: Providing too many or too few arguments.
- `AssignmentExpressionCountMismatch`: Assigning a multi-return function to a single variable.

```flowwing
fun greet(name: str) -> str {
  return "Hello " + name
}

greet(42) /; Error: FunctionArgumentTypeMismatch
```

### Constraints on `inout` Parameters

A critical caveat in FlowWing is that **literals cannot be passed directly to `inout` parameters**. You must assign the literal to a variable first.

```flowwing
fun test2(inout d: int) {
  println(d)
}

test2(1) /; Error: LiteralCannotBePassedToInoutParameter
```

### Reserved Keywords

The name `main` is reserved and cannot be used for user-defined functions.

```flowwing
fun main() -> nthg {
  var a: str = "Hello, World!"
} /; Error: kFunctionNamedMain
```

## 5. Return Statements

Functions can return various types of expressions, including arithmetic results and concatenated strings.

### Complex Return Expressions

```flowwing
fun compute(a: int, b: int) -> int {
  return a * b + a + b
}

fun join(a: str, b: str) -> str {
  return a + "-" + b
}
```

## 6. Array Operations with Functions

Arrays in FlowWing can be initialized using function calls and passed to functions as parameters.

### Array Initialization and Passing

Array elements can be initialized via function calls, and entire arrays can be passed to functions.

```flowwing
fun getVal() -> int {
  return 42
}

var a: int[3] = [getVal(), 2, 3]

fun sumArray(arr: int[3]) -> int {
  return arr[0] + arr[1] + arr[2]
}

println(sumArray(a))
```

### Returning Arrays

Functions can return arrays as their return type.

```flowwing
fun makeArray() -> int[3] {
  var arr: int[3] = [7, 8, 9]
  return arr
}

var result: int[3] = makeArray()
```

## 7. Complex Objects and Nested Structures

FlowWing supports complex `type` definitions, including nested objects and arrays of objects.

### Nested Object Structures

Objects can contain other objects or arrays of objects, allowing for deep hierarchical data structures.

```flowwing
type Vec2 = {x: deci, y: deci}
type Polygon = { vertices: Vec2[3], color: str }

fun shiftPolygon(inout poly: Polygon, dx: deci, dy: deci) {
  poly.vertices[0].x = poly.vertices[0].x + dx
  poly.vertices[0].y = poly.vertices[0].y + dy
  poly.color = "shifted"
}
```

### Arrays of Objects

You can define and manipulate arrays where each element is a complex object.

```flowwing
type Point = {x: int, y: int}
type Shape = {points: Point[2], name: str}

fun printShape(s: Shape) {
    println("Shape: ", s.name)
}

var p1: Point = {x: 1, y: 2}
var p2: Point = {x: 3, y: 4}
var arr: Point[2] = [p1, p2]
var myShape: Shape = {points: arr, name: "Original"}
```

## Lines 21221 - 23345

# FlowWing Technical Documentation: Functions and Objects

This documentation covers advanced function behaviors in FlowWing, including object manipulation, dynamic typing, error handling for return statements, and complex data structure handling.

## Functions and Object Manipulation

### Returning Objects and Arrays of Objects

FlowWing allows functions to return single objects, arrays of objects, or even multiple arrays of different object types.

**Returning a single object:**

```flowwing
type Person = {
  name: str
  age: int
}

fun makePerson(n: str, a: int) -> Person {
  var p: Person = {name: n, age: a}
  return p
}

var p: Person = makePerson("Alice", 30)
print(p, "\n")
```

**Returning an array of objects:**

```flowwing
type Obj_bool_r = { v: bool }
fun get_r_bool() -> Obj_bool_r[3] { return [{v: true}, {v: false}, {v: true}] }
var a: Obj_bool_r[3] = get_r_bool()
println(a[0].v)
```

**Returning multiple arrays of different types:**

```flowwing
type A = { a: int }
type B = { b: str }

fun getBoth() -> A[2], B[2] {
  var a_arr: A[2] = [{a: 1}, {a: 2}]
  var b_arr: B[2] = [{b: "one"}, {b: "two"}]
  return a_arr, b_arr
}

var arrA: A[2], arrB: B[2] = getBoth()
```

### Passing Objects as Parameters

Objects can be passed to functions either by value (creating a copy) or using the `inout` keyword (allowing modification of the original object).

**Pass by value (Copying):**
When an object is passed without `inout`, the function receives a copy. Changes made within the function do not affect the original.

```flowwing
type Box = {
  value: int
}

fun addOne(b: Box) -> int {
  var v: int = b.value
  return v + 1
}

var b: Box = {value: 10}
println(b.value)
println(addOne(b))
println(b.value) /; Remains 10
```

**Pass by `inout` (Modification):**
Using `inout` allows the function to modify the original object or its members.

```flowwing
type Counter = {
  value: int
}

fun increment(inout c: Counter) -> int {
  c.value = c.value + 1
  return c.value
}

var cnt: Counter = {value: 0}
increment(cnt)
print(cnt, "\n") /; { value: 1 }
```

### Object Initialization and Member Access

Functions can be used directly during object initialization or to access specific members during a function call.

**Initialization from function calls:**

```flowwing
type Point = {
  x: int
  y: int
}

fun getX() -> int {
  return 5
}

fun getY() -> int {
  return 10
}

var p: Point = {x: getX(), y: getY()}
```

**Accessing members in function calls:**

```flowwing
type Point = {
  x: int
  y: int
}

fun doubleN(n: int) -> int {
  return n * 2
}

var pt: Point = {x: 5, y: 10}
println(doubleN(pt.x))
```

## Dynamic Typing

### Dynamic Parameters and Returns

FlowWing supports dynamic typing for both function parameters and return values, allowing for more flexible code patterns.

**Dynamic `inout` parameters:**
Parameters without an explicit type can be reassigned to different types within the function.

```flowwing
fun test_all_types(inout i, inout d, inout s, inout b, inout c) {
    i = 42
    d = 3.14
    s = "changed"
    b = false
    c = 'z'
}

var v_i = 10
var v_d = 1.23
var v_s = "original"
var v_b = true
var v_c = 'a'

test_all_types(v_i, v_d, v_s, v_b, v_c)
```

**Dynamic return types:**
Functions can return values where the type is determined at runtime.

```flowwing
fun getFlag() {
  return true
}

var b: bool = getFlag()
println(b)
```

## Error Handling (Return Statements)

FlowWing enforces strict rules regarding `return` statements to prevent common logic errors.

**Invalid number of return expressions:**
If a function signature specifies a certain number of return values, providing more or fewer will result in an error.

```flowwing
/; EXPECT_ERROR: InvalidNumberOfReturnExpressions
fun getTwo() -> int {
  return 1, 2
}
```

**Return type mismatch:**
The expression being returned must match the type declared in the function signature.

```flowwing
/; EXPECT_ERROR: ReturnExpressionTypeMismatch
fun getInt() -> int {
  return "hello"
}
```

**Return outside of function:**
The `return` keyword can only be used within the scope of a function.

```flowwing
/; EXPECT_ERROR: ReturnStatementNotInFunction
return 42
```

## Advanced Scoping and Data Structures

### Block-level Variable Shadowing

FlowWing allows variables to be redefined within a local block `{ ... }`, shadowing the variable in the outer scope.

```flowwing
fun printVal(val: int) {
    println(val)
}

var a: int = 10
{
    var a: int = 20
    printVal(a) /; Prints 20
}
printVal(a) /; Prints 10
```

### 2D Array Initialization and Access

FlowWing supports multi-dimensional arrays, which can be returned from functions and accessed via standard indexing.

```flowwing
fun get2D() -> int[2][2] {
    var flat: int[2][2]
    return flat
}
var temp: int[2][2] = get2D()
temp[0][0] = 4
println(temp[0][0])
```

### Inline Array and Object Access

You can perform member access directly on the result of a function call without assigning it to a temporary variable first.

```flowwing
type Obj_0_2 = { val: bool }
fun getObjs() -> Obj_0_2[5] {
    var res: Obj_0_2[5] = [{val: true}, {val: false}, {val: false}, {val: false}, {val: false}]
    return res
}

println(getObjs()[4].val)
```

## Lines 23346 - 25468

# FlowWing Technical Documentation

This documentation covers advanced features including complex object access, `inout` array modifications, variable shadowing within blocks, multidimensional arrays in structs, multiple return values, and higher-order functions.

## Object and Array Access

FlowWing allows for accessing properties of objects stored within arrays. This is commonly used when a function returns an array of custom types.

```flowwing
type Obj_0_4 = { val: char }
fun getObjs() -> Obj_0_4[5] {
    var res: Obj_0_4[5] = [{val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}, {val: 'a'}]
    return res
}

println(getObjs()[4].val)
```

## Inout Array Modification

The `inout` keyword allows functions to modify arrays passed as arguments. This enables direct mutation of the original array.

```flowwing
fun mutateArray(inout arr: int[2], idx: int, v: int) {
    arr[idx] = v
}

var data: int[2] = [0, 1]
mutateArray(data, 1, 10)
println(data[1])
```

## Variable Shadowing and Block Scoping

FlowWing supports block-level scoping. Variables declared within a block `{ ... }` shadow variables with the same name declared in the outer scope. These shadowed variables only exist within the duration of the block.

```flowwing
var x: int = 999
var y: str = "outer"
{
    var x: int, y: str = getMulti_0()
    println(x)
    println(y)
}
println(x)
println(y)
```

## Structs with Multidimensional Arrays

Structs (defined via `type`) can contain multidimensional arrays. These can be initialized and manipulated using standard indexing.

```flowwing
type Matrix_0 = { rows: int[1][2], valid: bool }
fun getMatrix(v: int) -> Matrix_0 {
    var m: Matrix_0
    m.valid = true
    m.rows[0][0] = v
    return m
}

var mat: Matrix_0 = getMatrix(0)
println(mat.valid)
println(mat.rows[0][0])
```

## Multiple Return Values

Functions in FlowWing can return multiple values by specifying multiple types in the return signature. These can be assigned to multiple variables simultaneously.

```flowwing
fun pair() -> int, int {
  return 3, 7
}

var a: int, b: int = pair()
println(a * b)
println(a + b)
```

## Default Parameters

Parameters can be assigned default values. If a caller does not provide an argument for a parameter with a default value, the default is used.

```flowwing
fun f(a: int = 1, b: int = 2, c: int = 3) -> int {
  return a + b + c
}

println(f())
println(f(10))
println(f(10, 20, 30))
```

## Function Types and Higher-Order Functions

FlowWing treats functions as first-class citizens. You can define function types using the `[(params) -> return_type]` syntax and pass functions as arguments to other functions.

```flowwing
fun printX(x: int) -> nthg {
    print("Printing X",x)
}

fun main2(f:[(int)-> nthg]) -> nthg {
    f(2)
}

main2(printX)
```

Note: `nthg` is used to represent a `void` return type (no return value).

## Control Flow

The `if` statement supports `else if` and `else` branches for conditional logic.

```flowwing
var a: int = 3

if (a == 2) {
  println("a is 2")
} else if (a == 3) {
  println("a is 3")
} else {
  println("a is other")
}
```

## Lines 25469 - 27591

# FlowWing Documentation: If Statements, Conditionals, and Indexing

This documentation covers the implementation and usage of conditional logic, truthiness across various types, scoping rules, and array/string indexing in FlowWing.

---

## If Statements

FlowWing provides several ways to implement conditional branching, ranging from simple `if` blocks to complex `or if` chains.

### Basic If, Else If, and Else

A standard conditional block can consist of an `if` statement, followed by zero or more `else if` branches, and an optional `else` branch.

```flowwing
var a: int = 5

if (a == 2) {
  println("a is 2")
} else if (a == 3) {
  println("a is 3")
} else {
  println("a is other")
}
```

### The `or if` Syntax

FlowWing supports a unique `or if` syntax, which allows for chaining conditional branches. This is particularly useful for complex logic flows.

```flowwing
if (false) {
  println(4)
} or if (true) {
  println(5)
} else {
  println(6)
}
```

### Nested If Statements

Conditional blocks can be nested within one another to create complex decision trees.

```flowwing
var a: int = 2
var b: int = 3

if (a == 2) {
  if (b == 3) {
    println("both")
  } else {
    println("a only")
  }
} else {
  println("neither")
}
```

---

## Conditionals and Truthiness

In FlowWing, conditions are evaluated based on the "truthiness" of the expression. Various types have specific rules for what constitutes a `true` or `false` value.

### Truthiness by Type

The following table and examples describe how different types are evaluated in a conditional context:

- **`int` / `int8` / `int64`**: `0` is false; any non-zero value is true.
- **`bool`**: `false` is false; `true` is true.
- **`char`**: `'\0'` is false; any other character is true.
- **`deci` / `deci32`**: `0.0` is false; any non-zero value is true.
- **`str`**: `""` (empty string) is false; any non-empty string is true.
- **`object` / `array`**: `null` is false; an initialized object or array is true.

#### Examples of Truthiness

```flowwing
/; Char truthiness
var c: char = '\0'
if (c) {
  println("nonzero")
} else {
  println("zero")
}

/; String truthiness
var s: str = ""
if (s) {
  println("nonempty")
} else {
  println("empty")
}

/; Deci truthiness
var d: deci32 = 0.0f
if (d) {
  println("nonzero")
} else {
  println("zero")
}
```

### Logical and Unary Operators

Conditions can be manipulated using logical and unary operators.

- **Logical Operators**: `&&` (AND), `||` (OR), and `!` (NOT).
- **Unary Operators**: `-` (negate), `+` (unary plus), `~` (bitwise NOT).

```flowwing
var a: bool = true
var b: bool = false
var c: bool = true
var d: bool = false

/; Chained logical operators
if (a && b || c && !d) {
  println("true")
} else {
  println("false")
}
```

### Expressions in Conditions

Conditions can involve arithmetic, bitwise, and comparison operations.

```flowwing
var a: int = 5
var b: int = 3

/; Bitwise AND in condition
if (a & b) {
  println("nonzero")
} else {
  println("zero")
}

/; Comparison in condition
if (a > b) {
  println("greater")
} else {
  println("not greater")
}
```

---

## Scope and Shadowing

FlowWing follows strict scoping rules regarding variable declarations and assignments within conditional branches.

### Branch-Local Scope

Variables declared within an `if` or `else` block are local to that block and are not accessible outside of it.

```flowwing
if (true) {
  var y: int = 42
  println(y)
}
/; println(y) would result in a VariableNotFound error
println("done")
```

### Variable Shadowing

If a variable is declared within a branch with the same name as a variable in the outer scope, the inner variable "shadows" the outer one within that block.

```flowwing
var x: int = 1

if (true) {
  var x: int = 2
  println(x) /; Prints 2
} else {
  println(x) /; Prints 1
}
println(x) /; Prints 1
```

---

## Indexing

FlowWing supports indexing for arrays and strings, including multi-dimensional arrays and dynamic types.

### Array Indexing

Arrays can be indexed using integer values. FlowWing supports multi-dimensional arrays.

```flowwing
/; 2D Array indexing
var a:int[2][3] = [[1,2,3],[4,5,6]]
println(a[0][1]) /; Prints 2

/; 3D Array indexing
var b:int[2][2][2] = [[[1,2],[3,4]],[[5,6],[7,8]]]
println(b[1][0][1]) /; Prints 6
```

### String Indexing

Strings can be indexed similarly to arrays, allowing access to individual characters.

```flowwing
var s: str = "hello"
println(s[0]) /; Prints 'h'
println(s[4]) /; Prints 'o'

/; Modifying a string via index
var x = "hello"
x[1] = 'a'
println(x) /; Prints "hallo"
```

### Dynamic Indexing and Errors

When using dynamic types, indexing is permitted if the underlying value is a string. Attempting to index non-string dynamic values or using invalid indices will result in runtime errors.

```flowwing
/; Dynamic type truthiness and indexing
var d = "flow"
println(d[0]) /; Prints 'f'

/; Error: Index Out of Bounds
var a:int[3] = [1,2,3]
/; println(a[5]) -> Runtime Error: Array Index Out of Bounds.

/; Error: Invalid Index Type
var arr:int[2] = [1, 2]
var s:str = "idx"
/; println(arr[s]) -> ExpectedAnIntegerForIndexing
```

### Error Cases Summary

| Error Type                        | Description                                                   |
| :-------------------------------- | :------------------------------------------------------------ |
| `VariableNotFound`                | Attempting to access a variable that has not been declared.   |
| `InvalidBinaryOperationWithTypes` | Performing an operation (like `+`) on incompatible types.     |
| `FunctionArgumentCountMismatch`   | Passing the wrong number of arguments to a function.          |
| `Index Out of Bounds`             | Accessing an index that does not exist in an array or string. |
| `ExpectedAnIntegerForIndexing`    | Using a non-integer type to index an array.                   |

## Lines 27592 - 29711

# FlowWing Technical Documentation

This documentation covers advanced indexing, the JSON and Map modules, complex object/array manipulations, and the module system.

## String and Array Indexing

FlowWing supports indexing for both strings and arrays. Strings are mutable, allowing for direct character replacement via index.

### String Mutability and Indexing

You can access and modify individual characters in a string using the `[]` operator.

```flowwing
var s: str = "hello"

for (var i: int = 0 to 4) {
  println(s[i])
}

s[1] = 'a'
s[3] = 'p'
println(s)
```

### Indexing Errors and Edge Cases

Several error conditions exist regarding indexing:

- **Multi-dimensional Indexing Error**: Attempting to index a string with more dimensions than it possesses.
- **Non-integer Indexing**: Using non-integer types (like floats) for indexing.
- **Out of Bounds (OOB)**: Accessing an index that is outside the valid range of the string or array.
- **Negative Indexing**: Using negative integers for string indexing is not supported.

```flowwing
/; EXPECT_ERROR: IndexingMoreDimensionsThanArrayTypeHas
var s: str = "hello"
println(s[0][1])

/; EXPECT_ERROR: ExpectedAnIntegerForIndexing
var s: str = "hello"
println(s[3.14])

/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var s: str = "hi"
println(s[5])

/; EXPECT_ERROR: Runtime Error: String Index Out of Bounds.
var x: str = "hello"
x[-1] = 'z'
```

### Variable-based Indexing

Indices can be determined by variables, which is useful for dynamic array access.

```flowwing
var a:int[4] = [5, 10, 15, 20]
var i:int = 2
println(a[i])
a[i] = 99
println(a[i])
```

---

## JSON Module

The `json` module provides tools for programmatic JSON construction, parsing, and serialization.

### Programmatic Construction and Serialization

You can build JSON objects and arrays using `json::newObject()`, `json::newArray()`, and the `.put()` or `.push()` methods.

```flowwing
bring json

var myJson: json::JsonNode = json::newObject()
myJson.put("name", json::newString("FlowWing"))
      .put("version", json::newNumber(1.5))
      .put("isCompiled", json::newBool(true))
      .put("nullValue", json::newNull())

var featuresArr: json::JsonNode = json::newArray()
featuresArr.push(json::newString("Fast"))
           .push(json::newString("Dynamic"))
           .push(json::newString("Safe"))

myJson.put("features", featuresArr)

var serializedStr = json::stringify(myJson)
println(serializedStr)
```

### Parsing and Data Extraction

JSON strings can be parsed into `json::JsonNode` structures. Data can be extracted using `.get()`, `.getAt()`, and properties like `.strVal` or `.numVal`.

```flowwing
var rawJson: str = "{ \"user\": \"Kushagra\", \"id\": 42, \"active\": true, \"scores\": [95.5, 82.0, 100.0] }"
var parsedAst: json::JsonNode = json::parse(rawJson)

var userNode: json::JsonNode = parsedAst.get("user")
var idNode: json::JsonNode = parsedAst.get("id")

println("Parsed User: " + userNode.strVal)
println("Parsed ID: " + String(idNode.numVal))

var scoresArr: json::JsonNode = parsedAst.get("scores")
var firstScore: json::JsonNode = scoresArr.getAt(0)
println("Parsed First Score: " + String(firstScore.numVal))
```

---

## Map Module

The `map` module provides a key-value store implementation.

### Basic Map Operations

Maps support setting, getting, removing, and checking for existence of keys.

```flowwing
bring map

var customMap: map::Map = new map::Map()

customMap.set("title", "FlowWing")
customMap.set("version", 1.0)
customMap.set("isFast", true)

println(customMap.get("title"))
println(customMap.getOr("missingString", "default"))
println(customMap.has("title"))
println(customMap.size())

var wasRemoved = customMap.remove("isFast")
customMap.clear()
println(customMap.isEmpty())
```

### Method Chaining

The `map` module supports method chaining for operations like `set`, `insert`, and `clear`.

```flowwing
bring map

var customMap: map::Map = new map::Map()

customMap.set("first", 1).set("second", 2).insert("third", 3)

customMap.clear().set("reborn", true).insert("phoenix", "fire")

customMap.clear()
   .set("a", "Alpha")
   .set("b", "Beta")
   .set("c", "Gamma")
```

---

## Complex Object and Array Structures

FlowWing allows for deeply nested structures involving arrays of objects, multi-dimensional arrays, and objects containing arrays.

### Arrays of Objects

You can define arrays of custom types and manipulate their elements.

```flowwing
type Point = { x:int, y:int }
var pts:Point[2] = [{x:0,y:0}, {x:0,y:0}]
pts[0].x = 10
pts[0].y = 20
println(pts)
```

### Partial and Full Assignment

When assigning to an object, you can provide a full literal or a partial one. If a partial literal is used, the remaining fields are initialized to their default values.

```flowwing
type T = {
  a:int
  b:deci32
}

var st:T = {
  a: 5,
  b: 12.5f
}

var t:T[2] = [st]
t[1] = {b:5.5f}
println(t)
```

### Nested Member Access and Padding

For objects containing fixed-size arrays, FlowWing handles padding. If an array is partially initialized, the remaining slots are padded with default values (e.g., `0`).

```flowwing
type T = {
  a:int
  b:deci32,
  c:[3]
}

var st:T = {
  a: 5,
  b: 12.5f,
  c:[1,2]
}

println(st)
/; Output: { a: 5, b: 12.5, c: [ 1, 2, 0 ] }
```

---

## Module System and Scoping

Modules allow for code organization and encapsulation.

### Accessing Module Members

Variables and functions defined in a module are accessed using the `module_name::member` syntax.

```flowwing
module [m]
var x: int = 42
println(m::x)

module [lib]
fun getN() -> int {
  return 7
}
println(lib::getN())
```

### External C Declarations

FlowWing allows declaring functions that link to high-performance C engines using the `decl` keyword. This is often used to create wrapper classes that provide a chainable API.

```flowwing
module [fg]

fun strLength(str1: as str) -> as int decl/;in use

class Str {
  var _buffer: str
  var _len: int

  init(source: str) -> nthg {
    self._buffer = source
    self._len = strLength(source)
  }

  fun upper() -> FlowingStr::Flow {
    self._buffer = strToUpper(self._buffer)
    return self
  }

  fun get() -> str {
    return self._buffer
  }
}
```

---

## Object Assignment and Initialization

### Compatible Type Assignment

FlowWing supports assigning a type to a variable of a compatible type (e.g., a type with fewer fields being assigned to a type with more fields).

```flowwing
type type_test = {
    _string_name: str
    _int_age: int
    _int64: int64
}

type sub_type_test = {
    _int_age: int
    _int64: int64
    _string_name: str
}

var y: sub_type_test = {
    _string_name: "John",
    _int_age: 20
}

var x: type_test
x = y
```

### Empty Object Initialization

Declaring an object without providing values will initialize all its fields to their default values.

```flowwing
type Person = {
    name: str
    age: int
}

var p: Person = {}
println(p)
/; Output: { age: 0, name: "" }
```

## Lines 29712 - 31833

# FlowWing Object Documentation

This documentation covers the behavior, declaration, and advanced usage of objects in FlowWing, including constants, nested structures, circular references, and linked list implementations.

## Object Declaration and Initialization

FlowWing allows for flexible object declaration. You can declare multiple variables of the same type on a single line or provide initializers during declaration.

### Multiple Declarations

Variables of the same type can be declared together in a single statement.

```flowwing
type Person = {
    name: str
    age: int
}

var p1: Person, p2: Person, p3: Person
```

### Initialization with Initializers

You can initialize multiple variables with specific object values in a single line.

```flowwing
var p1: Person, p2: Person = {
    name: "Alice",
    age: 20
}, {
    name: "Bob",
    age: 25
}
```

### Partial and Uninitialized Objects

If an object is partially initialized, missing fields are assigned their default values (e.g., `0` for `int`, `""` for `str`). If an object is declared without any initialization, all its fields default to zero/empty values.

```flowwing
type Person = {
    name: str
    age: int
    height: deci
}

# Partial initialization: height will be 0
var p: Person = {
    name: "John",
    age: 25
}

# Uninitialized: all fields default to 0 or ""
var p: Person
```

### Expressions in Initializers

Initializers can contain complex expressions.

```flowwing
var x: int = 20
var y: int = 10

var p: Person = {
    name: "John",
    age: x + y
}
```

## Field Access and Modification

Fields within an object can be accessed using dot notation and modified directly.

### Deeply Nested Access

FlowWing supports deep nesting, allowing you to access and modify members deep within a hierarchy.

```flowwing
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var shape: Shape = {
    name: "MyShape",
    rect: {
        topLeft: { x: 0, y: 0 },
        bottomRight: { x: 100, y: 100 }
    }
}

# Deep access and modification
shape.rect.topLeft.x = 10
```

### Field Order in Printing

When printing an object, the fields are displayed in a specific order (typically alphabetical), regardless of the order in which they were defined in the source.

```flowwing
type Person = {
    name: str
    age: int
    height: deci
}

var p: Person = {
    height: 5.10,
    name: "John",
    age: 30
}

# Output: { age: 30, height: 5.1, name: "John" }
print(p, "\n")
```

## Constant Objects (`const`)

The `const` keyword defines read-only objects.

### Read-Only Behavior

Fields of a `const` object cannot be modified.

```flowwing
const p: Person = {
    name: "John",
    age: 30
}

print("Name: ", p.name, "\n")
```

### Equality and Mixing with Mutable Objects

`const` objects can be compared for equality with both other `const` objects and mutable `var` objects.

```flowwing
const p1: Person = {
    name: "Alice",
    age: 30
}

var p2: Person = {
    name: "Alice",
    age: 30
}

# Returns true if values are identical
print("p1 == p2: ", p1 == p2, "\n")
```

### Nested Constants

A `const` object provides read-only access to its nested members.

```flowwing
const outer: Outer = {
    inner: {
        value: 10
    }
}

# outer.inner.value is read-only
print("Const outer.inner.value: ", outer.inner.value, "\n")
```

## Operators and Expressions

Objects can be used extensively within mathematical and logical expressions.

### Arithmetic and Assignment Operators

You can perform arithmetic operations directly on object members.

```flowwing
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

p.age = p.age + 5
p.age = p.age /; 4
```

### Comparison and Logical Operators

Members can be compared using standard comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) and used in logical expressions.

```flowwing
type Person = {
    name: str
    age: int
    active: bool
}

const p1: Person = { name: "Alice", age: 30, active: true }
const p2: Person = { name: "Bob", age: 25, active: false }

print("p1.age > 20 && p2.age > 20: ", p1.age > 20 && p2.age > 20, "\n")
```

### The Bang (`!`) Operator

The `!` operator can be applied to objects and their members. For objects, it evaluates the truthiness of the object itself.

```flowwing
type T = { x: int }
var t1: T = { x: 10 }

print("!t1: ", !t1, "\n")
```

## Circularity and Self-Referencing

FlowWing handles circular references in objects by detecting cycles during printing.

### Circular References

When an object contains a reference to itself (directly or indirectly), the printer identifies the loop and outputs `<Cycle>`.

```flowwing
type Node = {
    value: int
    next: Node
}

var node1: Node = { value: 1 }
var node2: Node = { value: 2, next: node1 }

# Creates a cycle
node1.next = node2

# Output will contain <Cycle>
print("node2.next: ", node2.next, "\n")
```

### Circular Type Definitions

Types can be defined such that they reference each other.

```flowwing
type A = { b: B }
type B = { a: A }
```

## Advanced Data Structures: Linked Lists

The object system allows for the implementation of complex structures like linked lists using self-referencing types.

### Linked List Implementation

By using a `next` field of the same type as the object, you can create a chain of nodes.

```flowwing
type Node = {
    value: int
    next: Node
}

var node1: Node = {
    value: 1,
    next: {
        value: 2,
        next: {
            value: 3,
            next: null
        }
    }
}
```

### Deep Equality in Linked Lists

Equality checks for objects are deep; if two objects are compared, their nested members are also compared.

```flowwing
var node9: Node = {
    value: 2,
    next: { value: 3, next: null }
}

var node10: Node = {
    value: 2,
    next: { value: 3, next: null }
}

# Returns true because the entire structure is identical
print("node9 == node10: ", node9 == node10, "\n")
```

## Lines 31834 - 33955

# FlowWing Object Documentation

This documentation covers the behavior, edge cases, and error conditions associated with objects in FlowWing, including nesting, reference semantics, scoping, and type promotion.

## Reference Semantics

In FlowWing, objects are handled via reference semantics. When an object is assigned to a new variable, both variables point to the same underlying data. Modifying a member through one variable will reflect in the other.

```flowwing
type T = {
    x: int
    y: deci
}

var t1: T = { x: 10, y: 10.10 }
var t2: T = t1

t2.x = 100
t2.y = 100.100

# Both t1 and t2 now reflect the changes
# t1: { x: 100, y: 100.099999999999994 }
```

This behavior extends to nested members. Assigning a nested member from one object to another also creates a shared reference.

```flowwing
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

var rect1: Rectangle = {
    topLeft: { x: 0, y: 0 },
    bottomRight: { x: 10, y: 10 }
}

var rect2: Rectangle = {
    topLeft: { x: 20, y: 20 },
    bottomRight: { x: 30, y: 30 }
}

# Assigning a nested member
rect1.topLeft = rect2.topLeft

# Modifying rect1.topLeft affects rect2.topLeft
rect1.topLeft.x = 100
```

## Nested Object Structures

FlowWing supports deeply nested objects. An object can contain other objects as members, allowing for complex data modeling.

```flowwing
type Point = {
    x: int
    y: int
}

type Rectangle = {
    topLeft: Point
    bottomRight: Point
}

type Shape = {
    name: str
    rect: Rectangle
}

var shape: Shape = {
    name: "MyShape",
    rect: {
        topLeft: {
            x: 0,
            y: 0
        },
        bottomRight: {
            x: 100,
            y: 100
        }
    }
}
```

## Equality and Comparison

Equality (`==`) and inequality (`!=`) operators can be used to compare objects. For objects, equality is determined by comparing the values of their constituent members.

```flowwing
type Address = {
    street: str
    city: str
}

type Person = {
    name: str
    address: Address
}

const p1: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

const p2: Person = {
    name: "John",
    address: {
        street: "123 Main St",
        city: "New York"
    }
}

print("p1 == p2: ", p1 == p2, "\n") # true
```

## Scoping and Shadowing

FlowWing follows standard block scoping rules. Variables declared within a block `{ ... }` are local to that block. If a local variable has the same name as a variable in an outer scope, it **shadows** the outer variable.

```flowwing
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "Global",
    age: 100
}

{
    # This 'p' shadows the outer 'p'
    var p: Person = {
        name: "Local",
        age: 50
    }

    p.age = 25
    # Only the local 'p' is modified
}

# The outer 'p' remains unchanged
```

However, if an inner scope holds a reference to an outer object, it can modify the outer object's members.

```flowwing
type Point = {
    x: int
    y: int
}

var p1: Point = { x: 10, y: 20 }

{
    # Modifying the outer variable from within the scope
    p1.x = 100
    p1.y = 200
}
```

## Initialization and Default Values

When an object is declared but not fully initialized, or when it is partially initialized, FlowWing applies default "zero" values to its members.

- **Primitives**: `int` becomes `0`, `deci` becomes `0.0`, `bool` becomes `false`, `str` becomes `""`.
- **Objects**: Uninitialized object members default to `null`.

```flowwing
type T = {
    x: int
    y: deci
}

type Nested = {
    z: int
    t1: T
    n2: Nested
}

var n1: Nested

# n1: { n2: null, t1: null, z: 0 }
```

## Type Promotion and Partial Assignment

FlowWing allows "type promotion" where an object of a smaller type (fewer fields) is assigned to a variable of a larger type. The additional fields in the target type are automatically initialized with their default values.

```flowwing
type Small = {
    a: int
}

type Medium = {
    a: int
    b: str
}

var small: Small = { a: 10 }
var medium: Medium

# Promotion: medium gets 'a' from small, and 'b' is initialized to ""
medium = small
# medium: { a: 10, b: "" }
```

## Error Scenarios

The following table summarizes common errors encountered when working with objects:

### Assignment Errors

| Error                                 | Description                                                            | Example                       |
| :------------------------------------ | :--------------------------------------------------------------------- | :---------------------------- |
| `AssignmentExpressionCountMismatch`   | Assigning the wrong number of values in a multi-assignment.            | `p1, p2 = p3`                 |
| `AssignmentExpressionTypeMismatch`    | Assigning an object of one type to a variable of an incompatible type. | `shape3d.point = shape.point` |
| `InvalidAssignmentToConstantVariable` | Attempting to reassign or modify a member of a `const` object.         | `const p = {x: 1}; p.x = 2`   |

```flowwing
/; EXPECT_ERROR: AssignmentExpressionTypeMismatch
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x: int = 10
p.name = x # Error: name is str, x is int
```

### Member Access Errors

| Error                             | Description                                         | Example                    |
| :-------------------------------- | :-------------------------------------------------- | :------------------------- |
| `MemberNotFoundInObject`          | Accessing a field that is not defined in the type.  | `p.nonexistent`            |
| `MemberAccessOnNonObjectVariable` | Attempting to use dot notation on a primitive type. | `var x: int = 10; x.field` |

```flowwing
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var x = p.nonexistent # Error: MemberNotFoundInObject
```

### Initialization Errors

| Error                               | Description                                                                  | Example                               |
| :---------------------------------- | :--------------------------------------------------------------------------- | :------------------------------------ |
| `InitializerExpressionTypeMismatch` | Providing a value in an object literal that does not match the field's type. | `p = { name: 123 }`                   |
| `TooManyInitializerExpressions`     | Providing more fields in a literal than defined in the type.                 | `p = { name: "J", age: 1, extra: 2 }` |

```flowwing
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: "thirty" # Error: age must be int
}
```

## Lines 33956 - 36076

# FlowWing Technical Documentation

## Error Handling and Type Safety

FlowWing provides specific error messages when type definitions or variable declarations violate language rules.

### Custom Type Not Found

If you attempt to declare a variable using a type that has not been defined, the compiler will throw a `CustomTypeNotFound` error.

```flowwing
/; EXPECT_ERROR: CustomTypeNotFound
var p: UnknownType = {
    name: "John",
    age: 30
}
```

### Variable Redeclaration

Attempting to declare a variable with a name that is already in use within the same scope will trigger a `VariableAlreadyDeclared` error.

```flowwing
/; EXPECT_ERROR: VariableAlreadyDeclared
type Person = {
    name: str
    age: int
}

var p: Person = {
    name: "John",
    age: 30
}

var p: Person = {
    name: "Jane",
    age: 25
}
```

---

## Object Scoping and Dynamic Interaction

Objects in FlowWing follow standard scoping rules, but they also support dynamic interaction when types are not strictly enforced during assignment.

### Dynamic Object Interaction

When a variable is assigned a value from an object property, it can become a dynamic type, allowing it to be reassigned to different types later.

```flowwing
type T = { val:int }
var obj:T = { val: 42 }
var dyn2 = obj.val
println(dyn2)
dyn2 = "changed"
println(dyn2)
println(obj.val)
```

### Object Scoping and Shadowing

Objects can be declared in global or local scopes. A local declaration of an object with the same name as a global one will "shadow" the global object within that specific block.

```flowwing
type T = { n:int }
var obj:T = { n: 1 }
println(obj)
{
    var obj:T = { n: 999 }
    println(obj)
}
println(obj)
```

---

## Primitive Types

FlowWing supports a variety of primitive types, including integers of different sizes, floating-point decimals, booleans, characters, and strings.

### Integer Types

FlowWing provides several integer widths, including `int8`, `int32`, and `int64`.

```flowwing
var x:int8 = 127
var y:int32 = 2147483647
var z:int64 = 9223372036854775807
```

### Decimal Types

There are two decimal types: `deci32` (single precision, uses `f` suffix) and `deci` (higher precision).

```flowwing
var x:deci32 = 3.14f
var y:deci = 3.14159265358979
```

### Booleans, Characters, and Strings

Standard types for logic, single characters, and text.

```flowwing
var b:bool = true
var c:char = 'A'
var s:str = "Hello, FlowWing!"
```

---

## Variable and Array Scoping

Variables and arrays are subject to block-level scoping.

### Array Shadowing

An array declared within a local block will shadow an array of the same name declared in an outer scope.

```flowwing
var a:int[2] = [1, 2]
{
    var a:int[2] = [100, 200]
    println(a)
}
println(a)
```

### Modifying Global Arrays in Nested Scopes

Nested scopes can modify arrays declared in a higher scope.

```flowwing
var d:[3] = [1, "hello", true]
{
    d[2] = false
    {
        d[0] = 99
    }
}
println(d)
```

---

## The `text` Module

The `text` module provides a `text::Text` class for advanced string manipulation.

### Text Manipulation Methods

The `text::Text` class supports various operations including trimming, case conversion, reversing, and concatenation.

```flowwing
bring text

var s: text::Text = new text::Text("  Flow Wing  ")
println(s.trim().get())
println(s.toUpper().get())
println(s.reverse().get())
```

---

## Switch Statements

The `switch` statement allows for branching logic based on the value of an expression.

### Basic Usage and Types

Switch statements can be used with `bool`, `int`, `char`, `deci`, and `str`.

```flowwing
var a: int = 2

switch a {
  case 1:{
    println("one")
  }
  case 2:{
    println("two")
  }
  default:{
    println("default")
  }
}
```

### Complex Case Expressions

Cases can evaluate binary expressions, function calls, or variables.

```flowwing
fun getVal() -> int {
  return 3
}

var a: int = 3

switch a {
  case getVal():{
    println("match")
  }
  default:{
    println("default")
  }
}
```

### Switch Scope and Shadowing

Variables declared within a `case` block are local to that block. Shadowing can also occur within a case.

```flowwing
var x: int = 1
var a: int = 1

switch a {
  case 1:{
    var x: int = 2
    println(x)
  }
  case 2:{
    println(x)
  }
  default:{
    println(x)
  }
}
```

### Error Cases in Switch

The compiler prevents type mismatches in case expressions and forbids multiple `default` statements.

```flowwing
/; EXPECT_ERROR: CaseExpressionTypeMismatch
var a: int = 1

switch a {
  case "hello":{
    println("str case")
  }
  default:{
    println("default")
  }
}
```

---

## Ternary Operator

The ternary operator `condition ? true_expression : false_expression` provides a concise way to perform conditional assignments.

### Truthy and Falsy Evaluation

In FlowWing, non-zero numbers, non-empty strings, and non-null characters are considered "truthy."

```flowwing
println(1 ? "Hello" : "Bye")
println(0 ? "Hello" : "Bye")
println("" ? "nonempty" : "empty")
println('a' ? "nonzero" : "zero")
```

### Using Ternary for Assignments and Functions

Ternary operators can be used to assign values to variables or to trigger function calls.

```flowwing
var x: int = true ? 1 : 0

fun printA() { println("A") }
fun printB() { println("B") }
var a = 'A'
a == 'B' ? printA() : printB()
```

---

## Server-Side Rendering (SSR) and Vortex

The `vortex` module is used for building web servers and handling HTTP requests.

### Mission Control SSR Engine

A complex example of using `vortex` to create a file-driven SSR engine with template rendering.

```flowwing
bring vortex
bring json
bring text

fun fg_main() -> nthg {
  var app: vortex::Server = new vortex::Server()
  var err: Err::Result = app.listen(9433)

  /; ... logic for handling routes like "/" or "/crew" ...

  res.header("Content-Type", "text/html").status(200).send(layout.render())
}
```

### Vortex Routing

The `vortex::Server` handles incoming requests and allows for routing based on the HTTP method and path.

```flowwing
bring vortex

fun fg_main() -> nthg {
  var app: vortex::Server = new vortex::Server()
  app.listen(9432)

  for var i: int = 0 to 2 {
    var req: vortex::Request, res: vortex::Response = app.accept()

    if req.getMethod() == "GET" && req.getPath() == "/" {
      res.status(200).send("Welcome!")
    } else {
      res.status(404).send("404 - Route Not Found")
    }
  }
}
```

## Lines 36077 - 38197

# FlowWing Technical Documentation

This documentation covers the ternary operator, type conversion functions, scientific notation, and unary operators based on the provided test suites.

---

## Ternary Operator

The ternary operator `(condition) ? expression_if_true : expression_if_false` allows for conditional branching within an expression.

### Function Returns

Ternary expressions can invoke functions that return values, including complex types like objects.

```flowwing
type B = {
  s: int
}

fun printA() -> B {
  println("A")
  return {s: 0}
}

fun printB() -> B {
  println("B")
  return {s: 2}
}

var g: int = 2
var x: B = (g == 2) ? printA() : printB()

println(x)
```

### Type Safety and Errors

The ternary operator enforces strict type consistency. The types of both the "true" and "false" branches must be compatible.

**Common Errors:**

- `IncompatibleTypesForTernaryExpression`: Occurs when the two branches return different types.
- `FunctionArgumentTypeMismatch`: Occurs when a ternary expression returning `void` is passed to a function expecting a specific type.
- `InitializerExpressionTypeMismatch` / `AssignmentExpressionTypeMismatch`: Occurs when a `void` ternary result is assigned to a variable.

```flowwing
/; EXPECT_ERROR: IncompatibleTypesForTernaryExpression
var x: int = true ? 1 : "bad"

fun printA() {
  println("A")
}
fun printB() {
  println("B")
}

var a = 'A'
takeInt((a == 'B') ? printA() : printB())
```

### Dynamic Truthiness

FlowWing supports dynamic truthiness in ternary conditions. Non-boolean types are evaluated as follows:

- **Integers/Decimals:** `0` or `0.0` are `falsy`; all other values are `truthy`.
- **Strings:** `""` (empty string) is `falsy`; non-empty strings are `truthy`.
- **Nir (null):** `null` is `falsy`.

```flowwing
var d = 42
println(d ? "truthy" : "falsy")

var n = null
println(n ? "truthy" : "falsy")

var s = ""
println(s ? "truthy" : "falsy")
```

### Edge Cases and Chaining

Ternary operators support complex logic including chained boolean operators (`&&`, `||`, `!`) and nesting.

**Nested Ternary Example:**

```flowwing
var a: bool = true
var b: bool = false

println(a ? (b ? "a-t-b-t" : "a-t-b-f") : (b ? "a-f-b-t" : "a-f-b-f"))
```

**Chained Logic:**

```flowwing
var a: bool = true
var b: bool = false
var c: bool = true
var d: bool = false

println((a && b || c && !d) ? "true" : "false")
```

### Object and Array Integration

Ternary expressions can be used to access members of objects or to return entire arrays.

**Object Member Access:**

```flowwing
type Point = {
  x: int
  y: int
}

fun getPoint() -> Point {
  return { x: 5, y: 10 }
}

println((getPoint().x > 3) ? "x_gt_3" : "x_le_3")
```

**Array Results:**

```flowwing
var a: int[2] = true ? [1, 2] : [3, 4]
println(a[0])
```

### Scope

Ternary expressions can access both global and local variables within their conditional logic.

```flowwing
var g: int = 10

fun useBoth() {
  var local: int = 2
  println(g > local ? "g_gt" : "g_le")
  println((g == 10 && local == 2) ? "match" : "nomatch")
}

useBoth()
```

---

## Type Conversion Functions

FlowWing provides built-in conversion functions to transform values between types.

### Boolean Conversion (`Bool`)

Converts various types to a boolean value.

- **Numeric:** `0` and `0.0` are `false`; others are `true`.
- **String:** `""` is `false`; others are `true`.
- **Char:** Any character is `true`.

```flowwing
print(Bool(3.14), "\n")
print(Bool(0), "\n")
print(Bool(""), "\n")
```

### Character Conversion (`Char`)

Converts integers or strings to a single character.

- **From String:** The string must contain exactly one character.
- **From Integer:** Converts the integer to its corresponding Unicode/ASCII character.

```flowwing
print(Char('A'), "\n")
print(Char("🚀"), "\n")
print(Char(65), "\n")

/; EXPECT_ERROR: Runtime Error: String contains more than one character.
print(Char("AB"))
```

### Decimal and Decimal32 Conversions

Converts values to high-precision (`Decimal`) or single-precision (`Decimal32`) floating-point types.

```flowwing
print(Decimal(3.14159), "\n")
print(Decimal32(3.14f), "\n")
print(Decimal(String("3.14159")), "\n")
```

### Integer Conversions (`Int32`, `Int64`, `Int8`)

Converts values to signed integer types. Note that converting from larger types to smaller types (like `Int8`) may result in **overflow wrapping**.

```flowwing
print(Int32(1000), "\n")
print(Int64(10000000000l), "\n")

// Int8 Overflow Example
print(Int8(1000), "\n") // Results in -24 due to wrapping
```

### String Conversion (`String`)

Converts any supported type into its string representation.

```flowwing
print(String(true), "\n")
print(String(3.14159), "\n")
print(String(1000), "\n")
```

### Chained Conversions

Conversion functions can be nested to perform complex type transformations.

```flowwing
// Triple chain: Bool -> String -> Int32 -> Bool
print(Bool(Int32(String(Bool(42))), "\n")

// Decimal -> Int32 -> Decimal
print(Decimal(Int32(3.99)), "\n")
```

### Conversion Errors and Runtime Exceptions

- **Argument Count Mismatch:** Calling a conversion function without arguments or with too many arguments.
- **Type Mismatch:** Passing an invalid type to a conversion function.
- **Runtime Errors:** Passing invalid strings (e.g., non-numeric characters to `Int32` or empty strings to `Char`).

```flowwing
/; EXPECT_ERROR: FunctionArgumentCountMismatch
print(Int32())

/; EXPECT_ERROR: Runtime Error: Invalid input for Int conversion.
print(Int32("abc"))
```

---

## Scientific Notation

FlowWing supports scientific notation (e.g., `1e10`) for both literals and arithmetic operations.

```flowwing
// Basic usage
print(1e10, "\n")
print(1e-3, "\n")

// Arithmetic
print(1e3 + 1e2, "\n")

// Comparison
print(1e5 > 1e4, "\n")
```

---

## Unary Operators

Unary operators are applied to a single operand.

### Unary Minus (`-`)

Negates the value of a numeric type.

```flowwing
print(-3.14f, "\n")
print(-1000, "\n")
print(--1.0f, "\n") // Double negation results in positive
```

### Unary Not (`!`)

Inverts a boolean value. For other types, it checks for "truthiness" (e.g., `!0` is `true`).

```flowwing
print(!true, "\n")
print(!0, "\n")
print(!"", "\n") // Checks if string is empty
```

### Unary Plus (`+`)

Used to explicitly denote a positive value, though it typically returns the value unchanged.

```flowwing
print(+1.0, "\n")
print(+-1.0, "\n")
```

### Invalid Unary Operations

Certain unary operators are not supported for specific types. Attempting to use `-`, `+`, or `~` (tilde) on booleans, characters, or null values will result in an `InvalidUnaryOperator` error.

```flowwing
/; EXPECT_ERROR: InvalidUnaryOperator
print(-true)
print(~"Hello")
```

## Lines 38198 - 40318

# FlowWing Technical Documentation: Variable Declarations and Unary Operations

This documentation covers the behavior of unary operators, variable declaration patterns, assignment mechanics, type promotion, scoping rules, and error handling within the FlowWing programming language.

---

## Unary Operations

FlowWing supports unary operators that can be applied to literals and variables.

### Unary Plus (`+`)

The unary plus operator can be applied to integer literals, including hexadecimal representations with suffixes.

```flowwing
print(+0xFFFFFFFFl, "\n")
print(+127, "\n")
print(+-1, "\n")
```

### Unary Bitwise Not (`~`)

The bitwise NOT operator (`~`) inverts the bits of the operand. This is tested across various integer widths, including `int8`, `int32`, and `int64`.

```flowwing
print(~128, "\n")
print(~0, "\n")
print(~3000000000, "\n")
print(~4294967295l, "\n")
```

---

## Variable Declarations and Types

Variables are declared using the `var` keyword followed by the variable name, a colon, and the type. FlowWing supports several primitive types:

| Type     | Description                                        |
| :------- | :------------------------------------------------- |
| `bool`   | Boolean values (`true`, `false`)                   |
| `char`   | Single character literals                          |
| `deci`   | Decimal floating-point numbers                     |
| `deci32` | 32-bit decimal floating-point numbers (suffix `f`) |
| `int8`   | 8-bit signed integer                               |
| `int`    | Standard signed integer (typically 32-bit)         |
| `int64`  | 64-bit signed integer (suffix `l`)                 |
| `str`    | String literals                                    |

### Basic Declarations

Variables can be declared with or without immediate initialization.

```flowwing
var x:bool = true
var x:char = 'a'
var x:deci = 5.2
var x:int = 100
var x:int64 = 1000l
var x:str = "Hello"
```

### Uninitialized Variables

When a variable is declared without an explicit initial value, it defaults to a zero-value based on its type:

- Integers (`int8`, `int`, `int64`): `0`
- Decimals (`deci`, `deci32`): `0`
- Booleans (`bool`): `false`
- Strings (`str`): `""` (empty string)
- Characters (`char`): (No output/empty)

```flowwing
var a:int
var b:bool
var c:deci
print(a, " ", b, " ", c, "\n") // Output: 0 false 0
```

---

## Assignment and Reassignment

FlowWing provides two ways to assign values to variables: the standard assignment operator `=` and the reassignment operator `<-`.

### Assignment Syntax

Assignment can involve literals, expressions, or the results of function calls.

```flowwing
var x:int = 10
x = 20
x <- 30
x = 10 + 5
x = String(42)
```

### Chained and Multiple Assignments

FlowWing supports assigning multiple values to multiple variables, provided the count of expressions matches the count of targets.

```flowwing
var x:int = 10
var y:int = 20
var z:int = 30
z = y
y = x
x = 100
```

---

## Type Promotion

FlowWing allows for automatic type promotion during assignment. A variable of a "larger" or more precise type can be assigned a value from a "smaller" or less precise type.

### Supported Promotions

- `int8` $\rightarrow$ `int` $\rightarrow$ `int64`
- `deci32` $\rightarrow$ `deci`
- `char` $\rightarrow$ `str`

```flowwing
var x:int64 = 1000l
var y:int = 500
x = y // int promotion

var x:str = "Hello"
var y:char = 'a'
x = y // char to str promotion

var x:deci = 3.14
var y:deci32 = 2.5f
x = y // deci32 to deci promotion
```

---

## Scoping and Shadowing

FlowWing utilizes block-level scoping. Variables declared within a block `{ ... }` are local to that block.

### Scope Access and Shadowing

- **Global Access:** Variables declared in the global scope are accessible within local blocks.
- **Shadowing:** Declaring a variable with the same name inside a local block "shadows" the outer variable, creating a new local instance that exists only within that block.

```flowwing
var x:int = 100
{
  var x:int = 200 // Shadowing the global x
  print(x, "\n") // Prints 200
}
print(x, "\n") // Prints 100 (original global x)
```

---

## Error Handling

The compiler enforces strict rules regarding assignments and variable usage.

### Assignment Errors

- **`InvalidAssignmentToConstantVariable`**: Attempting to change a value declared with `const`.
- **`AssignmentExpressionTypeMismatch`**: Attempting to assign a value of an incompatible type.
- **`AssignmentToNonLValue`**: Attempting to assign a value to a literal or an expression rather than a variable.
- **`AssignmentExpressionCountMismatch`**: Mismatch between the number of variables and the number of values in an assignment.

```flowwing
const x:bool = true
x = false // Error: InvalidAssignmentToConstantVariable

var x:int = 10
x = "Hello" // Error: AssignmentExpressionTypeMismatch

var x:int = 10
5 = x // Error: AssignmentToNonLValue
```

### Initialization and Usage Errors

- **`VariableNotFound`**: Attempting to use a variable that has not been declared or is out of scope.
- **`InitializerExpressionTypeMismatch`**: Attempting to initialize a variable with a value of an incompatible type.

```flowwing
print(x, "\n") // Error: VariableNotFound (if x is not declared)

var x:int = true // Error: InitializerExpressionTypeMismatch
```

## Lines 40319 - 42367

# Vector Module (`vec::Vec`)

The `vec::Vec` type provides a dynamic array implementation capable of storing mixed types.

## Initialization and Mixed Type Support

A new vector can be initialized using `new vec::Vec()`. The vector supports pushing various types, including `int`, `str`, `deci`, `bool`, and `char`.

```flowwing
bring vec

var list: vec::Vec = new vec::Vec()

println("--- Test 1: Push Mixed Types & Size ---")
list.push(10)
list.push("FlowWing")
list.push(3.14159)
list.push(true)
list.push('Z')
```

## Element Manipulation

Vectors support several methods for modifying their contents:

- `set(index, value)`: Replaces the element at the specified index.
- `insert(index, value)`: Inserts a value at the specified index, shifting subsequent elements to the right.
- `removeAt(index)`: Removes the element at the specified index and returns it.

```flowwing
list.set(1, "Replaced!") /; String replaces String
list.set(2, false)       /; Boolean replaces Float

list.insert(0, "First")  /; Shift everything right

var removed = list.removeAt(0)
```

## List State and Cleanup

The following methods manage the lifecycle and state of the vector:

- `pop()`: Removes and returns the last element. If the list is empty, it returns `null`.
- `clear()`: Removes all elements from the vector.
- `isEmpty()`: Returns `true` if the vector contains no elements.
- `size()`: Returns the current number of elements.

```flowwing
println(list.isEmpty())
println(list.pop())      /; Pops 'Z'
list.clear()
println(list.isEmpty())
println(list.size())
println(list.pop())      /; Popping empty list should safely return (null)
```

## Searching, Sorting, and Reversal

Advanced manipulation includes:

- `sort(ascending: bool)`: Sorts the vector in ascending or descending order.
- `reverse()`: Reverses the order of elements in the vector.
- `indexOf(value)`: Returns the index of the first occurrence of the value, or `-1` if not found.

```flowwing
list.clear().push(42).push(-5).push(100).push(0).push(3.14)
list.sort(true)

list.clear().push(1).push(2).push(3).push(4)
list.reverse()

list.clear().push("Target").push(100).push(true).push('X')
println(list.indexOf(100))
println(list.indexOf("Missing")) /; Not found, returns -1
```

## Method Chaining

FlowWing allows for method chaining, enabling multiple operations to be performed in a single statement.

```flowwing
list.clear().push(1).push(2).push(3).reverse().push(4).sort(false)
```

## Edge Cases: Out of Bounds

Attempting to access an index that does not exist via `get()` will return `null`.

```flowwing
println(list.get(999))   /; Out of bounds! Should return (null)
```

---

# While Loops

The `while` loop executes a block of code repeatedly as long as the specified condition evaluates to true.

## Basic Syntax and Control Flow

A standard `while` loop uses a condition to control iteration.

```flowwing
var x = 0
while (x < 5) {
  x = x + 1
}
println(x)
```

## Truthiness and Conditionals

FlowWing supports various types within `while` conditions. A value is considered "truthy" if it meets the following criteria:

- **Integers/Decimals**: Non-zero values.
- **Characters**: Non-null characters.
- **Strings**: Non-empty strings.
- **Objects**: Non-null objects.
- **Arrays**: Arrays where the evaluated index/element is non-zero.

```flowwing
var c: char = 'a'
while (c) {
  c = '\0'
}

var s: str = "ab"
while (s) {
  s = ""
}

type Point = { x: int, y: int }
var p: Point = { x: 1, y: 2 }
while (p) {
  p = null
}
```

## Logical Operators and Short-Circuiting

The `&&` (AND) and `||` (OR) operators are used for complex conditions and support short-circuiting.

```flowwing
var a: bool = true
var b: bool = true
while (a && b) {
  a = false
}

var x = true
while (true && x) {
  x = false
}

var a = 0
var b = 5
while (a < 1 || b > 3) {
  a = a + 1
  b = b - 1
}
```

## Scope and Variable Declaration

Variables can be declared within the body of a `while` loop, creating a new scope for each iteration. This also allows for shadowing outer variables.

```flowwing
while (i < 2) {
  var x: int = getVal()
  println(x)
}

var x: int = 1
while (i < 2) {
  var x: int = 10
  println(x)
  i = i + 1
}
println(x)
```

## Complex Control Flow

`while` loops can handle complex logic including nested loops, ternary operators, and multi-variable assignments.

```flowwing
while (i < 3) {
  var v = i > 1 ? 10 : 0
  println(v)
  i = i + 1
}

while (i < 2) {
  a, b = getPair()
  i = i + 1
}
```

## Break and Continue Statements

- `break`: Immediately terminates the innermost loop.
- `continue`: Skips the remainder of the current loop iteration and proceeds to the next condition check.

```flowwing
while (x < 10) {
  x = x + 1
  if (x == 5) {
    break
  }
}

while (x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  println(x)
}
```

## Error Cases

Certain uses of `break` and `continue` are prohibited:

- Using `break` or `continue` outside of a loop (e.g., inside a function or an `if` block not contained in a loop).
- Using a function that returns `void` (or `nthg`) in a condition.

```flowwing
/; EXPECT_ERROR: BreakStatementNotAllowedOutsideOfLoop
fun foo() {
  if (true) {
    break
  }
}

/; EXPECT_ERROR: InvalidBinaryOperationWithTypes
fun doVoid() -> nthg {
  println("x")
}
while (doVoid() == true) {
  i = i + 1
}
```
