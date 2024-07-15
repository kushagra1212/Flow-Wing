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
  Token,
  TypeExpression,
  VariableDeclaration,
  VarKeyword,
} from "./types";
import { ClassCompletionItem, ProgramStructure, Stack } from "./stack";
import {
  CompletionItem,
  CompletionItemKind,
  ParameterInformation,
  Position,
} from "vscode-languageserver";
import { fileUtils } from "../utils/fileUtils";
import {
  formatVarExpr,
  getArrayType,
  getMarkSyntaxHighlightMarkdown,
  isPrimitiveType,
} from "../utils";

let currentParsingClassName: string | null = null;
let isInsideFunction = false;

const parseBracketedExpression = (
  bracketedExpression: BracketedExpression
): CompletionItem => {
  let bracketedExpressionString = "";
  let variableName = "";
  if (bracketedExpression?.[0]?.["LiteralExpression"]?.[0]) {
    variableName = getLiteralExpressionAsString(
      bracketedExpression[0]["LiteralExpression"][0]
    );
    bracketedExpressionString += variableName + ": ";
  }
  const typeName = getTypeExpressionAsString(bracketedExpression[1]);
  bracketedExpressionString += typeName;

  return {
    label: variableName,
    kind: CompletionItemKind.TypeParameter,
    data: { typeName: typeName },
    detail: bracketedExpressionString,
    documentation: {
      kind: "markdown",
      value: getMarkSyntaxHighlightMarkdown(bracketedExpressionString),
    },
  };
};

