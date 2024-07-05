import * as fs from "fs";
import {
  ArrayTypeExpression,
  BracketedExpression,
  ClassStatement,
  ConstKeyword,
  CustomTypeStatement,
  FunctionDeclaration,
  LiteralExpression,
  ObjectTypeExpression,
  PrimitiveTypeExpression,
  RootObject,
  TypeExpression,
  VariableDeclaration,
  VarKeyword,
} from "./types";

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

const getCustomTypeStatementAsString = (
  customTypeStatement: CustomTypeStatement
): string => {
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
  return customTypeStatementString;
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

const getVariableDeclarationAsString = (
  variableDeclaration: VariableDeclaration
): string => {
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

  return variableDeclarationStr;
};

const getFunctionDeclarationAsString = (
  functionDeclaration: FunctionDeclaration
): string => {
  let functionDeclarationStr = "";
  if (functionDeclaration[0]["FunctionKeyword"])
    functionDeclarationStr +=
      functionDeclaration[0]["FunctionKeyword"].value + " ";

  if (functionDeclaration[1]["IdentifierToken"])
    functionDeclarationStr += functionDeclaration[1]["IdentifierToken"].value;

  functionDeclarationStr += "(";
  let index = 2;
  while (functionDeclaration[index]["VariableDeclaration"]) {
    functionDeclarationStr +=
      getVariableDeclarationAsString(
        functionDeclaration[index++]["VariableDeclaration"]
      ) + ", ";
  }

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

  return functionDeclarationStr;
};

const getClassStatementsString = (classDeclaration: ClassStatement): string => {
  let classDeclarationStr = "";

  if (classDeclaration[0]["ClassKeyword"])
    classDeclarationStr += classDeclaration[0]["ClassKeyword"].value + " ";

  if (classDeclaration[1]["IdentifierToken"])
    classDeclarationStr += classDeclaration[1]["IdentifierToken"].value;

  return classDeclarationStr;
};

// Function to read the JSON file and process it
function readAndProcessJson(
  filePath: string,
  columnNumber: number,
  lineNumber: number
) {
  fs.readFile(filePath, "utf8", (err, data) => {
    if (err) {
      console.error("Error reading file:", err);
      return;
    }

    try {
      // Parse the JSON data and typecast it
      const jsonObject: RootObject = JSON.parse(data);

      // Recursive function to traverse the JSON structure
      const traverseJson = function (obj: any): string | null {
        if (Array.isArray(obj)) {
          for (const item of obj) {
            const result = traverseJson(item);
            if (result) return result;
          }
        } else if (typeof obj === "object" && obj !== null) {
          if (obj["VariableDeclaration"]) {
            return getVariableDeclarationAsString(obj["VariableDeclaration"]);
          } else if (obj["CustomTypeStatement"]) {
            return getCustomTypeStatementAsString(
              obj["CustomTypeStatement"] as CustomTypeStatement
            );
          } else if (obj["FunctionDeclarationSyntax"]) {
            return getFunctionDeclarationAsString(
              obj["FunctionDeclarationSyntax"] as FunctionDeclaration
            );
          } else if (obj["ClassStatement"]) {
            return getClassStatementsString(
              obj["ClassStatement"] as ClassStatement
            );
          }
          for (const value of Object.values(obj)) {
            const result = traverseJson(value);
            if (result) return result;
          }
        }
        return null;
      };

      // Traverse the JSON structure and get the result
      const result = traverseJson(jsonObject);

      if (result) {
        console.log(result);
      } else {
        console.log(
          `No VariableDeclaration found for column ${columnNumber} and line ${lineNumber}.`
        );
      }
    } catch (err) {
      console.error("Error parsing JSON:", err);
    }
  });
}

// Call the function with the provided columnNumber and lineNumber
readAndProcessJson(filePath, 4, 3);
