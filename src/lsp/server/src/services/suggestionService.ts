import {
  MarkupContent,
  TextDocumentPositionParams,
  TextDocuments,
} from "vscode-languageserver";
import {
  defaultValueNoSuggestion,
  getTempFileBasename,
  getIdentifierAtPosition,
  makeCodeCompleteForLsp,
  tryRepairCallForSem,
  tryRepairContentForSem,
  SuggestHandler,
} from "../utils";
import { Token } from "../types";
import { TextDocument } from "vscode-languageserver-textdocument";
import {
  runCompilerWithEmit,
} from "./documentService";
import { logger } from "./loggerService";
import { getCompletionItems, readTokens } from "../completionItemProvider";
import { fileUtils } from "../utils/fileUtils";
import { randomBytes } from "node:crypto";
import * as path from "path";
import * as os from "os";

/**
 * Returns tokens for the document at the given position, using repair strategies if needed.
 * Optimized to be called once per completion/hover request.
 */
export const getTokensForContext = async (
  document: TextDocument,
  position: { line: number; character: number }
): Promise<Token[]> => {
  try {
    const basename = getTempFileBasename(document.uri);
    const content = document.getText();
    const outputDir = path.join(os.tmpdir(), `flowwing-lsp-tokens-${Date.now()}-${randomBytes(4).toString("hex")}`);

    const variants: string[] = [
      content,
      makeCodeCompleteForLsp(content),
    ];

    // Call repair helps when cursor is in test(|) with no partial identifier
    const callRepaired = tryRepairCallForSem(content);
    if (callRepaired) variants.push(makeCodeCompleteForLsp(callRepaired));

    const partialId = getIdentifierAtPosition(content, position);
    logger.trace("tokens", "position", position, "partialId", partialId);
    if (partialId) {
      const repaired = tryRepairContentForSem(content, partialId, position);
      if (repaired) {
        variants.push(makeCodeCompleteForLsp(repaired));
        const callRepairedFromContent = tryRepairCallForSem(repaired);
        if (callRepairedFromContent) variants.push(makeCodeCompleteForLsp(callRepairedFromContent));
      }
    }

    for (const data of variants) {
      try {
        const tempPath = await fileUtils.createTempFile({
          fileName: basename + ".fg",
          data,
        });
        const tokensPath = await runCompilerWithEmit(tempPath, "tokens", outputDir);
        logger.trace("tokens", "resolved", tokensPath);
        return await readTokens(tokensPath, position);
      } catch (e) {
        logger.trace("tokens", "variant failed", String(e));
        continue;
      }
    }
  } catch (err) {
    console.error("Error getting tokens for context:", err);
  }
  return [];
};

/**
 * @deprecated Use getTokensForContext and call it once.
 */
export const getSuggestionHandlerObject = async (
  _textDocsParams: TextDocumentPositionParams,
  documents: TextDocuments<TextDocument>,
  callBack: (tokens: Token[]) => SuggestHandler
): Promise<SuggestHandler> => {
  const document = documents.get(_textDocsParams.textDocument.uri);
  if (!document) return defaultValueNoSuggestion;

  const tokens = await getTokensForContext(document, _textDocsParams.position);
  return callBack(tokens);
};

export const getDocumentationForCompletionItem = async (
  textDocUri: string,
  suggestion: SuggestHandler,
  documentText: string
): Promise<string | null | MarkupContent> => {
  try {
    const basename = getTempFileBasename(textDocUri);
    const outputDir = path.join(os.tmpdir(), `flowwing-lsp-hover-${Date.now()}-${randomBytes(4).toString("hex")}`);

    let treePath: string | null = null;
    const variants: string[] = [
      documentText,
      makeCodeCompleteForLsp(documentText),
    ];
    
    if (suggestion?.word && suggestion?.token) {
      const tok = suggestion.token;
      const charEnd = tok.columnNumber + (tok.value?.length ?? 0);
      const repaired = tryRepairContentForSem(
        documentText,
        suggestion.word,
        { line: tok.lineNumber, character: charEnd }
      );
      if (repaired) {
        variants.push(makeCodeCompleteForLsp(repaired));
        const callRepaired = tryRepairCallForSem(repaired);
        if (callRepaired) variants.push(makeCodeCompleteForLsp(callRepaired));
      }
    } else {
        const callRepaired = tryRepairCallForSem(documentText);
        if (callRepaired) variants.push(makeCodeCompleteForLsp(callRepaired));
    }

    for (const data of variants) {
      try {
        const tp = await fileUtils.createTempFile({
          fileName: basename + "-hover.fg",
          data,
        });
        treePath = await runCompilerWithEmit(tp, "sem", outputDir);
        break;
      } catch {
        try {
          const tp = await fileUtils.createTempFile({
            fileName: basename + "-hover.fg",
            data,
          });
          treePath = await runCompilerWithEmit(tp, "ast", outputDir);
          break;
        } catch {
          continue;
        }
      }
    }
    if (!treePath) return null;

    const result = await getCompletionItems(treePath, suggestion, textDocUri);

    return (
      result?.find((item) => item.label === suggestion.word)?.documentation ??
      (result?.length === 1 && result?.[0].documentation
        ? result?.[0].documentation
        : null)
    );
  } catch {
    return null;
  }
};
