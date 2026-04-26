---
sidebar_position: 4
---

import CodeBlock from "../../src/components/common/CodeBlock";


# File Handling Module

## Overview

The `File` module provides functions for file handling in the Flow-Wing language. It supports operations like creating, writing, and reading files, while also ensuring error handling using the `Err::Result` type. 

## Functions

### `File::createFile(path: str) -> Err::Result`

Creates a new file at the specified path. If the file already exists, it will not be overwritten.

#### Parameters
- `path`: The file path where the new file will be created.

#### Returns
- `Err::Result`: Returns `Nir` on success or an error object if the file creation fails.

## Example Usage

<CodeBlock code={
`bring File
bring Err

var err: Err::Result = File::createFile("test.txt")
if (err != Nir) {
  print(err.toString())
} else {
  print("File Created")
}
`} language="fg"/>

### `File::write(path: str, data: str, mode: str) -> Err::Result`

Writes data to the specified file. You can specify the mode for writing:
- `"w"`: Write, overwrites the file.
- `"a"`: Append, adds data to the end of the file.

#### Parameters
- `path`: The file path to write to.
- `data`: The content to write into the file.
- `mode`: The file writing mode. Choose `"w"` for overwrite, `"a"` for append.

#### Returns
- `Err::Result`: Returns `Nir` on success or an error object if writing fails.

## Example Usage

<CodeBlock code={
`bring File
bring Err

var errorWritingToFile: Err::Result = File::write("test.txt", "Hello", "w")
if (errorWritingToFile != Nir) {
        print(errorWritingToFile.toString())
} else {
        print("\\nFile Written")
}
`} language="fg"/>

### `File::read(path: str, mode: str) -> (str, Err::Result)`

Reads the content of a file and returns it as a string. You can specify the mode for reading:
- `"r"`: Read, reads the file normally.
- `"rb"`: Read in binary mode.

#### Parameters
- `path`: The file path to read from.
- `mode`: The file reading mode. Choose `"r"` for text read, `"rb"` for binary read.

#### Returns
- `(str, Err::Result)`: A tuple containing the file content (if read successfully) and the error result. Returns `Nir` if there is no error.

## Example Usage


<CodeBlock code={
`bring File
bring Err

var content: str, errorReadingFromFile: Err::Result = File::read("test.txt", "r")
if (errorReadingFromFile != Nir) {
        print(errorReadingFromFile.toString())
} else {
        print("\\nFile Read: ", content)
}
`} language="fg"/>


## Notes
- Always check for `Err::Result` after calling file operations to handle errors properly.
- Use appropriate file modes (`"w"`, `"a"`, `"r"`, `"rb"`) depending on whether you're writing, appending, or reading files.
