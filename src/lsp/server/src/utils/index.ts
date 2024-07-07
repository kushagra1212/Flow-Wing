import * as fs from "fs";
import * as os from "os";
import { ErrorResult } from "./types";
import { fileUtils } from "./fileUtils";
import { Position, Range } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";

export const getTempFgCodeFilePath = ({
  fileName,
}: {
  fileName: string;
}): string => {
  const tempDir = os.tmpdir();
  const path = tempDir + "/" + fileName;
  return path;
};

export const parseErrorAndExtractLocation = (error: string): ErrorResult => {
  const result: ErrorResult = {
    lineNumber: 0,
    columnNumber: 0,
    errorMessage: "",
    stdoutWithoutColors: "",
    location: null,
    hasError: true,
    errorObject: null,
  };

  // eslint-disable-next-line no-control-regex
  const colorRegex = /\x1b\[[0-9;]*m/g;

  // Remove all colors from the stdout
  result.stdoutWithoutColors = error.replace(colorRegex, "");
  const regex = /Line (\d+):(\d+)\s(.*)/g;
  const ans = regex.exec(result.stdoutWithoutColors);

  if (ans?.length !== 4) {
    return result;
  }

  result.lineNumber = parseInt(ans[1]) - 1; // Convert to 0-based index
  result.columnNumber = parseInt(ans[2]) - 1; // Convert to 0-based index
  result.errorMessage = ans[3];
  const locationRegex = /(Location:)\s(.*)/g;
  result.location = locationRegex.exec(result.stdoutWithoutColors);

  return result;
};

export const getMarkTSSyntaxHighlightMarkdown = (code: string): string => {
  return `
\`\`\`ts 
${code}
\`\`\`
  `;
};

export const getLastWordPosition = (
  document: TextDocument,
  position: Position,
  regex: RegExp
): {
  position: Position;
  word: string;
} => {
  const text = document.getText(Range.create(Position.create(0, 0), position));
  const lines = text.split("\n");

  const lastLine = lines[lines.length - 1];

  // Split the last line based on spaces, commas, curly braces, and parentheses
  const words = lastLine.split(regex);
  const lastWord = words[words.length - 1];

  return {
    position: {
      line: position.line,
      character: position.character - lastWord.length,
    },
    word: lastWord,
  };
};
