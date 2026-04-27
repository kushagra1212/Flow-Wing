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
const person: Person = new Person("Alice", 30)
person.print()
print("\n", person.getAge())
`} language="fg"/>


**Output:**

<CodeBlock code={
`Alice is 30 years old.
30`
} />

Here, `Person` is a class that has two properties `name` and `age`, and three methods `print`, `getAge`, and `setAge`. `init` is a constructor that initializes the properties of the class.

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
    // Second constructor — name only, default age
    fun init(n: str) -> nthg {
        self.name = n
        self.age = 0
    }
}
`} language="fg"/>

### The `self` Keyword

`self` is the current instance and is automatically available in all methods. You never pass `self` explicitly — it's implicit:

- `self.field` — access a member
- `self.method()` — call another method
- `self.field = value` — modify a member