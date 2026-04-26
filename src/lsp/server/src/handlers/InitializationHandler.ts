import {
  _Connection,
  DidChangeConfigurationNotification,
  InitializeParams,
  InitializeResult,
  TextDocumentSyncKind,
} from "vscode-languageserver";
import { existsSync } from "fs";
import { join } from "path";
import { platform } from "os";
import { doesFlowWingCompilerExist } from "../services/documentService";
import { getModulePath } from "../utils";
import { flowWingConfig } from "../config";

export class InitializationHandler {
  private hasConfigurationCapability: boolean = false;
  private hasWorkspaceFolderCapability: boolean = false;
  private hasDiagnosticRelatedInformationCapability: boolean = false;

  /**
   * Called after workspace `FlowWing` config is applied and `flowWingConfig.flowWingPath` is set.
   * Used to re-run validation so diagnostics appear on open (early validates may have used the
   * default `"FlowWing"` path before async config resolved).
   */
  constructor(
    private connection: _Connection,
    private readonly onWorkspaceCompilerPathReady?: () => void
  ) {}

  public initialize() {
    this.connection.onInitialize((params: InitializeParams) => {
      const capabilities = params.capabilities;

      // Set compiler path from client immediately to avoid race with document open
      const opts = params.initializationOptions as
        | { compilerPath?: string; modulePath?: string }
        | undefined;
      if (opts?.compilerPath) {
        flowWingConfig.flowWingPath = opts.compilerPath;
      }

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
            triggerCharacters: [".", ",", "{", "("],
          },
          signatureHelpProvider: {
            triggerCharacters: ["(", ","],
            retriggerCharacters: [","],
          },
          hoverProvider: true,
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
        .then(async (config) => {
          if (config?.modulePath) {
            flowWingConfig.modulePath = config.modulePath;
          } else {
            flowWingConfig.modulePath = getModulePath();
          }
          let compilerPath = config?.compilerPath ?? "FlowWing";
          if (compilerPath === "FlowWing") {
            const folders = await this.connection.workspace
              .getWorkspaceFolders()
              .catch(() => []);
            const paths = (folders ?? []).map((f) =>
              f.uri.replace(/^file:\/\/?/, "")
            );
            const bin = platform() === "win32" ? "FlowWing.exe" : "FlowWing";
            const findCompiler = (dir: string): string | null => {
              const candidate = join(dir, "build", "sdk", "bin", bin);
              return existsSync(candidate) ? candidate : null;
            };
            for (const p of paths.sort((a, b) => a.length - b.length)) {
              let dir = p;
              for (let i = 0; i < 10 && dir; i++) {
                const found = findCompiler(dir);
                if (found) {
                  compilerPath = found;
                  break;
                }
                const parent = join(dir, "..");
                if (parent === dir) break;
                dir = parent;
              }
              if (compilerPath !== "FlowWing") break;
            }
          }
          flowWingConfig.flowWingPath = compilerPath;
          this.connection.console.info(
            `FlowWing compiler path: ${flowWingConfig.flowWingPath}`
          );
          this.onWorkspaceCompilerPathReady?.();
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
          // Still refresh diagnostics using compiler path from initialize() / defaults.
          this.onWorkspaceCompilerPathReady?.();
        });

      if (this.hasConfigurationCapability) {
        // Register for all configuration changes.
        this.connection.client.register(
          DidChangeConfigurationNotification.type,
          undefined
        );
      }
      if (this.hasWorkspaceFolderCapability) {
        this.connection.workspace.onDidChangeWorkspaceFolders(() => {
          this.connection.console.log("Workspace folder change received.");
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
