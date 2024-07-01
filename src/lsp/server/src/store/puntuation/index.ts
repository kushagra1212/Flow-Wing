import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const punctuationCompletionItems: CompletionItem[] = [
  {
    label: "{",
    kind: CompletionItemKind.Text,
    data: "LeftCurlyBracket",
    detail: "Left Curly Bracket",
    insertText: "}",
    documentation: {
      kind: "markdown",
      value: `
**Left Curly Bracket**

The \`{\` symbol is used to denote the beginning of a block of code.

### Example:
\`\`\`ts
if (condition) {
  // Code block starts here
}
\`\`\`
      `,
    },
  },
  {
    label: "}",
    kind: CompletionItemKind.Text,
    data: "RightCurlyBracket",
    detail: "Right Curly Bracket",
    documentation: {
      kind: "markdown",
      value: `
**Right Curly Bracket**

The \`}\` symbol is used to denote the end of a block of code.

### Example:
\`\`\`ts
if (condition) {
  // Code block starts here
}
else {
  // Code block ends here
}
\`\`\`
      `,
    },
  },
  {
    label: "(",
    kind: CompletionItemKind.Text,
    data: "LeftParenthesis",
    detail: "Left Parenthesis",
    documentation: {
      kind: "markdown",
      value: `
**Left Parenthesis**

The \`(\` symbol is used to denote the beginning of a function call or expression grouping.

### Example:
\`\`\`ts
if (condition) {
  // Code block starts here
}
\`\`\`
      `,
    },
  },
  {
    label: ")",
    kind: CompletionItemKind.Text,
    data: "RightParenthesis",
    detail: "Right Parenthesis",
    documentation: {
      kind: "markdown",
      value: `
**Right Parenthesis**

The \`)\` symbol is used to denote the end of a function call or expression grouping.

### Example:
\`\`\`ts
if (condition) {
  // Code block starts here
}
\`\`\`
      `,
    },
  },
  {
    label: "[",
    kind: CompletionItemKind.Text,
    data: "LeftSquareBracket",
    detail: "Left Square Bracket",
    documentation: {
      kind: "markdown",
      value: `
**Left Square Bracket**

The \`[\` symbol is used to denote the beginning of an array or list literal.

### Example:
\`\`\`ts
var numbers:int[5] = [1, 2, 3, 4, 5]
\`\`\`
      `,
    },
  },
  {
    label: "]",
    kind: CompletionItemKind.Text,
    data: "RightSquareBracket",
    detail: "Right Square Bracket",
    documentation: {
      kind: "markdown",
      value: `
**Right Square Bracket**

The \`]\` symbol is used to denote the end of an array or list literal.

### Example:
\`\`\`ts
var numbers:int[5] = [1, 2, 3, 4, 5]
\`\`\`
      `,
    },
  },
  {
    label: ",",
    kind: CompletionItemKind.Text,
    data: "Comma",
    detail: "Comma",
    documentation: {
      kind: "markdown",
      value: `
**Comma**

The \`,\` symbol is used to separate items in a list or arguments in a function call.

### Example:
\`\`\`ts
var names:str[3] = ["Alice", "Bob", "Charlie"]
\`\`\`
      `,
    },
  },
  {
    label: ";",
    kind: CompletionItemKind.Text,
    data: "Semicolon",
    detail: "Semicolon",
    documentation: {
      kind: "markdown",
      value: `
**Semicolon**

The \`;\` symbol is used to terminate a statement or expression.

### Example:
\`\`\`ts
var x = 10;
\`\`\`
      `,
    },
  },
  {
    label: ":",
    kind: CompletionItemKind.Text,
    data: "Colon",
    detail: "Colon",
    documentation: {
      kind: "markdown",
      value: `
**Colon**

The \`:\` symbol is used in type annotations or to separate key-value pairs in maps or dictionaries.

### Example:
\`\`\`ts
type Person = {
  name:str,
  age:int
}
\`\`\`
      `,
    },
  },
  {
    label: ".",
    kind: CompletionItemKind.Text,
    data: "Dot",
    detail: "Dot",
    documentation: {
      kind: "markdown",
      value: `
**Dot**

The \`.\` symbol is used to access fields or methods of objects.

### Example:
\`\`\`ts
var person:Person = { name: "Alice", age: 30 }
var name = person.name
\`\`\`
      `,
    },
  },
];
