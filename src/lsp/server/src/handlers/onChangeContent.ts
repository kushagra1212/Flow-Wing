import { _Connection, TextDocuments } from "vscode-languageserver";
import { validateTextDocument } from "../services/documentService";
import { TextDocument } from "vscode-languageserver-textdocument";

export function onChangeContent(
  documents: TextDocuments<TextDocument>,
  connection: _Connection
) {
  documents.onDidChangeContent((change: any) => {
    documents.all().forEach((doc, index, docs) => {
      validateTextDocument(doc, connection);
    });
  });
}
