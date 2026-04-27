---
sidebar_position: 1
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# Fill Expression

Flow-Wing supports the `fill` keyword to create or update an array with a specific value.

### Example Usage:

<CodeBlock code={
`type Point = {
    x:int,
    y:int
  }

var arr: Point[3] = [ 3 fill {x: 0, y: 0} ]

arr = [ 2 fill { x: 5 } ]

print(arr)
`} language="fg"/>

**Output:**

<CodeBlock code={
`[{ x : 5, y : 0 }, { x : 5, y : 0 }, { x : 0, y : 0 }]
`} />

> **Note:** If the `fill` count is less than the array size, remaining elements keep their old values. In the example above, `[ 2 fill { x: 5 } ]` overwrites only the first two elements; the third retains its previous value `{ x: 0, y: 0 }`.

