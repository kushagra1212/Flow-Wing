/**
 * Tree-based completion context resolution.
 * Finds the node at cursor position and derives completion context from the tree structure.
 */

import { Position } from "vscode-languageserver";
import { logger } from "./loggerService";

export type CompletionContextKind =
  | "member_access" // c.b. or c.b.b.
  | "object_value" // {a: } - completing value for field a
  | "object_member" // { or {a:2, - completing next member name
  | "array_element" // [] - completing array element (e.g. var c: A[2] = [|])
  | "identifier" // general identifier completion
  | "function_call"; // funName( - argument completion

export interface CompletionContext {
  kind: CompletionContextKind;
  /** For member_access: "c.b" or "c.b.b" */
  path?: string;
  /** For object_value/object_member: expected type name (e.g. "int", "Object: <B {...}>") */
  expectedType?: string;
  /** For object_value: the field we're completing (e.g. "a") */
  memberName?: string;
  /** For object_member: already-specified member names (e.g. ["a"]) */
  existingMembers?: string[];
  /** Prefix to filter completions (e.g. partial identifier) */
  prefix?: string;
}

type AstNode = Record<string, unknown>;

function hasRange(
  obj: unknown
): obj is { range: { start: [number, number]; end: [number, number] } } {
  const r = (obj as any)?.range;
  return (
    !!obj &&
    typeof obj === "object" &&
    r &&
    (Array.isArray(r.start) || (r.start && r.end))
  );
}

function positionInRange(
  pos: Position,
  range: { start: [number, number]; end: [number, number] }
): boolean {
  const [sLine, sCol] = Array.isArray(range.start) ? range.start : [0, 0];
  const [eLine, eCol] = Array.isArray(range.end) ? range.end : [0, 0];
  if (pos.line < sLine || pos.line > eLine) return false;
  if (pos.line === sLine && pos.character < sCol) return false;
  if (pos.line === eLine && pos.character > eCol) return false;
  return true;
}

/** Find innermost node at position; returns node and parent chain (node first, root last) */
function findNodeAndParents(
  obj: unknown,
  pos: Position,
  parents: AstNode[] = []
): { node: AstNode; parents: AstNode[] } | null {
  if (!obj || typeof obj !== "object") return null;
  const node = obj as AstNode;
  const range = node.range as
    | { start: [number, number]; end: [number, number] }
    | undefined;
  if (range && !positionInRange(pos, range)) return null;

  let best: { node: AstNode; parents: AstNode[] } | null = range
    ? { node, parents: [...parents] }
    : null;

  for (const [key, v] of Object.entries(node)) {
    if (key === "range" || key === "kind") continue;
    if (Array.isArray(v)) {
      for (const item of v) {
        if (item && typeof item === "object" && hasRange(item)) {
          const found = findNodeAndParents(item, pos, [...parents, node]);
          if (found) best = found;
        } else if (item && typeof item === "object") {
          const found = findNodeAndParents(item, pos, [...parents, node]);
          if (found) best = found;
        }
      }
    } else if (v && typeof v === "object" && hasRange(v)) {
      const found = findNodeAndParents(v as any, pos, [...parents, node]);
      if (found) best = found;
    }
  }
  return best;
}

/** Extract identifier from key_expression or similar */
function getIdentifierValue(node: AstNode): string | undefined {
  const key =
    node.key_expression ??
    node.identifier_expression ??
    node.object_identifier_expr ??
    node.object_identifier_expression;
  if (key && typeof key === "object" && "value" in key)
    return String((key as any).value);
  return undefined;
}

/** Get type name from AST type expression (Int32TypeExpression -> int, etc.) */
function getTypeNameFromAstType(typeExpr: AstNode): string {
  const kind = String(typeExpr?.kind ?? "");
  if (kind.includes("Int32") || kind.includes("Int64") || kind.includes("Int8"))
    return "int";
  if (kind.includes("Deci") || kind.includes("Float")) return "deci";
  if (kind.includes("Str")) return "str";
  if (kind.includes("Bool")) return "bool";
  if (kind.includes("Char")) return "char";
  if (kind === "ObjectTypeExpression") {
    const id = (typeExpr.object_identifier_expr ??
      typeExpr.object_identifier_expression) as AstNode | undefined;
    if (id && "value" in id) return String(id.value);
  }
  if (kind === "ArrayTypeExpression") {
    const underlying = typeExpr.underlying_type as AstNode | undefined;
    if (underlying) return getTypeNameFromAstType(underlying);
  }
  return kind;
}

