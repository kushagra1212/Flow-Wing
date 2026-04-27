---
sidebar_position: 1
title: 2D Containers
sidebar_label: 2D Containers
---

import CodeBlock from "../../../src/components/common/CodeBlock";

# Two-Dimensional Containers

Flow-Wing supports multi-dimensional arrays. Start with 2D.

## Declaration

<CodeBlock code={
`var grid: int[2][3] = [[1, 2, 3], [4, 5, 6]]
`} language="fg"/>

This creates a 2×3 grid of integers.

## Access and Modification

<CodeBlock code={
`print(grid[0][1])  /; 2 — first row, second column
grid[1][0] = 10     /; modify an element
`} language="fg"/>

## Iteration

<CodeBlock code={
`for (var i: int = 0 to 1 : 1) {
    for (var j: int = 0 to 2 : 1) {
        print(grid[i][j])
    }
}
`} language="fg"/>

Output: `1 2 3 4 5 6`

## More Dimensions

See [Multi Dimensional Container](Multi%20Dimensional%20Container) for 3D, 4D, and beyond.
