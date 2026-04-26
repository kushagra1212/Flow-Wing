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
import { onDefinition } from "./handlers/onDefinition";
import { onDocumentFormatting } from "./handlers/onDocumentFormatting";
import { validateTextDocument } from "./services/documentService";

// Create a connection for the server, using Node's IPC as a transport.
// Also include all preview / proposed LSP features.
const connection = createConnection(ProposedFeatures.all);

// Create a simple text document manager.
export const documents: TextDocuments<TextDocument> = new TextDocuments(
  TextDocument
);

const initializationHandler = new InitializationHandler(connection, () => {
  // Workspace compiler path is applied asynchronously after `initialized`. Earlier
  // `didOpen` validations may have used the default `"FlowWing"` and published no diagnostics.
  setImmediate(() => {
    for (const doc of documents.all()) {
      void validateTextDocument(doc, connection);
    }
  });
});
initializationHandler.initialize();

onDidChangeConfiguration(connection, initializationHandler, documents);

// Only keep settings for open documents
onDidClose(documents);

onDefinition(documents, connection);

// The content of a text document has changed. This event is emitted
// when the text document first opened or when its content has changed.

onChangeContent(documents, connection);
//? connection.onDidChangeWatchedFiles((_change) => {});

// This handler provides the initial list of the completion items.
onCompletion(documents, connection);
// This handler resolves additional information for the item selected in
// the completion list.
onCompletionResolve(connection);

// This handler provides the initial list of the completion items. when hovering
onHover(documents, connection);

onDocumentFormatting(documents, connection);

// This handler provides signature help (e.g . function call parameters)
onSignatureHelp(documents, connection);

// Make the text document manager listen on the connection
// for open, change and close text document events
documents.listen(connection);

// Listen on the connection
connection.listen();
