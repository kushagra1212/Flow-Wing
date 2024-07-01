import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const inBuiltFunctionsCompletionItems: CompletionItem[] = [
  {
    label: "super",
    kind: CompletionItemKind.Function,
    data: "super",
    detail: "Superclass Reference",
    documentation: {
      kind: "markdown",
      value: `
**Superclass Reference**
	
The \`super\` keyword is used to refer to the superclass of the current class.
	
### Example:
\`\`\`ts
	class Dog extends Animal {
	  init(age:int) -> nthg {
		super(age)
	  }
	}
\`\`\`
		  `,
    },
  },
  {
    label: "print",
    kind: CompletionItemKind.Function,
    data: "print",
    detail: "Print Function",
    documentation: {
      kind: "markdown",
      value: `
**Print Function**
	
The \`print\` function is used to print a message to the console.
	
### Example:
\`\`\`ts
	print("Hello, World!")
	print(2, 3, 4,"Hello")
\`\`\`
		  `,
    },
  },
  {
    label: "input",
    kind: CompletionItemKind.Function,
    data: "input",
    detail: "Input Function",
    documentation: {
      kind: "markdown",
      value: `
**Input Function**
	
The \`input\` function is used to read input from the user.
	
### Example:
\`\`\`ts
	var name = input("Enter your name: ")
\`\`\` `,
    },
  },
  {
    label: "Int32",
    kind: CompletionItemKind.Function,
    data: "Int32",
    detail: "Integer Conversion",
    documentation: {
      kind: "markdown",
      value: `
**Integer Conversion**
	
The \`Int32\` function is used to convert a value to a 32-bit integer.
	
### Example:
\`\`\`ts
	var number = Int32("123")
\`\`\`
		  `,
    },
  },
  {
    label: "Decimal",
    kind: CompletionItemKind.Function,
    data: "Decimal",
    detail: "Decimal Conversion",
    documentation: {
      kind: "markdown",
      value: `
**Decimal Conversion**
	
The \`Decimal\` function is used to convert a value to a decimal.
	
### Example:
\`\`\`ts
	var number = Decimal("123.45")
\`\`\`
		  `,
    },
  },
  {
    label: "String",
    kind: CompletionItemKind.Function,
    data: "String",
    detail: "String Conversion",
    documentation: {
      kind: "markdown",
      value: `
**String Conversion**
	
The \`String\` function is used to convert a value to a string.
	
### Example:
\`\`\`ts
	var str = String(123)
\`\`\`
		  `,
    },
  },
  {
    label: "Bool",
    kind: CompletionItemKind.Function,
    data: "Bool",
    detail: "Boolean Conversion",
    documentation: {
      kind: "markdown",
      value: `
**Boolean Conversion**
	
The \`Bool\` function is used to convert a value to a boolean.
	
### Example:
\`\`\`ts
	var flag = Bool(1)
\`\`\`
		  `,
    },
  },
];
