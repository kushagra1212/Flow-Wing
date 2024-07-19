import {
  _Connection,
  SignatureHelp,
  TextDocuments,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getSuggestionHandlerObject } from "../services/suggestionService";
import { getCompletionItems } from "../hover";
import { flowWingConfig } from "../config/config";
import { fileUtils } from "../utils/fileUtils";
import { checkForFunctionSignatures } from "../utils";

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
        fileName: flowWingConfig.temp.syntaxFileName,
      }),
      suggestion
    );

    if (!result?.length || !suggestion?.hasFunctionSignature) return;

    return {
      signatures: result[0].data?.signatures,
      activeSignature: 0,
      activeParameter: suggestion?.data?.argumentNumber - 1,
    };
  });
};
