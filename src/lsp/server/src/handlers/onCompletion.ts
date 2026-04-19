import {
  _Connection,
  CompletionItem,
  TextDocumentPositionParams,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getTokensForContext } from "../services/suggestionService";
import {
  checkForObjectSuggestions,
  checkForFunctionSignatures,
  getFullPathAtPosition,
  getArgumentPrefixFromDocument,
  getVariableInitializerObjectContext,
  getFilesystemPathFromUri,
} from "../utils";
import { getCompletionItems } from "../completionItemProvider";
import {
  getCompletionItemsFromSem,
} from "../completionItemProvider/semCompletions";
import {
  getCompletionItemsForType,
  getCompletionItemsForFunctionArgument,
  getExpectedParamTypeFromSem,
  getNestedObjectLiteralContext,
  isSemFormat,
  getModuleQualifiedCompletionItems,
} from "../services/semService";
import {
  getSemPathForDocument,
  getSemPathForFileNoRepair,
  getAstPathForDocument,
  getAstPathForDocumentNoRepair,
} from "../services/documentService";
import { logger } from "../services/loggerService";
import { fileUtils } from "../utils/fileUtils";
import {
  getCompletionContextFromAst,
  getCompletionContextFromSem,
} from "../services/completionContextService";
import { getObjectMemberCompletionItems } from "../services/semService";
import path = require("path");
import { existsSync } from "fs";
import { pathToFileURL } from "url";

/** Parse member names from object literal prefix (e.g. "{b:" -> ["b"], "{a:1, b:" -> ["a","b"]). */
function parseObjectLiteralMembers(prefix: string): string[] {
  if (!prefix.startsWith("{")) return [];
  const inner = prefix.slice(1);
  const names: string[] = [];
  const re = /([a-zA-Z_][a-zA-Z0-9_]*)\s*:/g;
  let m: RegExpExecArray | null;
  while ((m = re.exec(inner)) !== null) names.push(m[1]);
  return names;
}

export async function onCompletion(
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) {
  connection.onCompletion(
    async (
      _textDocsParams: TextDocumentPositionParams
    ): Promise<CompletionItem[]> => {
      return getObjectSuggestion(_textDocsParams, documents);
    }
  );
}

