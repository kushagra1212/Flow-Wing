---
sidebar_position: 8
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Class

Define classes with the `class` keyword. Classes bundle fields and methods into a single type.

## Classes

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

`Person` has two fields (`name`, `age`), three methods (`print`, `getAge`, `setAge`), and a constructor (`init`) that sets the initial values. Create instances with `new`.

### Multiple Constructors Example

Define multiple constructors by marking additional ones with `fun init` (the first `init` stays bare). Each can accept different parameters:

<CodeBlock code={
`class Person {
    var name: str
    var age: int
    init(name: str, age: int) -> nthg {
        self.name = name
        self.age = age
    }
    /; Second constructor — name only, default age
    fun init(n: str) -> nthg {
        self.name = n
        self.age = 0
    }
}
`} language="fg"/>

### The `self` Keyword

`self` refers to the current instance. It's automatically available in every method — you never pass it explicitly:

- `self.field` — read a member
- `self.method()` — call another method
- `self.field = value` — modify a member