import {
  MarkupContent,
  TextDocumentPositionParams,
  TextDocuments,
} from "vscode-languageserver";
import {
  defaultValueNoSuggestion,
  getFileFullPath,
  SuggestHandler,
} from "../utils";
import { Token } from "../types";
import { TextDocument } from "vscode-languageserver-textdocument";
import { validateTextDocument } from "./documentService";
import { getCompletionItems, readTokens } from "../completionItemProvider";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";

export const getSuggestionHandlerObject = async (
  _textDocsParams: TextDocumentPositionParams,
  documents: TextDocuments<TextDocument>,
  callBack: (tokens: Token[]) => SuggestHandler
): Promise<SuggestHandler> => {
  const document = documents.get(_textDocsParams.textDocument.uri);

  if (!document) return defaultValueNoSuggestion;

  try {
    //? Added this to get Latest token
    await validateTextDocument(document, null);

    const tokens = await readTokens(
      fileUtils.getTempFilePath({
        fileName:
          getFileFullPath(_textDocsParams.textDocument.uri) +
          flowWingConfig.temp.tokenFileExt,
      }),
      _textDocsParams.position
    );

    return callBack(tokens);
  } catch (err) {
    console.log("🚀 ~ err~read-token~getSuggestion", err);
    return defaultValueNoSuggestion;
  }
};

export const getDocumentationForCompletionItem = async (
  textDocUri: string,
  suggestion: SuggestHandler
): Promise<string | null | MarkupContent> => {
  try {
    const result = await getCompletionItems(
      fileUtils.getTempFilePath({
        fileName:
          getFileFullPath(textDocUri) + flowWingConfig.temp.syntaxFileExt,
      }),
      suggestion,
      textDocUri
    );

    return (
      result?.find((item) => item.label === suggestion.word)?.documentation ??
      (result?.length === 1 && result?.[0].documentation
        ? result?.[0].documentation
        : null)
    );
  } catch (err) {
    console.log("🚀 ~ getDocumentationForCompletionItem ~ err:", err);
    return null;
  }
};
