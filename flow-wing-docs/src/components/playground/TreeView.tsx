// The syntax tree (--emit=ast) or the semantic tree (--emit=sem), as an
// outline. Each node shows its kind, what it names or holds, and in the
// semantic tree its type. Pointing at a node highlights its code; clicking
// one also scrolls the editor to it.
//
// A node is any object with a "kind". Its children are the fields that hold
// nodes; its other fields are shown as properties under it.

import React, { createContext, useContext, useEffect, useState } from "react";
import type { Range } from "./source";
import { SourceMap, describePoint } from "./source";
import styles from "./Playground.module.css";

type Tables = { symbols?: Record<string, any>; types?: Record<string, any> };

type Context = Tables & {
  map: SourceMap;
  generation: number; // bumped by Expand all / Collapse all
  expandAll: boolean | null;
  onPick: (range: Range) => void;
  onHover: (range: Range | null) => void;
};

const TreeContext = createContext<Context | null>(null);

const isNode = (value: any): boolean =>
  value !== null && typeof value === "object" && !Array.isArray(value) && typeof value.kind === "string";

const holdsNodes = (value: any): boolean =>
  isNode(value) || (Array.isArray(value) && value.some((item) => holdsNodes(item)));

export function typeName(types: Record<string, any> | undefined, id: string, depth = 0): string {
  const type = types?.[id];
  if (!type || depth > 8) return id;
  if (type.name) return type.name;
  if (type.base_type_id) return typeName(types, type.base_type_id, depth + 1);
  return type.kind ?? id;
}

// What a node names or holds, in a few characters.
function summary(node: any, tables: Tables): string {
  for (const key of ["name", "value", "lexeme", "operator"]) {
    const value = node[key];
    if (typeof value === "string") return key === "value" ? JSON.stringify(value) : value;
    if (typeof value === "number" || typeof value === "boolean") return String(value);
  }
  if (isNode(node.identifier) && typeof node.identifier.value === "string") return node.identifier.value;
  const symbol = node.symbol_id && tables.symbols?.[node.symbol_id];
  if (symbol?.name) return symbol.name;
  return "";
}

function typeOf(node: any, tables: Tables): string {
  if (!tables.types) return "";
  if (typeof node.type_id === "string") return typeName(tables.types, node.type_id);
  const symbol = node.symbol_id && tables.symbols?.[node.symbol_id];
  if (symbol?.type_id) return typeName(tables.types, symbol.type_id);
  if (Array.isArray(node.return_type_ids)) {
    return node.return_type_ids.map((id: string) => typeName(tables.types, id)).join(", ");
  }
  return "";
}

function propertyText(key: string, value: any, tables: Tables): string {
  if (typeof value === "string" && /_id$/.test(key)) {
    const symbol = tables.symbols?.[value];
    if (symbol) return `${value} → ${symbol.name ?? "?"} (${symbol.kind})`;
    if (tables.types?.[value]) return `${value} → ${typeName(tables.types, value)}`;
  }
  if (Array.isArray(value) && value.every((item) => typeof item === "string") && /_ids$/.test(key)) {
    return value.map((id) => tables.types?.[id] ? typeName(tables.types, id) : tables.symbols?.[id]?.name ?? id).join(", ");
  }
  const text = JSON.stringify(value);
  return text.length > 120 ? text.slice(0, 117) + "…" : text;
}

