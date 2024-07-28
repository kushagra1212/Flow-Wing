import { _Connection, TextDocuments } from "vscode-languageserver";

import { validateTextDocument } from "../services/documentService";
import { defaultSettings, documentSettings } from "../common";
import { ExampleSettings } from "../common/types";
import { InitializationHandler } from "./InitializationHandler";
import { TextDocument } from "vscode-languageserver-textdocument";

let globalSettings: ExampleSettings = defaultSettings;

export const onDidChangeConfiguration = (
  connection: _Connection,
  initializationHandler: InitializationHandler,
  documents: TextDocuments<TextDocument>
) => {
  connection.onDidChangeConfiguration((change) => {
    if (initializationHandler.getHasConfigurationCapability()) {
      // Reset all cached document settings
      documentSettings.clear();
    } else {
      globalSettings = <ExampleSettings>(
        (change.settings.languageServerExample || defaultSettings)
      );
    }

    // Revalidate all open text documents
    documents.all().forEach((doc, index, docs) => {
      return validateTextDocument(doc, connection);
    });
  });
};