export const getObjectSuggestion = async (
  _textDocsParams: TextDocumentPositionParams,
  documents: TextDocuments<TextDocument>
): Promise<CompletionItem[]> => {
  const document = documents.get(_textDocsParams.textDocument.uri);
  if (!document) return [];

  const pos = _textDocsParams.position;
  const posObj = { line: pos.line, character: pos.character };
  const contentProbe = document.getText();
  const lineProbe = contentProbe.split("\n")[pos.line] ?? "";
  const beforeProbe = lineProbe.slice(0, pos.character);
  // `print(test::|` is still "inside" a call for signature help, but module `::` wins.
  const isModuleQualifiedCursor = /(\w+)::\s*(\w*)$/.test(beforeProbe);

  // TOKENIZE ONCE
  const tokens = await getTokensForContext(document, pos);

  // 1. Try completion in function call context
  const funcSuggestion = checkForFunctionSignatures(tokens);

  const CONTROL_KEYWORDS = new Set(["if", "else", "or if", "while", "for"]);
  const isControlKeyword = (w: string) =>
    CONTROL_KEYWORDS.has(w) || w.startsWith("else ");

  if (
    funcSuggestion.hasFunctionSignature &&
    funcSuggestion.word &&
    !isControlKeyword(funcSuggestion.word) &&
    !isModuleQualifiedCursor
  ) {
    const funcName = funcSuggestion.word;
    const argNum = funcSuggestion.data?.argumentNumber ?? 1;
    // Use document-based prefix so test(|) yields "" not "{}" from repaired tokens
    const content = document.getText();
    const argPrefix = getArgumentPrefixFromDocument(content, pos) ?? funcSuggestion.data?.argumentPrefix ?? "";
    const semPath = await getSemPathForDocument(document, {
      position: { line: pos.line, character: pos.character },
      partialId: argPrefix || undefined,
    });
    const treePath = semPath ?? (await getAstPathForDocument(document, {
      position: { line: pos.line, character: pos.character },
      partialId: argPrefix || undefined,
    }));
    if (treePath) {
      try {
        const content = await fileUtils.readFile(treePath);
        const parsed = JSON.parse(content);
        if (isSemFormat(parsed)) {
          // Inside object literal (e.g. test({|}) or test({b:{|})): suggest field names
          // After colon (e.g. test({b:|)): suggest values of the field type
          if (argPrefix.trim().startsWith("{") || argPrefix.trim().startsWith("[")) {
            const rootExpectedType = getExpectedParamTypeFromSem(parsed, funcName, argNum);
            if (rootExpectedType) {
              const prefixForContext = argPrefix.replace(/\}\s*$/, "");
                const nested = getNestedObjectLiteralContext(parsed, rootExpectedType, prefixForContext);
                if (nested?.valueExpectedType) {
                  const valueItems = getCompletionItemsForType(
                   parsed,
                   nested.valueExpectedType,
                   "",
                   _textDocsParams.textDocument.uri
                 );
                if (valueItems.length > 0) return valueItems;
                return [];
               }
               const expectedType = nested?.expectedType ?? rootExpectedType;
               const existingMembers = nested?.existingMembers ?? parseObjectLiteralMembers(argPrefix);
               const memberItems = getObjectMemberCompletionItems(
                 parsed,
                 expectedType,
                 existingMembers,
                 _textDocsParams.textDocument.uri
               );
               if (memberItems.length > 0) return memberItems;
               // If we are definitely in an object literal field context, do not fall through
               return [];
            }
          }
          const typeAwareItems = getCompletionItemsForFunctionArgument(
            parsed,
            funcName,
            argNum,
            argPrefix,
            _textDocsParams.textDocument.uri
          );
          if (typeAwareItems.length > 0) return typeAwareItems;
          const items = getCompletionItemsFromSem(
            parsed,
            {
              word: argPrefix,
              data: { isDot: false, isValueCompletion: true },
            },
            _textDocsParams.textDocument.uri
          );
          if (items?.length) return items;
        }
      } catch {
        /* fall through */
      }
    }
  }

  // 2. Tree-based context: get AST without repair for incomplete code
  const content = contentProbe;

  // Early exit for member completion: cursor after dot (getPoints()[0].|) or after member name (getPoints()[0].x|)
  // Do this before AST block so we reliably get member completions when AST position may not align
  const line = content.split("\n")[pos.line] ?? "";
  const charBefore = pos.character > 0 ? line[pos.character - 1] : "";
  const fullPath = getFullPathAtPosition(content, posObj);
  const isMemberCompletionPosition =
    fullPath &&
    (charBefore === "." || (fullPath.includes(".") && /\.\w+$/.test(fullPath)) || /\[\d+\]$/.test(fullPath));
  if (fullPath && isMemberCompletionPosition) {
    const semPath = await getSemPathForFileNoRepair(document.uri, content, { position: posObj });
    if (semPath) {
      const semContent = await fileUtils.readFile(semPath);
      const semParsed = JSON.parse(semContent);
      if (isSemFormat(semParsed)) {
        const memberItems = getCompletionItemsFromSem(
          semParsed,
          { word: fullPath, data: { isDot: true } },
          _textDocsParams.textDocument.uri
        );
        if (memberItems?.length) return memberItems;
      }
    }
  }

  // Module-qualified access: lib::| or lib::get|
  const lineForMod = content.split("\n")[pos.line] ?? "";
  const beforeCursorMod = lineForMod.slice(0, pos.character);
  const modMatch = beforeCursorMod.match(/(\w+)::\s*(\w*)$/);
  if (modMatch) {
    const moduleName = modMatch[1];
    const partial = modMatch[2] ?? "";
    let modItems: CompletionItem[] = [];

    const semPathMod = await getSemPathForFileNoRepair(document.uri, content, {
      position: posObj,
    });
    if (semPathMod) {
      try {
        const semParsed = JSON.parse(await fileUtils.readFile(semPathMod));
        if (isSemFormat(semParsed)) {
          modItems = getModuleQualifiedCompletionItems(
            semParsed,
            moduleName,
            content,
            partial
          );
        }
      } catch {
        /* fall through */
      }
    }

    // `bring name` loads `name-module.fg`; members are not inlined in the main TU's sem tree.
    // Also run when main-file sem failed to load (incomplete `print(test::` at EOF).
    if (modItems.length === 0) {
      const fsPath = getFilesystemPathFromUri(_textDocsParams.textDocument.uri);
      if (fsPath) {
        const candidate = path.join(
          path.dirname(fsPath),
          `${moduleName}-module.fg`
        );
        if (existsSync(candidate)) {
          try {
            const modText = await fileUtils.readFile(candidate);
            const modSemPath = await getSemPathForFileNoRepair(
              pathToFileURL(candidate).href,
              modText,
              { position: posObj }
            );
            if (modSemPath) {
              const modParsed = JSON.parse(await fileUtils.readFile(modSemPath));
              if (isSemFormat(modParsed)) {
                modItems = getModuleQualifiedCompletionItems(
                  modParsed,
                  moduleName,
                  modText,
                  partial
                );
              }
            }
          } catch {
            /* fall through */
          }
        }
      }
    }

    if (modItems.length) return modItems;
  }

  // Variable initializer object literal (e.g. "var p: Point = { x: {} }" -> suggest x, y of A inside inner {})
  const varInitCtx = getVariableInitializerObjectContext(content, posObj);
  if (varInitCtx) {
    const semPath = await getSemPathForFileNoRepair(document.uri, content, { position: posObj });
    if (semPath) {
      try {
        const semContent = await fileUtils.readFile(semPath);
        const semParsed = JSON.parse(semContent);
        if (isSemFormat(semParsed)) {
          const nested = getNestedObjectLiteralContext(
            semParsed,
            varInitCtx.type,
            varInitCtx.prefix
          );
          if (nested) {
            const memberItems = getObjectMemberCompletionItems(
              semParsed,
              nested.expectedType,
              nested.existingMembers,
              _textDocsParams.textDocument.uri
            );
            if (memberItems?.length) return memberItems;
          }
        }
      } catch {
        /* fall through */
      }
    }
  }

  const astPathNoRepair = await getAstPathForDocumentNoRepair(document, { position: pos });

  if (astPathNoRepair) {
    try {
      const astContent = await fileUtils.readFile(astPathNoRepair);
      const astParsed = JSON.parse(astContent);
      const ctx = getCompletionContextFromAst(astParsed, pos, content);

      if (ctx?.kind === "object_value" || ctx?.kind === "array_element") {
        const semPath = await getSemPathForFileNoRepair(document.uri, content, { position: posObj });
        if (semPath) {
          const semContent = await fileUtils.readFile(semPath);
          const semParsed = JSON.parse(semContent);
          const valueItems = getCompletionItemsForType(
            semParsed,
            ctx.expectedType,
            ctx.prefix ?? "",
            _textDocsParams.textDocument.uri
          );
          if (valueItems?.length) return valueItems;
        }
        // SEM may fail when there are errors elsewhere (e.g. println(c.b.b) when c is array).
        // Fall back to AST-based completion so suggestions work independently of other errors.
        const fallbackSuggestion = {
          token: { value: ctx.prefix ?? "", lineNumber: pos.line, columnNumber: pos.character },
          word: ctx.prefix ?? "",
          data: { isDot: false, isValueCompletion: true },
        };
        const astItems = await getCompletionItems(
          astPathNoRepair,
          fallbackSuggestion as Parameters<typeof getCompletionItems>[1],
          _textDocsParams.textDocument.uri,
          documents
        );
        if (astItems?.length) return astItems;
      }

      if (ctx?.kind === "object_member" && ctx.expectedType && ctx.existingMembers) {
        const semPath = await getSemPathForFileNoRepair(document.uri, content, { position: posObj });
        if (semPath) {
          const semContent = await fileUtils.readFile(semPath);
          const semParsed = JSON.parse(semContent);
           let items = getObjectMemberCompletionItems(
             semParsed,
             ctx.expectedType,
             ctx.existingMembers,
             _textDocsParams.textDocument.uri
           );
           if (ctx.prefix) {
             const p = ctx.prefix.toLowerCase();
             items = items.filter((i) => i.label?.toLowerCase().startsWith(p));
           }
           if (items?.length) return items;
         }
        // SEM failed (e.g. error elsewhere); fall back to AST for generic completions
        const fallbackSuggestion = {
          token: { value: ctx.prefix ?? "", lineNumber: pos.line, columnNumber: pos.character },
          word: ctx.prefix ?? "",
          data: { isDot: false },
        };
        const astItems = await getCompletionItems(
          astPathNoRepair,
          fallbackSuggestion as Parameters<typeof getCompletionItems>[1],
          _textDocsParams.textDocument.uri,
          documents
        );
        if (astItems?.length) return astItems;
      }
    } catch (e) {
      logger.trace("completion", "tree context failed", String(e));
    }
  }

  // 3. Fallback to token-based suggestion + sem/ast with repair
  let suggestion = checkForObjectSuggestions(tokens);
  // Token-based check only gets the last identifier before dot (e.g. "b" for c[0].b.). Use full path for member completion.
  if (suggestion.hasObjectSuggestions && suggestion.data?.isDot) {
    const fullPath = getFullPathAtPosition(content, posObj);
    if (fullPath) {
      suggestion = { ...suggestion, word: fullPath };
    }
  }
  // When tokens fail (e.g. d[0]. in function body - completed content has "a" so last token isn't "."),
  // detect "cursor after dot" from document and treat as member access.
  if (!suggestion.hasObjectSuggestions || !suggestion.data?.isDot) {
    const line = content.split("\n")[pos.line] ?? "";
    const charBefore = pos.character > 0 ? line[pos.character - 1] : "";
    if (charBefore === ".") {
      const fullPath = getFullPathAtPosition(content, posObj);
      if (fullPath) {
        suggestion = {
          hasObjectSuggestions: true,
          token: null,
          word: fullPath,
          shouldNotProvideSuggestion: false,
          data: { isDot: true, argumentNumber: 0 },
        };
      }
    }
  }

  if (suggestion.shouldNotProvideSuggestion) return [];

  const partialId = suggestion.word;

  // For member access (d[0].), use NoRepair: raw content fails to parse, but makeCodeCompleteForLsp
  // produces valid code (d[0].a) so we get SEM. Identifier repair doesn't help for "d[0]".
  const semPath =
    suggestion.data?.isDot
      ? await getSemPathForFileNoRepair(document.uri, content, { position: posObj })
      : await getSemPathForDocument(document, {
          position: posObj,
          partialId: partialId || undefined,
        });
  const treePath =
    semPath ??
    (await getAstPathForDocument(document, {
      position: posObj,
      partialId: partialId || undefined,
    }));

  if (treePath) {
    return (
      (await getCompletionItems(
        treePath,
        suggestion,
        _textDocsParams.textDocument.uri,
        documents
      )) ?? []
    );
  }

  return [];
};
