import {
  _Connection,
  CompletionItem,
  TextDocumentPositionParams,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSuggestionHandlerObject } from "../services/suggestionService";
import { checkForObjectSuggestions } from "../utils";
import { getCompletionItems } from "../hover";
import { flowWingConfig } from "../config/config";
import { fileUtils } from "../utils/fileUtils";

export async function onCompletion(
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) {
  connection.onCompletion(
    async (
      _textDocsParams: TextDocumentPositionParams
    ): Promise<CompletionItem[]> => {
      const suggestion = await getSuggestionHandlerObject(
        _textDocsParams,
        documents,
        checkForObjectSuggestions
      );

      if (
        suggestion.shouldNotProvideSuggestion ||
        !suggestion.hasObjectSuggestions
      )
        return [];

      const result = await getCompletionItems(
        fileUtils.getTempFilePath({
          fileName: flowWingConfig.temp.syntaxFileName,
        }),
        suggestion
      );

      return result;
    }
  );
}
