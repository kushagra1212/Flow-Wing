# Flow-Wing Programming Language

Flow-Wing is a modern and flexible programming language that uniquely combines dynamic and static typing paradigms, providing developers with the versatility to choose between runtime adaptability and compile-time type safety. With intuitive syntax for variable and constant declarations, function definitions, and robust container support, Flow-Wing facilitates clean and efficient code writing. Whether initializing containers, implementing control flow structures like 'if' and 'for', or utilizing a set of built-in functions for common tasks. This language empowers developers, catering to both beginners and seasoned programmers, with a seamless balance between dynamic and static typing. To harness its full potential, Flow-Wing requires a dedicated AOT or JIT compiler, ensuring a powerful and adaptable development experience.

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


##### Function with 2D String Array Parameter and Normal String Parameter

```Flow-Wing
fun foo(a:str[2][3], x:str) -> nthg {
    a[0][1] = x
    print(a)
}

var x:str = "a"
var a:str[2][3] = [["a","b","c"],["d","e","f"]]
foo(a, x) /; output [[a, a, c], [d, e, f]]

```

This example defines a function foo that takes a 2D string array a and a string x as parameters. It modifies the element at [0][1] in the array a with the value of x and prints the modified array. Then, it declares a string variable x with the value "a" and a 2D string array a, calling the function foo with these variables.


##### 2D Container Indexing with Fill Expression

```
var x : int[2][2] = [2 fill 5]
var y : int = 1
print(x[y][y]) /; 0
```

This example initializes a 2D integer container x with dimensions [2][2] using the fill expression 2 fill 5. It then indexes into the container using the variable y and prints the corresponding value.
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

# Objects

Flow-Wing now provides support for objects, enabling developers to define structured data types with multiple fields. Objects offer the advantage of nesting within each other, enhancing flexibility in data modeling and organization.


## Sample Type Object Declaration

```
type Person = {
   name:str,
   age:int,
   address:str
}

```
## Object Initialization

```
var p : Person = {
  name : "John",
  age : 30,
  address : "123 Main St"
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

To run Flow-Wing programs, you'll need an `Flow-Wing AOT-compiler or JIT-Compiler` and if you want to use the Flow-Wing REPL, you'll need the Flow-Wing interpreter.


## Installing Flow-Wing 

### MacOS x86_64


#### Install Homebrew 

Visit [https://brew.sh](https://brew.sh) to install brew.

```bash
  brew tap kushagra1212/flow-wing
  brew install flowwing
  ```
#### Verify Installation

```bash
flowwing --version
```


