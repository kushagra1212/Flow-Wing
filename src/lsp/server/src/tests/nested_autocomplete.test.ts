/**
 * Nested and complex autocompletion - function results, arrays, object literals.
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

describe("Nested and Complex Autocompletion", () => {
  before(function () {
    flowWingConfig.flowWingPath = COMPILER_PATH;
  });

  beforeEach(function () {
    this.timeout(20000);
    clearDocumentCache();
  });

  describe("Property access on function results and arrays", () => {
    it("should suggest x, y for getPoints()[0].x. (nested path with function result and index)", async () => {
      const content = `
type A = {
  x: int
  y: int
}

type Point = {
  x: A
}

fun getPoints() -> Point[2] {
  return [{ x: { x: 1, y: 2 } }, { x: { x: 3, y: 4 } }]
}

getPoints()[0].x.
`;
      const pos = { line: 14, character: 18 };
      const uri = "file:///test_nested_func_index.fg";
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest 'x' for A");
      assert.include(labels, "y", "Should suggest 'y' for A");
    });

    it("should suggest x for getPoints()[0]. (path with function result and index)", async () => {
      const content = `
type A = { x: int, y: int }
type Point = { x: A }
fun getPoints() -> Point[2] { return [{ x: { x: 1, y: 2 } }, { x: { x: 3, y: 4 } }] }
getPoints()[0].
`;
      const pos = { line: 4, character: 15 };
      const uri = "file:///test_func_index.fg";
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest 'x' for Point");
    });

    it("should suggest members for multi-digit array index: arr[10].", async () => {
      const content = `
type A = { a: int }
var arr: A[20] = [{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0},{a:0}]
arr[10].
`;
      const pos = { line: 3, character: 8 };
      const uri = "file:///test_multidigit_index.fg";
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "a", "Should suggest 'a' for A");
    });
  });

  describe("Complex object literal nesting", () => {
    it("should suggest x, y inside nested object literal (repro case 1)", async () => {
      const content = `
type A = { x: int, y: int }
type Point = { x: A }
var p: Point = { x: {  } }
`;
      const pos = { line: 3, character: 22 };
      const uri = "file:///test_literal_repro1.fg";
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest 'x' for type A");
      assert.include(labels, "y", "Should suggest 'y' for type A");
    });

    it("should suggest x for top-level object in array (repro case 2)", async () => {
      const content = `
type A = { x: int, y: int }
type Point = { x: A }
fun getPoints() -> Point[2] {
  return [{ x: { x: 1, y: 2 } }, { x: { x: 3, y: 4 } }]
}
getPoints()[1].
`;
      const pos = { line: 6, character: 15 };
      const uri = "file:///test_literal_repro2.fg";
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest 'x' for type Point");
    });
  });
});
