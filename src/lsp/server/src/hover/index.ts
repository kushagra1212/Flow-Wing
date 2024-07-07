import * as fs from "fs";
import {
  ArrayTypeExpression,
  BracketedExpression,
  CallExpression,
  ClassStatement,
  ConstKeyword,
  CustomTypeStatement,
  FunctionDeclaration,
  IdentifierToken,
  LiteralExpression,
  ObjectTypeExpression,
  PrimitiveTypeExpression,
  RootObject,
  TypeExpression,
  VariableDeclaration,
  VarKeyword,
} from "./types";
import { HoverStack, Stack } from "./stack";
import {
  CompletionItem,
  CompletionItemKind,
  ParameterInformation,
  Position,
} from "vscode-languageserver";
import { fileUtils } from "../utils/fileUtils";
import { getMarkTSSyntaxHighlightMarkdown } from "../utils";

// Define interfaces for the JSON structure (if known parts are provided)

// Define the path to the JSON file
const filePath =
  "/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/a.json";

const getBrackedExpressionAsString = (
  bracketedExpression: BracketedExpression
): string => {
  let bracketedExpressionString = "";

  if (bracketedExpression?.[0]?.["LiteralExpression"]?.[0]) {
    bracketedExpressionString +=
      getLiteralExpressionAsString(
        bracketedExpression[0]["LiteralExpression"][0]
      ) + ": ";
  }

  bracketedExpressionString += getTypeExpressionAsString(
    bracketedExpression[1]
  );

  return bracketedExpressionString;
};

const parseCustomTypeStatement = (
  customTypeStatement: CustomTypeStatement
): CompletionItem => {
  let customTypeStatementString = "type ";

  if (customTypeStatement[0]["LiteralExpression"]) {
    customTypeStatementString +=
      getLiteralExpressionAsString(
        customTypeStatement[0]["LiteralExpression"][0]
      ) + " = {\n";
  }

  for (let i = 1; i < customTypeStatement.length; i++) {
    customTypeStatementString += "\t";
    if (customTypeStatement[i]["BracketedExpression"]) {
      customTypeStatementString +=
        getBrackedExpressionAsString(
          customTypeStatement[i]["BracketedExpression"]
        ) + (i == customTypeStatement.length - 1 ? "\n" : ",\n");
    }
  }
  customTypeStatementString += "}\n";

  const typeName = getTypeNameFromCustomTypeStatement(customTypeStatement);

  return {
    label: typeName,
    kind: CompletionItemKind.TypeParameter,
    data: typeName,
    detail: "Custom Type",
    documentation: {
      kind: "markdown",
      value: getMarkTSSyntaxHighlightMarkdown(customTypeStatementString),
    },
  };
};

const getTypeNameFromCustomTypeStatement = (
  customTypeStatement: CustomTypeStatement
): string => {
  if (!customTypeStatement[0]["LiteralExpression"]) {
    return "";
  }

  return getLiteralExpressionAsString(
    customTypeStatement[0]["LiteralExpression"][0]
  );
};

const getPrimitiveTypeAsString = (
  primitiveTypeExpression: PrimitiveTypeExpression
): string => {
  const typeMap: { [key: string]: string } = {
    Int32Keyword: "Int32Keyword",
    DeciKeyword: "DeciKeyword",
    Deci32Keyword: "Deci32Keyword",
    StrKeyword: "StrKeyword",
    BoolKeyword: "BoolKeyword",
    NthgKeyword: "NthgKeyword",
  };

  for (const key in typeMap) {
    if (typeMap[key] in primitiveTypeExpression) {
      return (primitiveTypeExpression as any)[typeMap[key]].value;
    }
  }

  return "";
};

const getLiteralExpressionAsString = (
  literalExpression: LiteralExpression
): string => {
  const typeMap: { [key: string]: string } = {
    NumberToken: "NumberToken",
    IdentifierToken: "IdentifierToken",
  };

  for (const key in typeMap) {
    if (typeMap[key] in literalExpression) {
      return (literalExpression as any)[typeMap[key]].value;
    }
  }

  return "";
};

