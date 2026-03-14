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
  getFileFullPath,
  getImportedFileUri,
} from "../utils";
import { getCompletionItems } from "../completionItemProvider";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import path = require("path");
import {
  getSemPathForDocument,
  getAstPathForDocument,
} from "../services/documentService";
import {
  getSymbolAtPosition,
  getDeclarationForSymbol,
  isSemFormat,
} from "../services/semService";

export const onDefinition = async (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onDefinition(async (params) => {
    const document = documents.get(params.textDocument.uri);
    if (!document) return null;

    let uri = params.textDocument.uri;

    // Prefer sem-based go-to-definition
    const semPath = await getSemPathForDocument(document);
    const treePath = semPath ?? (await getAstPathForDocument(document));
    if (treePath) {
      try {
        const content = await fileUtils.readFile(treePath);
        const parsed = JSON.parse(content);
        if (isSemFormat(parsed)) {
          const atPos = getSymbolAtPosition(parsed, params.position);
          if (atPos) {
            const loc = getDeclarationForSymbol(
              parsed,
              atPos.symbolId,
              params.textDocument.uri
            );
            if (loc) return loc;
          }
        }
      } catch {
        /* fall through */
      }
    }

    // Fallback: suggestion + completion-based
    const suggestion = await getSuggestionHandlerObject(
      params,
      documents,
      checkForHover
    );
    if (suggestion.word && suggestion.word.endsWith(".fg")) {
      uri = await getImportedFileUri(
        suggestion.word,
        params.textDocument.uri
      );
    } else if (suggestion.word && suggestion.word.split("::")[0]) {
      const moduleName = suggestion.word.split("::")[0];

      const found = await fileUtils.findFileBreadthFirst(
        flowWingConfig.modulePath,
        moduleName + "-module.fg"
      );
      if (found) uri = "file://" + found;
      else {
        const local = await fileUtils.findFileBreadthFirst(
          path.dirname(getFileFullPath(params.textDocument.uri)),
          moduleName + "-module.fg"
        );
        if (local) uri = "file://" + local;
      }
    }

    if (!treePath) return Location.create(uri, Range.create(0, 0, 0, 0));

    const result = await getCompletionItems(
      treePath,
      suggestion,
      params.textDocument.uri
    );

    let completionItem = result?.find((item) => item.label === suggestion.word);
    let range: Range | null = null;
    if (completionItem?.data?.range) {
      range = completionItem.data.range as Range;
    } else if (result?.length === 1 && result?.[0]?.data?.range) {
      range = result[0].data?.range as Range;
    }

    if (!uri) uri = params.textDocument.uri;
    if (!range) range = Range.create(0, 0, 0, 0);

    return Location.create(uri, range);
  });
};
