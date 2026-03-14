/**
 * Semantic tree (--emit=sem) service for LSP features.
 * Provides hover, definitions, completions, and signature help from sem JSON.
 */

import { logger } from "./loggerService";
import {
  CompletionItem,
  CompletionItemKind,
  Location,
  MarkupContent,
  Position,
  Range,
  SignatureHelp,
  SignatureInformation,
  ParameterInformation,
} from "vscode-languageserver";
import { keywordsCompletionItems } from "../store";
import { inBuiltFunctionsCompletionItems } from "../store/completionItems/functions/inbuilt";

/** Sem JSON structure from compiler --emit=sem */
export interface SemSymbol {
  kind: string;
  name: string;
  type_id?: string;
  parameters?: string[];
  is_declaration?: boolean;
  isConst?: boolean;
}

export interface SemType {
  kind: string;
  name?: string;
  base_type_id?: string;
  underlying_type_id?: string; // ArrayType uses this for element type
  return_type_ids?: string[];
  parameter_type_ids?: string[];
}

export interface SemRange {
  start: [number, number];
  end: [number, number];
}

export interface SemJson {
  sem?: {
    tree: unknown;
    symbols: Record<string, SemSymbol>;
    types: Record<string, SemType>;
  };
}

function semRangeToLspRange(r: SemRange): Range {
  return Range.create(
    r.start[0],
    r.start[1],
    r.end[0],
    r.end[1]
  );
}

function positionInRange(pos: Position, range: SemRange): boolean {
  if (pos.line < range.start[0] || pos.line > range.end[0]) return false;
  if (pos.line === range.start[0] && pos.character < range.start[1]) return false;
  if (pos.line === range.end[0] && pos.character > range.end[1]) return false;
  return true;
}

function resolveTypeName(
  typeId: string | undefined,
  types: Record<string, SemType>
): string {
  if (!typeId) return "";
  const t = types[typeId];
  if (!t) return "";
  if (t.name && (t.kind === "Primitive" || t.kind === "Type")) return t.name;
  if ((t.kind === "ReturnType" || t.kind === "ParameterType") && t.base_type_id) {
    return resolveTypeName(t.base_type_id, types);
  }
  if (t.kind === "Function" && t.return_type_ids?.length) {
    const ret = resolveTypeName(t.return_type_ids[0], types);
    const params = t.parameter_type_ids
      ?.map((pid) => resolveTypeName(pid, types))
      .join(", ");
    return `(${params ?? ""}) -> ${ret}`;
  }
  const arrayBase = t.base_type_id ?? t.underlying_type_id;
  if ((t.kind === "Array" || t.kind === "ArrayType") && arrayBase) {
    return resolveTypeName(arrayBase, types) + "[]";
  }
  return t.name ?? t.kind;
}

function getParamName(
  symbols: Record<string, SemSymbol> | undefined,
  paramId: string
): string {
  if (!symbols || !paramId) return "param";
  const s = symbols[paramId];
  return s?.name ?? "param";
}

function getFunctionSignature(
  sym: SemSymbol,
  types: Record<string, SemType>,
  symbols?: Record<string, SemSymbol>
): string {
  const typeId = sym.type_id;
  if (!typeId) return `${sym.name}()`;
  const t = types[typeId];
  if (!t || t.kind !== "Function") return `${sym.name}()`;
  const paramIds = sym.parameters ?? [];
  const paramTypes = t.parameter_type_ids ?? [];
  const parts: string[] = [];
  for (let i = 0; i < Math.max(paramIds.length, paramTypes.length); i++) {
    const name = symbols ? getParamName(symbols, paramIds[i]) : paramIds[i] ?? `p${i}`;
    const type = paramTypes[i] ? resolveTypeName(paramTypes[i], types) : "";
    parts.push(type ? `${name}: ${type}` : name);
  }
  const ret = t.return_type_ids?.[0]
    ? resolveTypeName(t.return_type_ids[0], types)
    : "nthg";
  return `${sym.name}(${parts.join(", ")}) -> ${ret}`;
}

/** Find the innermost node at position in the sem tree */
function findNodeAtPosition(
  obj: unknown,
  pos: Position
): { node: unknown; range: SemRange } | null {
  if (!obj || typeof obj !== "object") return null;

  const range = (obj as { range?: SemRange }).range;
  if (range && !positionInRange(pos, range)) return null;

  let best: { node: unknown; range: SemRange } | null = range
    ? { node: obj, range }
    : null;

  for (const v of Object.values(obj as Record<string, unknown>)) {
    if (Array.isArray(v)) {
      for (const item of v) {
        const found = findNodeAtPosition(item, pos);
        if (found) best = found;
      }
    } else if (v && typeof v === "object") {
      const found = findNodeAtPosition(v, pos);
      if (found) best = found;
    }
  }
  return best;
}