const getArrayTypeAsString = (
  arrayTypeExpression: ArrayTypeExpression
): string => {
  const expression = arrayTypeExpression[0];
  let typeName = "";

  if ("ObjectTypeExpression" in expression) {
    typeName = getObjectTypeAsString(expression["ObjectTypeExpression"][0]);
  } else {
    typeName = getPrimitiveTypeAsString(expression);
  }

  if (typeName) {
    let indexes = "";
    for (let i = 1; i < arrayTypeExpression.length; i++) {
      const literalExpression = arrayTypeExpression[i];
      indexes +=
        "[" +
        getLiteralExpressionAsString(
          literalExpression["LiteralExpression"][0]
        ) +
        "]";
    }

    return typeName + indexes;
  }

  return "";
};

const getObjectTypeAsString = (
  objectTypeExpression: ObjectTypeExpression
): string => {
  const literalExpression = objectTypeExpression["LiteralExpression"][0];
  return getLiteralExpressionAsString(literalExpression);
};

const getTypeExpressionAsString = (typeExpr: TypeExpression): string => {
  if (
    typeExpr["PrimitiveTypeExpression"] &&
    typeExpr["PrimitiveTypeExpression"].length
  ) {
    return getPrimitiveTypeAsString(typeExpr["PrimitiveTypeExpression"][0]);
  } else if (typeExpr["ArrayTypeExpression"]) {
    return getArrayTypeAsString(typeExpr["ArrayTypeExpression"]);
  } else if (
    typeExpr["ObjectTypeExpression"] &&
    typeExpr["ObjectTypeExpression"].length
  ) {
    return getObjectTypeAsString(typeExpr["ObjectTypeExpression"][0]);
  }

  return "";
};

const getVarorConstAsString = (varOrConst: {
  VarKeyword?: VarKeyword;
  ConstKeyword?: ConstKeyword;
}): string => {
  if (varOrConst["VarKeyword"]) {
    return varOrConst["VarKeyword"].value;
  } else if (varOrConst["ConstKeyword"]) {
    return varOrConst["ConstKeyword"].value;
  }

  return "";
};

const parseVariableDeclaration = (
  variableDeclaration: VariableDeclaration
): CompletionItem => {
  let variableDeclarationStr = "";
  let index = 0;
  if (
    variableDeclaration[index]["VarKeyword"] ||
    variableDeclaration[index]["ConstKeyword"]
  )
    variableDeclarationStr +=
      getVarorConstAsString(variableDeclaration[index++]) + " ";

  if (variableDeclaration[index]["InOutKeyword"])
    variableDeclarationStr +=
      variableDeclaration[index++]["InOutKeyword"].value + " ";

  if (variableDeclaration[index]["IdentifierToken"])
    variableDeclarationStr +=
      variableDeclaration[index++]["IdentifierToken"].value + ": ";

  if (variableDeclaration[index]["Askeyword"])
    variableDeclarationStr +=
      variableDeclaration[index++]["Askeyword"].value + " ";

  if (variableDeclaration[index])
    variableDeclarationStr += getTypeExpressionAsString(
      variableDeclaration[index] as TypeExpression
    );
  else variableDeclarationStr += "unknown";
  const variableName =
    getVariableNameFromVariableDeclaration(variableDeclaration);

  return {
    label: variableName,
    kind: CompletionItemKind.Variable,
    data: "variable",
    detail: variableDeclarationStr,
    documentation: {
      kind: "markdown",
      value: getMarkTSSyntaxHighlightMarkdown(variableDeclarationStr),
    },
  };
};

const getVariableNameFromVariableDeclaration = (
  variableDeclaration: VariableDeclaration
): string => {
  let index = 0;
  if (
    variableDeclaration[index]["VarKeyword"] ||
    variableDeclaration[index]["ConstKeyword"]
  )
    index++;

  if (variableDeclaration[index]["InOutKeyword"]) index++;

  return variableDeclaration[index]["IdentifierToken"].value;
};

