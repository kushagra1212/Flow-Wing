import {
  createConnection,
  TextDocuments,
  Diagnostic,
  DiagnosticSeverity,
  ProposedFeatures,
  InitializeParams,
  DidChangeConfigurationNotification,
  CompletionItem,
  TextDocumentPositionParams,
  TextDocumentSyncKind,
  InitializeResult,
  HoverParams,
  Range,
  Position,
  SignatureHelp,
} from "vscode-languageserver/node";
import { TextDocument } from "vscode-languageserver-textdocument";
import { keywordsCompletionItems } from "./store";
import {
  checkForFunctionSignatures,
  checkForObjectSuggestions,
  deColorize,
  defaultValueNoSuggestion,
  getLastWordPosition,
  isValidVariableName,
  SuggestHandler,
} from "./utils";
import { validateFile } from "./validation/validateFile";
import { fileUtils } from "./utils/fileUtils";
import {
  handleOnCompletion,
  readAndProcessSyntaxJSON,
  readTokens,
} from "./hover";
import { inBuiltFunctionsCompletionItems } from "./store/functions/inbuilt";
import { flowWingConfig } from "./config/config";
import { Token } from "./hover/types";

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
        triggerCharacters: [".", ",", "{"],
      },
      signatureHelpProvider: {
        triggerCharacters: ["(", ","],
      },
      hoverProvider: true,
      callHierarchyProvider: true,
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
  const text = textDocument.getText();
  const path = await fileUtils.createTempFile({
    fileName: flowWingConfig.temp.codeFileName,
    data: text,
  });

  const { stdoutWithoutColors, errorObject, errorMessage } = await validateFile(
    path
  );

  connection.sendDiagnostics({
    uri: textDocument.uri,
    diagnostics: [],
  });

  if (!errorObject.error) {
    return;
  }

  const diagnostics: Diagnostic[] = [];

  const range = Range.create(
    Position.create(
      errorObject.location.line - 1,
      errorObject.location.column - 1
    ),
    Position.create(
      errorObject.location.line - 1,
      errorObject.location.column + errorObject.location.length - 1
    )
  );
  const diagnostic: Diagnostic = {
    severity: DiagnosticSeverity.Error,
    range,
    message: deColorize(errorObject.message),
    source: textDocument.uri,
    relatedInformation: [
      {
        location: {
          uri: textDocument.uri,
          range,
        },
        message: errorObject.type,
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

const getSuggestionHandlerObject = (
  _textDocsParams: TextDocumentPositionParams,
  callBack: (tokens: Token[]) => SuggestHandler
): Promise<SuggestHandler> => {
  return new Promise((resolve) => {
    const document = documents.get(_textDocsParams.textDocument.uri);

    if (!document) {
      return resolve(defaultValueNoSuggestion);
    }
    //? Added this to get Latest token
    validateTextDocument(document)
      .then(() =>
        readTokens(
          fileUtils.getTempFilePath({
            fileName: flowWingConfig.temp.tokenFileName,
          }),
          _textDocsParams.position
        ).then((tokens) => resolve(callBack(tokens)))
      )
      .catch((err) => {
        console.log("🚀 ~ err~read-token~getSuggestion", err);
        resolve(defaultValueNoSuggestion);
      });
  });
};

// This handler provides the initial list of the completion items.
connection.onCompletion(
  async (
    _textDocsParams: TextDocumentPositionParams
  ): Promise<CompletionItem[]> => {
    const suggestion = await getSuggestionHandlerObject(
      _textDocsParams,
      checkForObjectSuggestions
    );

    if (suggestion.shouldNotProvideSuggestion) return [];

    if (suggestion.giveObjectSuggestions) {
      const result = await handleOnCompletion(
        fileUtils.getTempFilePath({
          fileName: flowWingConfig.temp.syntaxFileName,
        }),
        suggestion
      );

      return suggestion.data.isDot
        ? result
        : [...result, ...keywordsCompletionItems];
    }

    return [];
  }
);

// This handler resolves additional information for the item selected in
// the completion list.
connection.onCompletionResolve((item: CompletionItem): CompletionItem => {
  console.log("Item", item);
  return item;
});

connection.onHover(async (params: HoverParams) => {
  const document = documents.get(params.textDocument.uri);
  if (!document) {
    return;
  }

  const { word, position } = getLastWordPosition(
    document,
    params.position,
    new RegExp(/[\s\n,{}()]+/)
  );

  if (!word) {
    return;
  }
  let isSelf = false;

  if (word.split(".")?.[0] === "self") {
    isSelf = true;
    position.character += 5;
  }
  let result = [];

  try {
    result = await readAndProcessSyntaxJSON(
      fileUtils.getTempFilePath({
        fileName: flowWingConfig.temp.syntaxFileName,
      }),
      position,
      {
        isSelf,
      }
    );
  } catch (err) {
    console.log(err);
  }

  console.log("resultOnHOver", result);

  return {
    contents: result?.length
      ? result[0].documentation
      : keywordsCompletionItems.find(
          (item) => item.label.substring(0, word.length) === word
        )?.documentation,
  };
});

connection.onSignatureHelp(async (params): Promise<SignatureHelp> => {
  const suggestion = await getSuggestionHandlerObject(
    params,
    checkForFunctionSignatures
  );
  const result = await handleOnCompletion(
    fileUtils.getTempFilePath({
      fileName: flowWingConfig.temp.syntaxFileName,
    }),
    suggestion
  );

  if (!result?.length || !suggestion?.giveFunctionSignature) return;

  return {
    signatures: result[0].data?.signatures,
    activeSignature: 0,
    activeParameter: suggestion?.data?.argumentNumber - 1,
  };
});

// Make the text document manager listen on the connection
// for open, change and close text document events
documents.listen(connection);

// Listen on the connection
connection.listen();
