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
import { createHash, randomBytes } from "crypto";
import { Stack } from "../ds/stack";
import path = require("path");
import { fileURLToPath, pathToFileURL } from "url";
import { keywordsCompletionItems } from "../store";
import { inBuiltFunctionsCompletionItems } from "../store/completionItems/functions/inbuilt";
import { logger } from "../services/loggerService";
import os = require("os");
// eslint-disable-next-line no-control-regex
const COLOR_REGEX = /\x1b\[[0-9;]*m/g;

export const deColorize = (str: string): string => {
  return str.replace(COLOR_REGEX, "");
};

/**
 * Extracts defined function/variable names from content for sem repair.
 * Matches: fun name(, var name =, etc.
 */
export const getDefinedSymbolsFromContent = (content: string): string[] => {
  const symbols: string[] = [];
  const funMatch = content.matchAll(/\bfun\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\(/g);
  for (const m of funMatch) symbols.push(m[1]);
  const varMatch = content.matchAll(
    /\b(?:var|const)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*[:=]/g
  );
  for (const m of varMatch) symbols.push(m[1]);
  return [...new Set(symbols)];
};

/**
 * Extracts the identifier (word) at the given position from content.
 * Used when tokens are unavailable (e.g. compiler fails on undefined identifier).
 */
export const getIdentifierAtPosition = (
  content: string,
  position: { line: number; character: number }
): string => {
  const lines = content.split("\n");
  const line = lines[position.line];
  if (!line) return "";
  const before = line.slice(0, position.character);
  const match = before.match(/\w+$/);
  return match ? match[0] : "";
};

/**
 * Full identifier at position (expands left and right). Prefer over getIdentifierAtPosition
 * for go-to-definition so a cursor on any character of `getC` resolves to `getC`, not `get`.
 */
export const getWordAtPosition = (
  content: string,
  position: { line: number; character: number }
): string => {
  const lines = content.split("\n");
  const line = lines[position.line];
  if (!line) return "";
  let start = position.character;
  while (start > 0 && /\w/.test(line[start - 1]!)) start--;
  let end = position.character;
  while (end < line.length && /\w/.test(line[end]!)) end++;
  return line.slice(start, end);
};

/**
 * Extracts the argument prefix at position from document content (e.g. "" for test(|), "{" for test({|).
 * Uses the actual document text, not repaired tokens, so test(|) yields "" not "{}".
 */
export const getArgumentPrefixFromDocument = (
  content: string,
  position: { line: number; character: number }
): string => {
  const lines = content.split("\n");
  let offset = 0;
  for (let i = 0; i < position.line; i++) offset += (lines[i]?.length ?? 0) + 1;
  offset += position.character;
  const before = content.slice(0, offset);
  let depth = 0;
  let lastOpen = -1;
  for (let i = before.length - 1; i >= 0; i--) {
    const c = before[i];
    if (c === ")") depth--;
    else if (c === "(") {
      depth++;
      if (depth === 1) {
        lastOpen = i;
        break;
      }
    }
  }
  if (lastOpen < 0) return "";
  return before.slice(lastOpen + 1).replace(/\s+$/, "");
};

/**
 * If the cursor is inside an object literal that is a variable initializer (e.g. "var p: Point = { x: {} }"),
 * returns the variable's type and the object literal prefix from the opening "{" to the cursor.
 * Used for nested object literal completion (e.g. suggest x, y of A inside { x: { } }).
 */
export const getVariableInitializerObjectContext = (
  content: string,
  position: { line: number; character: number }
): { type: string; prefix: string } | undefined => {
  const lines = content.split("\n");
  let offset = 0;
  for (let i = 0; i < position.line; i++) offset += (lines[i]?.length ?? 0) + 1;
  offset += position.character;
  const before = content.slice(0, offset);
  let depth = 0;
  let rootOpen = -1;
  for (let i = 0; i < before.length; i++) {
    const c = before[i];
    if (c === "{") {
      depth++;
      if (depth === 1 && rootOpen === -1) rootOpen = i;
    } else if (c === "}") depth--;
  }
  if (depth < 1 || rootOpen < 0) return undefined;
  const beforeRoot = content.slice(0, rootOpen).trimEnd();
  const varMatch = beforeRoot.match(/\bvar\s+[a-zA-Z_][a-zA-Z0-9_]*\s*:\s*([a-zA-Z_][a-zA-Z0-9_\s\[\]]*)\s*=\s*$/);
  if (!varMatch) return undefined;
  const type = varMatch[1].trim();
  const prefix = content.slice(rootOpen, offset);
  return { type, prefix };
};

/**
 * Extracts the full dotted path at position (e.g. "c", "c.b", "c[0].b", "getPoints()[0].x").
 * Used for hover on member expressions and completion to resolve nested types.
 * Supports: id, id(), id()[0], id()[0].field, id.field, id[0].field, etc.
 */
export const getFullPathAtPosition = (
  content: string,
  position: { line: number; character: number }
): string => {
  const lines = content.split("\n");
  const line = lines[position.line];
  if (!line) return "";
  const before = line.slice(0, position.character);
  // `(new ClassName).` or `println((new ClassName)).` — member completion after `new`
  // FlowWing instance: `(new ClassName()).member` — note `()` after the class name
  const newIdx = before.lastIndexOf("(new");
  if (newIdx >= 0) {
    const afterNew = before.slice(newIdx);
    const newMatch = afterNew.match(
      /^\(\s*new\s+(\w+)\s*\(\s*\)\s*\)\s*\.\s*$/
    );
    if (newMatch) {
      return `(new ${newMatch[1]})`;
    }
  }
  // Match path: id or id() or id()[0], optionally followed by .field chains.
  // (?:\(\))? and (?:\[\d+\])? are optional so we match both obj.field and getPoints()[0].x
  const match = before.match(
    /(\w+(?:\(\))?(?:\[\d+\])?(?:\.\w+(?:\(\))?(?:\[\d+\])?)*)(?:\.)?$/
  );
  return match ? match[1] : "";
};

/**
 * Tries to repair content for sem by replacing partial identifier with a defined symbol.
 * E.g. println(funNa) with funName defined -> println(funName)
 */
export const tryRepairContentForSem = (
  content: string,
  partialId: string,
  position: { line: number; character: number }
): string | null => {
  const symbols = getDefinedSymbolsFromContent(content);
  const match = symbols.find((s) =>
    s.toLowerCase().startsWith(partialId.toLowerCase())
  );
  if (!match) return null;
  const lines = content.split("\n");
  const line = lines[position.line];
  if (!line) return null;
  const before = line.slice(0, position.character);
  const after = line.slice(position.character);
  const idStart = Math.max(0, before.search(/\w+$/));
  const repairedLine = line.slice(0, idStart) + match + after;
  lines[position.line] = repairedLine;
  return lines.join("\n");
};

/**
 * Tries to repair content for sem by removing a trailing dot at position.
 * E.g. d[0].b. -> d[0].b
 */
export const tryRepairDotForSem = (
  content: string,
  position: { line: number; character: number }
): string | null => {
  const lines = content.split("\n");
  const line = lines[position.line];
  if (line === undefined) return null;
  const before = line.slice(0, position.character);
  const after = line.slice(position.character);

  // Case 1: Cursor is after dot (e.g., d[0].|)
  if (before.trim().endsWith(".")) {
    const repairedLine =
      before.replace(/\.\s*$/, "") + after;
    lines[position.line] = repairedLine;
    return lines.join("\n");
  }
  // Case 2: Cursor is at dot (e.g., d[0]|.)
  if (after.trim().startsWith(".")) {
    const repairedLine =
      before + after.replace(/^\s*\./, "");
    lines[position.line] = repairedLine;
    return lines.join("\n");
  }
  return null;
};

/** Parse type definitions and var declarations for inout placeholder resolution. */
function buildTypeContext(content: string): {
  typeFields: Map<string, Record<string, string>>;
  varTypes: Map<string, string>;
} {
  const typeFields = new Map<string, Record<string, string>>();
  const varTypes = new Map<string, string>();
  for (const m of content.matchAll(/\btype\s+([A-Z]\w*)\s*=\s*\{([^}]*)\}/g)) {
    const fields: Record<string, string> = {};
    for (const f of m[2].matchAll(/([a-zA-Z_]\w*)\s*:\s*([A-Za-z0-9_[\]]+)/g)) {
      fields[f[1]] = f[2].trim();
    }
    typeFields.set(m[1], fields);
  }
  for (const m of content.matchAll(/\b(?:var|const)\s+([a-zA-Z_]\w*)\s*:\s*([A-Za-z0-9_[\]]+)/g)) {
    varTypes.set(m[1], m[2].trim());
  }
  return { typeFields, varTypes };
}

/** Find a variable path for inout param of type targetType (e.g. "c[0].b" for B, "c" for A[2]). */
function findInoutPlaceholder(
  targetType: string,
  typeFields: Map<string, Record<string, string>>,
  varTypes: Map<string, string>
): string | null {
  const targetBase = targetType.replace(/\[\d*\]/g, "").trim();
  for (const [varName, typeStr] of varTypes) {
    if (typeStr === targetType) return varName;
    const baseMatch = typeStr.match(/^([A-Z]\w*)(\[\d*\])?$/);
    if (!baseMatch) continue;
    const baseType = baseMatch[1];
    const isArray = !!baseMatch[2];
    const fields = typeFields.get(baseType);
    if (!fields) continue;
    for (const [fieldName, fieldType] of Object.entries(fields)) {
      const fieldBase = fieldType.replace(/\[\d*\]/g, "").trim();
      if (fieldBase === targetBase || fieldType === targetType) {
        return isArray ? `${varName}[0].${fieldName}` : `${varName}.${fieldName}`;
      }
    }
  }
  return null;
}

/**
 * Tries to repair content for sem when calls have wrong argument count.
 * E.g. funName() when funName(a:int, b:deci) -> funName(0, 0.0)
 * For inout object params, uses a variable path (e.g. c[0].b) so the compiler accepts it.
 */
export const tryRepairCallForSem = (content: string): string | null => {
  const funcParams = new Map<string, { types: string[]; inout: boolean[] }>();
  const funMatch = content.matchAll(
    /\bfun\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\(([^)]*)\)/g
  );
  for (const m of funMatch) {
    const name = m[1];
    const params = m[2].split(",").map((p) => p.trim());
    const types: string[] = [];
    const inout: boolean[] = [];
    for (const p of params) {
      const inoutMatch = p.startsWith("inout ");
      const typePart = inoutMatch ? p.slice(6).trim() : p;
      const colonIdx = typePart.indexOf(":");
      const typeStr = colonIdx >= 0 ? typePart.slice(colonIdx + 1).trim() : "";
      types.push(typeStr);
      inout.push(inoutMatch);
    }
    funcParams.set(name, { types: types.filter(Boolean), inout });
  }
  const { typeFields, varTypes } = buildTypeContext(content);
  const placeholderForType = (t: string, isInout: boolean): string => {
    if (isInout && /^[A-Z]\w*(\[\d*\])?$/.test(t)) {
      const path = findInoutPlaceholder(t, typeFields, varTypes);
      if (path) return path;
    }
    const lower = t.toLowerCase();
    if (lower.includes("int") || lower === "i32" || lower === "i64") return "0";
    if (lower.includes("deci") || lower.includes("float") || lower === "f32")
      return "0.0";
    if (lower.includes("str")) return '""';
    if (lower.includes("bool")) return "false";
    if (lower.includes("char")) return "'\\0'";
    if (/^[A-Z]\w*$/.test(t) || lower.includes("object")) return "{}";
    return "0";
  };
  for (const [name, { types, inout }] of funcParams) {
    if (types.length === 0) continue;
    const placeholders = types
      .map((t, i) => placeholderForType(t, inout[i] ?? false))
      .join(", ");
    // Repair funName() -> funName(0, 0.0) or funName(c[0].b) for inout
    const emptyCall = new RegExp(`\\b${name}\\s*\\(\\s*\\)`, "g");
    let repaired = content.replace(emptyCall, `${name}(${placeholders})`);
    if (repaired !== content) return repaired;
    // Repair bare funName (e.g. println(funName)) -> println(funName(0, 0.0))
    const bareId = new RegExp(`\\b${name}\\b(?!\\s*\\()`, "g");
    repaired = content.replace(bareId, `${name}(${placeholders})`);
    if (repaired !== content) return repaired;
    // Repair inout + object/array literal: test({}) -> test(c[0].b), test([{}]) -> test(c)
    const callRegex = new RegExp(`\\b${name}\\s*\\(`, "g");
    let m: RegExpExecArray | null;
    while ((m = callRegex.exec(content)) !== null) {
      const start = m.index + m[0].length;
      let depth = 1;
      let i = start;
      const args: string[] = [];
      let argStart = start;
      let argDepth = 0;
      while (i < content.length && depth > 0) {
        const c = content[i];
        if (c === "(" || c === "{" || c === "[") {
          if (depth === 1) argDepth++;
          depth++;
        } else if (c === ")" || c === "}" || c === "]") {
          depth--;
          if (depth === 1 && argDepth > 0) {
            argDepth--;
            if (argDepth === 0) {
              args.push(content.slice(argStart, i).trim());
              argStart = i + 1;
              while (argStart < content.length && /[,\s]/.test(content[argStart])) argStart++;
              i = argStart - 1;
            }
          }
        } else if (depth === 1 && c === ",") {
          args.push(content.slice(argStart, i).trim());
          argStart = i + 1;
          while (argStart < content.length && /[,\s]/.test(content[argStart])) argStart++;
          i = argStart - 1;
        }
        i++;
      }
      if (depth === 0) {
        const lastArg = content.slice(argStart, i - 1).trim();
        if (lastArg) args.push(lastArg);
        const newArgs = args.map((arg, idx) => {
          if (!inout[idx]) return arg;
          const trimmed = arg.trim();
          const isLiteral = (trimmed.startsWith("{") || trimmed.startsWith("[")) && trimmed.length > 0;
          if (!isLiteral) return arg;
          const ph = placeholderForType(types[idx] ?? "", true);
          return ph;
        });
        if (JSON.stringify(args) !== JSON.stringify(newArgs)) {
          const before = content.slice(0, start);
          const after = content.slice(i - 1);
          return before + newArgs.join(", ") + after;
        }
      }
    }
  }
  return null;
};

