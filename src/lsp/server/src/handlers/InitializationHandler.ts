import {
  _Connection,
  DidChangeConfigurationNotification,
  InitializeParams,
  InitializeResult,
  TextDocumentSyncKind,
} from "vscode-languageserver";
import { connection as globalConnection } from "../server";

export const onInitialize = () => {};

export class InitializationHandler {
  private hasConfigurationCapability: boolean = false;
  private hasWorkspaceFolderCapability: boolean = false;
  private hasDiagnosticRelatedInformationCapability: boolean = false;

  constructor(private connection: _Connection) {}

  public initialize() {
    this.connection.onInitialize((params: InitializeParams) => {
      const capabilities = params.capabilities;

      // Does the client support the `workspace/configuration` request?
      // If not, we fall back using global settings.
      this.hasConfigurationCapability = !!(
        capabilities.workspace && !!capabilities.workspace.configuration
      );
      this.hasWorkspaceFolderCapability = !!(
        capabilities.workspace && !!capabilities.workspace.workspaceFolders
      );
      this.hasDiagnosticRelatedInformationCapability = !!(
        capabilities.textDocument &&
        capabilities.textDocument.publishDiagnostics &&
        capabilities.textDocument.publishDiagnostics.relatedInformation
      );

      const result: InitializeResult = {
        capabilities: {
          textDocumentSync: TextDocumentSyncKind.Incremental,
          // Tell the client that this server supports code completion.
          completionProvider: {
            resolveProvider: true,
            triggerCharacters: [".", ",", "{"],
          },
          signatureHelpProvider: {
            triggerCharacters: ["(", ","],
          },
          hoverProvider: true,
          callHierarchyProvider: true,
        },
      };

      if (this.hasWorkspaceFolderCapability) {
        result.capabilities.workspace = {
          workspaceFolders: {
            supported: true,
          },
        };
      }
      return result;
    });

    this.onInitialize();
  }

  private onInitialize() {
    this.connection.onInitialized(() => {
      if (this.hasConfigurationCapability) {
        // Register for all configuration changes.
        this.connection.client.register(
          DidChangeConfigurationNotification.type,
          undefined
        );
      }
      if (this.hasWorkspaceFolderCapability) {
        this.connection.workspace.onDidChangeWorkspaceFolders((_event) => {
          this.connection.console.log(
            "Workspace folder change event received."
          );
        });
      }
    });
  }
  public getHasConfigurationCapability(): boolean {
    return this.hasConfigurationCapability;
  }

  public getHasWorkspaceFolderCapability(): boolean {
    return this.hasWorkspaceFolderCapability;
  }
}
