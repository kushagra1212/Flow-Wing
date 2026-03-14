import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const conditionalCompletionItems: CompletionItem[] = [
  {
    label: "if",
    kind: CompletionItemKind.Keyword,
    data: "if",
    detail: "Conditional Statement",
    documentation: {
      kind: "markdown",
      value: `
**Conditional Statement (if)**

The \`if\` keyword starts a conditional block. The block executes only when the condition is true.

### Example:
\`\`\`flowwing
if (condition) {
  /; Code to execute if the condition is true
}
\`\`\`
      `,
    },
  },
  {
    label: "or if",
    kind: CompletionItemKind.Keyword,
    data: "or if",
    detail: "Else If Statement",
    documentation: {
      kind: "markdown",
      value: `
**Else If Statement (or if)**

The \`or if\` keyword adds an else-if branch. Use it between \`if\` and \`else\` to chain multiple conditions.

### Example:
\`\`\`flowwing
if (condition1) {
  /; Code if condition1 is true
} or if (condition2) {
  /; Code if condition2 is true
} else {
  /; Code if neither is true
}
\`\`\`
      `,
    },
  },
  {
    label: "else",
    kind: CompletionItemKind.Keyword,
    data: "else",
    detail: "Else Statement",
    documentation: {
      kind: "markdown",
      value: `
**Else Statement**

The \`else\` keyword provides the fallback block when all \`if\` and \`or if\` conditions are false.

### Example:
\`\`\`flowwing
if (condition) {
  /; Code if condition is true
} else {
  /; Code if condition is false
}
\`\`\`
      `,
    },
  },
  {
    label: "switch",
    kind: CompletionItemKind.Keyword,
    data: "switch",
    detail: "Switch Statement",
    documentation: {
      kind: "markdown",
      value: `
**Switch Statement**

The \`switch\` keyword is used to declare a switch statement.

### Example:
\`\`\`flowwing
switch (condition) {
  case 1:
    /; Code to execute if the condition is 1
  case 2:
    /; Code to execute if the condition is 2
  default:
    /; Code to execute if the condition is neither 1 nor 2
}
\`\`\`
      `,
    },
  },
  {
    label: "case",
    kind: CompletionItemKind.Keyword,
    data: "case",
    detail: "Case Statement",
    documentation: {
      kind: "markdown",
      value: `
**Case Statement**  

The \`case\` keyword is used to declare a case statement.
  
### Example:
\`\`\`flowwing
switch (condition) {
  case 1:
    /; Code to execute if the condition is 1
  case 2:
    /; Code to execute if the condition is 2
  default:
    /; Code to execute if the condition is neither 1 nor 2
}
\`\`\`
      `,
    },
  },
  {
    label: "default",
    kind: CompletionItemKind.Keyword,
    data: "default",
    detail: "Default Statement",
    documentation: {
      kind: "markdown",
      value: `
**Default Statement**

The \`default\` keyword is used to declare a default statement. 

### Example:
\`\`\`flowwing
switch (condition) {
  case 1:
    /; Code to execute if the condition is 1
  case 2:
    /; Code to execute if the condition is 2
  default:
    /; Code to execute if the condition is neither 1 nor 2
}
\`\`\`
      `,
    },
  },
  {
    label: "?",
    kind: CompletionItemKind.Keyword,
    data: "questionMark",
    detail: "Question Mark",
    documentation: {
      kind: "markdown",
      value: `
**Question Mark**

The \`?\` symbol is used to denote the ternary operator.

### Example:
\`\`\`flowwing
var x:str = true ? "Hello" : "Bye"
\`\`\`
      `,
    },
  },
];
