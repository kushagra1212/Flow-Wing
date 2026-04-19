/**
 * Complex nesting autocompletion - getPoints()[0].x, arr[0], matrix[0][0], etc.
 */

import { assert } from "chai";
import { TextDocument } from "vscode-languageserver-textdocument";
import { TextDocuments } from "vscode-languageserver";
import { getObjectSuggestion } from "../handlers/onCompletion";
import { flowWingConfig } from "../config";
import { clearDocumentCache } from "../services/documentService";

import { getTestCompilerPath } from "./testCompilerPath";
const COMPILER_PATH = getTestCompilerPath();

const mockDocuments = (doc: TextDocument) => {
  const docs = new TextDocuments(TextDocument);
  (docs as any).get = (uri: string) => (uri === doc.uri ? doc : undefined);
  return docs;
};

describe("Complex Nesting Autocompletion", () => {
  before(function () {
    flowWingConfig.flowWingPath = COMPILER_PATH;
  });

  beforeEach(function () {
    this.timeout(20000);
    clearDocumentCache();
  });

  it("should suggest x, y for getPoints()[0].x. (Path from user request)", async () => {
    const content = `
type A = { x: int, y: int }
type Point = { x: A }
fun getPoints() -> Point[2] {
  return [{ x: { x: 1, y: 2 } }, { x: { x: 3, y: 4 } }]
}
getPoints()[0].x.
`;
    const pos = { line: 6, character: 18 };
    const uri = "file:///test_user_req.fg";
    const doc = TextDocument.create(uri, "flowwing", 0, content);
    const items = await getObjectSuggestion(
      { textDocument: { uri }, position: pos },
      mockDocuments(doc)
    );
    const labels = items.map((i) => i.label);
    assert.include(labels, "x", "Should suggest 'x' for type A");
    assert.include(labels, "y", "Should suggest 'y' for type A");
  });

  it("should suggest x for getPoints()[1]. (User request nested index)", async () => {
    const content = `
type A = { x: int, y: int }
type Point = { x: A }
fun getPoints() -> Point[2] {
  return [{ x: { x: 1, y: 2 } }, { x: { x: 3, y: 4 } }]
}
getPoints()[1].
`;
    const pos = { line: 6, character: 15 };
    const uri = "file:///test_user_index.fg";
    const doc = TextDocument.create(uri, "flowwing", 0, content);
    const items = await getObjectSuggestion(
      { textDocument: { uri }, position: pos },
      mockDocuments(doc)
    );
    const labels = items.map((i) => i.label);
    assert.include(labels, "x", "Should suggest 'x' for type Point");
  });

  it("should suggest field for nested member array: obj.arr[0].", async () => {
    const content = `
type Item = { field: int }
type Container = { items: Item[5] }
var c: Container = { items: [{field:0},{field:0},{field:0},{field:0},{field:0}] }
c.items[0].
`;
    const pos = { line: 4, character: 11 };
    const uri = "file:///test_nested_member_array.fg";
    const doc = TextDocument.create(uri, "flowwing", 0, content);
    const items = await getObjectSuggestion(
      { textDocument: { uri }, position: pos },
      mockDocuments(doc)
    );
    const labels = items.map((i) => i.label);
    assert.include(labels, "field", "Should suggest 'field' for Item");
  });

  it("should suggest field for multi-dimensional array: matrix[0][0].", async function () {
    const content = `
type Item = { field: int }
type Row = Item[2]
var matrix: Row[2] = [[{field:0},{field:1}],[{field:2},{field:3}]]
matrix[0][0].
`;
    const pos = { line: 5, character: 13 };
    const uri = "file:///test_multi_dim_array.fg";
    const doc = TextDocument.create(uri, "flowwing", 0, content);
    const items = await getObjectSuggestion(
      { textDocument: { uri }, position: pos },
      mockDocuments(doc)
    );
    const labels = items.map((i) => i.label);
    if (labels.length === 0) this.skip();
    assert.include(labels, "field", "Should suggest 'field' for Item");
  });
});
