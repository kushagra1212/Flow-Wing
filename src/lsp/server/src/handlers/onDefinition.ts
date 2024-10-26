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
  getModulePath,
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
    if (suggestion.word && suggestion.word.endsWith(".fg")) {
      uri = await getImportedFileUri(
        suggestion.word,
        _textDocsParams.textDocument.uri
      );
    } else if (suggestion.word && suggestion.word.split("::")[0]) {
      const moduleName = suggestion.word.split("::")[0];

      uri = await fileUtils.findFileBreadthFirst(
        getModulePath(),
        moduleName + "-module.fg"
      );

      if (!uri)
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

    let completionItem = result?.find((item) => item.label === suggestion.word);

    let range = null;
    if (completionItem?.data?.range) {
      range = completionItem?.data?.range;
    } else if (result?.length === 1 && result?.[0]?.data?.range) {
      completionItem = result?.[0];
      range = result?.[0]?.data?.range;
    }

    if (!uri) {
      uri = _textDocsParams.textDocument.uri;
    }

    if (uri !== _textDocsParams.textDocument.uri) {
      // range = createRange(undefined).range;
    }

    if (!range) {
      range = Range.create(0, 0, 0, 0);
    }

    return Location.create(uri, range);
  });
};