/** Find CustomTypeStatement by name in CompilationUnit */
function findFunctionDefinition(
  tree: AstNode,
  funcName: string
): AstNode | undefined {
  if (!tree || !tree.statements) return undefined;
  for (const s of tree.statements as AstNode[]) {
    if (String(s.kind).includes("FunctionDeclaration")) {
      const id = (s.identifier ?? s.name) as AstNode | undefined;
      if (id && "value" in id && id.value === funcName) return s;
    }
  }
  return undefined;
}

function findTypeDefinition(
  tree: AstNode,
  typeName: string
): AstNode | undefined {
  const statements = tree.statements;
  if (!Array.isArray(statements)) return undefined;
  for (const st of statements) {
    const s = st as AstNode;
    if (
      s.kind === "CustomTypeStatement" ||
      String(s.kind).includes("CustomType")
    ) {
      const id = (s.custom_type_identifier_expr ??
        s.customTypeIdentifierExpr) as AstNode | undefined;
      if (id && "value" in id && id.value === typeName) return s;
    }
  }
  return undefined;
}

/** Collect *complete* member names (exclude those with ErrorExpression value) */
function collectObjectMemberNames(expr: AstNode | undefined): string[] {
  if (!expr) return [];
  const names: string[] = [];
  let current: AstNode | undefined = expr;
  while (current) {
    if (String(current.kind).includes("ColonExpression")) {
      const val = (current.value_expression ?? current.valueExpression) as
        | AstNode
        | undefined;
      const isComplete =
        val && !String((val as AstNode).kind).includes("Error");
      if (isComplete) {
        const name = getIdentifierValue(current);
        if (name) names.push(name);
      }
      current = undefined;
    } else if (String(current.kind).includes("BinaryExpression")) {
      const left = current.left ?? current.left_expression;
      const right = current.right ?? current.right_expression;
      if (left && String((left as AstNode).kind).includes("ColonExpression")) {
        const leftVal =
          (left as AstNode).value_expression ??
          (left as AstNode).valueExpression;
        const leftComplete =
          leftVal && !String((leftVal as AstNode).kind).includes("Error");
        if (leftComplete) {
          const name = getIdentifierValue(left as AstNode);
          if (name) names.push(name);
        }
      }
      current = right as AstNode;
    } else {
      break;
    }
  }
  return names;
}

/** Get expected type for a field from CustomTypeStatement */
function getFieldType(typeDef: AstNode, fieldName: string): string | undefined {
  const fields = typeDef.field_declarations ?? typeDef.fieldDeclarations;
  if (!Array.isArray(fields)) return undefined;
  for (const f of fields) {
    const field = f as AstNode;
    const key = (field.key_expression ?? field.keyExpression) as
      | AstNode
      | undefined;
    if (key && "value" in key && key.value === fieldName) {
      const val = field.value_expression ?? field.valueExpression;
      if (val) return getTypeNameFromAstType(val as AstNode);
      return undefined;
    }
  }
  return undefined;
}

/**
 * Get the expected type for an ObjectExpression, handling nesting.
 * For top-level: uses VariableDeclaration's type.
 * For nested (e.g. b:{ }): uses the field type from the enclosing ColonExpression.
 * parents are ancestors of the node we found; objExpr may be at parents[0] (e.g. when node was ErrorExpression inside it).
 */
