import { TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { documentSettings } from "../common";
import { validateTextDocument } from "../services/documentService";

export const onDidClose = (documents: TextDocuments<TextDocument>) => {
  documents.onDidClose((d) => {
    documentSettings.delete(d.document.uri);
  });
};