/** Get symbol at position from sem tree (IdentifierExpression, CallExpression, etc.) */
export function getSymbolAtPosition(
  semJson: SemJson,
  position: Position,
  partialName?: string
): { symbol: SemSymbol; symbolId: string; range: Range } | null {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem.tree) return null;

  const found = findNodeAtPosition(sem.tree, position);
  if (!found) return null;

  const node = found.node as Record<string, unknown>;
  const symbolId =
    node.symbol_id ?? node.function_symbol_id ?? node.parameter_symbol_id;
  if (!symbolId || typeof symbolId !== "string") return null;

  const symbol = sem.symbols[symbolId];
  if (!symbol) return null;

  // Fallback: if names don't match, try to find symbol by name in the map
  if (partialName && symbol.name !== partialName) {
    const betterSymEntry = Object.entries(sem.symbols).find(
      ([, s]) => s.name === partialName
    );
    if (betterSymEntry) {
      return {
        symbol: betterSymEntry[1],
        symbolId: betterSymEntry[0],
        range: semRangeToLspRange(found.range),
      };
    }
  }

  return {
    symbol,
    symbolId,
    range: semRangeToLspRange(found.range),
  };
}

/** Get declaration location for a symbol (where it's defined) */
export function getDeclarationForSymbol(
  semJson: SemJson,
  symbolId: string,
  uri: string
): Location | null {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem.tree) return null;

  const symbol = sem.symbols[symbolId];
  if (!symbol) return null;

  // Find declaration: FunctionStatement (symbol_id), VariableDeclaration (symbol in initializer), Parameter
  function findDeclaration(
    obj: unknown,
    sid: string
  ): SemRange | null {
    if (!obj || typeof obj !== "object") return null;
    const o = obj as Record<string, unknown>;
    // FunctionStatement or node with direct symbol_id
    if (o.symbol_id === sid || o.parameter_symbol_id === sid) {
      return (o.range as SemRange) ?? null;
    }
    // VariableDeclaration: symbol is in initializer_expressions
    if (o.kind === "VariableDeclaration" && Array.isArray(o.initializer_expressions)) {
      for (const init of o.initializer_expressions as Record<string, unknown>[]) {
        if (init?.symbol_id === sid) {
          return (o.range as SemRange) ?? null;
        }
      }
    }
    for (const v of Object.values(o)) {
      if (Array.isArray(v)) {
        for (const item of v) {
          const r = findDeclaration(item, sid);
          if (r) return r;
        }
      } else if (v && typeof v === "object") {
        const r = findDeclaration(v, sid);
        if (r) return r;
      }
    }
    return null;
  }

  const range = findDeclaration(sem.tree, symbolId);
  if (!range) return null;

  return Location.create(uri, semRangeToLspRange(range));
}

function getNestedContent(str: string, openChar: string, closeChar: string): string | undefined {
  const start = str.indexOf(openChar);
  if (start === -1) return undefined;
  let nest = 0;
  for (let i = start; i < str.length; i++) {
    if (str[i] === openChar) nest++;
    else if (str[i] === closeChar) nest--;
    if (nest === 0) return str.slice(start + 1, i);
  }
  return undefined;
}

function getTopLevelFields(membersStr: string): { name: string; type: string }[] {
  const matches = [...membersStr.matchAll(/([a-zA-Z_][a-zA-Z0-9_]*)\s*:/g)];
  const topLevel = matches.filter(m => {
      const before = membersStr.slice(0, m.index);
      const nestBrace = (before.match(/\{/g) || []).length - (before.match(/\}/g) || []).length;
      const nestBracket = (before.match(/</g) || []).length - (before.match(/>/g) || []).length;
      return nestBrace === 0 && nestBracket === 0 && m[1] !== "Object" && m[1] !== "Array";
  });

  const fields: { name: string; type: string }[] = [];
  for (let i = 0; i < topLevel.length; i++) {
      const name = topLevel[i][1];
      const startPos = topLevel[i].index! + topLevel[i][0].length;
      const endPos = (i + 1 < topLevel.length) ? topLevel[i+1].index : membersStr.length;
      const type = membersStr.slice(startPos, endPos).trim();
      fields.push({ name, type: type.replace(/[, ]+$/, "") });
  }
  return fields;
}

/** Extract base identifier from part (e.g. "c[0]" -> "c", "b" -> "b"). */
function extractBaseName(part: string): string {
  const m = part.match(/^([a-zA-Z_][a-zA-Z0-9_]*)/);
  return m ? m[1] : part;
}

/** Get element type_id for array types. */
function getArrayElementTypeId(
  types: Record<string, SemType>,
  typeId: string | undefined
): string | undefined {
  if (!typeId) return undefined;
  let t = types[typeId];
  if (!t) return undefined;
  // Unwrap ParameterType (e.g. inout d: A[2]) so we can get the array element type
  if ((t.kind === "ParameterType" || t.kind === "ReturnType") && t.base_type_id) {
    return getArrayElementTypeId(types, t.base_type_id);
  }
  const arrayBase = t.base_type_id ?? t.underlying_type_id;
  if ((t.kind === "Array" || t.kind === "ArrayType") && arrayBase) {
    return arrayBase;
  }
  // Compiler may serialize Array without underlying_type_id; parse from name "Array: <X[n]>"
  if ((t.kind === "Array" || t.kind === "ArrayType") && t.name) {
    const m = t.name.match(/^Array:\s*<(.+)\[\d+\]>$/);
    if (m) {
      const elementTypeName = m[1].trim();
      const found = Object.entries(types).find(
        ([, tt]) =>
          tt.name === elementTypeName ||
          tt.name?.startsWith(elementTypeName + " ") ||
          tt.name?.startsWith(`Object: <${elementTypeName}`)
      );
      return found?.[0];
    }
  }
  return undefined;
}

