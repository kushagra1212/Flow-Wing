import { ErrorResult } from "./types";
import {
  CompletionItem,
  CompletionItemKind,
  Position,
  Range,
} from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { typesCompletionItems } from "../store/completionItems/keywords/types";
import { Token } from "../types";
import { fileUtils } from "./fileUtils";
import { randomBytes } from "crypto";
import { Stack } from "../ds/stack";
import path = require("path");
import { keywordsCompletionItems } from "../store";
import { inBuiltFunctionsCompletionItems } from "../store/completionItems/functions/inbuilt";

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
  if (!expression) return "";

  const splitedExpr = expression?.split(".");
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

export interface SuggestHandler {
  token: Token;
  word: string;
  data?: {
    isDot?: boolean;
    argumentNumber?: number;
  };
  shouldNotProvideSuggestion?: boolean;
  hasObjectSuggestions?: boolean;
  hasFunctionSignature?: boolean;
  hasHoverResult?: boolean;
}

const defaultValue: SuggestHandler = {
  hasObjectSuggestions: false,
  token: null,
  word: "",
  data: {
    isDot: false,
    argumentNumber: 0,
  },
  hasFunctionSignature: false,
};

export const defaultValueNoSuggestion: SuggestHandler = {
  ...defaultValue,
  shouldNotProvideSuggestion: true,
};

export const checkForHover = (tokens: Token[]): SuggestHandler => {
  let i = tokens.length - 1;
  let isDot = false;
  let word = "";

  if (
    tokens[i].value.indexOf(`"`) === 0 &&
    tokens[i].value.lastIndexOf(`"`) === tokens[i].value.length - 1
  ) {
    return {
      hasHoverResult: true,
      token: tokens[i],
      word: tokens[i].value.split(`"`)?.[1],
      data: {
        isDot: isDot,
        argumentNumber: 0,
      },
    };
  }

  while (i >= 0) {
    const isIdentifier = isValidVariableName(tokens[i].value);

    if (
      isIdentifier &&
      ((i - 1 >= 0 && tokens[i - 1].value !== ".") || i - 1 < 0)
    ) {
      word += tokens[i].value;

      const reversedWord = word.split(".");
      const res = reversedWord.map((w) => {
        const splited = w.split("[]");
        let response: string = splited[splited.length - 1];
        for (let j = 0; j < splited.length - 1; j++) {
          response += "[]";
        }

        return response;
      });
      if (tokens[i].value === "self") {
        return {
          hasHoverResult: true,
          token: tokens[i],
          word: res.reverse().join("."),
          data: {
            isDot: isDot,
            argumentNumber: 0,
          },
        };
      }

      return {
        hasHoverResult: true,
        token: tokens[i],
        word: res.reverse().join("."),
        data: {
          isDot: isDot,
          argumentNumber: 0,
        },
      };
    }

    if (isIdentifier) {
      word += tokens[i].value;
      i--;
      continue;
    }

    if (tokens[i].value === ".") {
      isDot = true;
      word += tokens[i].value;
      i--;
      continue;
    }

    if (tokens[i].value === "]") {
      i -= 2;
      if (tokens[i].value === "[") {
        i--;
      }

      word += "[]";
      continue;
    }
    return defaultValueNoSuggestion;
  }

  return defaultValueNoSuggestion;
};

export const checkForFunctionSignatures = (tokens: Token[]): SuggestHandler => {
  let argNumber = 0;
  let braceCount = 0,
    bracketCount = 0,
    parenthesesCount = 0;
  for (let i = tokens.length - 1; i >= 0; i--) {
    {
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
    }
    if (tokens[i].value === ",") {
      argNumber++;
      continue;
    }

    if (i - 1 >= 0 && tokens[i].value === "(") {
      let isDot = false;
      let word = "",
        token = null;
      if (i - 3 >= 0 && tokens[i - 2].value === ".") {
        isDot = true;
        word = tokens[i - 3].value + tokens[i - 2].value + tokens[i - 1].value;
        token = tokens[i - 3];
      } else {
        word = tokens[i - 1].value;
        token = tokens[i - 1];
      }

      return {
        hasFunctionSignature: true,
        token: token,
        word: word,
        data: {
          isDot: isDot,
          argumentNumber: argNumber + 1,
        },
      };
    }
  }

  return defaultValueNoSuggestion;
};

