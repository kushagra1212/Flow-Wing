import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const variableDeclareCompletionItems: CompletionItem[] = [
  {
    label: "var",
    kind: CompletionItemKind.Keyword,
    data: "var",
    detail: "Variable Declaration",
    documentation: {
      kind: "markdown",
      value: `
  **Variable Declaration**
  
  The \`var\` keyword is used to declare a variable in ts.
  
  ### Example Usage:
  \`\`\`ts
  var age:int = 30
  \`\`\`
  
  ### Properties:
  - **Usage**: Used for declaring variables that can be reassigned.
		`,
    },
  },
];