/** Resolve the type name for a dotted path (e.g. "c.b.b", "c[0].b", "getPoints()[0].x" -> "int"). Returns undefined if path cannot be resolved. */
function resolveTypeForPath(
  symbols: Record<string, SemSymbol>,
  types: Record<string, SemType>,
  path: string
): string | undefined {
  const parts = path.split(".").filter(Boolean);
  if (parts.length === 0) return undefined;

  const baseSymName = extractBaseName(parts[0]);
  const baseSym = Object.values(symbols).find((s) => s.name === baseSymName);
  if (!baseSym) return undefined;

  let currentTypeId: string | undefined = baseSym.type_id;
  let currentTypeName: string | undefined;

  // For function calls (e.g. getPoints()), use return type instead of function type
  if (baseSym.kind === "Function" && currentTypeId) {
    const funcType = types[currentTypeId];
    if (funcType?.kind === "Function" && funcType.return_type_ids?.length) {
      currentTypeId = funcType.return_type_ids[0];
    }
  }

  if (/\[\d+\]$/.test(parts[0])) {
    currentTypeId = getArrayElementTypeId(types, currentTypeId);
    if (!currentTypeId) return undefined;
  }

  for (let i = 1; i < parts.length; i++) {
    const part = parts[i];
    const isIndexed = /\[\d+\]$/.test(part);

    if (isIndexed) {
      currentTypeId = getArrayElementTypeId(types, currentTypeId);
      if (!currentTypeId) return undefined;
    } else {
      currentTypeName = resolveTypeName(currentTypeId, types);
      if (!currentTypeName?.startsWith("Object:")) return undefined;
      const content = getNestedContent(currentTypeName, "{", "}");
      if (!content) return undefined;
      const fields = getTopLevelFields(content);
      const field = fields.find((f) => f.name === part);
      if (!field) return undefined;
      currentTypeName = field.type;
      const typeEntry = Object.entries(types).find(
        ([, t]) =>
          t.name === currentTypeName || t.name?.startsWith(`Object: <${currentTypeName}`)
      );
      currentTypeId = typeEntry?.[0];
    }
  }
  return (currentTypeName ?? resolveTypeName(currentTypeId, types)) || undefined;
}

/** Get the type of a field in an object type (e.g. field "b" in A -> "Object: <B {...}>"). */
function getFieldTypeFromObjectType(
  rootTypeName: string,
  fieldName: string,
  types: Record<string, SemType>
): string | undefined {
  const objType = Object.values(types).find(
    (t) =>
      t.name === rootTypeName ||
      t.name?.startsWith(`Object: <${rootTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? rootTypeName.match(/(\w+)/)?.[1]}`) ||
      (rootTypeName.startsWith("Object:") && t.name === rootTypeName)
  );
  if (!objType?.name?.startsWith("Object:")) return undefined;
  const content = getNestedContent(objType.name, "{", "}");
  if (!content) return undefined;
  const fields = getTopLevelFields(content);
  const field = fields.find((f) => f.name === fieldName);
  if (!field) return undefined;
  const rawType = field.type;
  if (!rawType) return undefined;
  if (rawType.startsWith("Object:")) return rawType;
  const resolved = Object.values(types).find(
    (t) => t.name === rawType || t.name?.startsWith(`Object: <${rawType}`)
  );
  return resolved?.name ?? rawType;
}

/** Resolve expected type and existing members for nested object literal (e.g. test({b:{|}) -> B, []).
 * When completing value after colon (e.g. test({b:|)), returns valueExpectedType for that field. */
