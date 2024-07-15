import {
  CompletionItem,
  CompletionItemKind,
  MarkupContent,
} from "vscode-languageserver";

const documentation: Record<
  "print" | "super" | "input" | "Int32" | "Decimal" | "String" | "Bool",
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
  Int32: {
    kind: "markdown",
    value: `
**Integer Conversion**

The \`Int32\` function is used to convert a value to a 32-bit integer.

### Example:
\`\`\`flowwing
var number = Int32("123")
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
var number = Decimal("123.45")
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
var flag = Bool(1)
\`\`\`
    `,
  },
};

export const inBuiltFunctionsCompletionItems: CompletionItem[] = [
  {
    label: "super",
    kind: CompletionItemKind.Function,
    data: {
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
    label: "Int32",
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: "Int32()",
          documentation: documentation.Int32,
        },
      ],
    },
    detail: "Integer Conversion",
    documentation: documentation.Int32,
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
