---
sidebar_position: 1
---
import CodeBlock from "../../../src/components/common/CodeBlock";

# Multi Dimensional Container

Flow-Wing supports multi dimensional containers.

## 4D Array Example

<CodeBlock code={
`var arr: int[2][3][4][5] = [
    [ [ [1, 2, 3, 4], [5, 6, 7, 8] ], [ [9, 10, 11, 12], [13, 14, 15, 16] ] ],
]

for var i = 0 to 1 {
    for var j = 0 to 2 {
        for var k = 0 to 3 {
            for var l = 0 to 4 {
                print(arr[i][j][k][l], " ")
            }

            print("\\n")
        }

        print("\\n")
    }
}
`} language="fg"/>