/**
 * Makes incomplete code parseable for LSP (tokens, sem, ast).
 * Closes unclosed parentheses; adds placeholder when ending with comma.
 * E.g. funName( -> funName(); funName(1, -> funName(1,0)
 */
export const makeCodeCompleteForLsp = (content: string): string => {
  const match = content.match(/(\s*)$/);
  const trailing = match ? match[1] : "";
  let trimmed = content.slice(0, content.length - trailing.length);

  const stack: string[] = [];
  let inString = false;
  let lastChar = "";

  for (let i = 0; i < trimmed.length; i++) {
    const c = trimmed[i];
    if (c === '"' && lastChar !== "\\") inString = !inString;
    if (inString) {
      lastChar = c;
      continue;
    }
    if (c === "(" || c === "{" || c === "[") {
      stack.push(c);
    } else if (c === ")" && stack[stack.length - 1] === "(") {
      stack.pop();
    } else if (c === "}" && stack[stack.length - 1] === "{") {
      stack.pop();
    } else if (c === "]" && stack[stack.length - 1] === "[") {
      stack.pop();
    }
    lastChar = c;
  }

  // Remove trailing dot for semantic analysis of the base expression
  if (trimmed.endsWith(".")) {
    trimmed = trimmed.replace(/\.\s*$/, "");
  }

  // Multi-colon repair: handle all empty fields {a:, b:|, c: }
  trimmed = trimmed.replace(/:\s*(?=[,}\]])/g, ": 0 ");

  const lastCharNoSpace = trimmed.trimEnd().slice(-1);
  let suffix = "";

  if (lastCharNoSpace === ":") {
    suffix += "0"; // Placeholder for value after colon
  } else if (lastCharNoSpace === ",") {
    // Only add placeholder if NOT in an object literal (innermost '{')
    // because Flow-Wing allows trailing commas in objects but rejects them in calls/arrays,
    // and '0' can cause type mismatch in objects.
    if (stack[stack.length - 1] !== "{") {
      suffix += "0";
    }
  }

  // Close unclosed symbols
  while (stack.length > 0) {
    const open = stack.pop();
    if (open === "(") suffix += ")";
    if (open === "{") suffix += "}";
    if (open === "[") suffix += "]";
  }

  // Incomplete if/else if/while/for need a body: "if (expr)" -> "if (expr) {}"
  const beforeTrailing = trimmed + suffix;
  const lastLine = beforeTrailing.split("\n").pop()?.trimEnd() ?? "";
  if (
    lastLine.endsWith(")") &&
    !lastLine.includes("{") &&
    /^\s*(if|else\s+if|while|for)\s*\(/.test(lastLine)
  ) {
    suffix += " {}";
  }

  return trimmed + suffix + trailing;
};

