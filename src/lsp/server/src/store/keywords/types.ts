import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const typesCompletionItems: CompletionItem[] = [
  {
    label: "int",
    kind: CompletionItemKind.TypeParameter,
    data: "int",
    detail: "Integer Data Type",
    documentation: {
      kind: "markdown",
      value: `
**Integer Data Type**

The \`int\` datatype represents a 32-bit signed integer. It is used to store numeric values without any fractional components.

### Example Usage:
\`\`\`ts
var x:int = 42
\`\`\`

### Properties:
- **Range**: -2,147,483,648 to 2,147,483,647
- **Default Value**: 0
- **Usage**: Commonly used for counting, indexing, and simple arithmetic operations.
      `,
    },
  },
  {
    label: "deci",
    kind: CompletionItemKind.TypeParameter,
    data: "deci",
    detail: "Decimal Data Type",
    documentation: {
      kind: "markdown",
      value: `
**Decimal Data Type**

The \`deci\` datatype is used to store floating-point numbers with decimal points.

### Example Usage:
\`\`\`ts
var y:deci = 3.14
\`\`\`

### Properties:
- **Precision**: Can handle a wide range of decimal values
- **Usage**: Commonly used for financial calculations, scientific computations, and anywhere precision with decimals is required.
      `,
    },
  },
  {
    label: "bool",
    kind: CompletionItemKind.TypeParameter,
    data: "bool",
    detail: "Boolean Data Type",
    documentation: {
      kind: "markdown",
      value: `
**Boolean Data Type**

The \`bool\` datatype represents a boolean value, which can be either \`true\` or \`false\`.

### Example Usage:
\`\`\`ts
var isActive:bool = true
\`\`\`

### Properties:
- **Values**: \`true\` or \`false\`
- **Usage**: Commonly used for conditional statements, flags, and toggles.
      `,
    },
  },
  {
    label: "str",
    kind: CompletionItemKind.TypeParameter,
    data: "str",
    detail: "String Data Type",
    documentation: {
      kind: "markdown",
      value: `
**String Data Type**

The \`str\` datatype is used to store sequences of characters.

### Example Usage:
\`\`\`ts
var name:str = "ts"
\`\`\`

### Properties:
- **Usage**: Commonly used for text processing, displaying messages, and storing any form of textual data.
      `,
    },
  },
  {
    label: "nthg",
    kind: CompletionItemKind.TypeParameter,
    data: "nthg",
    detail: "Nothing Data Type",
    documentation: {
      kind: "markdown",
      value: `
**Nothing Data Type**

The \`nthg\` datatype represents the absence of a value, often used as a return type for functions that do not return any value.

### Example Usage:
\`\`\`ts
fun doNothing() -> nthg {
  /; This function does not return anything
}
\`\`\`

### Properties:
- **Usage**: Used to indicate no return value from a function.
      `,
    },
  },
  {
    label: "deci32",
    kind: CompletionItemKind.TypeParameter,
    data: "deci32",
    detail: "32-bit Decimal Data Type",
    documentation: {
      kind: "markdown",
      value: `
**32-bit Decimal Data Type**

The \`deci32\` datatype represents a 32-bit floating-point number, used for storing decimal values with less precision compared to \`deci\`.

### Example Usage:
\`\`\`ts
var z:deci32 = 1.23
\`\`\`

### Properties:
- **Precision**: Lower precision compared to \`deci\`
- **Usage**: Suitable for scenarios where memory usage is a concern and high precision is not required.
      `,
    },
  },
];