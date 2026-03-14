import { TextDocument } from "vscode-languageserver-textdocument";
import { ErrorObject } from "../utils/types";
import {
  Diagnostic,
  DiagnosticSeverity,
  Position,
  Range,
} from "vscode-languageserver";
import { deColorize } from "../utils";

export const createDiagnostic = (
  errorObject: ErrorObject,
  textDocument: TextDocument
): Diagnostic => {
  // Compiler uses 0-based line and column (same as LSP)
  const line = Math.max(0, errorObject.location.line);
  const character = Math.max(0, errorObject.location.column);
  const length = Math.max(1, errorObject.location.length);

  const range = Range.create(
    Position.create(line, character),
    Position.create(line, character + length)
  );
  return {
    severity: DiagnosticSeverity.Error,
    range,
    message: deColorize(errorObject.message),
    source: "flowwing",
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
};
