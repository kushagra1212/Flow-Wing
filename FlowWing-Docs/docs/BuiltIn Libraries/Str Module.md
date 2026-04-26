---
sidebar_position: 2
---

import CodeBlock from "../../src/components/common/CodeBlock";

# Str Module

The Str module in Flow-Wing provides various utilities for string manipulation and handling. Below is the list of available functions, descriptions, and examples of how to use them.


### makeCopy

`Function:` makeCopy(dest: str, src: str)
`Description:` Copies the content of src string to dest. After the copy, changes to one string do not affect the other.

#

<CodeBlock code={
`var x: str = "HS"
var y: str
Str::makeCopy(y, x)
print(x)  /; Output: HS
print(y)  /; Output: HS
`} language="fg"/>


### concat

`Function:` concat(a: str, b: str) -> str
`Description:` Concatenates two strings and returns the result.

#

<CodeBlock code={
`var x: str = "HS"
var y: str = "S"
var z: str = Str::concat(x, y)
print(z)  /; Output: HSS
`} language="fg"/>


### compare

`Function:` compare(a: str, b: str) -> int
`Description:` Compares two strings lexicographically. Returns:

- `0` if a equals b
- `< 0` if a is lexicographically less than b
- `> 0` if a is greater than b


#

<CodeBlock code={
`print(Str::compare("HS", "HS"))  /; Output: 0
print(Str::compare("HS", "S"))   /; Output: -1
print(Str::compare("S", "HS"))   /; Output: 1
`} language="fg"/>


### toUpper

`Function:` toUpper(s: str) -> str
`Description:` Converts the string s to uppercase.

#

<CodeBlock code={
`var x: str = "abc"
print(Str::toUpper(x))  /; Output: ABC
`} language="fg"/>


### toLower

`Function:` toLower(s: str) -> str
`Description:` Converts the string s to lowercase.

#

<CodeBlock code={
`var x: str = "ABC"
print(Str::toLower(x))  /; Output: abc
`} language="fg"/>


`Function:` length(s: str) -> int
`Description:` Returns the length of the string s.

#

<CodeBlock code={
`var x: str = "FlowWing"
print(Str::length(x))  /; Output: 8
`} language="fg"/>


### reverse


`Function:` reverse(s: str) -> str
`Description:` Returns the reversed version of the string s without modifying the original string.


#

<CodeBlock code={
`var x: str = "abc"
print(Str::reverse(x))  /; Output: cba
`} language="fg"/>


### reverseInPlace

`Function:` reverseInPlace(s: str)
`Description:` Reverses the string s in place.

#

<CodeBlock code={
`var x: str = "abc"
Str::reverseInPlace(x)
print(x)  /; Output: cba
`} language="fg"/>


### subStrIndex

`Function:` subStrIndex(s: str, sub: str) -> int
`Description:` Returns the index of the first occurrence of the substring sub in s. Returns -1 if sub is not found.

#

<CodeBlock code={
`var x: str = "FlowWing"
print(Str::subStrIndex(x, "Wing"))  /; Output: 4
`} language="fg"/>



### replaceInPlace

`Function:` replaceInPlace(s: str, old: str, new: str)
`Description:` Replaces all occurrences of the old substring in s with new, modifying the original string.

#

<CodeBlock code={
`var x: str = "abcabc"
Str::replaceInPlace(x, "a", "x")
print(x)  /; Output: xbcxbc
`} language="fg"/>


### trim


`Function:` trimInPlace(s: str) -> str
`Description:` Removes leading and trailing whitespace characters from the string s.

#

<CodeBlock code={
`var x: str = "   abc   "
Str::trimInPlace(x)
print(x)  /; Output: abc
`} language="fg"/>


### indexOfChar

`Function:` indexOfChar(s: str, c: char) -> int
`Description:` Returns the index of the first occurrence of the character c in the string s. Returns -1 if c is not found.

#

<CodeBlock code={
`var x: str = "FlowWing"
print(Str::indexOfChar(x, 'W'))  /; Output: 4
`} language="fg"/>



### charAt

`Function:` charAt(s: str, index: int) -> char
`Description:` Returns the character at the specified index of string s.

#

<CodeBlock code={
`var x: str = "FlowWing"
print(Str::charAt(x, 1))  /; Output: l
`} language="fg"/>



### int8ToString

`Function:` int8ToString(n: Int8) -> str
`Description:` Converts an Int8 value to a string representation.

#

<CodeBlock code={
    `print(Str::int8ToString(Int8(99)))  /; Output: 99`
} language="fg"/>



This module provides a comprehensive set of string operations that cover common string manipulation needs. Each function is designed to be efficient and easy to use within the Flow-Wing language.