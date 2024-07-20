import { ProgramStructure } from "../ds/stack";
import { CompletionItem, Position } from "vscode-languageserver";
import { fileUtils } from "../utils/fileUtils";
import { formatVarExpr, getArrayType, SuggestHandler } from "../utils";
import { FunctionDeclarationExpressionStrategy } from "../strategies/FunctionDeclarationExpressionStrategy";
import { IdentifierCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/IdentifierCompletionItemsStrategy";
import { CompletionItemService } from "../services/completionItemService";
import { AllCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/AllCompletionItemsStrategy";
import { ScopeCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/ScopeCompletionItemsStrategy";
import { ProgramContext } from "../ds/programContext";
import { FunctionDeclarationCompletionItemGenerationStrategy } from "../completionItemGeneration/strategies/FunctionDeclarationCompletionItemGenerationStrategy";
import { CompletionItemGenerationFactory } from "../completionItemGeneration/completionItemGenerationFactory";
import { IdentifierToken, RootObject, Token } from "../types";

export const declareGlobals = (
  program: ProgramStructure,
  obj: RootObject,
  option: { skip: string[] }
): void => {
  if (Array.isArray(obj)) {
    for (const item of obj) {
      declareGlobals(program, item, option);
    }
  } else if (typeof obj === "object") {
    if (
      (option.skip.includes("ClassStatement") && obj["ClassStatement"]) ||
      (option.skip.includes("variableDeclarations") &&
        obj["ClavariableDeclarationsssStatement"])
    ) {
      return;
    }

    const result: any = {};
    if (obj["FunctionDeclarationSyntax"]) {
      result.name =
        new FunctionDeclarationExpressionStrategy().getExpressionAsString(
          obj["FunctionDeclarationSyntax"]
        );
      result.completionItem =
        new FunctionDeclarationCompletionItemGenerationStrategy().createCompletionItem(
          obj["FunctionDeclarationSyntax"]
        );

      program.functions?.set(result.name, result.completionItem);
    }

    for (const child of Object.values(obj)) {
      declareGlobals(program, child, option);
    }
  }
};

export async function getCompletionItems(
  filePath: string,
  suggestion: SuggestHandler
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const programCtx = new ProgramContext(JSON.parse(syntaxTreeAsString));

    // Recursive function to traverse the JSON structure
    const traverseJson = (obj: any): CompletionItem[] => {
      if (Array.isArray(obj)) {
        for (const item of obj) {
          const res = traverseJson(item);
          if (res?.length) return res;
        }
      } else if (typeof obj === "object" && obj !== null) {
        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        ) {
          programCtx.pushEmptyProgramStructure();
        }

        if (obj["IdentifierToken"]) {
          const identifierToken: IdentifierToken = obj["IdentifierToken"];
          if (
            suggestion.token &&
            identifierToken.columnNumber === suggestion.token.columnNumber &&
            identifierToken.lineNumber === suggestion.token.lineNumber
          ) {
            if (suggestion.data.isDot) {
              let firstWord = suggestion.word.split(".")?.[0],
                typeName = "";
              let remainingWord = suggestion.word.split(".").slice(1).join(".");

              if (
                firstWord === "self" &&
                programCtx.isInsideClass() &&
                remainingWord === ""
              ) {
                return [
                  ...Array.from(
                    programCtx.rootProgram.classes
                      .get(programCtx.currentParsingClassName)
                      .variableDeclarations.values()
                  ),
                  ...Array.from(
                    programCtx.rootProgram.classes
                      .get(programCtx.currentParsingClassName)
                      .functions.values()
                  ),
                ];
              }

              if (suggestion.data.argumentNumber) {
                typeName = new CompletionItemService(
                  new ScopeCompletionItemsStrategy()
                ).getCompletionItems({
                  stack: programCtx.stack,
                  identifier: firstWord,
                  expressionName: "functions",
                })[0].data?.functionParametersTypes[
                  suggestion.data.argumentNumber - 1
                ];
                typeName = formatVarExpr(
                  formatVarExpr(typeName).split("[]")[0] + "." + remainingWord
                );

                const result = new CompletionItemService(
                  new ScopeCompletionItemsStrategy()
                ).getCompletionItems({
                  stack: programCtx.stack,
                  identifier: typeName,
                  expressionName: "variableExpressions",
                  closestScope: false,
                });
                return result;
              }

              if (firstWord === "self" && programCtx.isInsideClass()) {
                (firstWord = remainingWord.split(".")?.[0]),
                  (remainingWord = remainingWord.split(".").slice(1).join("."));
              }

              const array = getArrayType(firstWord);
              if (array.isArray) {
                firstWord = array.ofType;
              }

              typeName = new CompletionItemService(
                new ScopeCompletionItemsStrategy()
              ).getCompletionItems({
                stack: programCtx.stack,
                identifier: firstWord,
                expressionName: "variableDeclarations",
              })[0]?.data?.typeName;

              typeName = array.isArray
                ? formatVarExpr(typeName).split("[]")[0] +
                  "." +
                  formatVarExpr(remainingWord)
                : formatVarExpr(typeName + "." + remainingWord);

              const result = new CompletionItemService(
                new ScopeCompletionItemsStrategy()
              ).getCompletionItems({
                stack: programCtx.stack,
                identifier: typeName,
                expressionName: "variableExpressions",
                closestScope: false,
              });

              return result;
            }

            const result = new CompletionItemService(
              new IdentifierCompletionItemsStrategy()
            ).getCompletionItems({
              stack: programCtx.stack,
              identifier: identifierToken.value,
            });

            if (result?.length) return result;
          }
        }

        if (obj["EndOfFileToken"]) {
          let result = [];
          if (!suggestion.data.isDot)
            result = new CompletionItemService(
              new AllCompletionItemsStrategy()
            ).getCompletionItems({ stack: programCtx.stack });

          return result;
        }

        if (obj["OpenBraceToken"]) {
          const lineNumberCloseBraceToken = obj["OpenBraceToken"]["lineNumber"];
          const columnNumberCloseBraceToken =
            obj["OpenBraceToken"]["columnNumber"];
          if (
            suggestion.token &&
            (lineNumberCloseBraceToken > suggestion.token.lineNumber ||
              (columnNumberCloseBraceToken >= suggestion.token.columnNumber &&
                lineNumberCloseBraceToken === suggestion.token.lineNumber))
          ) {
            programCtx.stack?.pop();
            let result = [];
            if (!suggestion.data.isDot)
              result = new CompletionItemService(
                new AllCompletionItemsStrategy()
              ).getCompletionItems({ stack: programCtx.stack });
            return result;
          }
        }

        const completionItems = CompletionItemGenerationFactory?.create(
          programCtx,
          obj
        )?.generateCompletionItems();

        if (completionItems?.length) return completionItems;

        for (const value of Object.values(obj)) {
          const result = traverseJson(value);
          if (result?.length) return result;
        }

        if (obj["FunctionDeclarationSyntax"])
          programCtx.isInsideFunction = false;
        if (obj["ClassStatement"]) programCtx.currentParsingClassName = null;

        if (obj["CloseBraceToken"]) {
          const lineNumberCloseBraceToken =
            obj["CloseBraceToken"]["lineNumber"];
          const columnNumberCloseBraceToken =
            obj["CloseBraceToken"]["columnNumber"];
          if (
            suggestion.token &&
            (lineNumberCloseBraceToken > suggestion.token.lineNumber ||
              (columnNumberCloseBraceToken >= suggestion.token.columnNumber &&
                lineNumberCloseBraceToken === suggestion.token.lineNumber))
          ) {
            let result = [];
            if (!suggestion.data.isDot)
              result = new CompletionItemService(
                new AllCompletionItemsStrategy()
              ).getCompletionItems({ stack: programCtx.stack });
            return result;
          }
        }
        if (
          obj["BlockStatement"] ||
          obj["ClassStatement"] ||
          obj["FunctionDeclarationSyntax"]
        ) {
          programCtx.stack?.pop();
        }
      }
      return [];
    };
    const result = traverseJson(programCtx.syntaxTree);

    return result.length === 0 && !suggestion.data.isDot
      ? new CompletionItemService(
          new AllCompletionItemsStrategy()
        ).getCompletionItems({ stack: programCtx.stack })
      : result;
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
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
