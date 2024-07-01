import {
  createConnection,
  TextDocuments,
  Diagnostic,
  DiagnosticSeverity,
  ProposedFeatures,
  InitializeParams,
  DidChangeConfigurationNotification,
  CompletionItem,
  CompletionItemKind,
  TextDocumentPositionParams,
  TextDocumentSyncKind,
  InitializeResult,
  CompletionItemTag,
  HoverParams,
  Range,
  Position,
} from "vscode-languageserver/node";
import { TextDocument } from "vscode-languageserver-textdocument";
import { keywordsCompletionItems } from "./store";
import { createFileAndAppend, getTempFgCodeFilePath } from "./utils";
import { validateFile } from "./validation/validateFile";

// Create a connection for the server, using Node's IPC as a transport.
// Also include all preview / proposed LSP features.
const connection = createConnection(ProposedFeatures.all);

// Create a simple text document manager.
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

let hasConfigurationCapability: boolean = false;
let hasWorkspaceFolderCapability: boolean = false;
let hasDiagnosticRelatedInformationCapability: boolean = false;

connection.onInitialize((params: InitializeParams) => {
  const capabilities = params.capabilities;

  // Does the client support the `workspace/configuration` request?
  // If not, we fall back using global settings.
  hasConfigurationCapability = !!(
    capabilities.workspace && !!capabilities.workspace.configuration
  );
  hasWorkspaceFolderCapability = !!(
    capabilities.workspace && !!capabilities.workspace.workspaceFolders
  );
  hasDiagnosticRelatedInformationCapability = !!(
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
      },
      hoverProvider: true,
    },
  };
  if (hasWorkspaceFolderCapability) {
    result.capabilities.workspace = {
      workspaceFolders: {
        supported: true,
      },
    };
  }
  return result;
});

connection.onInitialized(() => {
  if (hasConfigurationCapability) {
    // Register for all configuration changes.
    connection.client.register(
      DidChangeConfigurationNotification.type,
      undefined
    );
  }
  if (hasWorkspaceFolderCapability) {
    connection.workspace.onDidChangeWorkspaceFolders((_event) => {
      connection.console.log("Workspace folder change event received.");
    });
  }
});

// The example settings
interface ExampleSettings {
  maxNumberOfProblems: number;
}

// The global settings, used when the `workspace/configuration` request is not supported by the client.
// Please note that this is not the case when using this server with the client provided in this example
// but could happen with other clients.
const defaultSettings: ExampleSettings = { maxNumberOfProblems: 1000 };
let globalSettings: ExampleSettings = defaultSettings;

// Cache the settings of all open documents
const documentSettings: Map<string, Thenable<ExampleSettings>> = new Map();

connection.onDidChangeConfiguration((change) => {
  if (hasConfigurationCapability) {
    // Reset all cached document settings
    documentSettings.clear();
  } else {
    globalSettings = <ExampleSettings>(
      (change.settings.languageServerExample || defaultSettings)
    );
  }

  // Revalidate all open text documents
  documents.all().forEach(validateTextDocument);
});

function getDocumentSettings(resource: string): Thenable<ExampleSettings> {
  return Promise.resolve(globalSettings);

  let result = documentSettings.get(resource);
  if (!result) {
    result = connection.workspace.getConfiguration({
      scopeUri: resource,
      section: "flow-wing",
    });
    documentSettings.set(resource, result);
  }
  return result;
}

// Only keep settings for open documents
documents.onDidClose((e) => {
  documentSettings.delete(e.document.uri);
});

// The content of a text document has changed. This event is emitted
// when the text document first opened or when its content has changed.
documents.onDidChangeContent((change) => {
  validateTextDocument(change.document);
});

async function validateTextDocument(textDocument: TextDocument): Promise<void> {
  // In this simple example we get the settings for every validate run.
  const settings = await getDocumentSettings(textDocument.uri);
  // The validator creates diagnostics for all uppercase words length 2 and more
  const text = textDocument.getText();
  const path = getTempFgCodeFilePath("code.fg");
  createFileAndAppend(path, text);

  connection.sendDiagnostics({ uri: textDocument.uri, diagnostics: [] });

  const result = await validateFile(path);

  if (!result.hasError) {
    return;
  }

  const diagnostics: Diagnostic[] = [];

  const range = Range.create(
    Position.create(result.lineNumber, 0),
    Position.create(result.lineNumber, result.columnNumber)
  );

  const diagnostic: Diagnostic = {
    severity: DiagnosticSeverity.Error,
    range,
    message: result.errorMessage,
    source: textDocument.uri,
    relatedInformation: [
      {
        location: {
          uri: textDocument.uri,
          range,
        },
        message: result.stdoutWithoutColors,
      },
    ],
  };

  diagnostics.push(diagnostic);
  // Send the computed diagnostics to VS Code.
  connection.sendDiagnostics({ uri: textDocument.uri, diagnostics });
}

connection.onDidChangeWatchedFiles((_change) => {
  // Monitored files have change in VS Code
  connection.console.log("We received a file change event");
});

// This handler provides the initial list of the completion items.
connection.onCompletion(
  (_textDocumentPosition: TextDocumentPositionParams): CompletionItem[] => {
    // The pass parameter contains the position of the text document in
    // which code complete got requested. For the example we ignore this
    // info and always provide the same completion items.
    return keywordsCompletionItems;
  }
);

// This handler resolves additional information for the item selected in
// the completion list.
connection.onCompletionResolve((item: CompletionItem): CompletionItem => {
  console.log("Item", item);
  if (item.data === 1) {
    item.detail = "TypeScript details";
    item.documentation = "TypeScript documentation";
  } else if (item.data === 2) {
    item.detail = "JavaScript details";
    item.documentation = "JavaScript documentation";
  }
  return item;
});

connection.onHover((params: HoverParams) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return;
  }

  const text = document.getText(
    Range.create(Position.create(0, 0), params.position)
  );
  const lines = text.split("\n");

  const lastLine = lines[lines.length - 1];

  const words = lastLine.split(/\s+/);
  const lastWord = words[words.length - 1];

  if (!lastWord) {
    return;
  }
  return {
    contents: keywordsCompletionItems.find(
      (item) => item.label.substring(0, lastWord.length) === lastWord
    )?.documentation,
  };
});

// Make the text document manager listen on the connection
// for open, change and close text document events
documents.listen(connection);

// Listen on the connection
connection.listen();
