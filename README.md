# FlowWing Programming Language (Elang --> Old Name)

Elang is a simple, dynamically-typed programming language designed for ease of use and readability. It supports a variety of language constructs and inbuilt functions to help you write expressive and efficient code.

## Language Syntax

### Variables and Constants

You can declare variables and constants using the `var` and `const` keywords:

```Elang
var a = 2
const pi = 3.14159265
```

## Functions

Functions are defined using the fun keyword. You can specify the return type after the arrow (->), and functions can have parameters:

```Elang
fun isPrime(n) -> bool {
  // Function body here
}

fun getInputAsInt() -> int {
  // Function body here
}
```

## Control Flow

Elang supports conditional statements and loops:

```
if (condition) {
  // Code to execute if the condition is true
} or if (condition) {
  // Code to execute or if the condition is true
}
else {
  // Code to execute if the condition is false
}

for (var i = 0 to 5 : 2) {
  // Code to execute in the loop
}

```

## Comments

You can use both single-line (//) and multi-line (#/#) comments in your code:

```
// Single line comment

/#
  Multi-line comment
/#
```

## Inbuilt Functions

Elang provides several inbuilt functions for common operations:

```
Decimal(10)
Int32(10)
String(10)
Bool(10)
input("Enter a number: ")
print("Hello")
...

```

## Sample Programs

Here are some sample programs in Elang to get you started:

## Check if a Number is Prime

```

fun main() -> nthg {
    var n = getInputAsInt()
    if (isPrime(n)) {
        print("The number is prime")
    } else {
        print("The number is not prime")
    }
}

main()

```

## Loop Examples

```
for var i = 0 to 5 {
  if i == 3 {
    break
  } or if i == 2 {
    print(i)
  } else {
    print(i)
  }
}

while(x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  print(x + "\n")
  if (x == 4) {
    break
  }
}

```

### Getting Started

To run Elang programs, you'll need an Elang compiler and if you want to use the Elang REPL, you'll need the Elang interpreter.
