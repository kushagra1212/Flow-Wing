import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";

const documentation: Record<
  | "print"
  | "println"
  | "super"
  | "input"
  | "Int8"
  | "Int32"
  | "Int64"
  | "Decimal"
  | "Decimal32"
  | "String"
  | "Bool"
  | "Char",
  string | MarkupContent
> = {
  print: {
    kind: "markdown",
    value: `
**Print Function**

The \`print\` function is used to print a message to the console.

### Example:
\`\`\`flowwing
print("Hello, World!")
print(2, 3, 4,"Hello")
\`\`\`
    `,
  },
  println: {
    kind: "markdown",
    value: `
**Print Line Function**

The \`println\` function is like \`print\` but also prints a newline at the end.

### Example:
\`\`\`flowwing
println("Hello, World!")
println(2, 3, 4, "Hello")
\`\`\`
    `,
  },
  super: {
    kind: "markdown",
    value: `
**Superclass Reference**

The \`super\` keyword is used to refer to the superclass of the current class.

### Example:
\`\`\`flowwing
class Dog extends Animal {
  init(age:int) -> nthg {
  super(age)
  }
}
\`\`\`
    `,
  },
  input: {
    kind: "markdown",
    value: `
**Input Function**
The \`input\` function is used to read input from the user.

### Example:
\`\`\`flowwing
var name = input("Enter your name: ")
\`\`\`
### Return Type: \`str\`

### Properties:
- **Usage**: read input from the user
 `,
  },
  Int8: {
    kind: "markdown",
    value: `
**8-bit Integer Conversion**

The \`Int8\` function converts a value to an 8-bit integer.

### Example:
\`\`\`flowwing
var x: int8 = Int8("42")
\`\`\`
    `,
  },
  Int32: {
    kind: "markdown",
    value: `
**Integer Conversion**

The \`Int32\` function is used to convert a value to a 32-bit integer.

### Example:
\`\`\`flowwing
var number: int = Int32("123")
\`\`\`
    `,
  },
  Int64: {
    kind: "markdown",
    value: `
**64-bit Integer Conversion**

The \`Int64\` function converts a value to a 64-bit integer.

### Example:
\`\`\`flowwing
var n: int64 = Int64("1234567890")
\`\`\`
    `,
  },
  Char: {
    kind: "markdown",
    value: `
**Character Conversion**

The \`Char\` function converts a value to a character.

### Example:
\`\`\`flowwing
var c: char = Char(65)
\`\`\`
    `,
  },
  Decimal: {
    kind: "markdown",
    value: `
**Decimal Conversion**

The \`Decimal\` function is used to convert a value to a decimal.

### Example:
\`\`\`flowwing
var number: deci = Decimal("123.45")
\`\`\`
    `,
  },
  Decimal32: {
    kind: "markdown",
    value: `
**Decimal Conversion** 

The \`Decimal32\` function is used to convert a value to a 32-bit decimal.

### Example:
\`\`\`flowwing
var number:deci32 = Decimal32("123.45")
\`\`\`
    `,
  },
  String: {
    kind: "markdown",
    value: `
**String Conversion**

The \`String\` function is used to convert a value to a string.

### Example:
\`\`\`flowwing
var myStr = String(123)
\`\`\`
    `,
  },
  Bool: {
    kind: "markdown",
    value: `
**Boolean Conversion**

The \`Bool\` function is used to convert a value to a boolean.

### Example:
\`\`\`flowwing
var flag: bool = Bool(1)
\`\`\`
    `,
  },
};

export const inBuiltFunctionsCompletionItems: CompletionItem[] = [
  {
    label: "super",
    kind: CompletionItemKind.Function,
    data: {
      functionParametersTypes: ["class"],
      signatures: [
        {
          label: "super()",
          documentation: documentation.super,
        },
      ],
    },
    detail: "Superclass Reference",
    documentation: documentation.super,
  },
  {
    label: "print",
    kind: CompletionItemKind.Function,
    data: {
      functionParametersTypes: ["int", "int", "int", "str"],
      signatures: [
        {
          label: "print()",
          documentation: documentation.print,
        },
      ],
    },
    detail: "Print Function",
    documentation: documentation.print,
  },
  {
    label: "println",
    kind: CompletionItemKind.Function,
    data: {
      functionParametersTypes: ["int", "int", "int", "str"],
      signatures: [
        {
          label: "println()",
          documentation: documentation.println,
        },
      ],
    },
    detail: "Print with newline",
    documentation: documentation.println,
  },
  {
    label: "input",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "input()",
          documentation: documentation.input,
        },
      ],
    },
    detail: "Input Function",
    documentation: documentation.input,
  },
  {
    label: "Int8",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Int8(str) -> int8",
          documentation: documentation.Int8,
        },
      ],
    },
    detail: "8-bit Integer Conversion",
    documentation: documentation.Int8,
  },
  {
    label: "Int32",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Int32(str) -> int",
          documentation: documentation.Int32,
        },
      ],
    },
    detail: "Integer Conversion",
    documentation: documentation.Int32,
  },
  {
    label: "Int64",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Int64(str) -> int64",
          documentation: documentation.Int64,
        },
      ],
    },
    detail: "64-bit Integer Conversion",
    documentation: documentation.Int64,
  },
  {
    label: "Char",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Char(int8) -> char",
          documentation: documentation.Char,
        },
      ],
    },
    detail: "Character Conversion",
    documentation: documentation.Char,
  },
  {
    label: "Decimal",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Decimal()",
          documentation: documentation.Decimal,
        },
      ],
    },
    detail: "Decimal Conversion",
    documentation: documentation.Decimal,
  },
  {
    label: "Decimal32",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Decimal32()",
          documentation: documentation.Decimal32,
        },
      ],
    },
    detail: "Decimal32 Conversion",
    documentation: documentation.Decimal32,
  },
  {
    label: "String",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "String()",
          documentation: documentation.String,
        },
      ],
    },
    detail: "String Conversion",
    documentation: documentation.String,
  },
  {
    label: "Bool",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Bool()",
          documentation: documentation.Bool,
        },
      ],
    },
    detail: "Boolean Conversion",
    documentation: documentation.Bool,
  },
];