export const checkForObjectSuggestions = (tokens: Token[]): SuggestHandler => {
  let word = "";
  if (tokens[tokens.length - 1].value === "}") {
    return defaultValueNoSuggestion;
  }
  if (tokens.length && isValidVariableName(tokens[tokens.length - 1].value)) {
    return {
      hasObjectSuggestions: true,
      token: tokens[tokens.length - 1],
      word: tokens[tokens.length - 1].value,
      data: {
        isDot: false,
        argumentNumber: 0,
      },
    };
  }

  const getDefaultValue = () => {
    if (tokens.length && isValidVariableName(tokens[tokens.length - 1].value)) {
      return {
        hasObjectSuggestions: true,
        token: tokens[tokens.length - 1],
        word: tokens[tokens.length - 1].value,
        data: {
          isDot: false,
          argumentNumber: 0,
        },
      };
    }

    return defaultValue;
  };

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
          hasObjectSuggestions: true,
          token: tokens[i - 4],
          word: tokens[i - 4].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: 0,
          },
        };
      }

      return {
        hasObjectSuggestions: true,
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
        if (tokens[i].value === "bring") {
          break;
        }
      }

      if (tokens[i].value === "bring") {
        return {
          token: tokens[i],
          word: tokens[i].value,
          data: {
            isDot: false,
            argumentNumber: 0,
          },
        };
      }

      if (tokens[i].value === "(") {
        i--;
        return {
          hasObjectSuggestions: true,
          token: tokens[i],
          word: tokens[i].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: argumentNumber + 1,
          },
        };
      }
      let bracket = "";
      let index = i - 1;
      if (tokens[index].value === "]") {
        while (index >= 0) {
          if (tokens[index].value !== "]") {
            break;
          }

          index--; // skip ]
          index--; // skip Number

          if (index >= 0 && tokens[index].value === "[") {
            bracket += "[]";
            index--;
          }
        }
      }
      if (index >= 0) {
        if (index - 2 >= 0 && tokens[index - 1].value === ":") {
          return {
            hasObjectSuggestions: true,
            token: tokens[index - 2],
            word: tokens[index - 2].value + bracket + "." + word,
            data: {
              isDot: true,
              argumentNumber: 0,
            },
          };
        } else {
          return {
            hasObjectSuggestions: true,
            token: tokens[index],
            word: tokens[index].value + bracket + "." + word,
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
          hasObjectSuggestions: true,
          token: tokens[i],
          word: tokens[i].value + "." + word,
          data: {
            isDot: true,
            argumentNumber: argumentNumber + 1,
          },
        };
      }

      return getDefaultValue();
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
        ? getDefaultValue()
        : {
            hasObjectSuggestions: true,
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

  return getDefaultValue();
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
export const reverseStack = <T>(stack: Stack<T>): Stack<T> => {
  const result = new Stack<T>();
  while (!stack.isEmpty()) {
    result.push(stack.pop());
  }
  return result;
};

/**
 * Extracts and returns the full file path from a given URI.
 *
 * This function splits the URI string to remove the "file:/" prefix and the ".fg" extension.
 *
 * @param {string} uri - The URI string from which to extract the file path.
 * @returns {string} The full file path extracted from the URI.
 */
export const getFileFullPath = (uri: string): string => {
  return uri.split("file:/")[1].split(".fg")[0];
};

export const createRange = (token: Token | null) => {
  if (!token)
    return {
      range: {
        start: {
          line: 0,
          character: 0,
        },
        end: {
          line: 0,
          character: 0,
        },
      },
    };

  return {
    range: {
      start: {
        line: token.lineNumber,
        character: token.columnNumber,
      },

      end: {
        line: token.lineNumber,
        character: token.columnNumber + token.value.length,
      },
    },
  };
};

export const getImportedFileUri = async (
  _filePath: string,
  currentFileUri: string
): Promise<string> => {
  try {
    const filePath = path.resolve(
      path.dirname(getFileFullPath(currentFileUri)),
      _filePath
    );
    const doesFileExits = await fileUtils.doesFileExist(filePath);
    if (doesFileExits) {
      return "file://" + filePath;
    }
  } catch (err) {
    console.log(`Error in getImportedFileUri: ${err}`);
  }
  return currentFileUri;
};

export const userDefinedKeywordsFilter = (keyword: CompletionItem) => {
  const index = [
    ...keywordsCompletionItems,
    ...inBuiltFunctionsCompletionItems,
  ].findIndex(
    (keywordsCompletionItem) => keywordsCompletionItem.label === keyword.label
  );

  if (index === -1) return true;

  return false;
};
