/* --------------------------------------------------------------------------------------------
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License. See License.txt in the project root for license information.
 * ------------------------------------------------------------------------------------------ */
import * as path from "path";
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

let defaultClient: LanguageClient;
const clients: Map<string, LanguageClient> = new Map();

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
  // Default "FlowWing" not in PATH - use project root (shortest path), not LatestTests
  const paths = (workspaceFolders ?? []).map((f) => f.uri.fsPath);
  const root = paths.sort((a, b) => a.length - b.length)[0];
  if (root) {
    return path.join(root, "build", "sdk", "bin", "FlowWing");
  }
  return configPath ?? "FlowWing";
}

export function activate(context: ExtensionContext) {
  const module = context.asAbsolutePath(
    path.join("server", "out", "server.js")
  );
  const outputChannel: OutputChannel = Window.createOutputChannel("flow-wing");
  // Defer show so flow-wing output is selected after other extensions (e.g. pip)
  setTimeout(() => outputChannel.show(), 1500);
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
  // Empty or legacy "flowwing" default causes ENOENT scandir. Use workspace fallback.
  const modulePath =
    rawModulePath && rawModulePath !== "flowwing"
      ? rawModulePath
      : root
        ? path.join(root, "build", "sdk", "lib", "modules")
        : undefined;

  function didOpenTextDocument(document: TextDocument): void {
    // We are only interested in language mode text
    if (
      document.languageId !== "flowwing" ||
      (document.uri.scheme !== "file" && document.uri.scheme !== "untitled")
    ) {
      return;
    }

    const uri = document.uri;
    // Untitled files go to a default client.
    if (uri.scheme === "flow-wing" && !defaultClient) {
      const serverOptions: ServerOptions = {
        run: { module, transport: TransportKind.ipc },
        debug: { module, transport: TransportKind.ipc },
      };
      const clientOptions: LanguageClientOptions = {
        documentSelector: [{ scheme: "flow-wing", language: "flowwing" }],
        diagnosticCollectionName: "FlowWing",
        outputChannel: outputChannel,
        initializationOptions: { compilerPath, modulePath },
      };
      defaultClient = new LanguageClient(
        "FlowWing",
        "A Flow-Wing language server for VSCode",
        serverOptions,
        clientOptions
      );
      defaultClient.start();
      return;
    }
    let folder = Workspace.getWorkspaceFolder(uri);
    // Files outside a folder can't be handled. This might depend on the language.
    // Single file languages like JSON might handle files outside the workspace folders.
    if (!folder) {
      return;
    }
    // If we have nested workspace folders we only start a server on the outer most workspace folder.
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
        diagnosticCollectionName: "flow-wing",
        workspaceFolder: folder,
        outputChannel: outputChannel,
        initializationOptions: { compilerPath, modulePath },
      };
      const client = new LanguageClient(
        "flow-wing",
        "A Flow-Wing language server for VSCode",
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
        client.stop();
      }
    }
  });
}

export function deactivate(): Thenable<void> {
  const promises: Thenable<void>[] = [];
  if (defaultClient) {
    promises.push(defaultClient.stop());
  }
  for (const client of clients.values()) {
    promises.push(client.stop());
  }
  return Promise.all(promises).then(() => undefined);
}