function getExpectedTypeForObjectExpression(
  objExpr: AstNode,
  parents: AstNode[],
  tree: AstNode,
  rootNode: AstNode
): string | undefined {
  // 1. Check if we're in nested object value: objExpr is value of ColonExpression
  const colonParent = parents.find((p) => {
    const val =
      (p as AstNode).value_expression ?? (p as AstNode).valueExpression;
    return String(p.kind).includes("ColonExpression") && val === objExpr;
  }) as AstNode | undefined;

  if (colonParent) {
    const fieldName = getIdentifierValue(colonParent);
    if (fieldName) {
      const colonIdx = parents.indexOf(colonParent);
      const parentObjExpr = parents.find(
        (p, i) => i > colonIdx && String(p.kind).includes("ObjectExpression")
      ) as AstNode | undefined;
      if (parentObjExpr) {
        const parentExpected = getExpectedTypeForObjectExpression(
          parentObjExpr,
          parents.slice(parents.indexOf(parentObjExpr) + 1),
          tree,
          rootNode
        );
        if (parentExpected) {
          const typeDef = findTypeDefinition(tree, parentExpected);
          return typeDef ? getFieldType(typeDef, fieldName) : undefined;
        }
      }
    }
  }

  // 2. Check if we're inside an array element: objExpr (or some wrapper) is in ContainerExpression.elements
  const containerParent = parents.find((p) => {
    const elms = (p as AstNode).elements as AstNode[] | undefined;
    return (
      String(p.kind).includes("ContainerExpression") &&
      Array.isArray(elms) &&
      (elms.includes(objExpr) || parents.some((prnt) => elms.includes(prnt)))
    );
  }) as AstNode | undefined;

  if (containerParent) {
    const containerIdx = parents.indexOf(containerParent);
    const parentType = getExpectedTypeForObjectExpression(
      containerParent,
      parents.slice(containerIdx + 1),
      tree,
      rootNode
    );
    if (parentType && parentType.includes("[")) {
      return parentType.split("[")[0]; // "A[2]" -> "A"
    }
  }

  // 3. Base case: Root VariableDeclaration or CallExpression
  if (String(rootNode.kind).includes("VariableDeclaration")) {
    const typeExpr =
      (rootNode.declarators as AstNode[])?.[0]?.type_expression ??
      (rootNode.declarators as AstNode[])?.[0]?.typeExpression;
    return typeExpr ? getTypeNameFromAstType(typeExpr as AstNode) : undefined;
  }

  if (String(rootNode.kind).includes("CallExpression")) {
    const args = (rootNode.arguments as AstNode[]) || [];
    const topArg =
      parents.find((p) => args.includes(p)) ||
      (args.includes(objExpr) ? objExpr : undefined);
    if (topArg) {
      const argIdx = args.indexOf(topArg);
      const funcName = getIdentifierValue(rootNode);
      if (funcName) {
        const funcDef = findFunctionDefinition(tree, funcName);
        if (funcDef) {
          const params = (funcDef.parameters as AstNode[]) || [];
          const param = params[argIdx];
          if (param) {
            const typeExpr = param.type_expression ?? param.typeExpression;
            return typeExpr
              ? getTypeNameFromAstType(typeExpr as AstNode)
              : undefined;
          }
        }
      }
    }
  }

  return undefined;
}

