---
sidebar_position: 8
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Class

Flow-Wing supports classes and objects.

## Classes

In Flow-Wing, classes are defined using the `class` keyword.

### Example:

<CodeBlock code={
`class Person {
   var name: str
   var age: int

   init(name: str, age: int) -> nthg {
       self.name = name
       self.age = age
   }

   print() -> nthg {
       print(self.name, " is ", self.age, " years old.")
   }

   getAge() -> int {
       return self.age
   }

   setAge(age: int) -> nthg {
       self.age = age
   }

}

const person: Person = Person("Alice", 30)

person.print()
print("\\n"person.getAge())
`} language="fg"/>


**Output:**

<CodeBlock code={
`Alice is 30 years old.
30`
} />

Here, `Person` is a class that has two properties `name` and `age`, and two methods `print` and `getAge`. `init` is a constructor that initializes the properties of the class. `setAge` is a method that sets the value of the `age` property.

### Multiple Constructors Example

Flow-Wing supports multiple constructors. The `init` keyword can have multiple constructors.

<CodeBlock code={
`class Person {
   var name: str
   var age: int

   init(name: str, age: int) -> nthg {
       self.name = name
       self.age = age
   }
}
`} language="fg"/>