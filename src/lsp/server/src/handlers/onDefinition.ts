import {
  _Connection,
  Location,
  Range,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSuggestionHandlerObject } from "../services/suggestionService";
import {
  checkForHover,
  createRange,
  getFileFullPath,
  getImportedFileUri,
} from "../utils";
import { getCompletionItems } from "../completionItemProvider";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import path = require("path");

export const onDefinition = async (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onDefinition(async (_textDocsParams) => {
    const suggestion = await getSuggestionHandlerObject(
      _textDocsParams,
      documents,
      checkForHover
    );
    let uri = _textDocsParams.textDocument.uri;
    console.log("suggestionDEf", suggestion);
    if (suggestion.word && suggestion.word.endsWith(".fg")) {
      uri = await getImportedFileUri(
        suggestion.word,
        _textDocsParams.textDocument.uri
      );
    } else if (suggestion.word && suggestion.word.indexOf("::") !== -1) {
      const moduleName = suggestion.word.split("::")[0];
      uri = await fileUtils.findFileBreadthFirst(
        path.dirname(getFileFullPath(_textDocsParams.textDocument.uri)),
        moduleName + "-module.fg"
      );
    }

    const result = await getCompletionItems(
      fileUtils.getTempFilePath({
        fileName:
          getFileFullPath(_textDocsParams.textDocument.uri) +
          flowWingConfig.temp.syntaxFileExt,
      }),
      suggestion,
      _textDocsParams.textDocument.uri
    );
    const range =
      result?.find((item) => item.label === suggestion.word)?.data?.range ??
      (result?.length === 1 && result?.[0]?.data?.range
        ? result?.[0]?.data?.range
        : null);

    if (uri !== _textDocsParams.textDocument.uri) {
      // range = createRange(undefined).range;
    }

    if (!range) return undefined;

    return Location.create(uri, range);
  });
};