/** Derive completion context from AST (used when SEM not available - incomplete code) */
export function getCompletionContextFromAst(
  astJson: { tree?: AstNode },
  pos: Position,
  content: string
): CompletionContext | null {
  const tree = astJson.tree ?? astJson;
  if (!tree || typeof tree !== "object") return null;

  // Flow-Wing AST uses 0-based line numbers (same as LSP)
  let found = findNodeAndParents(tree, pos);
  if (!found) {
    // If no node found, try back-tracking if we are in trailing whitespace at EOF
    const adjustedPos = { ...pos };
    while (adjustedPos.line >= 0) {
      const line = content.split("\n")[adjustedPos.line] ?? "";
      const before =
        adjustedPos.character > 0 ? line.slice(0, adjustedPos.character) : "";
      if (before.trim() === "") {
        if (adjustedPos.line === 0) break;
        adjustedPos.line--;
        const prevLine = content.split("\n")[adjustedPos.line] ?? "";
        adjustedPos.character = prevLine.length;
      } else {
        // Found last non-space character
        const lastCharIdx = before.search(/\S\s*$/);
        if (lastCharIdx >= 0) {
          adjustedPos.character = lastCharIdx + 1;
        }
        break;
      }
    }
    found = findNodeAndParents(tree, adjustedPos);
  }
  if (!found) return null;
  const { node, parents } = found;
  logger.debug(
    "context",
    "leaf node:",
    node.kind,
    "parents:",
    parents.map((p) => p.kind).join(" -> ")
  );

  // Array element completion: we're inside ContainerExpression ([]) that is initializer of VariableDeclaration
  if (String(node.kind).includes("ContainerExpression")) {
    const varDecl = parents.find(
      (p) =>
        String(p.kind).includes("VariableDeclaration") ||
        p.kind === "VariableDeclaration"
    ) as AstNode | undefined;
    const initExpr =
      varDecl?.initializer_expression ?? varDecl?.initializerExpression;
    if (varDecl && initExpr === node) {
      const typeExpr =
        (varDecl.declarators as AstNode[])?.[0]?.type_expression ??
        (varDecl.declarators as AstNode[])?.[0]?.typeExpression;
      if (
        typeExpr &&
        String((typeExpr as AstNode).kind).includes("ArrayTypeExpression")
      ) {
        const expectedType = getTypeNameFromAstType(typeExpr as AstNode);
        if (
          expectedType &&
          (findTypeDefinition(tree as AstNode, expectedType) ||
            ["int", "deci", "str", "bool", "char"].includes(expectedType))
        ) {
          return {
            kind: "array_element",
            expectedType,
            prefix: getPrefixAtPosition(content, pos),
          };
        }
      }
    }
  }

  // Object value completion: we're in ErrorExpression as DIRECT value_expression of ColonExpression ({a: })
  // OR we're on the ColonExpression itself because there's no value expression yet.
  // OR we're on a placeholder node (like Literal 0) that was added by repair logic.
  {
    const immediateParent = parents[0] as AstNode | undefined;
    const isDirectValueOfColon =
      immediateParent &&
      String(immediateParent.kind).includes("ColonExpression") &&
      (immediateParent.value_expression ?? immediateParent.valueExpression) ===
        node;

    const isColonItself = String(node.kind).includes("ColonExpression");

    logger.debug(
      "context",
      "directValueCheck",
      "isDirectValueOfColon:",
      isDirectValueOfColon,
      "isColonItself:",
      isColonItself
    );

    if (isDirectValueOfColon || isColonItself) {
      const colonParent = isColonItself ? node : immediateParent!;
      const val = (colonParent.value_expression ??
        colonParent.valueExpression) as AstNode | undefined;

      // If we already have an ObjectExpression as the value, we should be suggesting members for it,
      // not treating the whole thing as a value completion.
      if (val && String(val.kind).includes("ObjectExpression")) {
        logger.debug(
          "context",
          "found nested ObjectExpression in colon, skipping object_value"
        );
      } else {
        const memberName = getIdentifierValue(colonParent);
        const root = parents.find(
          (p) =>
            String(p.kind).includes("VariableDeclaration") ||
            p.kind === "VariableDeclaration" ||
            String(p.kind).includes("CallExpression") ||
            p.kind === "CallExpression"
        ) as AstNode | undefined;

        if (root && memberName) {
          const colonIdx = parents.indexOf(colonParent);
          let parentObjExpr: AstNode | undefined;
          for (let i = colonIdx + 1; i < parents.length; i++) {
            if (String(parents[i].kind).includes("ObjectExpression")) {
              parentObjExpr = parents[i];
              break;
            }
          }
          const parentExpected = parentObjExpr
            ? getExpectedTypeForObjectExpression(
                parentObjExpr,
                parents.slice(parents.indexOf(parentObjExpr) + 1),
                tree as AstNode,
                root
              )
            : getExpectedTypeForRoot(root, parents, tree as AstNode);

          if (parentExpected) {
            const typeDef = findTypeDefinition(tree as AstNode, parentExpected);
            return {
              kind: "object_value",
              memberName,
              expectedType: typeDef
                ? getFieldType(typeDef, memberName)
                : undefined,
              prefix: "",
            };
          }
        }
      }
    }
  }

  function getExpectedTypeForRoot(
    root: AstNode,
    parents: AstNode[],
    tree: AstNode
  ): string | undefined {
    if (String(root.kind).includes("VariableDeclaration")) {
      const typeExpr =
        (root.declarators as AstNode[])?.[0]?.type_expression ??
        (root.declarators as AstNode[])?.[0]?.typeExpression;
      return typeExpr ? getTypeNameFromAstType(typeExpr as AstNode) : undefined;
    }
    if (String(root.kind).includes("CallExpression")) {
      const funcName = getIdentifierValue(root);
      if (funcName) {
        const funcDef = findFunctionDefinition(tree, funcName);
        if (funcDef) {
          const args = (root.arguments as AstNode[]) || [];
          const targetIdx = parents.findIndex((p) => args.includes(p));
          const argIdx = targetIdx >= 0 ? args.indexOf(parents[targetIdx]) : -1;
          if (argIdx >= 0) {
            const params = (funcDef.parameters as AstNode[]) || [];
            const param = params[argIdx];
            if (param) {
              const typeExpr = param.type_expression ?? param.typeExpression;
              return typeExpr
                ? getTypeNameFromAstType(typeExpr as AstNode)
                : undefined;
            }
          }
        }
      }
    }
    return undefined;
  }

  // Object member completion: we're in ObjectExpression, after { or after comma
  // Prefer the nested ObjectExpression (value of ColonExpression) when we're inside one
  const colonWithNestedObj = parents.find((p) => {
    const val =
      (p as AstNode).value_expression ?? (p as AstNode).valueExpression;
    return (
      String((p as AstNode).kind).includes("ColonExpression") &&
      val &&
      String((val as AstNode).kind).includes("ObjectExpression")
    );
  }) as AstNode | undefined;
  let objExpr: AstNode | undefined;
  let expectedType: string | undefined;
  if (colonWithNestedObj) {
    objExpr = (colonWithNestedObj.value_expression ??
      colonWithNestedObj.valueExpression) as AstNode;
    const fieldName = getIdentifierValue(colonWithNestedObj);
    if (fieldName) {
      const parentObjExpr = parents.find(
        (p, i) =>
          i > parents.indexOf(colonWithNestedObj) &&
          String(p.kind).includes("ObjectExpression")
      ) as AstNode | undefined;
      const varDecl = parents.find((p) =>
        String(p.kind).includes("VariableDeclaration")
      ) as AstNode | undefined;
      const parentExpected =
        parentObjExpr && varDecl
          ? getExpectedTypeForObjectExpression(
              parentObjExpr,
              parents.slice(parents.indexOf(parentObjExpr) + 1),
              tree as AstNode,
              varDecl
            )
          : varDecl
          ? getTypeNameFromAstType(
              ((varDecl.declarators as AstNode[])?.[0]?.type_expression ??
                (varDecl.declarators as AstNode[])?.[0]
                  ?.typeExpression) as AstNode
            )
          : undefined;
      const typeDef = parentExpected
        ? findTypeDefinition(tree as AstNode, parentExpected)
        : undefined;
      expectedType = typeDef ? getFieldType(typeDef, fieldName) : undefined;
    }
  }
  if (!objExpr) {
    objExpr = [node, ...parents].find(
      (p) =>
        String(p.kind).includes("ObjectExpression") ||
        p.kind === "ObjectExpression"
    ) as AstNode | undefined;
  }
  if (objExpr) {
    const root = parents.find(
      (p) =>
        String(p.kind).includes("VariableDeclaration") ||
        p.kind === "VariableDeclaration" ||
        String(p.kind).includes("CallExpression") ||
        p.kind === "CallExpression"
    ) as AstNode | undefined;
    if (root) {
      const resolvedExpected =
        expectedType ??
        getExpectedTypeForObjectExpression(
          objExpr,
          parents,
          tree as AstNode,
          root
        );
      if (
        resolvedExpected &&
        (findTypeDefinition(tree as AstNode, resolvedExpected) ||
          ["int", "deci", "str", "bool", "char"].includes(resolvedExpected))
      ) {
        const existing = collectObjectMemberNames(
          (objExpr as AstNode).expression as AstNode
        );
        return {
          kind: "object_member",
          expectedType: resolvedExpected,
          existingMembers: existing,
          prefix: getPrefixAtPosition(content, pos),
        };
      }
    }
  }

  return null;
}

