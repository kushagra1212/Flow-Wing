---
sidebar_position: 4
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Assignment Expressions

**Flow-Wing provides the following assignment operators:**

- `=` Used for Updating Variables
- `<-` Used for Complete Reassignment of Variables

Assignment expressions in Flow-Wing allow updating the value of a variable. The assignment operator (=) is used to set a variable to a new value.

<CodeBlock code={
`var x = 10
x = 20
`} language="fg"/>

**`=` Behavior for Complex Types (Container / Objects)**


## Example:

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var person: Person =  { name: "Alice", age: 30 }

person = { name: "Bob" }

print(person)
`} language="fg"/>

**Output:**

<CodeBlock code={
`{ name : 'Bob', age : 30 }
`}/>

The value of person is updated to `{"name": "Bob", "age": 30}`. In this case, only the value of name is updated, while the rest of the properties remain the same. If we want to change the entire person object, we can use `person = {"name": "Bob", "age": 30}` or we can use the `<-` operator.


The `<-` operator is used to update the variable completely. For primitive types, the behavior of `<-` is similar to that of `=`, but for complex types, the behavior of `<-` is different.

## Example:
<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var person: Person =  { name: "Alice", age: 30 }

person <- { name: "Bob" }

print(person)
`} language="fg"/>

The value of person is updated to `{"name": "Bob", "age": 0}`. The age property is set to `0` since it was not provided, so it defaults to this value.


## Container Example:

Using `<-` for Assignment

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var person: Person =  { name: "Alice", age: 30 }

var people: Person[2] = [person, { name: "Bob", age: 30 }]

people <- [{ name: "Charlie", age: 30 }]

print(people) 
`} language="fg"/>

**Output:**
<CodeBlock code={
`[{ name : 'Charlie', age : 30 }, { name : '', age : 0 }]
`} />

The value of the first element in people is updated to `{"name": "Charlie", "age": 30}`, while the rest are set to their default values.

Using `=` for Assignment 

<CodeBlock code={
`var people: Person[2] = [person, { name: "Bob", age: 30 }]

people = [{ name: "Charlie", age: 30 }]

print(people) 
`} language="fg"/>

**Output:**
<CodeBlock code={
`[{ name : 'Charlie', age : 30 }, { name : 'Bob', age : 30 }]
`}/>

