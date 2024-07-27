import { _Connection, HoverParams, TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import {
  getDocumentationForCompletionItem,
  getSuggestionHandlerObject,
} from "../services/suggestionService";
import { checkForHover } from "../utils";
import { getCompletionItems } from "../completionItemProvider";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { getObjectSuggestion } from "./onCompletion";

export const onHover = async (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onHover(async (params: HoverParams) => {
    const suggestion = await getSuggestionHandlerObject(
      params,
      documents,
      checkForHover
    );

    if (!suggestion?.hasHoverResult) {
      return {
        contents: null,
      };
    }

    const documentation = await getDocumentationForCompletionItem(
      params.textDocument.uri,
      suggestion
    );

    return {
      contents: documentation,
    };
  });
};
