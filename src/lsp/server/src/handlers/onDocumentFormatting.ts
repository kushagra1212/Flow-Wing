import { _Connection, TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import {
  formatFlowWingFile,
  validateTextDocument,
} from "../services/documentService";

export const onDocumentFormatting = async (
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) => {
  connection.onDocumentFormatting(async (params) => {
    const document = documents.get(params.textDocument.uri);

    if (!document) return;

    const text = await formatFlowWingFile(
      params.textDocument.uri,
      document.getText()
    );
    return [
      {
        newText: text,
        range: {
          start: { line: 0, character: 0 },
          end: document.positionAt(document.getText().length),
        },
      },
    ];
  });
};