export function getNestedObjectLiteralContext(
  semJson: SemJson,
  rootExpectedType: string,
  objectLiteralPrefix: string
): { expectedType: string; existingMembers: string[]; valueExpectedType?: string } | undefined {
  const types = semJson.sem?.types;
  if (!types) return undefined;

  const rootType = resolveExpectedTypeName(rootExpectedType, types);
  const stack: string[] = [rootType];
  let i = 0;
  const prefix = objectLiteralPrefix.trim();
  let valueExpectedType: string | undefined;

  while (i < prefix.length) {
    const c = prefix[i];
    if (c === "[") {
      const top = stack[stack.length - 1];
      const typeEntry = Object.entries(types).find(
        ([id, t]) =>
          (t.kind === "Array" || t.kind === "ArrayType") &&
          (t.name === top || resolveTypeName(id, types) === top)
      );
      const arrayBase = typeEntry ? (typeEntry[1].base_type_id ?? typeEntry[1].underlying_type_id) : undefined;
      const elemTypeId = typeEntry ? getArrayElementTypeId(types, typeEntry[0]) : undefined;

      if (elemTypeId) {
        stack.push(resolveExpectedTypeName(resolveTypeName(elemTypeId, types), types));
      } else if (arrayBase) {
        stack.push(resolveExpectedTypeName(resolveTypeName(arrayBase, types), types));
      } else if (top.endsWith("]")) {
        stack.push(resolveExpectedTypeName(top.slice(0, top.lastIndexOf("[")).trim(), types));
      } else if (top.startsWith("Array:")) {
        const match = top.match(/Array:\s*<([^>]+)>/);
        if (match) {
          let inner = match[1].trim();
          if (inner.endsWith("]")) {
            inner = inner.slice(0, inner.lastIndexOf("[")).trim();
          }
          stack.push(resolveExpectedTypeName(inner, types));
        } else {
          stack.push(top);
        }
      } else {
        stack.push(top);
      }
      i++;
      continue;
    }
    if (c === "]") {
      if (stack.length > 1) stack.pop();
      i++;
      continue;
    }
    if (c === "{") {
      const top = stack[stack.length - 1];
      // If we are at root and it's an array, it's [{ so we already pushed A above.
      // If we are doing field: {, the field: logic already pushed.
      // So { doesn't push by itself unless it's the very first char and we haven't resolved to object yet.
      if (!top.startsWith("Object:")) {
        const resolved = resolveExpectedTypeName(top, types);
        if (resolved.startsWith("Object:")) stack[stack.length - 1] = resolved;
      }
      i++;
      continue;
    }
    if (c === "}") {
      if (stack.length > 1) stack.pop();
      valueExpectedType = undefined;
      i++;
      continue;
    }
    const fieldMatch = prefix.slice(i).match(/^([a-zA-Z_][a-zA-Z0-9_]*)\s*:/);
    if (fieldMatch) {
      const fieldName = fieldMatch[1];
      const afterColon = i + fieldMatch[0].length;
      const rest = prefix.slice(afterColon).trim();
      const nextChar = rest[0];
      const current = stack[stack.length - 1];
      const fieldType = getFieldTypeFromObjectType(current, fieldName, types);
      if (nextChar === "{") {
        if (fieldType) stack.push(resolveExpectedTypeName(fieldType, types));
        else stack.push("unknown");
        valueExpectedType = undefined;
      } else {
        if (fieldType) valueExpectedType = resolveExpectedTypeName(fieldType, types);
      }
      i = afterColon;
      continue;
    }
    if (c === ",") valueExpectedType = undefined;
    i++;
  }

  const currentType = stack[stack.length - 1];
  const existingMembers = parseObjectLiteralMembersAtDepth(prefix, stack.length);
  const result: { expectedType: string; existingMembers: string[]; valueExpectedType?: string } = {
    expectedType: currentType,
    existingMembers,
  };
  if (valueExpectedType) result.valueExpectedType = valueExpectedType;
  return result;
}

/** Parse member names at the current brace depth (handles nesting). */
function parseObjectLiteralMembersAtDepth(prefix: string, depth: number): string[] {
  let currentDepth = 0;
  let innerStart = -1;
  for (let i = 0; i < prefix.length; i++) {
    if (prefix[i] === "{") {
      currentDepth++;
      if (currentDepth === depth) innerStart = i + 1;
    } else if (prefix[i] === "}") {
      if (currentDepth === depth && innerStart >= 0) {
        const inner = prefix.slice(innerStart, i);
        const names: string[] = [];
        const re = /([a-zA-Z_][a-zA-Z0-9_]*)\s*:/g;
        let m: RegExpExecArray | null;
        while ((m = re.exec(inner)) !== null) {
          const before = inner.slice(0, m.index);
          const nest = (before.match(/\{/g) || []).length - (before.match(/\}/g) || []).length;
          if (nest === 0) names.push(m[1]);
        }
        return names;
      }
      currentDepth--;
    }
  }
  if (innerStart >= 0) {
    const inner = prefix.slice(innerStart);
    const names: string[] = [];
    const re = /([a-zA-Z_][a-zA-Z0-9_]*)\s*:/g;
    let m: RegExpExecArray | null;
    while ((m = re.exec(inner)) !== null) {
      const before = inner.slice(0, m.index);
      const nest = (before.match(/\{/g) || []).length - (before.match(/\}/g) || []).length;
      if (nest === 0) names.push(m[1]);
    }
    return names;
  }
  return [];
}

/** Get field names for an object type (e.g. "B" or "Object: <B {...}>"). */
function getObjectTypeFieldNames(
  typeName: string,
  types: Record<string, SemType>
): string[] {
  const objType = Object.values(types).find(
    (t) =>
      t.name === typeName ||
      t.name?.startsWith(`Object: <${typeName}`) ||
      t.name?.includes(`<${typeName}`)
  );
  if (!objType?.name?.startsWith("Object:")) return [];
  const content = getNestedContent(objType.name, "{", "}");
  if (!content) return [];
  return getTopLevelFields(content).map((f) => f.name);
}

