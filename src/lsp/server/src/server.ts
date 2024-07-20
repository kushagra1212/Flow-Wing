import {
  createConnection,
  TextDocuments,
  ProposedFeatures,
} from "vscode-languageserver/node";
import { TextDocument } from "vscode-languageserver-textdocument";
import { onChangeContent } from "./handlers/onChangeContent";
import { onCompletion } from "./handlers/onCompletion";
import { onCompletionResolve } from "./handlers/onCompletionResolve";
import { onHover } from "./handlers/onHover";
import { onSignatureHelp } from "./handlers/onSignatureHelp";
import { onDidChangeConfiguration } from "./handlers/onDidChangeConfiguration";
import { onDidClose } from "./handlers/onDidClose";
import { InitializationHandler } from "./handlers/InitializationHandler";

// Create a connection for the server, using Node's IPC as a transport.
// Also include all preview / proposed LSP features.
const connection = createConnection(ProposedFeatures.all);

// Create a simple text document manager.
const documents: TextDocuments<TextDocument> = new TextDocuments(TextDocument);

// The example settings

// The global settings, used when the `workspace/configuration` request is not supported by the client.
// Please note that this is not the case when using this server with the client provided in this example
// but could happen with other clients.

// Cache the settings of all open documents

const initializationHandler = new InitializationHandler(connection);
initializationHandler.initialize();

onDidChangeConfiguration(connection, initializationHandler, documents);

// Only keep settings for open documents
onDidClose(documents);

// The content of a text document has changed. This event is emitted
// when the text document first opened or when its content has changed.
onChangeContent(documents, connection);

connection.onDidChangeWatchedFiles((_change) => {
  // Monitored files have change in VS Code
  connection.console.log("We received a file change event");
});

// This handler provides the initial list of the completion items.
onCompletion(documents, connection);
// This handler resolves additional information for the item selected in
// the completion list.
onCompletionResolve(connection);

// This handler provides the initial list of the completion items. when hovering
onHover(documents, connection);

// This handler provides signature help (e.g . function call parameters)
onSignatureHelp(documents, connection);

// Make the text document manager listen on the connection
// for open, change and close text document events
documents.listen(connection);

// Listen on the connection
connection.listen();

// function getDocumentSettings(resource: string): Thenable<ExampleSettings> {
//   return Promise.resolve(globalSettings);

//   let result = documentSettings.get(resource);
//   if (!result) {
//     result = connection.workspace.getConfiguration({
//       scopeUri: resource,
//       section: "flow-wing",
//     });
//     documentSettings.set(resource, result);
//   }
//   return result;
// }