/**
 * Parses compiler stderr output from the FlowWing compiler (pipeline-based).
 * Format: [Error:ErrorCode] : Line X:Y "message"
 * Line/column are 0-based in compiler output (same as LSP).
 */
export const parseErrorAndExtractLocation = (stderr: string): ErrorResult => {
  const result: ErrorResult = {
    lineNumber: 0,
    columnNumber: 0,
    errorMessage: "",
    stdoutWithoutColors: "",
    location: null,
    hasError: false,
    errorObject: null,
  };

  const plain = deColorize(stderr);
  result.stdoutWithoutColors = plain;

  // Match: [Error:ErrorCode] : Line X:Y "message"
  const errorRegex = /\[Error:([^\]]+)\]\s*:\s*Line\s+(\d+):(\d+)\s+"([^"]*)"/;
  const match = errorRegex.exec(plain);

  if (!match) {
    return result;
  }

  const [, errorCode, lineStr, colStr, message] = match;
  const line = parseInt(lineStr, 10);
  const column = parseInt(colStr, 10);

  result.hasError = true;
  result.lineNumber = line;
  result.columnNumber = column;
  result.errorMessage = message;
  result.errorObject = {
    error: true,
    level: "Error",
    location: {
      line,
      column,
      length: 1, // Compiler doesn't provide length; highlight 1 char
    },
    message,
    type: "Semantic", // Error code (e.g. InvalidAssignmentToConstantVariable) in relatedInformation
  };

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
    argumentPrefix?: string;
    /** When true, use empty prefix for completion (value after colon in object literal) */
    isValueCompletion?: boolean;
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
  if (tokens.length === 0) return defaultValueNoSuggestion;
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
      i - 3 >= 0 &&
      tokens[i - 1].value === ":" &&
      tokens[i - 2].value == ":"
    ) {
      return {
        hasHoverResult: true,
        token: tokens[i - 3],
        word:
          tokens[i - 3].value +
          tokens[i - 2].value +
          tokens[i - 1].value +
          tokens[i].value,
        data: {
          isDot: isDot,
          argumentNumber: 0,
        },
      };
    }
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
  let lastCommaIndex = -1;
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
      // Only treat comma as argument separator when at top level of call (not inside {}, [], ())
      if (braceCount === 0 && bracketCount === 0 && parenthesesCount === 0) {
        if (lastCommaIndex < 0) lastCommaIndex = i;
        argNumber++;
      }
      continue;
    }

    if (parenthesesCount === 0 && i - 1 >= 0 && tokens[i].value === "(") {
      let isDot = false;
      let word = "",
        token = null;
      if (i - 3 >= 0 && tokens[i - 2].value === ".") {
        isDot = true;
        word = tokens[i - 3].value + tokens[i - 2].value + tokens[i - 1].value;
        token = tokens[i - 3];
      } else if (
        i - 4 >= 0 &&
        tokens[i - 2].value == ":" &&
        tokens[i - 3].value == ":"
      ) {
        word =
          tokens[i - 4].value +
          tokens[i - 3].value +
          tokens[i - 2].value +
          tokens[i - 1].value;
        token = tokens[i - 4];
      } else {
        word = tokens[i - 1].value;
        token = tokens[i - 1];
      }

      const argumentPrefix =
        lastCommaIndex >= 0
          ? tokens
              .slice(lastCommaIndex + 1)
              .map((t) => t.value)
              .join("")
          : tokens
              .slice(i + 1)
              .map((t) => t.value)
              .join("");

      return {
        hasFunctionSignature: true,
        token: token,
        word: word,
        data: {
          isDot: isDot,
          argumentNumber: argNumber + 1,
          argumentPrefix,
        },
      };
    }
  }

  return defaultValueNoSuggestion;
};

