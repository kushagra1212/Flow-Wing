---
sidebar_position: 1
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Custom Types

Custom types in Flow-Wing are a powerful feature that allows you to define your own data types, with the ability to define methods and properties for your custom types.

## Example:

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

fun printPerson(person: Person) {
    print(person.name, " is ", person.age, " years old.")
}

var person: Person = { name: "Alice", age: 30 }

printPerson(person)
`} language="fg"/>

**Output:**
<CodeBlock code={
`Alice is 30 years old.
`} />

Here, the `Person` type is defined with two properties: `name` and `age`. The `Person` type is then used in the `printPerson` function.

## Array of Custom Types

Flow-Wing supports arrays of custom types. The `Person` type is used in the `people` array.

<CodeBlock code={
`type Person = {
    name: str,
    age: int,
}

var people: Person[2] = [ { name: "Alice", age: 30 }, { name: "Bob", age: 30 } ]
print(people)
`} language="fg"/>

**Output:**
<CodeBlock code={
`[{ name : 'Alice', age : 30 }, { name : 'Bob', age : 30 }]
`} />

Here, the `Person` type is used in the `people` array.


## Complex Custom Types

<CodeBlock code={`type NestedType = {
      value: int
}

type ParentType = {
      name: str,
      nestedArray: NestedType[5]
}

type ComplexType = {
        id: int,
        message: str,
        amount: deci,
        flag: bool,
        parentArray: ParentType[1]
}

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
`} language="fg"/>

In this example:

- `NestedType` defines a structure with a single integer field.
- `ParentType` includes a string field and an array of `NestedType`.
- `ComplexType` combines various primitive types and an array of `ParentType`.

The variable complexArray is a container of `ComplexType` with two elements, each containing nested structures. This demonstrates how Flow-Wing handles complex type definitions and their initialization.