function TreeNode({ node, field, depth }: { node: any; field: string; depth: number }) {
  const context = useContext(TreeContext)!;
  const initial = () => (context.expandAll === null ? depth < 3 : context.expandAll);
  const [open, setOpen] = useState(initial);
  useEffect(() => setOpen(initial()), [context.generation]); // eslint-disable-line react-hooks/exhaustive-deps

  const children: [string, any][] = [];
  const properties: [string, any][] = [];
  for (const [key, value] of Object.entries(node)) {
    if (key === "kind" || key === "range") continue;
    if (holdsNodes(value)) children.push([key, value]);
    else if (value !== null && value !== "" && !(Array.isArray(value) && value.length === 0)) {
      properties.push([key, value]);
    }
  }
  const expandable = children.length > 0 || properties.length > 0;
  const text = summary(node, context);
  const type = typeOf(node, context);
  const range: Range | undefined = node.range;

  return (
    <li role="treeitem" aria-expanded={expandable ? open : undefined} className={styles.treeItem}>
      <div className={styles.treeRow}>
        <button
          type="button"
          className={styles.treeToggle}
          aria-label={open ? "Collapse" : "Expand"}
          tabIndex={-1}
          disabled={!expandable}
          onClick={() => setOpen(!open)}
        >
          {expandable ? (open ? "▾" : "▸") : "·"}
        </button>
        <button
          type="button"
          className={styles.treeLabel}
          onClick={() => {
            if (range) context.onPick(range);
            if (expandable && !open) setOpen(true);
          }}
          onKeyDown={(event) => {
            if (event.key === "ArrowRight" && expandable) setOpen(true);
            if (event.key === "ArrowLeft") setOpen(false);
          }}
          onMouseEnter={() => range && context.onHover(range)}
          onMouseLeave={() => context.onHover(null)}
          onFocus={() => range && context.onHover(range)}
          onBlur={() => context.onHover(null)}
        >
          {field && <span className={styles.treeField}>{field}</span>}
          <span className={styles.treeKind}>{node.kind}</span>
          {text && <span className={styles.treeValue}>{text}</span>}
          {type && <span className={styles.treeType}>: {type}</span>}
          {range && <span className={styles.treeRange}>{describePoint(context.map, range.start)}</span>}
        </button>
      </div>
      {open && expandable && (
        <ul role="group" className={styles.treeGroup}>
          {properties.map(([key, value]) => (
            <li key={key} className={styles.treeProperty}>
              <span className={styles.treeField}>{key}</span>
              <span>{propertyText(key, value, context)}</span>
            </li>
          ))}
          {children.map(([key, value]) => (
            <Children key={key} field={key} value={value} depth={depth + 1} />
          ))}
        </ul>
      )}
    </li>
  );
}

function Children({ field, value, depth }: { field: string; value: any; depth: number }) {
  if (isNode(value)) return <TreeNode node={value} field={field} depth={depth} />;
  const items = (value as any[]).flat(4).filter(isNode);
  return (
    <>
      {items.map((item, index) => (
        <TreeNode key={index} node={item} field={`${field}[${index}]`} depth={depth} />
      ))}
    </>
  );
}

export function countNodes(value: any): number {
  if (Array.isArray(value)) return value.reduce((sum, item) => sum + countNodes(item), 0);
  if (value === null || typeof value !== "object") return 0;
  let count = isNode(value) ? 1 : 0;
  for (const [key, child] of Object.entries(value)) {
    if (key !== "range") count += countNodes(child);
  }
  return count;
}

type Props = Tables & {
  root: any;
  map: SourceMap;
  label: string;
  onPick: (range: Range) => void;
  onHover: (range: Range | null) => void;
};

export default function TreeView({ root, map, label, symbols, types, onPick, onHover }: Props) {
  const [expansion, setExpansion] = useState<{ generation: number; expandAll: boolean | null }>(
    { generation: 0, expandAll: null });
  const set = (expandAll: boolean) =>
    setExpansion(({ generation }) => ({ generation: generation + 1, expandAll }));

  return (
    <TreeContext.Provider value={{ map, symbols, types, onPick, onHover, ...expansion }}>
      <div className={styles.viewBar}>
        <span className={styles.viewTitle}>{countNodes(root)} nodes</span>
        <span className={styles.viewHint}>Point at a node to see its code; click to go there.</span>
        <span className={styles.spacer} />
        <button type="button" className={styles.miniButton} onClick={() => set(true)}>Expand all</button>
        <button type="button" className={styles.miniButton} onClick={() => set(false)}>Collapse all</button>
      </div>
      <ul role="tree" aria-label={label} className={styles.tree}>
        <TreeNode node={root} field="" depth={0} />
      </ul>
    </TreeContext.Provider>
  );
}
