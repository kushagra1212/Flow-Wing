---
sidebar_position: 1
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Passing Functions as Arguments

## Overview

This documentation explains how to pass functions as arguments to other functions in the Flow-Wing programming language. This feature allows for greater flexibility and modularity in code design.

## Example Code

Below is an example that demonstrates how to define and pass functions as arguments:


<CodeBlock code={
`fun printX(x: int, y: deci, p: str, u: bool, callback: [(str) -> nthg]) -> nthg {
    print("Printing X:", x)
    print(y, p, u)
    callback("Hello") /; Calling the callback function
}

fun printString(message: str) -> nthg {
    print("\\nFrom printString:", message)
}

fun mainFunction(handler: [(int, deci, str, bool, [(str) -> nthg]) -> nthg]) -> nthg {
    handler(2, 2.2, "Sample String", false, printString) /; Passing arguments and the function
}

mainFunction(printX) /; Calling mainFunction with printX as the handler
`} language="fg"/>


## Explanation of Functions

### `printX`

- **Signature**: `fun printX(x: int, y: deci, p: str, u: bool, callback: [(str) -> nthg]) -> nthg`
- **Parameters**:
  - `x`: An integer value to be printed.
  - `y`: A decimal value to be printed.
  - `p`: A string to be printed.
  - `u`: A boolean value to be printed.
  - `callback`: A function that takes a string as an argument and returns nothing (`nthg`).
- **Description**: This function prints the values of `x`, `y`, `p`, and `u`. It then calls the `callback` function with the string `"Hehe"`.

### `printString`

- **Signature**: `fun printString(message: str) -> nthg`
- **Parameters**:
  - `message`: A string message to be printed.
- **Description**: This function prints the provided message. It is designed to be passed as a callback to other functions.

### `mainFunction`

- **Signature**: `fun mainFunction(handler: [(int, deci, str, bool, [(str) -> nthg]) -> nthg]) -> nthg`
- **Parameters**:
  - `handler`: A function that matches the signature of `printX`.
- **Description**: This function accepts a handler function and calls it with specific arguments, including `printString` as the callback.

### Usage

- The `mainFunction` is invoked with `printX` as the handler, demonstrating how to pass a function as an argument. When `printX` is executed, it prints the provided values and calls `printString` with a sample string.

## Conclusion

Passing functions as arguments in Flow-Wing allows for more dynamic and reusable code. This pattern can be used to implement callbacks and event handling, making your code more modular and maintainable.
