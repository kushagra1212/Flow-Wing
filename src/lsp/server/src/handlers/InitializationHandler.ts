import {
  _Connection,
  DidChangeConfigurationNotification,
  InitializeParams,
  InitializeResult,
  TextDocuments,
  TextDocumentSyncKind,
  WorkspaceFolder,
} from "vscode-languageserver";
import {
  doesFlowWingCompilerExist,
  validateFile,
} from "../services/documentService";
import { TextDocument } from "vscode-languageserver-textdocument";
import { fileUtils } from "../utils/fileUtils";
import { getFileFullPath, getModulePath } from "../utils";
import { flowWingConfig } from "../config";

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
          definitionProvider: true,
          documentFormattingProvider: true,
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
    this.connection.onInitialized((handler) => {
      this.connection.workspace
        .getConfiguration("FlowWing")
        .then((config) => {
          if (config?.compilerPath) {
            flowWingConfig.flowWingPath = config?.compilerPath;
            console.info(
              `FlowWing compiler path: ${flowWingConfig.flowWingPath}`
            );
          }
          doesFlowWingCompilerExist().then((exists) => {
            flowWingConfig.doesFlowWingExist = exists;
            if (!flowWingConfig.doesFlowWingExist) {
              this.connection.window.showErrorMessage(
                "FlowWing not found. Please install FlowWing and try again reloading the window."
              );
            }
          });
        })
        .catch((err) => {
          console.error(err);
        });

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
        this.connection.workspace.getWorkspaceFolders().then(this.validateAll);
      }
    });
  }
  public getHasConfigurationCapability(): boolean {
    return this.hasConfigurationCapability;
  }

  public getHasWorkspaceFolderCapability(): boolean {
    return this.hasWorkspaceFolderCapability;
  }

  private async validateAll(folders: WorkspaceFolder[]) {
    if (folders) {
      folders.forEach((folder) => {
        const rootPath = getModulePath();

        if (rootPath) {
          fileUtils.bfsTraverseVisit(rootPath, async (uri) => {
            const data = await fileUtils.readFile(uri);
            const path = await fileUtils.createTempFile({
              fileName: uri,
              data,
            });

            await validateFile("file:/" + uri, path);
          });
        }
      });
    }
  }
}
