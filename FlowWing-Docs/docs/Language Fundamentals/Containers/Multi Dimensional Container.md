---
sidebar_position: 1
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# Multi Dimensional Container

Flow-Wing supports multi dimensional containers.

## 4D Array Example

Initializer shape must match every dimension (here `2×2×2×2`):

<CodeBlock code={
`var arr: int[2][2][2][2] = [
    [[[1, 2], [3, 4]], [[5, 6], [7, 8]]],
    [[[9, 10], [11, 12]], [[13, 14], [15, 16]]]
]
for (var i = 0 to 1) {
    for (var j = 0 to 1) {
        for (var k = 0 to 1) {
            for (var l = 0 to 1) {
                print(arr[i][j][k][l], " ")
            }
            print("\n")
        }
        print("\n")
    }
}
`} language="fg"/>