export const checkForObjectSuggestions = (tokens: Token[]): SuggestHandler => {
  tokens = tokens.filter((t) => t.value !== "");
  if (tokens.length === 0) return defaultValueNoSuggestion;
  let word = "";

  logger.trace("objectSuggestions", "lastToken", tokens[tokens.length - 1]?.value, "tokens.length", tokens.length);

  if (tokens[tokens.length - 1].value === "}") {
    return defaultValueNoSuggestion;
  }
  if (tokens.length && isValidVariableName(tokens[tokens.length - 1].value)) {
    // If the token before this identifier is ',' or '{' (and not ':'), it's likely a key
    if (tokens.length >= 2) {
      const prev = tokens[tokens.length - 2].value;
      if (prev === "," || prev === "{") {
        // This might be a key. Let's let the loop below find the object base.
      } else if (prev === ".") {
        // path.ident - member access, typing partial member name (e.g. d[0].abc)
        return {
          hasObjectSuggestions: true,
          token: tokens[tokens.length - 1],
          word: tokens[tokens.length - 1].value,
          data: {
            isDot: true,
            argumentNumber: 0,
          },
        };
      } else {
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
    } else {
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
  }

  // Handle b. case - cursor is after a dot
  if (
    tokens.length >= 2 &&
    tokens[tokens.length - 1].value === "." &&
    isValidVariableName(tokens[tokens.length - 2].value)
  ) {
    return {
      hasObjectSuggestions: true,
      token: tokens[tokens.length - 2],
      word: tokens[tokens.length - 2].value,
      data: {
        isDot: true,
        argumentNumber: 0,
      },
    };
  }

  // Handle {a: } case - cursor is after a colon and identifier (value completion)
  if (
    tokens.length >= 2 &&
    tokens[tokens.length - 1].value === ":" &&
    isValidVariableName(tokens[tokens.length - 2].value)
  ) {
    return {
      hasObjectSuggestions: true,
      token: tokens[tokens.length - 2],
      word: tokens[tokens.length - 2].value, // Field name for context
      data: {
        isDot: false, // Value completion, not member access
        isValueCompletion: true, // Use empty prefix so we suggest all symbols (x, etc.)
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
          word: tokens[i - 4].value + (word ? "." + word : ""),
          data: {
            isDot: true,
            argumentNumber: 0,
          },
        };
      }

      return {
        hasObjectSuggestions: true,
        token: tokens[i - 2],
        word: tokens[i - 2].value + (word ? "." + word : ""),
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
      word = tokens[i - 2].value + (word ? "." + word : "");
    } else if (
      i - 3 >= 0 &&
      tokens[i].value === "{" &&
      tokens[i - 1].value === "[" &&
      tokens[i - 2].value === ":"
    ) {
      i--; // skip {
      i--; // skip [
      i--; // skip :
      word = tokens[i].value + "[]" + (word ? "." + word : "");
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
          word: tokens[i].value + (word ? "." + word : ""),
          data: {
            isDot: true,
            argumentNumber: argumentNumber + 1,
          },
        };
      }
      let bracket = "";
      let index = i - 1;
      if (index >= 0 && tokens[index].value === "]") {
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
            word: tokens[index - 2].value + bracket + (word ? "." + word : ""),
            data: {
              isDot: true,
              argumentNumber: 0,
            },
          };
        } else {
          return {
            hasObjectSuggestions: true,
            token: tokens[index],
            word: tokens[index].value + bracket + (word ? "." + word : ""),
            data: {
              isDot: true,
              argumentNumber: 0,
            },
          };
        }
      }

      return getDefaultValue();
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
          word: tokens[i].value + (word ? "." + word : ""),
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

        if (tokens[i].value === ":") {
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
    } else if (
      i - 2 >= 0 &&
      tokens[i].value === ":" &&
      tokens[i - 1].value === ":" &&
      isValidVariableName(tokens[i - 2].value)
    ) {
      return {
        hasObjectSuggestions: true,
        token: tokens[i - 2],
        word: tokens[i - 2].value,
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

/** Max basename length for temp files to avoid Windows MAX_PATH (260) when joined with temp dir. */
export const MAX_TEMP_BASENAME_LENGTH = 80;

/**
 * Real filesystem path for a `file:` URI. Use this for `path.resolve`, `fs`, etc.
 * **Do not** use {@link getFileFullPath} for this — that returns a mangled string for temp-file basenames only.
 */
export const getFilesystemPathFromUri = (uri: string): string | null => {
  if (!uri || !uri.startsWith("file:")) return null;
  try {
    return fileURLToPath(uri);
  } catch {
    return null;
  }
};

/**
 * Extracts the file path from a file URI for use as a temp file basename.
 * Handles file://, file:///, and file:/ schemes.
 *
 * @param uri - The URI string (e.g. file:///path/to/file.fg or file:///path/to/file)
 * @returns A path-like string suitable for temp file names (no leading slashes)
 */
export const getFileFullPath = (uri: string): string => {
  try {
    // file:///path or file:/path - extract path part
    const match = uri.match(/^file:\/\/?(.+?)(\.fg)?$/);
    if (match) {
      let pathPart = match[1];
      // Remove leading slashes and normalize all path separators (/, \) to underscore
      // so path.join(tempDir, basename) never produces an absolute path on Windows
      pathPart = pathPart.replace(/^\/+/, "").replace(/[/\\]+/g, "_");
      return pathPart;
    }
    return uri.replace(/[^a-zA-Z0-9_-]/g, "_");
  } catch {
    return "unknown";
  }
};

/**
 * Returns a temp-file-safe basename for the given file URI. Shortens via hash when
 * getFileFullPath(uri) would exceed MAX_TEMP_BASENAME_LENGTH (avoids Windows MAX_PATH).
 */
export const getTempFileBasename = (uri: string): string => {
  const full = getFileFullPath(uri);
  if (full.length <= MAX_TEMP_BASENAME_LENGTH) return full;
  return createHash("sha256").update(uri).digest("hex").slice(0, 32);
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
  relativeImport: string,
  currentFileUri: string
): Promise<string> => {
  try {
    const basePath = getFilesystemPathFromUri(currentFileUri);
    if (basePath) {
      const resolved = path.resolve(path.dirname(basePath), relativeImport);
      if (await fileUtils.doesFileExist(resolved)) {
        return pathToFileURL(resolved).href;
      }
    }
  } catch (err) {
    logger.debug("utils", "getImportedFileUri", String(err));
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

/**
 * Filter completion items by prefix (case-insensitive).
 * Used when typing partial identifiers so "funNa" suggests "funName".
 */
export const filterCompletionItemsByPrefix = (
  items: import("vscode-languageserver").CompletionItem[],
  prefix: string
): import("vscode-languageserver").CompletionItem[] => {
  if (!prefix) return items;
  const p = prefix.toLowerCase();
  return items.filter(
    (item) => item.label && (item.label as string).toLowerCase().startsWith(p)
  );
};

export const getUnique = (
  arr1: CompletionItem[],
  arr2: CompletionItem[]
): CompletionItem[] => {
  const mp = new Map();

  for (let i = 0; i < arr1.length; i++) {
    mp.set(arr1[i].label, arr1[i]);
  }

  for (let i = 0; i < arr2.length; i++) {
    if (!mp.has(arr2[i].label)) {
      mp.set(arr2[i].label, arr2[i]);
    }
  }

  return Array.from(mp.values());
};
export const getModulePath = () => {
  let modulePath;

  switch (os.platform()) {
    case "darwin": // macOS
      modulePath = "/opt/homebrew/opt/flowwing/lib/modules";
      break;
    case "win32": // Windows
      modulePath = "C:\\Program Files(x86)\\FlowWing\\lib\\modules";
      break;
    case "linux": // Linux
      modulePath = "/usr/local/flowwing/lib/modules";
      break;
    default:
      throw new Error("Unsupported OS platform");
  }

  return path.normalize(modulePath); // Ensure the path is correctly formatted
};