const parseFunctionDeclaration = (
  functionDeclaration: FunctionDeclaration
): CompletionItem => {
  let functionDeclarationStr = "";
  let index = 0;

  if (functionDeclaration[index]["FunctionKeyword"])
    functionDeclarationStr +=
      functionDeclaration[index++]["FunctionKeyword"].value + " ";
  else functionDeclarationStr += "fun ";

  if (functionDeclaration[index]["IdentifierToken"])
    functionDeclarationStr +=
      functionDeclaration[index++]["IdentifierToken"].value;

  functionDeclarationStr += "(";
  let hasCommaAtEnd = false;

  const functionParameters: ParameterInformation[] = [];
  while (functionDeclaration[index]["VariableDeclaration"]) {
    const functionParameter = parseVariableDeclaration(
      functionDeclaration[index++]["VariableDeclaration"]
    );
    functionDeclarationStr += functionParameter.detail + ", ";
    functionParameters.push({
      label: functionParameter.label,
      documentation: functionParameter.documentation,
    });
    hasCommaAtEnd = true;
  }

  if (hasCommaAtEnd)
    functionDeclarationStr = functionDeclarationStr.slice(
      0,
      functionDeclarationStr.length - 2
    );

  functionDeclarationStr += ") -> ";
  while (index < functionDeclaration.length) {
    if (functionDeclaration[index]["Askeyword"])
      functionDeclarationStr +=
        functionDeclaration[index]["Askeyword"].value + " ";

    if (functionDeclaration[index]["DeclKeyword"])
      functionDeclarationStr +=
        functionDeclaration[index]["DeclKeyword"].value + " ";

    if (functionDeclaration[index])
      functionDeclarationStr += getTypeExpressionAsString(
        functionDeclaration[index]
      );
    index++;
  }

  const functionName =
    getFunctionNameFromFunctionDeclaration(functionDeclaration);

  return {
    label: functionName,
    kind: CompletionItemKind.Function,
    data: {
      signatures: [
        {
          label: functionDeclarationStr,
          parameters: functionParameters,
        },
      ],
    },
    detail: functionDeclarationStr,
    documentation: {
      kind: "markdown",
      value: getMarkTSSyntaxHighlightMarkdown(functionDeclarationStr),
    },
  };
};

const getFunctionNameFromFunctionDeclaration = (
  functionDeclaration: FunctionDeclaration
): string => {
  if (functionDeclaration[0]["IdentifierToken"])
    return functionDeclaration[0]["IdentifierToken"].value;

  if (!functionDeclaration[1]["IdentifierToken"]) return "";

  return functionDeclaration[1]["IdentifierToken"].value;
};

const getClassStatementsString = (
  classDeclaration: ClassStatement
): CompletionItem => {
  let classDeclarationStr = "";

  if (classDeclaration[0]["ClassKeyword"])
    classDeclarationStr += classDeclaration[0]["ClassKeyword"].value + " ";

  if (classDeclaration[1]["IdentifierToken"])
    classDeclarationStr += classDeclaration[1]["IdentifierToken"].value;

  const className = getClassNameFromClassStatement(classDeclaration);
  return {
    label: className,
    kind: CompletionItemKind.Class,
    data: "class",
    detail: classDeclarationStr,
    documentation: {
      kind: "markdown",
      value: getMarkTSSyntaxHighlightMarkdown(classDeclarationStr),
    },
  };
};

const getClassNameFromClassStatement = (
  classDeclaration: ClassStatement
): string => {
  if (!classDeclaration[1]["IdentifierToken"]) return "";

  return classDeclaration[1]["IdentifierToken"].value;
};

const parseCallExpression = (
  callExpression: CallExpression
): CompletionItem => {
  let callExpressionStr = "",
    index = 0;

  if (callExpression[index]["IdentifierToken"])
    callExpressionStr += callExpression[index++]["IdentifierToken"].value;

  callExpressionStr += "(";
  let hasCommaAtEnd = false;
  while (callExpression[index]["VariableDeclaration"]) {
    callExpressionStr +=
      parseVariableDeclaration(callExpression[index++]["VariableDeclaration"])
        .detail + ", ";
    hasCommaAtEnd = true;
  }

  if (hasCommaAtEnd)
    callExpressionStr = callExpressionStr.slice(
      0,
      callExpressionStr.length - 2
    );

  callExpressionStr += ")";
  const callerName = getCallExpressionCallerName(callExpression);
  return {
    label: callerName,
    kind: CompletionItemKind.Function,
    data: callerName,
    detail: callExpressionStr,
    documentation: {
      kind: "markdown",
      value: getMarkTSSyntaxHighlightMarkdown(callExpressionStr),
    },
  };
};

const getCallExpressionCallerName = (
  callExpression: CallExpression
): string => {
  if (!callExpression[0]["IdentifierToken"]) return "";

  return callExpression[0]["IdentifierToken"].value;
};

const reverseStack = <T>(stack: Stack<T>): Stack<T> => {
  const result = new Stack<T>();
  while (!stack.isEmpty()) {
    result.push(stack.pop());
  }
  return result;
};

