import {
  _Connection,
  SignatureHelp,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSuggestionHandlerObject } from "../services/suggestionService";
import { getCompletionItems } from "../completionItemProvider";
import { flowWingConfig } from "../config";
import { fileUtils } from "../utils/fileUtils";
import { checkForFunctionSignatures, getFileFullPath } from "../utils";

export const onSignatureHelp = (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onSignatureHelp(async (params): Promise<SignatureHelp> => {
    const suggestion = await getSuggestionHandlerObject(
      params,
      documents,
      checkForFunctionSignatures
    );

    const result = await getCompletionItems(
      fileUtils.getTempFilePath({
        fileName:
          getFileFullPath(params.textDocument.uri) +
          flowWingConfig.temp.syntaxFileExt,
      }),
      suggestion,
      params.textDocument.uri
    );

    if (!result?.length || !suggestion?.hasFunctionSignature) return;

    let res = result.find((item) => item.label === suggestion.word);

    if (!res) {
      res = result[0];
    }
    return {
      signatures: res.data?.signatures,
      activeSignature: 0,
      activeParameter: suggestion?.data?.argumentNumber - 1,
    };
  });
};
