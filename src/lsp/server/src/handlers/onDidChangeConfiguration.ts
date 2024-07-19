import { _Connection } from "vscode-languageserver";
import {
  connection,
  defaultSettings,
  documents,
  documentSettings,
  ExampleSettings,
  initializationHandler,
} from "../server";
import { validateTextDocument } from "../services/documentService";
import { InitializationHandler } from "./InitializationHandler";

let globalSettings: ExampleSettings = defaultSettings;

export const onDidChangeConfiguration = () => {
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
