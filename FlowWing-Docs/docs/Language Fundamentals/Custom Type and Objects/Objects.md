---
sidebar_position: 2
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# Objects

Flow-Wing supports objects.

<CodeBlock code={
`type Person = {
    name: str,
    age: int
}

var alice: Person = { name: "Alice", age: 20 }

print(alice.name + " " + alice.age)
`} language="fg"/>


**Output:**
<CodeBlock code={
`Alice 20
`} />