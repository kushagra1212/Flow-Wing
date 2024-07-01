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
**Conditional Statement**
	
The \`if\` keyword is used to declare a conditional statement.
	
	### Example:
\`\`\`ts
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
**Else If Statement**
	
The \`or if\` keyword is used to declare an else if statement.
	
### Example:
\`\`\`ts
	if (condition1) {
	  /; Code to execute if condition1 is true
	} or if (condition2) {
	  /; Code to execute if condition2 is true
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
	
The \`else\` keyword is used to declare an else statement.
	
### Example:
\`\`\`ts
	if (condition) {
	  /; Code to execute if the condition is true
	} else {
	  /; Code to execute if the condition is false
	}
\`\`\`
		  `,
    },
  },
];
