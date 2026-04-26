---
sidebar_position: 5
---
import CodeBlock from "../../src/components/common/CodeBlock";

# Operators

Flow-Wing supports the following operators, categorized for ease of understanding:

## Arithmetic Operators
| Operator | Description                |
|----------|----------------------------|
| `+`      | Addition                   |
| `-`      | Subtraction                |
| `*`      | Multiplication             |
| `/`      | Division                   |
| `%`      | Modulus                    |
| `^`      | Xor                        |
| `~`      | Bitwise NOT                |
| `//`     | Floor Division             |

## Examples:

<CodeBlock code={
`println(1 - 1) /; integer subtraction
println(1.0 * 1.0) /; Output: 1
println("Hello"+ 2.0) /; Output: Hello2
println(1 / 2) /; Output: 0.5
println(3// 2) /; Output: 1
println("Hello"+"FlowWing") /; Output: HelloFlowWing
`} language="fg"/>

## Comparison Operators
| Operator | Description                |
|----------|----------------------------|
| `==`     | Equal to                   |
| `!=`     | Not equal to               |
| `<`      | Less than                  |
| `<=`     | Less than or equal to      |
| `>`      | Greater than               |
| `>=`     | Greater than or equal to   |

## Logical Operators
| Operator | Description                |
|----------|----------------------------|
| `&&`     | Logical AND                |
| `\|\|`     | Logical OR                 |

## Bitwise Operators
| Operator | Description                |
|----------|----------------------------|
| `&`      | Bitwise AND                |
| `\|`      | Bitwise OR                 |
| `^`      | Bitwise XOR                |

## Assignment Operators
| Operator | Description                |
|----------|----------------------------|
| `=`      | Assignment                 |
| `<-`     | Full Reassignment          |

## Miscellaneous Operators
| Operator | Description                |
|----------|----------------------------|
| `;`      | Return Statement terminator       |
| `,`      | Separator                  |
| `/#`      | Multiline Comment Beginning                         |
| `#/`      | Multiline Comment Ending                           |
| `/;`      | Singleline Comment                            |
| `:`      | Label or case separator     |
| `.`      | Member access operator      |
| `?`      | Ternary conditional operator |

## Parentheses and Brackets
| Operator | Description                |
|----------|----------------------------|
| `(`      | Open parenthesis            |
| `)`      | Close parenthesis           |
| `{`      | Open brace                  |
| `}`      | Close brace                 |
| `[`      | Open bracket                |
| `]`      | Close bracket               |