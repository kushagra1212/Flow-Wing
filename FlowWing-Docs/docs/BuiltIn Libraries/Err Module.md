---
sidebar_position: 5
---

import CodeBlock from "../../src/components/common/CodeBlock";


# Err Module Documentation

## Overview

The `Err` module is designed to handle error codes and error messages in Flow-Wing. It includes an `ErrorCode` type for predefined error codes, a `Result` class for handling error messages, and methods to enhance error management and reporting.

## Types

### `Err::ErrorCode`

This type defines a set of error codes that are used throughout the module for standardized error handling. 

#### Fields:
- `NOT_FOUND`: Represents an error when a resource is not found (value: `1`).
- `FAILED`: Represents a general failure error (value: `2`).
- `INVALID_ARGUMENT`: Represents an error when an invalid argument is provided (value: `3`).

### Example

<CodeBlock code={
`bring Err
print(Err::CODE.NOT_FOUND)
`} language="fg"/>

## Classes

### `Err::Result`

The `Result` class represents an error object containing an error message, error code, and optional details. It provides multiple constructors and methods to work with error messages, extend error details, and retrieve error information.

#### Constructors

- **`init(message: str = "")`**: Initializes the result with only a message.
- **`init(message: str = "", code: int = 0)`**: Initializes the result with a message and an error code.
- **`init(message: str = "", code: int = 0, details: str = "")`**: Initializes the result with a message, an error code, and additional details.

#### Methods

- **`getMessage() -> str`**: Returns the error message.
- **`getCode() -> int`**: Returns the error code.
- **`getDetails() -> str`**: Returns the additional error details.
- **`withMessage(extraMessage: str) -> Err::Result`**: Adds an extra message to the existing error message and returns a new `Result`.
- **`withDetails(details: str) -> Err::Result`**: Adds or replaces the details of the error and returns a new `Result`.
- **`toString() -> str`**: Converts the error object into a string representation of the error.

### Example


<CodeBlock code={
`bring Err

fun handle_error() -> nthg {
  var err1: Err::Result = new Err::Result("File not found", Err::CODE.NOT_FOUND)
  print(err1.getMessage())   /; Error: File not found

  var err2: Err::Result = err1.withMessage("Please check the path")
  print(err2.toString())     /; Error: File not found -> Please check the path

  var err3: Err::Result = err2.withDetails("The file might have been deleted")
  print(err3.toString())     /; Error: File not found -> Please check the path (Details: The file might have been deleted)

  var err4: Err::Result = new Err::Result("Invalid argument", Err::CODE.INVALID_ARGUMENT)
  print(err4.toString())     /; Error: Invalid argument
}

handle_error()
`} language="fg"/>


### Notes
- The `Err::Result` class provides flexibility in managing errors by allowing additional messages and details to be attached to errors.
- Use `Err::ErrorCode` for standardized error codes when dealing with different failure scenarios.