const getBracketedExpressionVariableName = (
  bracketedExpression: BracketedExpression
): string | null => {
  if (bracketedExpression?.[0]?.["LiteralExpression"]?.[0]) {
    return getLiteralExpressionAsString(
      bracketedExpression[0]["LiteralExpression"][0]
    );
  }

  return null;
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
  const data = [];
  for (let i = 1; i < customTypeStatement.length; i++) {
    customTypeStatementString += "\t";
    if (customTypeStatement[i]["BracketedExpression"]) {
      data.push({
        ...parseBracketedExpression(
          customTypeStatement[i]["BracketedExpression"]
        ),
        kind: CompletionItemKind.Variable,
      });
      customTypeStatementString +=
        data[data.length - 1].detail +
        (i == customTypeStatement.length - 1 ? "\n" : ",\n");
    }
  }
  customTypeStatementString += "}\n";

  const typeName = getTypeNameFromCustomTypeStatement(customTypeStatement);

  return {
    label: typeName,
    kind: CompletionItemKind.TypeParameter,
    data: data,
    detail: "Custom Type",
    documentation: {
      kind: "markdown",
      value: getMarkSyntaxHighlightMarkdown(customTypeStatementString),
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

  if (expression && "ObjectTypeExpression" in expression) {
    typeName = getObjectTypeAsString(expression["ObjectTypeExpression"][0]);
  } else if (expression && "PrimitiveTypeExpression" in expression) {
    typeName = getPrimitiveTypeAsString(
      expression["PrimitiveTypeExpression"][0]
    );
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
  if (!typeExpr) {
    return "";
  }
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

  const variableName =
    getVariableNameFromVariableDeclaration(variableDeclaration);

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

  let typeName = "";
  if (variableDeclaration[index]) {
    typeName = getTypeExpressionAsString(
      variableDeclaration[index] as TypeExpression
    );
    variableDeclarationStr += typeName;
  } else variableDeclarationStr += "unknown";

  return {
    label: variableName,
    kind: CompletionItemKind.Variable,
    data: {
      typeName: typeName,
    },
    detail: variableDeclarationStr,
    documentation: {
      kind: "markdown",
      value: getMarkSyntaxHighlightMarkdown(variableDeclarationStr),
    },
  };
};

const populateVariableExpressionCompletionItem = (
  st: Stack<ProgramStructure>,
  variableName: string,
  typeName: string
): void => {
  if (isPrimitiveType(typeName)) {
    return;
  }

  const customTypesCompletionItem = getScopeCompletionItemFromExpression(
    st,
    typeName,
    "customTypes"
  );

  if (customTypesCompletionItem) {
    const innerVariableName = variableName + ".";
    for (const item of customTypesCompletionItem.data) {
      if (!st?.peek().variableExpressions.get(innerVariableName)) {
        st?.peek().variableExpressions.set(innerVariableName, []);
      }
      st?.peek().variableExpressions.get(innerVariableName).push(item);

      const array = getArrayType(item.data.typeName);

      console.log(innerVariableName + item.label, array);
      if (array.isArray) {
        populateVariableExpressionCompletionItem(
          st,
          innerVariableName + item.label + array.dim,
          array.ofType
        );
      } else {
        populateVariableExpressionCompletionItem(
          st,
          innerVariableName + item.label,
          item.data.typeName
        );
      }
    }
  }
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
  st: Stack<ProgramStructure>,
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
  const functionParametersTypes: string[] = [];
  while (functionDeclaration[index]["VariableDeclaration"]) {
    const functionParameter = parseVariableDeclaration(
      functionDeclaration[index++]["VariableDeclaration"]
    );
    st.peek().variableDeclarations.set(
      functionParameter.label,
      functionParameter
    );
    functionDeclarationStr += functionParameter.detail + ", ";
    functionParameters.push({
      label: functionParameter.label,
      documentation: functionParameter.documentation,
    });
    functionParametersTypes.push(functionParameter.data.typeName);
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

  functionDeclarationStr = currentParsingClassName
    ? `${currentParsingClassName}:${functionDeclarationStr.replace("fun", "")}`
    : functionDeclarationStr;

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
      functionParametersTypes: functionParametersTypes,
    },
    detail: functionDeclarationStr,
    documentation: {
      kind: "markdown",
      value: getMarkSyntaxHighlightMarkdown(functionDeclarationStr),
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

const parseClassStatement = (
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
      value: getMarkSyntaxHighlightMarkdown(classDeclarationStr),
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
      value: getMarkSyntaxHighlightMarkdown(callExpressionStr),
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
  currentStack: Stack<ProgramStructure>
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);
  const result: CompletionItem[] = [];
  const mapping: ProgramStructure = {
    variableDeclarations: new Map(),
    customTypes: new Map(),
    classes: new Map(),
    functions: new Map(),
    callExpression: new Map(),
    variableExpressions: new Map(),
  };
  while (!reversedStack.isEmpty()) {
    const current = reversedStack?.pop();
    currentStack.push(current);
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

  if (mapping.classes) {
    Array.from(mapping.classes.values()).forEach((value) => {
      result.push(value.classCompletionItem);
    });
  }

  if (currentParsingClassName) {
    result.push(
      ...Array.from(
        mapping.classes.get(currentParsingClassName).callExpression.values()
      )
    );
    result.push(
      ...Array.from(
        mapping.classes.get(currentParsingClassName).customTypes.values()
      )
    );
    result.push(
      ...Array.from(
        mapping.classes.get(currentParsingClassName).functions.values()
      )
    );
    result.push(
      ...Array.from(
        mapping.classes
          .get(currentParsingClassName)
          .variableDeclarations.values()
      )
    );
  }

  if (mapping.functions) result.push(...Array.from(mapping.functions.values()));

  if (mapping.callExpression)
    result.push(...Array.from(mapping.callExpression.values()));

  return result;
};

const getAllCompletionItemsOfIdentifier = (
  currentStack: Stack<ProgramStructure>,
  identifier: string
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);
  const result: CompletionItem[] = [];
  const update = (
    identifier: string,
    result: CompletionItem[],
    newValue: CompletionItem
  ) => {
    const index = result.findIndex((item) => item.label === identifier);

    if (index !== -1) {
      result[index] = newValue;
    } else {
      result.push(newValue);
    }
  };

  while (!reversedStack.isEmpty()) {
    const current = reversedStack?.pop();
    currentStack.push(current);
    if (current.variableDeclarations.get(identifier)) {
      update(identifier, result, current.variableDeclarations.get(identifier));
    }

    if (current.customTypes.get(identifier))
      update(identifier, result, current.customTypes.get(identifier));

    if (current.functions.get(identifier))
      update(identifier, result, current.functions.get(identifier));

    if (current.classes.get(identifier)) {
      update(
        identifier,
        result,
        current.classes.get(identifier).classCompletionItem
      );
    }

    if (current.callExpression.get(identifier))
      update(identifier, result, current.callExpression.get(identifier));

    // if (
    //   currentParsingClassName &&
    //   current.classes.get(currentParsingClassName)
    // ) {
    //   const classCI = current.classes.get(currentParsingClassName);

    //   if (classCI.variableDeclarations.get(identifier))
    //     update(
    //       identifier,
    //       result,
    //       classCI.variableDeclarations.get(identifier)
    //     );
    //   if (classCI.functions.get(identifier))
    //     update(identifier, result, classCI.functions.get(identifier));
    //   if (classCI.callExpression.get(identifier))
    //     update(identifier, result, classCI.callExpression.get(identifier));
    //   if (classCI.customTypes.get(identifier))
    //     update(identifier, result, classCI.customTypes.get(identifier));
    // }

    // Maping Class Name with init Function
    if (current.classes.get(identifier)) {
      const classCI = current.classes.get(identifier);
      if (classCI.functions.get("init"))
        update(identifier, result, classCI.functions.get("init"));
    }
  }

  return result;
};

const getScopeCompletionItemFromExpression = (
  currentStack: Stack<ProgramStructure>,
  identifier: string,
  expressionName: keyof ProgramStructure
): CompletionItem => {
  const reversedStack = reverseStack(currentStack);

  let result: CompletionItem | null = null;

  while (!reversedStack.isEmpty()) {
    const current = reversedStack?.pop();
    currentStack.push(current);
    if (result) continue;

    const completionItem = current[expressionName].get(identifier);

    if (completionItem) {
      if (completionItem["classCompletionItem"]) {
        result = completionItem["classCompletionItem"];
      } else if ((completionItem as CompletionItem[])?.length > 0) {
        result = completionItem[0];
      } else {
        result = completionItem as CompletionItem;
      }
    }
  }

  return result;
};
const getScopeCompletionAllItemFromExpression = (
  currentStack: Stack<ProgramStructure>,
  identifier: string,
  expressionName: keyof ProgramStructure
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);

  let result: CompletionItem[] = [];

  while (!reversedStack.isEmpty()) {
    const current = reversedStack?.pop();
    currentStack.push(current);
    if (result?.length) continue;

    const completionItem = current[expressionName].get(identifier);

    if (completionItem) {
      if (completionItem["classCompletionItem"]) {
        result = [completionItem["classCompletionItem"]];
      } else if ((completionItem as CompletionItem[])?.length > 0) {
        result = completionItem as CompletionItem[];
      } else {
        result = [completionItem as CompletionItem];
      }
    }
  }

  return result;
};

const getScopeCompletionItemsListFromExpression = (
  currentStack: Stack<ProgramStructure>,
  identifier: string,
  expressionName: keyof ProgramStructure
): CompletionItem[] => {
  const reversedStack = reverseStack(currentStack);

  let result: CompletionItem[] = [];
  let found = false;
  while (!reversedStack.isEmpty()) {
    const current = reversedStack?.pop();
    currentStack.push(current);

    if (found) continue;

    const index = result.findIndex((item) => item.label === identifier);
    // let newIdentifier;

    // if (
    //   identifier.split(".")?.[0] === "self" &&
    //   identifier.split(".")?.length > 2
    // ) {
    //   newIdentifier = identifier.replace("self.", "");
    // } else {
    //   newIdentifier = identifier;
    // }
    let value = null;
    if (currentParsingClassName && currentParsingClassName !== identifier) {
      value = (
        current["classes"].get(currentParsingClassName) as ClassCompletionItem
      )?.[expressionName]?.get(identifier);
    }
    if (!value && current[expressionName].get(identifier)) {
      value = current[expressionName].get(identifier);
      if (value && value["classCompletionItem"]) {
        value = value["classCompletionItem"];
      }
    }

    if (value && Array.isArray(value)) {
      result = value;
      found = true;
    }

    if (!found && value) {
      if (index !== -1) {
        result[index] = value as CompletionItem;
      } else {
        result.push(value as CompletionItem);
      }
    }
  }
  return result;
};

const getCompletionItemsOfVariable = (
  currentStack: Stack<ProgramStructure>,
  identifier: string
): CompletionItem[] => {
  const variablesCompletionItem = getScopeCompletionItemFromExpression(
    currentStack,
    identifier,
    "variableDeclarations"
  );

  if (
    !variablesCompletionItem ||
    isPrimitiveType(variablesCompletionItem.data.typeName)
  )
    return [];

  const customTypesCompletionItem = getScopeCompletionItemFromExpression(
    currentStack,
    variablesCompletionItem.data.typeName,
    "customTypes"
  );

  if (!customTypesCompletionItem) return [];

  return customTypesCompletionItem.data;
};

const getCurrentClassMemberVariableCompletionItem = (
  st: Stack<ProgramStructure>,
  currentClassName: string,
  identifier: string
): CompletionItem => {
  st = reverseStack(st);

  const cI = st
    ?.peek()
    ?.classes?.get(currentClassName)
    ?.variableDeclarations?.get(identifier);

  st = reverseStack(st);

  return cI;
};

const traverseJson = (
  st: Stack<ProgramStructure>,
  rootProgram: ProgramStructure,
  obj: RootObject,
  options: { isSelf: boolean } = { isSelf: false },
  position: Position
): CompletionItem[] => {
  if (Array.isArray(obj)) {
    for (const item of obj) {
      const result = traverseJson(st, rootProgram, item, options, position);
      if (result.length) return result;
    }
  } else if (typeof obj === "object") {
    handleStatements(st, rootProgram, obj);

    if (obj["IdentifierToken"]) {
      const identifierToken: IdentifierToken = obj["IdentifierToken"];

      if (
        identifierToken.columnNumber === position.character &&
        identifierToken.lineNumber === position.line
      ) {
        if (currentParsingClassName && options.isSelf) {
          return [
            getCurrentClassMemberVariableCompletionItem(
              st,
              currentParsingClassName,
              identifierToken.value
            ),
          ];
        }

        return getAllCompletionItemsOfIdentifier(st, identifierToken.value);
      }
    }

    if (
      obj["BlockStatement"] ||
      obj["FunctionDeclarationSyntax"] ||
      obj["ClassStatement"]
      //    ||  obj["CustomTypeStatement"]
    ) {
      st.push({
        variableDeclarations: new Map(),
        customTypes: new Map(),
        classes: new Map(),
        functions: new Map(),
        callExpression: new Map(),
        variableExpressions: new Map(),
      });
    }

    if (obj["FunctionDeclarationSyntax"]) isInsideFunction = true;

    for (const child of Object.values(obj)) {
      const result = traverseJson(st, rootProgram, child, options, position);

      if (result.length) return result;
    }

    if (obj["FunctionDeclarationSyntax"]) isInsideFunction = false;
    if (obj["ClassStatement"]) currentParsingClassName = null;

    if (
      obj["BlockStatement"] ||
      obj["FunctionDeclarationSyntax"] ||
      obj["ClassStatement"]
      //||   obj["CustomTypeStatement"]
    ) {
      st.pop();
    }
  }
  return [];
};

// Function to read the JSON file and process it
export async function readAndProcessSyntaxJSON(
  filePath: string,
  postion: Position,
  options: { isSelf: boolean }
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const jsonObject: RootObject = JSON.parse(syntaxTreeAsString);
    const st = new Stack<ProgramStructure>();
    st.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
      variableExpressions: new Map(),
    });
    const rootObject = st.peek();
    isInsideFunction = false;
    currentParsingClassName = null;
    // Recursive function to traverse the JSON structure

    // Traverse the JSON structure and get the result
    return traverseJson(st, rootObject, jsonObject, options, postion);
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
}

const getAllSuggestionsOfType = (
  st: Stack<ProgramStructure>,
  typeName: string
): CompletionItem[] => {
  console.log("🚀 ~ getAllSuggestionsOfType:", typeName);

  return getScopeCompletionAllItemFromExpression(
    st,
    typeName,
    "variableExpressions"
  );
};

export async function handleOnCompletion(
  filePath: string,
  postion: Position,
  options: { isDot: boolean; word: string; argumentNumber: number }
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const jsonObject: RootObject = JSON.parse(syntaxTreeAsString);
    const hoverStack = new Stack<ProgramStructure>();
    hoverStack.push({
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
      variableExpressions: new Map(),
    });
    const rootProgram = hoverStack.peek();
    currentParsingClassName = null;
    isInsideFunction = false;
    let result: CompletionItem[] = [];
    // Recursive function to traverse the JSON structure
    const traverseJson = function (obj: any): boolean {
      if (Array.isArray(obj)) {
        for (const item of obj) {
          const res = traverseJson(item);
          if (res) return true;
        }
      } else if (typeof obj === "object" && obj !== null) {
        handleStatements(hoverStack, rootProgram, obj);
        if (obj["IdentifierToken"]) {
          const identifierToken: IdentifierToken = obj["IdentifierToken"];
          if (
            identifierToken.columnNumber === postion.character &&
            identifierToken.lineNumber === postion.line
          ) {
            console.log("IDE", identifierToken);
            if (options.isDot) {
              console.log("options.word", options.word);
              let firstWord = options.word.split(".")?.[0],
                typeName = "";
              const remainingWord = options.word.split(".").slice(1).join(".");
              if (options.argumentNumber) {
                firstWord = hoverStack?.peek()?.functions?.get(firstWord).data
                  ?.functionParametersTypes[options.argumentNumber - 1];
                typeName = formatVarExpr(
                  formatVarExpr(firstWord).split("[]")[0] + "." + remainingWord
                );
              } else if (
                firstWord === "self" &&
                currentParsingClassName &&
                getAllSuggestionsOfType(
                  hoverStack,
                  firstWord + "." + remainingWord
                )
              ) {
                typeName = firstWord + "." + remainingWord;
                if (typeName.split(".")?.length > 2) {
                  typeName = remainingWord;
                }
              } else {
                const array = getArrayType(firstWord);
                if (array.isArray) {
                  firstWord = array.ofType;
                }
                const varDecCI = getScopeCompletionItemFromExpression(
                  hoverStack,
                  firstWord,
                  "variableDeclarations"
                );
                typeName = array.isArray
                  ? formatVarExpr(varDecCI?.data?.typeName).split("[]")[0] +
                    "." +
                    formatVarExpr(remainingWord)
                  : formatVarExpr(
                      varDecCI?.data?.typeName + "." + remainingWord
                    );
              }

              result = getAllSuggestionsOfType(hoverStack, typeName);

              return true;
            }
            result = getAllCompletionItemsOfIdentifier(
              hoverStack,
              identifierToken.value
            );
            return true;
          }
        }
        if (obj["EndOfFileToken"]) {
          if (!options.isDot) result = getAllCompletionItems(hoverStack);
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
            hoverStack?.pop();
            if (!options.isDot) result = getAllCompletionItems(hoverStack);
            return true;
          }
        }
        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
          //    || obj["CustomTypeStatement"]
        ) {
          hoverStack.push({
            variableDeclarations: new Map(),
            customTypes: new Map(),
            classes: new Map(),
            functions: new Map(),
            callExpression: new Map(),
            variableExpressions: new Map(),
          });
        }
        for (const value of Object.values(obj)) {
          if (obj["EndOfFileToken"]) {
            if (!options.isDot) result = getAllCompletionItems(hoverStack);
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
            if (!options.isDot) result = getAllCompletionItems(hoverStack);
            return true;
          }
        }

        if (obj["FunctionDeclarationSyntax"]) isInsideFunction = false;
        if (obj["ClassStatement"]) currentParsingClassName = null;

        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
          // || obj["CustomTypeStatement"]
        ) {
          hoverStack?.pop();
        }
      }
      return false;
    };
    traverseJson(jsonObject);
    return result.length === 0 && !options.isDot
      ? getAllCompletionItems(hoverStack)
      : result;
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
  return [];
}