/** Check if type A is assignable to type B (simplified: exact match or object/primitive compatibility). */
function typeMatches(
  actualTypeName: string,
  expectedTypeName: string,
  types: Record<string, SemType>
): boolean {
  if (!expectedTypeName) return true;
  if (actualTypeName === expectedTypeName) return true;
  const expBase = expectedTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? expectedTypeName;
  const actBase = actualTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? actualTypeName;
  if (expectedTypeName.startsWith("Object:") && (actualTypeName.startsWith("Object:") || /^[A-Z]\w*$/.test(actualTypeName))) {
    return expBase === actBase || actualTypeName.includes(`<${expBase}`) || actualTypeName === expBase;
  }
  return false;
}

/** Direct type match: same type, not "contains". Use when suggesting array elements - c[0] only if element type is B, not if A contains B. */
function directTypeMatches(
  actualTypeName: string,
  expectedTypeName: string,
  _types: Record<string, SemType>
): boolean {
  if (!expectedTypeName) return true;
  if (actualTypeName === expectedTypeName) return true;
  const expBase = expectedTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? expectedTypeName;
  const actBase = actualTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? actualTypeName;
  return expBase === actBase;
}

/** Get expected parameter type name for function argument (e.g. "Object: <B { b: int }>" or "B"). */
export function getExpectedParamTypeFromSem(
  semJson: SemJson,
  functionName: string,
  argumentNumber: number
): string | undefined {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem?.types) return undefined;
  const funcEntry = Object.entries(sem.symbols).find(
    ([, s]) => s.name === functionName && s.kind === "Function"
  );
  if (!funcEntry) return undefined;
  const [, funcSym] = funcEntry;
  const funcType = sem.types[funcSym.type_id ?? ""];
  const paramTypeId = funcType?.parameter_type_ids?.[argumentNumber - 1];
  if (!paramTypeId) return undefined;
  const name = resolveTypeName(paramTypeId, sem.types);
  return name || undefined;
}

/** Build completion items for function call argument - type-aware. */
export function getCompletionItemsForFunctionArgument(
  semJson: SemJson,
  functionName: string,
  argumentNumber: number,
  prefix: string,
  uri: string
): CompletionItem[] {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem?.types) return [];

  const { symbols, types } = sem;
  const funcEntry = Object.entries(symbols).find(([, s]) => s.name === functionName && s.kind === "Function");
  if (!funcEntry) return [];

  const [, funcSym] = funcEntry;
  const funcType = types[funcSym.type_id ?? ""];
  if (!funcType?.parameter_type_ids) return [];

  const paramTypeId = funcType.parameter_type_ids[argumentNumber - 1];
  if (!paramTypeId) return [];

  const expectedTypeName = resolveTypeName(paramTypeId, types);
  if (!expectedTypeName) return [];

  return getCompletionItemsForType(semJson, expectedTypeName, prefix, uri, funcSym.parameters?.[argumentNumber - 1]);
}

/** Build completion items filtered by expected type. */
export function getCompletionItemsForType(
  semJson: SemJson,
  expectedTypeName: string,
  prefix: string,
  uri: string,
  paramIdToExclude?: string
): CompletionItem[] {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem?.types) return [];

  const { symbols, types } = sem;
  expectedTypeName = resolveExpectedTypeName(expectedTypeName, types); // Resolve short names like "B" to "Object: <B {...}>"
  const prefixLower = prefix.toLowerCase();
  const matches = (label: string) => !prefixLower || label.toLowerCase().startsWith(prefixLower);

  const items: CompletionItem[] = [];
  const seen = new Set<string>();

  const allItems: CompletionItem[] = [];
  const addItem = (label: string, detail?: string, kind?: CompletionItemKind) => {
    if (seen.has(label)) return;
    seen.add(label);
    const item: CompletionItem = {
      label,
      kind: kind ?? CompletionItemKind.Variable,
      detail: detail ?? `Type: ${expectedTypeName}`,
    };
    allItems.push(item);
    if (matches(label)) items.push(item);
  };

  const isObjectType = expectedTypeName.startsWith("Object:");
  const expectedBase = expectedTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? expectedTypeName;

  // 1. Suggest symbols matching the expected type
  for (const [symId, sym] of Object.entries(symbols)) {
    if (!sym.name || sym.name.startsWith("0x") || sym.kind === "Function") continue;
    // Skip type definitions (Object, Type) - we need values, not type names
    if (sym.kind === "Object" || sym.kind === "Type") continue;
    // Don't suggest the parameter we're filling in (e.g. "b" when typing test(|))
    if (paramIdToExclude && symId === paramIdToExclude) continue;
    const symTypeName = resolveTypeName(sym.type_id, types);
    // Use directTypeMatches: only suggest vars that are exactly type B, not A (which contains B)
    if (directTypeMatches(symTypeName, expectedTypeName, types)) {
      addItem(sym.name, `var ${sym.name}: ${symTypeName}`);
    }
    if (isObjectType && (sym.kind === "Variable" || sym.kind === "Parameter")) {
      const baseTypeName = symTypeName;
      if (baseTypeName.startsWith("Array:") || baseTypeName.endsWith("[]")) {
        const elemTypeId = getArrayElementTypeId(types, sym.type_id);
        if (elemTypeId) {
          const elemTypeName = resolveTypeName(elemTypeId, types);
          if (directTypeMatches(elemTypeName, expectedTypeName, types)) {
            addItem(`${sym.name}[0]`, `Element of ${sym.name}`);
          } else if (elemTypeName.startsWith("Object:")) {
            const elemContent = getNestedContent(elemTypeName, "{", "}");
            if (elemContent) {
              const elemFields = getTopLevelFields(elemContent);
              for (const f of elemFields) {
                if (typeMatches(f.type, expectedTypeName, types)) {
                  addItem(`${sym.name}[0].${f.name}`, `Member ${f.name} of ${sym.name}[0]`);
                }
              }
            }
          }
        }
      }
    }
  }

  if (isObjectType) {
    addItem("{", `Object literal of type ${expectedBase}`, CompletionItemKind.Snippet);
  }

  // When prefix filters out all items (e.g. user typed "abc"), still return type-aware suggestions
  if (items.length === 0 && allItems.length > 0) return allItems;
  return items;
}

