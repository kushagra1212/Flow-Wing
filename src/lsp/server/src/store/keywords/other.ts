import { CompletionItem, CompletionItemKind } from "vscode-languageserver";

export const otherCompletionItems: CompletionItem[] = [
  {
    label: "fun",
    kind: CompletionItemKind.Keyword,
    data: "fun",
    detail: "Function Declaration",
    insertText: `fun funName() -> returnType {
	/; Function body
}`,
    documentation: {
      kind: "markdown",
      value: `
**Function Declaration**

The \`fun\` keyword is used to declare a function.

### Example:
\`\`\`ts
fun isPrime(n) -> bool {
  /; Function body here
}
\`\`\`
      `,
    },
  },
  {
    label: "type",
    kind: CompletionItemKind.Keyword,
    data: "type",
    detail: "Type Declaration",
    insertText: `type TypeName = {
	/; Type body
}`,
    documentation: {
      kind: "markdown",
      value: `
**Type Declaration**

The \`type\` keyword is used to declare a custom type.

### Example:
\`\`\`ts
type Person = {
  name:str,
  age:int,
  address:str
}
\`\`\`
      `,
    },
  },
  {
    label: "class",
    kind: CompletionItemKind.Keyword,
    data: "class",
    detail: "Class Declaration",
    insertText: `class ClassName {
	/; Class body
	/; Class Variables
	var 

	/; Initializer
	init() -> nthg {

	}
}
	`,
    documentation: {
      kind: "markdown",
      value: `
**Class Declaration**

The \`class\` keyword is used to declare a class.

### Example:
\`\`\`ts
class Animal {
  var age:int 
  var species:str 
  init(age:int) -> nthg {
    self.age = age
  }
  getAge() -> int {
    return self.age
  }
  printSpecies() -> nthg { 
    print("Species: ", self.species)
  }
}
\`\`\`
      `,
    },
  },
  {
    label: "extends",
    kind: CompletionItemKind.Keyword,
    data: "extends",
    detail: "Class Inheritance",
    documentation: {
      kind: "markdown",
      value: `
**Class Inheritance**

The \`extends\` keyword is used to declare a class that inherits from another class.

### Example:
\`\`\`ts
class Dog extends Animal {
  var breed:str 

  init(age:int) -> nthg {
    super(age)
  }

  getAge() -> int {
    return 7 * self.age  /; Dog years conversion
  }
  printBreed() -> nthg { 
    print("Breed: ", self.breed)
  }
}
\`\`\`
      `,
    },
  },
  {
    label: "for",
    kind: CompletionItemKind.Keyword,
    data: "for",
    detail: "For Loop",
    documentation: {
      kind: "markdown",
      value: `
**For Loop**

The \`for\` keyword is used to declare a for loop.

### Example:
\`\`\`ts
for (var i = 0 to 5 : 2) {
  /; Code to execute in the loop
}
\`\`\`
      `,
    },
  },
  {
    label: "while",
    kind: CompletionItemKind.Keyword,
    data: "while",
    detail: "While Loop",
    documentation: {
      kind: "markdown",
      value: `
**While Loop**

The \`while\` keyword is used to declare a while loop.

### Example:
\`\`\`ts
while(x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  print(x + "\\n")
  if (x == 4) {
    break
  }
}
\`\`\`
      `,
    },
  },
  {
    label: "break",
    kind: CompletionItemKind.Keyword,
    data: "break",
    detail: "Break Statement",
    documentation: {
      kind: "markdown",
      value: `
**Break Statement**

The \`break\` keyword is used to exit a loop prematurely.

### Example:
\`\`\`ts
for var i = 0 to 5 {
  if i == 3 {
    break
  }
}
\`\`\`
      `,
    },
  },
  {
    label: "continue",
    kind: CompletionItemKind.Keyword,
    data: "continue",
    detail: "Continue Statement",
    documentation: {
      kind: "markdown",
      value: `
**Continue Statement**

The \`continue\` keyword is used to skip the current iteration of a loop and proceed to the next iteration.

### Example:
\`\`\`ts
while(x < 5) {
  x = x + 1
  if (x == 3) {
    continue
  }
  print(x + "\\n")
}
\`\`\`
      `,
    },
  },
  {
    label: "return",
    kind: CompletionItemKind.Keyword,
    data: "return",
    detail: "Return Statement",
    documentation: {
      kind: "markdown",
      value: `
**Return Statement**

The \`return\` keyword is used to return a value from a function.

### Example:
\`\`\`ts
fun getAge() -> int {
  return self.age
}
\`\`\`
      `,
    },
  },
  {
    label: "inout",
    kind: CompletionItemKind.Keyword,
    data: "inout",
    detail: "Inout Keyword",
    documentation: {
      kind: "markdown",
      value: `
**Inout Keyword**

The \`inout\` keyword is used to declare an input and output parameter in a function.

### Properties:
- **Usage**: allow parameters to be passed by reference

### Example:
\`\`\`ts
fun getAge(inout age:int) -> int {
  age = age + 1
  return age
}
\`\`\`
      `,
    },
  },
];
