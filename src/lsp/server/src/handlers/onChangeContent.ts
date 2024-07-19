import { _Connection, TextDocuments } from "vscode-languageserver";
import { validateTextDocument } from "../services/documentService";
import { TextDocument } from "vscode-languageserver-textdocument";

export function onChangeContent(
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) {
  documents.onDidChangeContent((change: any) => {
    validateTextDocument(change.document, connection);
  });
}
