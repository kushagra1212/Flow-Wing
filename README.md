# Flow-Wing Programming Language

Flow-Wing: 

Flow-Wing is a programming language experiment that combines static and dynamic typing, along with other features. It is still a work in progress and supports object-oriented programming, memory management, garbage collection, and modularity. Flow-Wing includes support for AOT (Ahead-of-Time) and JIT (Just-In-Time) compilers, a REPL, LSP integration for VS Code, build basic servers and basic games


## Download Flow-Wing

Get started with Flow-Wing by downloading the latest version:

[Download Flow-Wing](https://flowwing.frii.site/)

## Documentation

Learn more about Flow-Wing's features, syntax, and usage in the official documentation:

[Flow-Wing Documentation](https://flow-wing-docs.vercel.app/)

## Language Syntax

### Classes

Flow-Wing supports `object-oriented programming` with class definitions. Classes can contain properties and methods. Here's an example:

```Flow-Wing
class Vehicle {
  var make:str
  var model:str
  var year:int

  init(make:str, model:str, year:int) -> nthg {
    self.make = make
    self.model = model
    self.year = year
  }

  getDetails() -> str {
    return self.year + " " + self.make + " " + self.model
  }

  printDetails() -> nthg {
    print("Vehicle: ", self.getDetails())
  }
}

```

### Inheritance

Classes can inherit from other classes using the `extends` keyword. Here's an example of a `Car` class that inherits from `Vehicle`:

```Flow-Wing
class Car extends Vehicle {
  var doors: int
  init(make: str, model: str, year: int, doors: int) -> nthg {
    super(make, model, year)
    self.doors = doors
  }

  getDetails() -> str {
    return self.year + " " + self.make + " " + self.model + " with " + self.doors + " doors"
  }

  printDetails() -> nthg {
    print("Car: ", self.getDetails())
  }

}
```

### Using Classes and Functions

Here’s how you can use these classes and functions in a `main` function:

```Flow-Wing
fun printVehicleDetails(v: Vehicle) -> nthg {
  v.printDetails()
}

fun main() -> nthg {
  var vehicle:Vehicle = new Vehicle("Toyota", "Camry", 2020)
  var car:Car = new Car("Honda", "Civic", 2022, 4)

  printVehicleDetails(vehicle)
  printVehicleDetails(car)
}

main()

```

In this example, the main function creates instances of Vehicle and Car, sets their properties, and calls their methods. This demonstrates the object-oriented capabilities of `Flow-Wing`, including `inheritance` and `method overriding`.

### Complex Types and Containers

Flow-Wing supports defining complex types and using them within containers. Here’s an example to illustrate this:

```Flow-Wing
type NestedType = {
  value:int
}

type ParentType = {
  name:str,
  nestedArray:NestedType[5]
}

type ComplexType = {
  id:int,
  message:str,
  amount:deci,
  flag:bool,
  parentArray:ParentType[1]
}

{
  var complexArray:ComplexType[2] = [
    {
      id:1,
      message:"hello",
      amount:3.3,
      flag:true,
      parentArray:[
        {
          name:"Parent1",
          nestedArray:[
            {value:1}, {value:2}, {value:3}, {value:4}, {value:5}
          ]
        }
      ]
    },
    {
      id:2,
      message:"world",
      amount:4.4,
      flag:false,
      parentArray:[
        {
          name:"Parent2",
          nestedArray:[
            {value:6}, {value:7}, {value:8}, {value:9}, {value:10}
          ]
        }
      ]
    }
  ]
  print(complexArray)
}

```

In this example:

- `NestedType` defines a structure with a single integer field.
- `ParentType` includes a string field and an array of `NestedType`.
- `ComplexType` combines various primitive types and an array of `ParentType`.

The variable `complexArray` is a container of `ComplexType` with two elements, each containing nested structures. This demonstrates how Flow-Wing handles complex type definitions and their initialization.

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

In these examples, a will become `[10, 20, 30, 4, 5]` and d will become `["hello", "world", "this", "d", "e"]`.

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