/** Get prefix (partial identifier) at position from content */
function getPrefixAtPosition(content: string, pos: Position): string {
  const lines = content.split("\n");
  const line = lines[pos.line];
  if (!line) return "";
  const before = line.slice(0, pos.character);
  const match = before.match(/(\w+(?:\.\w+)*)(?:\.)?$/);
  return match ? match[1] : "";
}

/** Derive completion context from SEM (when we have full semantic info) */
export function getCompletionContextFromSem(
  semJson: {
    sem?: {
      tree: unknown;
      symbols: Record<string, unknown>;
      types: Record<string, unknown>;
    };
  },
  pos: Position,
  content: string
): CompletionContext | null {
  const sem = semJson.sem;
  if (!sem?.tree) return null;

  const found = findNodeAndParents(sem.tree, pos);
  if (!found) return null;

  const { node } = found;
  const path = getPrefixAtPosition(content, pos);

  // Member access: path like "c.b" or "c.b.b" with trailing dot
  const line = content.split("\n")[pos.line] ?? "";
  const charBefore = pos.character > 0 ? line[pos.character - 1] : "";
  if (path && charBefore === ".") {
    return {
      kind: "member_access",
      path,
      prefix: "",
    };
  }

  // If we have a path with dots, it's member access (cursor might be after last segment)
  if (path && path.includes(".")) {
    return {
      kind: "member_access",
      path,
      prefix: path.split(".").pop() ?? "",
    };
  }

  return {
    kind: "identifier",
    prefix: path,
  };
}
