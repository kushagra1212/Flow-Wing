---
sidebar_position: 1
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Vec Module (Dynamic Array)

The Vec module in Flow-Wing provides a vector (dynamic array) implementation for storing and manipulating collections of elements of a specific type. It supports common operations such as adding, getting, setting, and removing elements, as well as checking the size of the vector.

**Key Features of the Vec Module**
Dynamic Arrays: Vectors can dynamically grow as new elements are added.
Type-Specific Vectors: The module provides specialized vectors for different types such as Int, Bool, String, and Deci (decimal values).

`Memory Management`: The `free()` function is used to release memory allocated for the vector, ensuring efficient memory usage.

Supported Types in Vec Module
- `Vec::Int:` A vector that stores integer values.
- `Vec::Bool:` A vector that stores boolean values (true or false).
- `Vec::String:` A vector that stores string values.
- `Vec::Deci:` A vector that stores decimal values (floating-point numbers).

## Examples

**Importing Vec**


## **bring Vec**


### Working with integer vectors

<CodeBlock code={
`var intVec: Vec::Int = new Vec::Int()
  intVec.add(10)
  intVec.add(20)
  print(intVec.get(0))
  print(intVec.size()) 

  intVec.remove(1)
  print(intVec.size())
  intVec.free()

`} language="fg"/>

### Boolean vectors

<CodeBlock code={
`var boolVec: Vec::Bool = new Vec::Bool()
  boolVec.add(true)
  boolVec.add(false)
  print(boolVec.get(0))
  print(boolVec.size()) 

  boolVec.remove(1)
  print(boolVec.size()) 
  boolVec.free()

`} language="fg"/>

### String vectors

<CodeBlock code={
`var strVec: Vec::String = new Vec::String()
  strVec.add("Hello")
  strVec.add("World")
  print(strVec.get(0)) 
  print(strVec.size()) 

  strVec.remove(1)
  print(strVec.size()) 
  strVec.free()

`} language="fg"/>

### Decimal vectors

<CodeBlock code={
`var dblVec: Vec::Deci = new Vec::Deci()
  dblVec.add(1.23)
  dblVec.add(4.56)
  print(dblVec.get(0)) 

  dblVec.set(0, 6.78)
  print(dblVec.get(0)) 
  print(dblVec.size()) 

  dblVec.remove(1)
  print(dblVec.size()) 
  dblVec.free()

`} language="fg"/>

