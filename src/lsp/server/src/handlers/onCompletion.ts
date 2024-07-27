import {
  _Connection,
  CompletionItem,
  TextDocumentPositionParams,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSuggestionHandlerObject } from "../services/suggestionService";
import { checkForObjectSuggestions, getFileFullPath } from "../utils";
import { getCompletionItems } from "../completionItemProvider";
import { flowWingConfig } from "../config";
import { fileUtils } from "../utils/fileUtils";

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
) => {
  const suggestion = await getSuggestionHandlerObject(
    _textDocsParams,
    documents,
    checkForObjectSuggestions
  );

  // if (suggestion.shouldNotProvideSuggestion || !suggestion.hasObjectSuggestions)
  //   return [];

  const result = await getCompletionItems(
    fileUtils.getTempFilePath({
      fileName:
        getFileFullPath(_textDocsParams.textDocument.uri) +
        flowWingConfig.temp.syntaxFileExt,
    }),
    suggestion
  );

  return result;
};
