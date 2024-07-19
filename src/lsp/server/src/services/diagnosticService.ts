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
  return {
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
};
