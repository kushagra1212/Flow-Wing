import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const constantDeclareCompletionItems: CompletionItem[] = [
  {
    label: "const",
    kind: CompletionItemKind.Keyword,
    data: "const",
    detail: "Constant Declaration",
    documentation: {
      kind: "markdown",
      value: `
  **Constant Declaration**
  
  The \`const\` keyword is used to declare a constant in flowwing.
  
  ### Example Usage:
  \`\`\`flowwing
  const pi:deci = 3.14159265
  \`\`\`
  
  ### Properties:
  - **Usage**: Used for declaring variables that cannot be reassigned.
		`,
    },
  },
];
