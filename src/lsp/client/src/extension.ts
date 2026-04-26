/* --------------------------------------------------------------------------------------------
 * Flow-Wing LSP client for VS Code / compatible editors.
 * SPDX-License-Identifier: GPL-2.0-only
 * ------------------------------------------------------------------------------------------ */
import * as path from "path";
import * as os from "os";
import {
  workspace as Workspace,
  window as Window,
  ExtensionContext,
  TextDocument,
  OutputChannel,
  WorkspaceFolder,
  Uri,
} from "vscode";

import {
  LanguageClient,
  LanguageClientOptions,
  ServerOptions,
  TransportKind,
} from "vscode-languageclient/node";

const clients: Map<string, LanguageClient> = new Map();

function flowWingBinaryName(): string {
  return os.platform() === "win32" ? "FlowWing.exe" : "FlowWing";
}

let _sortedWorkspaceFolders: string[] | undefined;
function sortedWorkspaceFolders(): string[] {
  if (_sortedWorkspaceFolders === void 0) {
    _sortedWorkspaceFolders = Workspace.workspaceFolders
      ? Workspace.workspaceFolders
          .map((folder) => {
            let result = folder.uri.toString();
            if (result.charAt(result.length - 1) !== "/") {
              result = result + "/";
            }
            return result;
          })
          .sort((a, b) => {
            return a.length - b.length;
          })
      : [];
  }
  return _sortedWorkspaceFolders;
}
Workspace.onDidChangeWorkspaceFolders(
  () => (_sortedWorkspaceFolders = undefined)
);

function getOuterMostWorkspaceFolder(folder: WorkspaceFolder): WorkspaceFolder {
  const sorted = sortedWorkspaceFolders();
  for (const element of sorted) {
    let uri = folder.uri.toString();
    if (uri.charAt(uri.length - 1) !== "/") {
      uri = uri + "/";
    }
    if (uri.startsWith(element)) {
      return Workspace.getWorkspaceFolder(Uri.parse(element))!;
    }
  }
  return folder;
}

function resolveCompilerPath(
  configPath: string | undefined,
  workspaceFolders: readonly { uri: { fsPath: string } }[] | undefined
): string {
  if (configPath && path.isAbsolute(configPath)) {
    return configPath;
  }
  if (configPath && configPath !== "FlowWing") {
    return configPath;
  }
  const bin = flowWingBinaryName();
  const paths = (workspaceFolders ?? []).map((f) => f.uri.fsPath);
  const root = paths.sort((a, b) => a.length - b.length)[0];
  if (root) {
    return path.join(root, "build", "sdk", "bin", bin);
  }
  return configPath ?? "FlowWing";
}

export function activate(extContext: ExtensionContext) {
  const enabled = Workspace.getConfiguration("FlowWing").get<boolean>(
    "enable",
    true
  );
  if (!enabled) {
    return;
  }

  const module = extContext.asAbsolutePath(
    path.join("server", "out", "server.js")
  );
  const outputChannel: OutputChannel = Window.createOutputChannel("Flow-Wing");

  const configPath =
    Workspace.getConfiguration("FlowWing").get<string>("compilerPath");
  const sorted = (Workspace.workspaceFolders ?? [])
    .map((f) => f.uri.fsPath)
    .sort((a, b) => a.length - b.length);
  const root = sorted[0];
  const compilerPath = resolveCompilerPath(
    configPath,
    Workspace.workspaceFolders
  );
  const rawModulePath =
    Workspace.getConfiguration("FlowWing").get<string>("modulePath");
  const modulePath =
    rawModulePath && rawModulePath !== "flowwing"
      ? rawModulePath
      : root
        ? path.join(root, "build", "sdk", "lib", "modules")
        : undefined;

  function didOpenTextDocument(document: TextDocument): void {
    if (
      document.languageId !== "flowwing" ||
      (document.uri.scheme !== "file" && document.uri.scheme !== "untitled")
    ) {
      return;
    }

    const uri = document.uri;
    let folder = Workspace.getWorkspaceFolder(uri);
    if (!folder) {
      return;
    }
    folder = getOuterMostWorkspaceFolder(folder);

    if (!clients.has(folder.uri.toString())) {
      const serverOptions = {
        run: { module, transport: TransportKind.ipc },
        debug: { module, transport: TransportKind.ipc },
      };
      const clientOptions: LanguageClientOptions = {
        documentSelector: [
          {
            scheme: "file",
            language: "flowwing",
            pattern: `${folder.uri.fsPath}/**/*`,
          },
        ],
        diagnosticCollectionName: "flowwing",
        workspaceFolder: folder,
        outputChannel: outputChannel,
        initializationOptions: { compilerPath, modulePath },
      };
      const client = new LanguageClient(
        "flowwing",
        "Flow-Wing Language Server",
        serverOptions,
        clientOptions
      );
      client.start();
      clients.set(folder.uri.toString(), client);
    }
  }

  Workspace.onDidOpenTextDocument(didOpenTextDocument);
  Workspace.textDocuments.forEach(didOpenTextDocument);
  Workspace.onDidChangeWorkspaceFolders((event) => {
    for (const folder of event.removed) {
      const client = clients.get(folder.uri.toString());
      if (client) {
        clients.delete(folder.uri.toString());
        void client.stop();
      }
    }
  });
}

export function deactivate(): Thenable<void> {
  const promises: Thenable<void>[] = [];
  for (const client of clients.values()) {
    promises.push(client.stop());
  }
  return Promise.all(promises).then(() => undefined);
}
