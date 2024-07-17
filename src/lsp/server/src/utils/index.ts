import { ErrorResult } from "./types";
import { Position, Range } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { typesCompletionItems } from "../store/keywords/types";
import { Token } from "../hover/types";
import { fileUtils } from "./fileUtils";
import { flowWingConfig } from "../config/config";
import { randomBytes } from "crypto";

// eslint-disable-next-line no-control-regex
const COLOR_REGEX = /\x1b\[[0-9;]*m/g;

export const deColorize = (str: string): string => {
  return str.replace(COLOR_REGEX, "");
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

  // Remove all colors from the stdout
  result.stdoutWithoutColors = deColorize(error);
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

export const getMarkSyntaxHighlightMarkdown = (
  code: string,
  language: string = "flowwing"
): string => {
  return `
\`\`\`${language}
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

  // Split the last line based on spaces, commas, curly braces, and parentheses
  const words = text.split(regex);
  const lastWord = words[words.length - 1];

  return {
    position: {
      line: position.line,
      character: position.character - lastWord.length,
    },
    word: lastWord,
  };
};

export const isPrimitiveType = (type: string): boolean => {
  const index = typesCompletionItems.findIndex((item) => item.label === type);

  return index !== -1;
};

export const getArrayType = (typeName: string) => {
  const splitATypeName = typeName.split("[");
  const size = splitATypeName?.length;
  const isArray = size > 1;
  let dim = size - 1;
  let rest = "";
  while (dim > 0) {
    rest += "[]";
    dim--;
  }
  return {
    isArray: isArray,
    dimesion: size - 1,
    ofType: splitATypeName?.[0],
    typeName: splitATypeName?.[0] + rest,
    dim: rest,
  } as {
    isArray: boolean;
    dimesion: number;
    ofType: string;
    typeName: string;
    dim: string;
  };
};
export const formatVarExpr = (expression: string) => {
  const splitedExpr = expression.split(".");
  let res = "";
  for (const expr of splitedExpr) {
    if (expr === "") continue;

    const array = getArrayType(expr);

    if (array.isArray) {
      res += array.typeName;
    } else {
      res += expr;
    }
    res += ".";
  }

  return res;
};

interface SuggestHandler {
  giveObjectSuggestions: boolean;
  token: Token;
  word: string;
  data?: {
    isDot?: boolean;
    argumentNumber?: number;
  };
  shouldNotProvideSuggestion?: boolean;
}
export const checkForObjectSuggestions = (tokens: Token[]): SuggestHandler => {
  const defaultValue: SuggestHandler = {
    giveObjectSuggestions: false,
    token: null,
    word: "",
    data: {
      isDot: false,
      argumentNumber: 0,
    },
  };
  const defaultValueNoSuggestion: SuggestHandler = {
    ...defaultValue,
    shouldNotProvideSuggestion: true,
  };
  let word = "";

  if (tokens[tokens.length - 1].value === "}") {
    return defaultValueNoSuggestion;
  }

  let braceCount = 0,
    bracketCount = 0,
    parenthesesCount = 0;

  for (let i = tokens.length - 1; i >= 0; i--) {
    if (tokens[i].value === "}") {
      braceCount++;
      continue;
    }

    if (tokens[i].value === "]") {
      bracketCount++;
      continue;
    }

    if (tokens[i].value === ")") {
      parenthesesCount++;
      continue;
    }

    if (tokens[i].value === "{" && braceCount) {
      braceCount--;
      continue;
    }

    if (tokens[i].value === "[" && bracketCount) {
      bracketCount--;
      continue;
    }

    if (tokens[i].value === "(" && parenthesesCount) {
      parenthesesCount--;
      continue;
    }

    if (i - 2 >= 0 && tokens[i].value === "{" && tokens[i - 1].value === "=") {
      if (i - 4 >= 0 && tokens[i - 3].value === ":") {
        return {
          giveObjectSuggestions: true,
          token: tokens[i - 4],
          word: tokens[i - 4].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: 0,
          },
        };
      }

      return {
        giveObjectSuggestions: true,
        token: tokens[i - 2],
        word: tokens[i - 2].value + "." + word,
        data: {
          isDot: true,
          argumentNumber: 0,
        },
      };
    } else if (
      i - 2 >= 0 &&
      tokens[i].value === "{" &&
      tokens[i - 1].value === ":"
    ) {
      word = tokens[i - 2].value + "." + word;
    } else if (
      i - 3 >= 0 &&
      tokens[i].value === "{" &&
      tokens[i - 1].value === "[" &&
      tokens[i - 2].value === ":"
    ) {
      i--; // skip {
      i--; // skip [
      i--; // skip :
      word = tokens[i].value + "[]" + "." + word;
    } else if (
      i - 3 >= 0 &&
      tokens[i].value === "{" &&
      (tokens[i - 1].value === "[" || tokens[i - 1].value === ",")
    ) {
      i--; // skip {
      let argumentNumber = 0;
      let _squareBracketCount = 0,
        _parenthesisCount = 0,
        _curlyBracketCount = 0;
      for (; i >= 0; i--) {
        // close
        if (tokens[i].value === "]") {
          _squareBracketCount++;
          continue;
        }
        if (tokens[i].value === "}") {
          _curlyBracketCount++;
          continue;
        }
        if (tokens[i].value === ")") {
          _parenthesisCount++;
          continue;
        }
        // Open
        if (tokens[i].value === "[" && _squareBracketCount) {
          _squareBracketCount--;
          continue;
        }

        if (tokens[i].value === "{" && _curlyBracketCount) {
          _curlyBracketCount--;
          continue;
        }
        if (tokens[i].value === "(" && _parenthesisCount) {
          _parenthesisCount--;
          continue;
        }
        if (tokens[i].value === "=") {
          break;
        }

        if (tokens[i].value === ",") {
          argumentNumber++;
        }

        if (tokens[i].value === "(") {
          break;
        }
      }

      if (tokens[i].value === "(") {
        i--;
        return {
          giveObjectSuggestions: true,
          token: tokens[i],
          word: tokens[i].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: argumentNumber + 1,
          },
        };
      }

      let index = i - 1;
      if (tokens[index].value === "]") {
        while (index >= 0) {
          if (tokens[index].value !== "]") {
            break;
          }

          index--; // skip ]
          index--; // skip Number

          if (index >= 0 && tokens[index].value === "[") {
            index--;
          }
        }
      }
      if (index >= 0) {
        if (index - 2 >= 0 && tokens[index - 1].value === ":") {
          return {
            giveObjectSuggestions: true,
            token: tokens[index - 2],
            word: tokens[index - 2].value + "[]" + "." + word,
            data: {
              isDot: true,
              argumentNumber: 0,
            },
          };
        } else {
          return {
            giveObjectSuggestions: true,
            token: tokens[index],
            word: tokens[index].value + "[]" + "." + word,
            data: {
              isDot: true,
              argumentNumber: 0,
            },
          };
        }
      }
    } else if (
      i - 2 >= 0 &&
      tokens[i].value === "{" &&
      (tokens[i - 1].value === "," || tokens[i - 1].value === "(")
    ) {
      i--; // skip {
      let argumentNumber = 0;
      let _squareBracketCount = 0,
        _parenthesisCount = 0,
        _curlyBracketCount = 0;
      for (; i >= 0; i--) {
        // close
        if (tokens[i].value === "]") {
          _squareBracketCount++;
          continue;
        }
        if (tokens[i].value === "}") {
          _curlyBracketCount++;
          continue;
        }
        if (tokens[i].value === ")") {
          _parenthesisCount++;
          continue;
        }
        // Open
        if (tokens[i].value === "[" && _squareBracketCount) {
          _squareBracketCount--;
          continue;
        }

        if (tokens[i].value === "{" && _curlyBracketCount) {
          _curlyBracketCount--;
          continue;
        }
        if (tokens[i].value === "(" && _parenthesisCount) {
          _parenthesisCount--;
          continue;
        }
        if (tokens[i].value === "(") {
          break;
        }

        if (tokens[i].value === ",") {
          argumentNumber++;
        }
      }
      i--; // skip (

      if (i >= 0) {
        return {
          giveObjectSuggestions: true,
          token: tokens[i],
          word: tokens[i].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: argumentNumber + 1,
          },
        };
      }

      return defaultValue;
    } else if (i - 1 >= 0 && tokens[i].value === ".") {
      let response = tokens[i--].value;
      let wasVar = false;
      while (i >= 0) {
        if (tokens[i].value === "]" && !wasVar) {
          i--;
          while (tokens[i].value !== "[") {
            i--;
          }
          i--;
          response = "[]" + response;
          wasVar = false;
          continue;
        }

        if (isValidVariableName(tokens[i].value) && !wasVar) {
          response = tokens[i--].value + response;
          wasVar = true;
          continue;
        }
        if (tokens[i].value === ".") {
          response = tokens[i--].value + response;
          wasVar = false;
          continue;
        }
        break;
      }

      return !response || (response?.length && response[0] === ".")
        ? defaultValue
        : {
            giveObjectSuggestions: true,
            token: tokens[i + 1],
            word: response,
            data: {
              isDot: true,
            },
          };
    }
    if (isSquareBracket(tokens[i].value)) {
      return defaultValueNoSuggestion;
    }
  }

  return defaultValue;
};

const isSquareBracket = (char: string) => {
  return char === "[" || char === "]";
};
export const isValidVariableName = (name) => {
  if (!name || name === "") return false;
  const validNamePattern = /^[a-zA-Z_][a-zA-Z_0-9]*$/;
  return validNamePattern.test(name);
};
export function generateRandomFilename() {
  return randomBytes(16).toString("hex");
}