export async function readTokens(
  filePath: string,
  postion: Position
): Promise<Token[]> {
  try {
    const tokensAsString = await fileUtils.readFile(filePath);
    const tokens = JSON.parse(tokensAsString) as Array<Token>;
    const resTokens = [];

    for (const token of tokens) {
      if (
        token.lineNumber < postion.line ||
        (token.lineNumber <= postion.line &&
          token.columnNumber < postion.character)
      ) {
        resTokens.push(token);
      } else {
        break;
      }
    }
    return resTokens;
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
}

const handleStatements = (
  st: Stack<ProgramStructure>,
  rootProgram: ProgramStructure,
  obj: any
): void => {
  const result: { name: string; completionItem: CompletionItem } = {
    name: "",
    completionItem: {} as CompletionItem,
  };

  if (obj["VariableDeclaration"]) {
    result.name = getVariableNameFromVariableDeclaration(
      obj["VariableDeclaration"]
    );
    result.completionItem = parseVariableDeclaration(
      obj["VariableDeclaration"]
    );
    st?.peek()?.variableDeclarations?.set(result.name, result.completionItem);

    setClassMembersIfNeeded(rootProgram, "variableDeclarations", result);
  } else if (obj["CallExpression"]) {
    result.name = getCallExpressionCallerName(obj["CallExpression"]);
    result.completionItem = parseCallExpression(obj["CallExpression"]);

    st?.peek()?.callExpression?.set(result.name, result.completionItem);

    setClassMembersIfNeeded(rootProgram, "callExpression", result);
  } else if (obj["CustomTypeStatement"]) {
    result.name = getTypeNameFromCustomTypeStatement(
      obj["CustomTypeStatement"]
    );
    result.completionItem = parseCustomTypeStatement(
      obj["CustomTypeStatement"] as CustomTypeStatement
    );

    st?.peek()?.customTypes?.set(result.name, result.completionItem);
    if (result.completionItem.label !== "unknown") {
      populateVariableExpressionCompletionItem(
        st,
        result.completionItem.label,
        result.completionItem.label
      );
    }

    setClassMembersIfNeeded(rootProgram, "customTypes", result);
  } else if (obj["FunctionDeclarationSyntax"]) {
    result.name = getFunctionNameFromFunctionDeclaration(
      obj["FunctionDeclarationSyntax"]
    );
    result.completionItem = parseFunctionDeclaration(
      st,
      obj["FunctionDeclarationSyntax"] as FunctionDeclaration
    );

    st?.peek()?.functions?.set(result.name, result.completionItem);

    setClassMembersIfNeeded(rootProgram, "functions", result);
  } else if (obj["ClassStatement"]) {
    result.name = getClassNameFromClassStatement(obj["ClassStatement"]);
    result.completionItem = parseClassStatement(
      obj["ClassStatement"] as ClassStatement
    );
    currentParsingClassName = result.name;

    rootProgram.classes.set(result.name, {
      classCompletionItem: result.completionItem,
      callExpression: new Map(),
      customTypes: new Map(),
      variableDeclarations: new Map(),
      functions: new Map(),
      variableExpressions: new Map(),
    });
  } else if (obj["BracketedExpression"]) {
    result.name = getBracketedExpressionVariableName(
      obj["BracketedExpression"]
    );
    result.completionItem = parseBracketedExpression(
      obj["BracketedExpression"]
    );
    if (result.name)
      st?.peek()?.callExpression?.set(result.name, result.completionItem);
  }
};

const setClassMembersIfNeeded = (
  rootProgram: ProgramStructure,
  expressionName: keyof ProgramStructure,
  result: { name: string; completionItem: CompletionItem }
) => {
  if (currentParsingClassName && !isInsideFunction) {
    rootProgram?.classes
      .get(currentParsingClassName)
      ?.[expressionName]?.set(result.name, result.completionItem);
  }
};
