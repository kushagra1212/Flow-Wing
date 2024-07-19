import { _Connection, HoverParams, TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import {
  getDocumentationForCompletionItem,
  getSuggestionHandlerObject,
} from "../services/suggestionService";
import { checkForHover } from "../utils";

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

    if (!suggestion?.hasHoverResult)
      return {
        contents: null,
      };

    const documentation = await getDocumentationForCompletionItem(suggestion);

    return {
      contents: documentation,
    };
  });
};
