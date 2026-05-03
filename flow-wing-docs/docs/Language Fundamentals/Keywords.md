---
sidebar_position: 6
---

# Keywords

Flow-Wing programming language supports the following keywords, grouped by category:

## Types

| Keyword   | Description                                | Docs |
|-----------|--------------------------------------------|------|
| `int`     | 32-bit integer type                        | [Data Types](Data%20Types.md) |
| `int8`    | 8-bit integer type                         | [Data Types](Data%20Types.md) |
| `int64`   | 64-bit integer type                        | [Data Types](Data%20Types.md) |
| `str`     | String type                                | [Data Types](Data%20Types.md) |
| `char`    | Character type (single Unicode character)  | [Data Types](Data%20Types.md) |
| `deci`    | Decimal type (64-bit)                      | [Data Types](Data%20Types.md) |
| `deci32`  | 32-bit decimal type                        | [Data Types](Data%20Types.md) |
| `bool`    | Boolean type                               | [Data Types](Data%20Types.md) |
| `nthg`    | Represents 'nothing' or 'void'             | [Data Types](Data%20Types.md) |
| `unknown` | Represents an unknown type                 | [Data Types](Data%20Types.md) |

## Literal Values

| Keyword   | Description                                | Docs |
|-----------|--------------------------------------------|------|
| `true`    | Boolean true value                         | [Data Types](Data%20Types.md) |
| `false`   | Boolean false value                        | [Data Types](Data%20Types.md) |
| `null`    | Null value; type of the null literal       | [Data Types](Data%20Types.md) |

## Control Flow

| Keyword   | Description                                          | Docs |
|-----------|------------------------------------------------------|------|
| `if`      | Conditional statement                                 | [Or if else Statement](Conditionals/Or%20if%20else%20Statement.md) |
| `or`      | Logical OR operator / alternative `if` branch         | [Or if else Statement](Conditionals/Or%20if%20else%20Statement.md) |
| `else`    | Alternative branch in conditional statement           | [Or if else Statement](Conditionals/Or%20if%20else%20Statement.md) |
| `switch`  | Switch statement                                      | [Switch Statement](Conditionals/Switch%20Statement.md) |
| `case`    | Case in a switch statement                            | [Switch Statement](Conditionals/Switch%20Statement.md) |
| `default` | Default case in a switch statement                    | [Switch Statement](Conditionals/Switch%20Statement.md) |

## Loops

| Keyword    | Description                               | Docs |
|------------|-------------------------------------------|------|
| `while`    | Looping statement                         | [While Loop](Loops/While%20Loop.md) |
| `for`      | Looping statement                         | [For Loop](Loops/For%20Loop.md) |
| `to`       | Used in range expressions                 | [For Loop](Loops/For%20Loop.md) |
| `continue` | Skip to the next iteration in a loop      | [While Loop](Loops/While%20Loop.md) |
| `break`    | Exit from a loop                          | [While Loop](Loops/While%20Loop.md) |

## Declarations

| Keyword   | Description                    | Docs |
|-----------|--------------------------------|------|
| `var`     | Variable declaration            | [Variables and Constants](Variables%20and%20Constants.md) |
| `const`   | Constant declaration            | [Variables and Constants](Variables%20and%20Constants.md) |
| `fun`     | Function declaration            | [Declare and Define Functions](Functions/Declare%20and%20Define%20Functions.md) |
| `class`   | Class declaration               | [Class](Classes%20and%20Objects/Class.md) |
| `type`    | Define a custom type            | [Custom Types and Objects](Custom%20Types%20and%20Objects/Custom%20Types%20and%20Objects.md) |
| `decl`    | Forward-declare a type/function | [Declare and Define Functions](Functions/Declare%20and%20Define%20Functions.md) |
| `return`  | Return a value from a function  | [Declare and Define Functions](Functions/Declare%20and%20Define%20Functions.md) |

## Modules & Imports

| Keyword  | Description                      | Docs |
|----------|----------------------------------|------|
| `bring`  | Import a module or file          | [Bring Import Exports](../Advanced/Bring%20Import%20Exports.md) |
| `expose` | Expose functionality of a module | [Bring Import Exports](../Advanced/Bring%20Import%20Exports.md) |
| `from`   | Used in import statements        | [Bring Import Exports](../Advanced/Bring%20Import%20Exports.md) |
| `module` | Module declaration               | [Creating and Using Modules](../Advanced/Creating%20and%20Using%20Modules.md) |

## Object-Oriented

| Keyword   | Description                    | Docs |
|-----------|--------------------------------|------|
| `new`     | Instantiate a class or object  | [Class](Classes%20and%20Objects/Class.md) |
| `extends` | Inherit from a superclass      | [Inheritance](../Advanced/Inheritance.md) |
| `inout`   | Parameter passing mode         | [Declare and Define Functions](Functions/Declare%20and%20Define%20Functions.md) |
| `as`      | Type casting or aliasing       | [Data Types](Data%20Types.md) |

## Other

| Keyword | Description       | Docs |
|---------|-------------------|------|
| `fill`  | Fill a data structure | [Fill Expression](Containers/Fill%20Expression.md) |