/** Resolve short type name (e.g. "B") to full sem type (e.g. "Object: <B {...}>"). */
function resolveExpectedTypeName(
  expectedTypeName: string,
  types: Record<string, SemType>
): string {
  if (expectedTypeName.startsWith("Object:")) return expectedTypeName;
  if (expectedTypeName.endsWith("]")) {
    const lastOpenBracket = expectedTypeName.lastIndexOf("[");
    if (lastOpenBracket > 0) {
      const base = expectedTypeName.slice(0, lastOpenBracket).trim();
      return resolveExpectedTypeName(base, types) + expectedTypeName.slice(lastOpenBracket);
    }
  }
  const found = Object.values(types).find(
    (t) =>
      t.name === expectedTypeName ||
      t.name?.startsWith(`Object: <${expectedTypeName}`) ||
      t.name?.includes(`<${expectedTypeName}`)
  );
  return found?.name ?? expectedTypeName;
}

/** Build completion items for a value of given type (e.g. object field value after colon: {b:|). */
export function getCompletionItemsForExpectedType(
  semJson: SemJson,
  expectedTypeName: string,
  prefix: string,
  uri: string
): CompletionItem[] {
  const sem = semJson.sem;
  if (!sem?.symbols || !sem?.types) return [];

  const { symbols, types } = sem;
  expectedTypeName = resolveExpectedTypeName(expectedTypeName, types);
  const prefixLower = prefix.toLowerCase();
  const matches = (label: string) => !prefixLower || label.toLowerCase().startsWith(prefixLower);

  const items: CompletionItem[] = [];
  const seen = new Set<string>();
  const allItems: CompletionItem[] = [];
  const addItem = (label: string, detail?: string, kind?: CompletionItemKind) => {
    if (seen.has(label)) return;
    seen.add(label);
    const item: CompletionItem = {
      label,
      kind: kind ?? CompletionItemKind.Variable,
      detail: detail ?? `Type: ${expectedTypeName}`,
    };
    allItems.push(item);
    if (matches(label)) items.push(item);
  };

  const isObjectType = expectedTypeName.startsWith("Object:");
  const expectedBase = expectedTypeName.match(/Object:\s*<(\w+)/)?.[1] ?? expectedTypeName;

  for (const [symId, sym] of Object.entries(symbols)) {
    if (!sym.name || sym.name.startsWith("0x") || sym.kind === "Function") continue;
    if (sym.kind === "Object" || sym.kind === "Type") continue;
    const symTypeName = resolveTypeName(sym.type_id, types);
    if (directTypeMatches(symTypeName, expectedTypeName, types)) {
      addItem(sym.name, `var ${sym.name}: ${symTypeName}`);
    }
    if (isObjectType && (sym.kind === "Variable" || sym.kind === "Parameter")) {
      const baseTypeName = symTypeName;
      if (baseTypeName.startsWith("Array:") || baseTypeName.endsWith("[]")) {
        const elemTypeId = getArrayElementTypeId(types, sym.type_id);
        if (elemTypeId) {
          const elemTypeName = resolveTypeName(elemTypeId, types);
          if (directTypeMatches(elemTypeName, expectedTypeName, types)) {
            addItem(`${sym.name}[0]`, `Element of ${sym.name}`);
          } else if (elemTypeName.startsWith("Object:")) {
            const elemContent = getNestedContent(elemTypeName, "{", "}");
            if (elemContent) {
              const elemFields = getTopLevelFields(elemContent);
              for (const f of elemFields) {
                if (typeMatches(f.type, expectedTypeName, types)) {
                  addItem(`${sym.name}[0].${f.name}`, `Member ${f.name} of ${sym.name}[0]`);
                }
              }
            }
          }
        }
      }
    }
  }

  if (isObjectType) {
    addItem("{", `Object literal of type ${expectedBase}`, CompletionItemKind.Snippet);
  }

  if (items.length === 0 && allItems.length > 0) return allItems;
  return items;
}

