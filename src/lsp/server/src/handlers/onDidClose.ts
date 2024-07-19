import { TextDocuments } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { documentSettings } from "../server";

export const onDidClose = (documents: TextDocuments<TextDocument>) => {
  documents.onDidClose((d) => {
    documentSettings.delete(d.document.uri);
  });
};
