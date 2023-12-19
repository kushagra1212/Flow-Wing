# Elang Programming Language ( AKA Flow-Wing )

Flow-Wing is a simple, dynamically-typed programming language designed for ease of use and readability. It supports a variety of language constructs and inbuilt functions to help you write expressive and efficient code.

## Language Syntax

### Variables and Constants

You can declare variables and constants using the `var` and `const` keywords:

```Flow-Wing
var a = 2
const pi = 3.14159265
```

## Functions

Functions are defined using the fun keyword. You can specify the return type after the arrow (->), and functions can have parameters:

```Flow-Wing
fun isPrime(n) -> bool {
  /; Function body here
}

fun getInputAsInt() -> int {
  /; Function body here
}
```

## Container Support

Flow-Wing language supports container types for integers, decimals, booleans, and strings. You can declare a container with a specific size and initialize it with values. Here are some examples:

```Flow-Wing
var a:int[5] = [1, 2, 3, 4, 5]  /; Declare an integer container
var b:deci[5] = [1.1, 2.2, 3.3, 4.4, 5.5]  
var c:bool[5] = [true, false, true, false, true]  
var d:str[5] = ["a", "b", "c", "d", "e"]  
```
You can also assign new values to the container:

```Flow-Wing
a = [10, 20, 30, 40, 50]  /; Assign new values to the integer container
b = [10.10, 20.20, 30.30, 40.40, 50.50]  
c = [false, true, false, true, false]  
d = ["hello", "world", "this", "is", "test"]  
```
Partial assignment is also supported. If the new values do not fill the entire container, the remaining elements will retain their original values:

```Flow-Wing
a = [10, 20, 30]  
d = ["hello", "world", "this"]  /; Partial assignment to the string container
```

In these examples, a will become ```[10, 20, 30, 4, 5]``` and d will become ```["hello", "world", "this", "d", "e"]```.

## Fill Expression


You can use the fill expression to fill a container with a specific value:

```Flow-Wing
var a:int[5] = [5 fiill 10]  /; a will become [10, 10, 10, 10, 10]
```

Assigning a fill expression to a container will fill the container with the specified value:

```Flow-Wing
a = [2 fill 9]  /; a will become [9, 9, 10, 10, 10]
```


Assigning a value to a container element is also supported:

```Flow-Wing
a[0] = 11  /; a will become [11, 9, 10, 10, 10]
```






## Control Flow

Flow-Wing supports conditional statements and loops:

```
if (condition) {
  /; Code to execute if the condition is true
} or if (condition) {
  /; Code to execute or if the condition is true
}
else {
  /; Code to execute if the condition is false
}

for (var i = 0 to 5 : 2) {
  /; Code to execute in the loop
}

```

## Comments

You can use both single-line (/\;) and multi-line (#/ #/) comments in your code:

```
/; Single line comment

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
... and more

```

## Sample Programs

Here are some sample programs in Flow-Wing to get you started:

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

To run Flow-Wing programs, you'll need an `Flow-Wing compiler` and if you want to use the Flow-Wing REPL, you'll need the Flow-Wing interpreter.