/** Build completion items for object literal member names (e.g. {a:2, b|). */
export function getObjectMemberCompletionItems(
  semJson: SemJson,
  expectedType: string,
  existingMembers: string[],
  uri: string
): CompletionItem[] {
  const sem = semJson.sem;
  if (!sem?.types) return [];

  const fieldNames = getObjectTypeFieldNames(expectedType, sem.types);
  const existing = new Set(existingMembers);
  const items: CompletionItem[] = [];

  for (const name of fieldNames) {
    if (!existing.has(name)) {
      items.push({
        label: name,
        kind: CompletionItemKind.Field,
        detail: `Field of ${expectedType}`,
      });
    }
  }
  return items;
}

/** Build completion items from sem with context filtering */
export function getCompletionItemsFromSem(
  semJson: SemJson,
  word: string,
  isDot: boolean,
  uri: string,
  isValueCompletion = false
): CompletionItem[] {
  const sem = semJson.sem;
  if (!sem?.symbols) return [];

  const { symbols, types = {} } = sem;
  logger.debug("semCompletion", "symbols", Object.keys(symbols).length, "types", Object.keys(types).length, "word", word, "isDot", isDot, "isValueCompletion", isValueCompletion);
  logger.debug("semCompletion", "symbolNames", Object.values(symbols).map((s) => s.name).join(", "));

  const seen = new Set<string>();
  const items: CompletionItem[] = [];
  // 1. If isDot is true, we want members of the variable/path 'word' (supports c[0].b)
  if (isDot && word) {
    const parts = word.split(".");
    const baseSymName = extractBaseName(parts[0]);
    logger.debug("semCompletion", "parts", parts, "baseSymName", baseSymName);
    let currentTypeId: string | undefined;
    let currentTypeName: string | undefined;

    const baseSym = Object.values(symbols).find((s) => s.name === baseSymName);
    logger.debug("semCompletion", "baseSymFound", !!baseSym);

    if (baseSym) {
      currentTypeId = baseSym.type_id;
      // For function calls (e.g. getPoints()), use return type
      if (baseSym.kind === "Function" && currentTypeId) {
        const funcType = types[currentTypeId];
        if (funcType?.kind === "Function" && funcType.return_type_ids?.length) {
          currentTypeId = funcType.return_type_ids[0];
        }
      }
      if (/\[\d+\]$/.test(parts[0])) {
        currentTypeId = getArrayElementTypeId(types, currentTypeId);
      }

      for (let i = 1; i < parts.length && currentTypeId; i++) {
        const part = parts[i];
        const isIndexed = /\[\d+\]$/.test(part);
        logger.debug("semCompletion", "Traversing part", part, "isIndexed", isIndexed);

        if (isIndexed) {
          currentTypeId = getArrayElementTypeId(types, currentTypeId);
        } else {
          currentTypeName = resolveTypeName(currentTypeId, types);
          if (!currentTypeName?.startsWith("Object:")) {
            currentTypeName = undefined;
            break;
          }
          const content = getNestedContent(currentTypeName, "{", "}");
          if (!content) {
            currentTypeName = undefined;
            break;
          }
          const fields = getTopLevelFields(content);
          const field = fields.find((f) => f.name === part);
          if (!field) {
            currentTypeName = undefined;
            break;
          }
          currentTypeName = field.type;
          const typeEntry = Object.entries(types).find(
            ([, t]) =>
              t.name === currentTypeName || t.name?.startsWith(`Object: <${currentTypeName}`)
          );
          currentTypeId = typeEntry?.[0];
        }
      }
      if (!currentTypeName && currentTypeId) {
        currentTypeName = resolveTypeName(currentTypeId, types);
      }
    }

    if (currentTypeName && currentTypeName.startsWith("Object:")) {
      logger.debug("semCompletion", "FINAL typeName", currentTypeName);
      const content = getNestedContent(currentTypeName, "{", "}");
      if (content) {
        const fields = getTopLevelFields(content);
        for (const f of fields) {
          if (!seen.has(f.name)) {
            seen.add(f.name);
            items.push({
              label: f.name,
              kind: CompletionItemKind.Field,
              detail: `Member of ${word}`,
            });
          }
        }
      }
      return items;
    }
  }

  // 2. Default completion: keywords, built-ins, and all visible symbols
  // For value completion after colon ({a: }), use empty prefix to suggest all symbols
  const prefix = (isValueCompletion ? "" : (word || "")).toLowerCase();
  const matches = (label: string) =>
    !prefix || label.toLowerCase().startsWith(prefix);

  // Add keywords and built-ins
  for (const kw of [...keywordsCompletionItems, ...inBuiltFunctionsCompletionItems]) {
    if (kw.label && matches(kw.label) && !seen.has(kw.label)) {
      seen.add(kw.label);
      items.push(kw);
    }
  }

  // Add symbols from semantic tree
  for (const sym of Object.values(symbols)) {
    if (
      sym.name &&
      !sym.name.startsWith("0x") &&
      matches(sym.name) &&
      !seen.has(sym.name)
    ) {
      seen.add(sym.name);
      items.push(symbolToCompletionItem(sym, types, uri, symbols));
    }
  }

  return items;
}