const getAllCompletionItems = (
  currentStack: Stack<HoverStack>
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);
  const result: CompletionItem[] = [];
  const mapping: HoverStack = {
    variableDeclarations: new Map(),
    customTypes: new Map(),
    classes: new Map(),
    functions: new Map(),
    callExpression: new Map(),
  };
  while (!reversedStack.isEmpty()) {
    const current = reversedStack.pop();

    current.variableDeclarations.forEach((value, key) => {
      mapping.variableDeclarations.set(key, value);
    });

    current.customTypes.forEach((value, key) => {
      mapping.customTypes.set(key, value);
    });

    current.classes.forEach((value, key) => {
      mapping.classes.set(key, value);
    });

    current.functions.forEach((value, key) => {
      mapping.functions.set(key, value);
    });

    current.callExpression.forEach((value, key) => {
      mapping.callExpression.set(key, value);
    });
  }

  if (mapping.variableDeclarations)
    result.push(...Array.from(mapping.variableDeclarations.values()));

  if (mapping.customTypes)
    result.push(...Array.from(mapping.customTypes.values()));

  if (mapping.classes) result.push(...Array.from(mapping.classes.values()));

  if (mapping.functions) result.push(...Array.from(mapping.functions.values()));

  if (mapping.callExpression)
    result.push(...Array.from(mapping.callExpression.values()));

  return result;
};

const getAllCompletionItemsOfIdentifier = (
  currentStack: Stack<HoverStack>,
  identifier: string
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);
  const result: CompletionItem[] = [];

  while (!reversedStack.isEmpty()) {
    const current = reversedStack.pop();
    if (current.variableDeclarations.get(identifier))
      result.push(current.variableDeclarations.get(identifier));

    if (current.customTypes.get(identifier))
      result.push(current.customTypes.get(identifier));

    if (current.functions.get(identifier))
      result.push(current.functions.get(identifier));

    if (current.classes.get(identifier))
      result.push(current.classes.get(identifier));

    if (current.callExpression.get(identifier))
      result.push(current.callExpression.get(identifier));
  }

  return result;
};

// Function to read the JSON file and process it
export async function readAndProcessSyntaxJSON(
  filePath: string,
  postion: Position
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const jsonObject: RootObject = JSON.parse(syntaxTreeAsString);
    const hoverStack = new Stack<HoverStack>();
    hoverStack.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
    });

    // Recursive function to traverse the JSON structure
    const traverseJson = function (obj: any): CompletionItem[] {
      if (Array.isArray(obj)) {
        for (const item of obj) {
          const result = traverseJson(item);
          if (result.length) return result;
        }
      } else if (typeof obj === "object" && obj !== null) {
        if (obj["VariableDeclaration"]) {
          hoverStack
            .peek()
            .variableDeclarations.set(
              getVariableNameFromVariableDeclaration(
                obj["VariableDeclaration"]
              ),
              parseVariableDeclaration(obj["VariableDeclaration"])
            );
        } else if (obj["CallExpression"]) {
          hoverStack
            .peek()
            .callExpression.set(
              getCallExpressionCallerName(obj["CallExpression"]),
              parseCallExpression(obj["CallExpression"])
            );
        } else if (obj["CustomTypeStatement"]) {
          hoverStack
            .peek()
            .customTypes.set(
              getTypeNameFromCustomTypeStatement(obj["CustomTypeStatement"]),
              parseCustomTypeStatement(
                obj["CustomTypeStatement"] as CustomTypeStatement
              )
            );
        } else if (obj["FunctionDeclarationSyntax"]) {
          hoverStack
            .peek()
            .functions.set(
              getFunctionNameFromFunctionDeclaration(
                obj["FunctionDeclarationSyntax"]
              ),
              parseFunctionDeclaration(
                obj["FunctionDeclarationSyntax"] as FunctionDeclaration
              )
            );
        } else if (obj["ClassStatement"]) {
          hoverStack
            .peek()
            .functions.set(
              getClassNameFromClassStatement(obj["ClassStatement"]),
              getClassStatementsString(obj["ClassStatement"] as ClassStatement)
            );
        } else if (obj["IdentifierToken"]) {
          const identifierToken: IdentifierToken = obj["IdentifierToken"];
          if (
            identifierToken.columnNumber === postion.character &&
            identifierToken.lineNumber === postion.line
          ) {
            return getAllCompletionItemsOfIdentifier(
              hoverStack,
              identifierToken.value
            );
          }
        }
        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        ) {
          hoverStack.push({
            variableDeclarations: new Map(),
            customTypes: new Map(),
            classes: new Map(),
            functions: new Map(),
            callExpression: new Map(),
          });
        }

        for (const value of Object.values(obj)) {
          const result = traverseJson(value);

          if (result.length) return result;
        }
        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        ) {
          hoverStack.pop();
        }
      }
      return [];
    };

    // Traverse the JSON structure and get the result
    return traverseJson(jsonObject);
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
}

