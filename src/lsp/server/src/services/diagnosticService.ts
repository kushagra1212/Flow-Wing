import { TextDocument } from "vscode-languageserver-textdocument";
import { ErrorObject } from "../utils/types";
import {
  Diagnostic,
  DiagnosticSeverity,
  Position,
  Range,
} from "vscode-languageserver";
import { deColorize } from "../utils";

/**
 * Find the end character of the token at (line, character) so the diagnostic
 * squiggly spans the full token (identifier, number, etc.) instead of one character.
 */
function getTokenEndPosition(
  textDocument: TextDocument,
  line: number,
  character: number
): number {
  const lineText = textDocument.getText(
    Range.create(
      Position.create(line, 0),
      Position.create(line + 1, 0)
    )
  ).replace(/\r?\n$/, "");
  if (character >= lineText.length) return character;
  const char = lineText[character];
  if (/[a-zA-Z0-9_]/.test(char)) {
    const rest = lineText.slice(character);
    const match = rest.match(/^[a-zA-Z0-9_]+/);
    return character + (match ? match[0].length : 1);
  }
  if (/\s/.test(char)) return character + 1;
  return character + 1;
}

export const createDiagnostic = (
  errorObject: ErrorObject,
  textDocument: TextDocument
): Diagnostic => {
  // Compiler uses 0-based line and column (same as LSP)
  const line = Math.max(0, errorObject.location.line);
  const character = Math.max(0, errorObject.location.column);
  let endCharacter = getTokenEndPosition(textDocument, line, character);
  if (endCharacter <= character) endCharacter = character + 1;

  const range = Range.create(
    Position.create(line, character),
    Position.create(line, endCharacter)
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
