import { ProgramStructure } from "../ds/stack";
import {
  CompletionItem,
  CompletionItemKind,
  Position,
} from "vscode-languageserver";
import { fileUtils } from "../utils/fileUtils";
import {
  formatVarExpr,
  getArrayType,
  getFileFullPath,
  getImportedFileUri,
  getModulePath,
  getUnique,
  SuggestHandler,
  userDefinedKeywordsFilter,
} from "../utils";
import { FunctionDeclarationExpressionStrategy } from "../strategies/FunctionDeclarationExpressionStrategy";
import { IdentifierCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/IdentifierCompletionItemsStrategy";
import { CompletionItemService } from "../services/completionItemService";
import { AllCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/AllCompletionItemsStrategy";
import { ScopeCompletionItemsStrategy } from "../strategies/CompletionItemStrategy/ScopeCompletionItemsStrategy";
import { ProgramContext } from "../ds/programContext";
import { FunctionDeclarationCompletionItemGenerationStrategy } from "../completionItemGeneration/strategies/FunctionDeclarationCompletionItemGenerationStrategy";
import { CompletionItemGenerationFactory } from "../completionItemGeneration/completionItemGenerationFactory";
import { IdentifierToken, RootObject, Token } from "../types";
import { flowWingConfig } from "../config";
import { validateTextDocument } from "../services/documentService";
import { documents } from "../server";

export const declareGlobals = (
  program: any,
  obj: RootObject,
  option: { skip: string[] }
): void => {
  if (Array.isArray(obj)) {
    for (const item of obj) {
      declareGlobals(program, item, option);
    }
  } else if (typeof obj === "object") {
    if (!obj) return;

    if (
      (option.skip.includes("ClassStatement") && obj["ClassStatement"]) ||
      (option.skip.includes("VariableDeclarations") &&
        obj["VariableDeclarations"]) ||
      (option.skip.includes("BringStatementSyntax") &&
        obj["BringStatementSyntax"]) ||
      (option.skip.includes("ModuleStatement") && obj["ModuleStatement"])
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

type TraverseJsonParams = {
  obj: any;
  suggestion: SuggestHandler;
  programCtx: ProgramContext;
  currentTextDocUri: string;
};

const traverseJson = async ({
  obj,
  suggestion,
  programCtx,
  currentTextDocUri,
}: TraverseJsonParams): Promise<CompletionItem[]> => {
  if (Array.isArray(obj)) {
    for (const item of obj) {
      const res = await traverseJson({
        obj: item,
        currentTextDocUri: currentTextDocUri,
        programCtx: programCtx,
        suggestion: suggestion,
      });
      if (res?.length) return wrap(res, programCtx, currentTextDocUri);
    }
  } else if (typeof obj === "object" && obj !== null) {
    if (obj["BringStatementSyntax"]) {
      const result = await handleBringStatement({
        obj,
        currentTextDocUri,
        programCtx,
        suggestion,
      });

      if (result.length) return wrap(result, programCtx, currentTextDocUri);
    }
    if (obj["ClassKeyword"]) {
      if (
        suggestion.token &&
        (obj["ClassKeyword"]["lineNumber"] > suggestion.token.lineNumber ||
          (obj["ClassKeyword"]["columnNumber"] >=
            suggestion.token.columnNumber &&
            obj["ClassKeyword"]["lineNumber"] === suggestion.token.lineNumber))
      ) {
        programCtx.setCurrentParsingClassName(null);
      }
    }

    if (obj["ModuleStatement"]) {
      programCtx.setCurrentParsingModuleName(null);
    }

    if (obj["IdentifierToken"]) {
      const identifierToken: IdentifierToken = obj["IdentifierToken"];

      if (
        suggestion.token &&
        suggestion.token.columnNumber === identifierToken.columnNumber &&
        suggestion.token.lineNumber === identifierToken.lineNumber
      ) {
        if (suggestion.data.isDot) {
          return getCompletionItemsForDot(suggestion, programCtx);
        }

        const identifierResult =
          new CompletionItemService(
            new IdentifierCompletionItemsStrategy()
          ).getCompletionItems({
            programCtx: programCtx,
            identifier: identifierToken.value,
          }) ?? [];

        const allResult =
          new CompletionItemService(
            new AllCompletionItemsStrategy()
          ).getCompletionItems({ programCtx: programCtx }) ?? [];

        const result = getUnique(identifierResult, allResult);
        if (result?.length) return wrap(result, programCtx, currentTextDocUri);
      }
    }

    if (
      obj["BlockStatement"] ||
      obj["ClassStatement"] ||
      obj["FunctionDeclarationSyntax"] ||
      obj["ModuleStatement"]
    ) {
      programCtx.pushEmptyProgramStructure();
    }

    CompletionItemGenerationFactory?.create(
      programCtx,
      obj
    )?.generateCompletionItems();
    for (const value of Object.values(obj)) {
      const result = await traverseJson({
        obj: value,
        currentTextDocUri: currentTextDocUri,
        programCtx: programCtx,
        suggestion: suggestion,
      });

      if (result?.length) return wrap(result, programCtx, currentTextDocUri);
    }

    if (obj["BringStatementSyntax"]) {
      programCtx.onExitBring();
    }

    if (
      obj["BlockStatement"] ||
      obj["ClassStatement"] ||
      obj["FunctionDeclarationSyntax"] ||
      obj["ModuleStatement"]
    ) {
      if (obj["FunctionDeclarationSyntax"])
        programCtx.setCurrentParsingFunctionName(null);

      if (obj["ClassStatement"]) programCtx.setCurrentParsingClassName(null);

      if (obj["ModuleStatement"]) {
        programCtx.setCurrentParsingModuleName(null);
      }

      programCtx.stack?.pop();
    }
  }
  return [];
};

const wrap = (
  result: CompletionItem[],
  programCtx: ProgramContext,
  currentTextDocUri: string
) => {
  return result.map((item) => {
    return {
      ...item,
      data: {
        ...item.data,
        textDocUri: programCtx?.currentBringFilePath ?? currentTextDocUri,
      },
    };
  });
};

export async function getCompletionItems(
  filePath: string,
  suggestion: SuggestHandler,
  currentTextDocUri: string
): Promise<CompletionItem[]> {
  try {
    const syntaxTreeAsString = await fileUtils.readFile(filePath);
    const programCtx = new ProgramContext(JSON.parse(syntaxTreeAsString));

    const result = await traverseJson({
      obj: programCtx.syntaxTree,
      currentTextDocUri: currentTextDocUri,
      programCtx: programCtx,
      suggestion: suggestion,
    });

    const finalResult =
      result.length === 0 && !suggestion.data.isDot
        ? new CompletionItemService(
            new AllCompletionItemsStrategy()
          ).getCompletionItems({ programCtx: programCtx })
        : result;

    return wrap(finalResult, programCtx, currentTextDocUri);
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${filePath}`, err);
    return [];
  }
}

export async function readTokens(
  filePath: string,
  position: Position
): Promise<Token[]> {
  try {
    const tokensAsString = await fileUtils.readFile(filePath);
    const tokens = JSON.parse(tokensAsString) as Array<Token>;
    const resTokens = [];

    for (const token of tokens) {
      if (
        token.lineNumber < position.line ||
        (token.lineNumber <= position.line &&
          token.columnNumber < position.character)
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
const getCompletionItemsForDot = (
  suggestion: SuggestHandler,
  programCtx: ProgramContext
) => {
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
          .get(programCtx.getCurrentParsingClassName())
          .variableDeclarations.values()
      ),
      ...Array.from(
        programCtx.rootProgram.classes
          .get(programCtx.getCurrentParsingClassName())
          .functions.values()
      ).filter((item) => item.label !== "init"),
    ];
  }
  if (programCtx.doesModuleExist(firstWord.split("::")[0])) {
    const moduleName = firstWord.split("::")[0];
    if (suggestion.word.indexOf(".") !== -1) {
      const typeName = programCtx.rootProgram.modules
        .get(moduleName)
        .variableDeclarations.get(firstWord).data?.typeName;

      return [
        ...Array.from(
          programCtx.rootProgram.modules
            .get(moduleName)
            .variableExpressions.get(typeName + ".")
            .values()
        ),
      ];
    }

    const className = firstWord.split("::")[1];

    if (
      programCtx.rootProgram.classes.get(firstWord) &&
      programCtx.rootProgram.classes.get(firstWord).functions.get("init")
    ) {
      return [
        programCtx.rootProgram.classes.get(firstWord).functions.get("init"),
      ];
    }

    return [
      ...Array.from(
        programCtx.rootProgram.modules
          .get(moduleName)
          .variableDeclarations.values()
      ),
      ...Array.from(
        programCtx.rootProgram.modules.get(moduleName).functions.values()
      ),
      ...Array.from(
        programCtx.rootProgram.modules.get(moduleName).customTypes.values()
      ),
      ...Array.from(
        programCtx.rootProgram.modules.get(moduleName).classes.values()
      ).map((item) => item.classCompletionItem),
    ];
  }

  if (suggestion.data.argumentNumber) {
    {
      let className = new CompletionItemService(
        new ScopeCompletionItemsStrategy()
      ).getCompletionItems({
        programCtx: programCtx,
        identifier: firstWord,
        expressionName: "variableDeclarations",
      })[0]?.data?.typeName;

      if (!className) {
        className = programCtx.getCurrentParsingClassName();
      }

      if (
        programCtx.doesClassExist(className) &&
        programCtx.rootProgram.classes
          .get(className)
          .functions.get(remainingWord)
      ) {
        return [
          programCtx.rootProgram.classes
            .get(className)
            .functions.get(remainingWord),
        ];
      }
    }
  }
  if (firstWord === "self" && programCtx.isInsideClass()) {
    (firstWord = remainingWord.split(".")?.[0]),
      (remainingWord = remainingWord.split(".").slice(1).join("."));

    const memberFunCI = programCtx.rootProgram.classes
      .get(programCtx.getCurrentParsingClassName())
      ?.functions?.get(firstWord);

    if (memberFunCI) return [memberFunCI];
  }

  const array = getArrayType(firstWord);
  if (array.isArray) {
    firstWord = array.ofType;
  }

  typeName = new CompletionItemService(
    new ScopeCompletionItemsStrategy()
  ).getCompletionItems({
    programCtx: programCtx,
    identifier: firstWord,
    expressionName: "variableDeclarations",
  })[0]?.data?.typeName;

  if (programCtx.doesClassExist(typeName) && remainingWord === "") {
    return [
      ...Array.from(
        programCtx.rootProgram.classes
          .get(typeName)
          .variableDeclarations.values()
      ),
      ...Array.from(
        programCtx.rootProgram.classes.get(typeName).functions.values()
      ).filter((item) => item.label !== "init"),
    ];
  }

  if (
    programCtx.doesClassExist(typeName) &&
    programCtx.rootProgram.classes.get(typeName).functions.get(remainingWord)
  ) {
    return [
      programCtx.rootProgram.classes.get(typeName).functions.get(remainingWord),
    ];
  }

  if (programCtx.doesClassExist(typeName) && remainingWord !== "") {
    (firstWord = remainingWord.split(".")?.[0]),
      (remainingWord = remainingWord.split(".").slice(1).join("."));
    typeName = programCtx.rootProgram.classes
      .get(typeName)
      .variableDeclarations.get(firstWord).data?.typeName;
  }

  typeName = array.isArray
    ? formatVarExpr(typeName).split("[]")[0] +
      "." +
      formatVarExpr(remainingWord)
    : formatVarExpr(typeName + "." + remainingWord);

  if (suggestion?.hasHoverResult) {
    typeName = typeName.slice(0, typeName.lastIndexOf("."));
  }
  const result = new CompletionItemService(
    new ScopeCompletionItemsStrategy()
  ).getCompletionItems({
    programCtx: programCtx,
    identifier: typeName,
    expressionName: "variableExpressions",
    closestScope: false,
  });

  return result;
};

const handleBringStatement = async ({
  obj,
  programCtx,
  suggestion,
  currentTextDocUri,
}: {
  obj: any;
  programCtx: ProgramContext;
  suggestion: SuggestHandler;
  currentTextDocUri: string;
}) => {
  const bringkeyword = obj["BringStatementSyntax"]?.[0]?.[
    "BringKeyword"
  ] as Token;

  programCtx.setInsideBring(true);

  const possibleModuleIdef: Token | undefined =
    obj["BringStatementSyntax"]?.[1]?.["IdentifierToken"];
  {
    let index = 2;
    while (
      obj["BringStatementSyntax"]?.[index]?.["LiteralExpression"]?.[0]?.[
        "IdentifierToken"
      ]
    ) {
      const idefImportToken =
        obj["BringStatementSyntax"]?.[index]?.["LiteralExpression"]?.[0]?.[
          "IdentifierToken"
        ];

      programCtx.bringStatementMap.set(idefImportToken.value, true);

      index++;
    }
  }

  try {
    const suggestionToken = suggestion?.token;
    let relPath = null;

    if (
      obj["BringStatementSyntax"]?.[1]?.["StringToken"]?.lineNumber ===
        suggestionToken?.lineNumber &&
      obj["BringStatementSyntax"]?.[1]?.["StringToken"]?.columnNumber ===
        suggestionToken?.columnNumber
    ) {
      relPath = (
        obj["BringStatementSyntax"]?.[1]?.["StringToken"] as Token
      )?.value?.split(`"`)?.[1];
    } else if (
      possibleModuleIdef &&
      possibleModuleIdef.columnNumber === suggestionToken?.columnNumber &&
      possibleModuleIdef.lineNumber === suggestionToken?.lineNumber
    ) {
      relPath = await fileUtils.findFileBreadthFirst(
        getModulePath(),
        possibleModuleIdef.value + "-module.fg"
      );

      if (!relPath)
        relPath = await fileUtils.findFileBreadthFirst(
          __dirname,
          possibleModuleIdef.value
        );
    }

    if (!!relPath && typeof relPath === "string") {
      const importedFileURI = await getImportedFileUri(
        relPath,
        currentTextDocUri
      );
      if (importedFileURI && importedFileURI !== "") {
        await validateTextDocument(documents.get(importedFileURI), null);

        let result = (
          await getCompletionItems(
            fileUtils.getTempFilePath({
              fileName:
                getFileFullPath(importedFileURI) +
                flowWingConfig.temp.syntaxFileExt,
            }),
            {
              data: {
                isDot: false,
              },
            } as SuggestHandler,
            importedFileURI
          )
        )?.filter(userDefinedKeywordsFilter);
        programCtx.currentBringFilePath = importedFileURI;
        result = result.map((item) => {
          return {
            ...item,
            data: {
              ...item.data,
              textDocUri: importedFileURI,
            },
          };
        });

        return result ?? [];
      }
    }
  } catch (err) {
    console.error(`Error reading and processing JSON file: ${err}`);
  }

  return [];
};