export async function handleOnCompletion(
  filePath: string,
  postion: Position
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const jsonObject: RootObject = JSON.parse(syntaxTreeAsString);
    const hoverStack = new Stack<HoverStack>();
    hoverStack.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
    });

    let result: CompletionItem[] = [];
    // Recursive function to traverse the JSON structure
    const traverseJson = function (obj: any): boolean {
      if (Array.isArray(obj)) {
        for (const item of obj) {
          const res = traverseJson(item);

          if (res) return true;
        }
      } else if (typeof obj === "object" && obj !== null) {
        if (obj["VariableDeclaration"]) {
          hoverStack
            .peek()
            .variableDeclarations.set(
              getVariableNameFromVariableDeclaration(
                obj["VariableDeclaration"]
              ),
              parseVariableDeclaration(obj["VariableDeclaration"])
            );
        } else if (obj["CallExpression"]) {
          hoverStack
            .peek()
            .callExpression.set(
              getCallExpressionCallerName(obj["CallExpression"]),
              parseCallExpression(obj["CallExpression"])
            );
        } else if (obj["CustomTypeStatement"]) {
          hoverStack
            .peek()
            .customTypes.set(
              getTypeNameFromCustomTypeStatement(obj["CustomTypeStatement"]),
              parseCustomTypeStatement(
                obj["CustomTypeStatement"] as CustomTypeStatement
              )
            );
        } else if (obj["FunctionDeclarationSyntax"]) {
          hoverStack
            .peek()
            .functions.set(
              getFunctionNameFromFunctionDeclaration(
                obj["FunctionDeclarationSyntax"]
              ),
              parseFunctionDeclaration(
                obj["FunctionDeclarationSyntax"] as FunctionDeclaration
              )
            );
        } else if (obj["ClassStatement"]) {
          hoverStack
            .peek()
            .functions.set(
              getClassNameFromClassStatement(obj["ClassStatement"]),
              getClassStatementsString(obj["ClassStatement"] as ClassStatement)
            );
        }
        if (obj["EndOfFileToken"]) {
          result = getAllCompletionItems(hoverStack);
          return true;
        }

        if (obj["OpenBraceToken"]) {
          const lineNumberCloseBraceToken = obj["OpenBraceToken"]["lineNumber"];
          const columnNumberCloseBraceToken =
            obj["OpenBraceToken"]["columnNumber"];

          if (
            lineNumberCloseBraceToken > postion.line ||
            (columnNumberCloseBraceToken >= postion.character &&
              lineNumberCloseBraceToken === postion.line)
          ) {
            hoverStack.pop();
            result = getAllCompletionItems(hoverStack);
            return true;
          }
        }

        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        )
          hoverStack.push({
            variableDeclarations: new Map(),
            customTypes: new Map(),
            classes: new Map(),
            functions: new Map(),
            callExpression: new Map(),
          });

        for (const value of Object.values(obj)) {
          if (obj["EndOfFileToken"]) {
            result = getAllCompletionItems(hoverStack);
            return true;
          }

          const res = traverseJson(value);
          if (res) return true;
        }

        if (obj["CloseBraceToken"]) {
          const lineNumberCloseBraceToken =
            obj["CloseBraceToken"]["lineNumber"];
          const columnNumberCloseBraceToken =
            obj["CloseBraceToken"]["columnNumber"];

          if (
            lineNumberCloseBraceToken > postion.line ||
            (columnNumberCloseBraceToken >= postion.character &&
              lineNumberCloseBraceToken === postion.line)
          ) {
            result = getAllCompletionItems(hoverStack);
            return true;
          }
        }

        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        )
          hoverStack.pop();
      }
      return false;
    };

    traverseJson(jsonObject);
    return result.length === 0 ? getAllCompletionItems(hoverStack) : result;
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
}