function symbolToCompletionItem(
  symbol: SemSymbol,
  types: Record<string, SemType>,
  uri: string,
  symbols: Record<string, SemSymbol>
): CompletionItem {
  const typeName = resolveTypeName(symbol.type_id, types);
  const doc: MarkupContent = {
    kind: "markdown",
    value: typeName
      ? `**${symbol.name}**\n\nType: \`${typeName}\``
      : `**${symbol.name}**`,
  };

  let kind: CompletionItemKind = CompletionItemKind.Text;
  if (symbol.kind === "Function") kind = CompletionItemKind.Function;
  else if (symbol.kind === "Variable" || symbol.kind === "Parameter")
    kind = CompletionItemKind.Variable;
  else if (symbol.kind === "Type") kind = CompletionItemKind.Class;

  const type = types[symbol.type_id ?? ""];
  const paramIds = symbol.parameters ?? [];
  const paramTypeIds = type?.parameter_type_ids ?? [];
  const params = paramIds.map((paramId, i) => {
    const name = getParamName(symbols, paramId);
    const tid = paramTypeIds[i];
    const t = tid ? resolveTypeName(tid, types) : "";
    return t ? `${name}: ${t}` : name;
  });
  const signatures = [
    {
      label: getFunctionSignature(symbol, types, symbols),
      parameters: params,
    },
  ];

  return {
    label: symbol.name,
    kind,
    detail: typeName || undefined,
    documentation: doc,
    data: {
      typeName,
      signatures,
      symbolId: symbol.type_id,
      uri,
    },
  };
}

/** Build hover content for symbol at position. Pass fullPath (e.g. "c.b" or "c.b.b") to resolve member expression types. */
export function getHoverFromSem(
  semJson: SemJson,
  position: Position,
  partialName?: string,
  fullPath?: string
): MarkupContent | null {
  const sem = semJson.sem;
  const symbols = sem?.symbols ?? {};
  const types = sem?.types ?? {};

  // Resolve member expression type (e.g. c.b -> Object: <B {...}>, c.b.b -> int)
  if (fullPath && fullPath.includes(".")) {
    const memberType = resolveTypeForPath(symbols, types, fullPath);
    if (memberType) {
      const displayName = fullPath;
      const value = `**${displayName}**\n\nType: \`${memberType}\``;
      return { kind: "markdown", value };
    }
  }

  const result = getSymbolAtPosition(semJson, position, partialName);
  if (!result) return null;

  const { symbol } = result;
  const typeName = resolveTypeName(symbol.type_id, types);

  let value = `**${symbol.name}**`;
  if (typeName) value += `\n\nType: \`${typeName}\``;
  if (symbol.kind === "Function") {
    const sig = getFunctionSignature(symbol, types, sem?.symbols);
    value += `\n\n\`\`\`flowwing\n${sig}\n\`\`\``;
  }

  return { kind: "markdown", value };
}

/** Build signature help from sem for function call at position */
export function getSignatureHelpFromSem(
  semJson: SemJson,
  position: Position,
  activeParam: number,
  functionName?: string
): SignatureHelp | null {
  let result = getSymbolAtPosition(semJson, position, functionName);
  
  // For signature help, if we are inside a call but getSymbolAtPosition failed 
  // (e.g. no symbol_id on CallExpression), try to find the function symbol by name
  if ((!result || result.symbol.kind !== "Function") && functionName) {
    const sem = semJson.sem;
    const entry = Object.entries(sem?.symbols ?? {}).find(([, s]) => s.name === functionName && s.kind === "Function");
    if (entry) {
      result = {
        symbol: entry[1],
        symbolId: entry[0],
        range: Range.create(position, position), // dummy range
      };
    }
  }

  if (!result) return null;

  const { symbol } = result;
  if (symbol.kind !== "Function") return null;

  const types = semJson.sem?.types ?? {};
  const typeName = resolveTypeName(symbol.type_id, types);
  const sem = semJson.sem;
  const paramIds = symbol.parameters ?? [];
  const type = types[symbol.type_id ?? ""];
  const paramTypeIds = type?.parameter_type_ids ?? [];

  const params: ParameterInformation[] = paramIds.map((paramId, i) => {
    const name = sem?.symbols[paramId]?.name ?? `p${i}`;
    const tid = paramTypeIds[i];
    const t = tid ? resolveTypeName(tid, types) : "";
    return ParameterInformation.create(t ? `${name}: ${t}` : name);
  });

  const sig: SignatureInformation = {
    label: getFunctionSignature(symbol, types, sem?.symbols),
    parameters: params,
    documentation: typeName
      ? `Returns: \`${typeName}\``
      : undefined,
  };

  return {
    signatures: [sig],
    activeSignature: 0,
    activeParameter: Math.max(0, Math.min(activeParam, params.length - 1)),
  };
}

export function isSemFormat(parsed: unknown): parsed is SemJson {
  return (
    typeof parsed === "object" &&
    parsed !== null &&
    "sem" in parsed &&
    typeof (parsed as SemJson).sem === "object"
  );
}
