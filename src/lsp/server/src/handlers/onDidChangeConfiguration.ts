import { _Connection, TextDocuments } from "vscode-languageserver";

import { validateTextDocument } from "../services/documentService";
import { documentSettings } from "../common";
import { InitializationHandler } from "./InitializationHandler";
import { TextDocument } from "vscode-languageserver-textdocument";
import { flowWingConfig } from "../config";
import { getModulePath } from "../utils";

export const onDidChangeConfiguration = (
  connection: _Connection,
  initializationHandler: InitializationHandler,
  documents: TextDocuments<TextDocument>
) => {
  connection.onDidChangeConfiguration(() => {
    void connection.workspace.getConfiguration("FlowWing").then((config) => {
      if (initializationHandler.getHasConfigurationCapability()) {
        documentSettings.clear();
      }

      // Do not set flowWingPath to the string "FlowWing" (config default) — that
      // would overwrite the absolute path from initialization / workspace
      // discovery and make execFile resolve via PATH (often a stale system copy),
      // while the CLI used from the repo with an explicit path is correct.
      if (
        typeof config?.compilerPath === "string" &&
        config.compilerPath &&
        config.compilerPath !== "FlowWing"
      ) {
        flowWingConfig.flowWingPath = config.compilerPath;
      }
      if (config?.modulePath !== undefined) {
        flowWingConfig.modulePath =
          typeof config.modulePath === "string" && config.modulePath.length > 0
            ? config.modulePath
            : getModulePath();
      }

      for (const doc of documents.all()) {
        void validateTextDocument(doc, connection);
      }
    });
  });
};
