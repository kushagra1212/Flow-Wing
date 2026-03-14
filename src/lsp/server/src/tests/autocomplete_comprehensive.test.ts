/**
 * Comprehensive autocomplete tests - all possible completion scenarios.
 * Tests must pass. Implement features to make them pass.
 */

import { assert } from "chai";
import { TextDocument } from "vscode-languageserver-textdocument";
import { TextDocuments } from "vscode-languageserver";
import { getObjectSuggestion } from "../handlers/onCompletion";
import { flowWingConfig } from "../config";
import { clearDocumentCache } from "../services/documentService";

const COMPILER_PATH = "/Users/apple/code/per/Flow-Wing/build/sdk/bin/FlowWing";

const mockDocuments = (doc: TextDocument) => {
  const docs = new TextDocuments(TextDocument);
  (docs as any).get = (uri: string) => (uri === doc.uri ? doc : undefined);
  return docs;
};

describe("Autocomplete comprehensive", () => {
  before(function () {
    flowWingConfig.flowWingPath = COMPILER_PATH;
  });

  beforeEach(function () {
    this.timeout(10000);
    clearDocumentCache();
  });

  describe("Function call argument - type-aware completion", () => {
    it("test(inout b: B): suggest c[0].b when cursor in test(|)", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a:2, b: {b:5}}]
fun test(inout b: B) { b.b = 2 }
test(
`;
      const pos = { line: 6, character: 5 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "c[0].b", "Should suggest c[0].b (type B) for test(inout b: B)");
    });

    it("test(inout b: B): suggest object literal { for type B", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a:2, b: {b:5}}]
fun test(inout b: B) { b.b = 2 }
test(
`;
      const pos = { line: 6, character: 5 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.isTrue(
        labels.some((l) => l === "{" || l === "c[0].b"),
        "Should suggest { or c[0].b for object type B"
      );
    });

    it("add(a:int, b:int): suggest int literals/vars when typing first arg", async () => {
      const content = `
fun add(a: int, b: int) -> int { return a + b }
var x: int = 42
add(
`;
      const pos = { line: 3, character: 4 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest x (int) for first param");
    });
  });

  describe("Object literal completion", () => {
    it("object member: {a:2, | suggests b", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A = {a:2, 
`;
      const pos = { line: 4, character: 16 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b after comma");
    });

    it("test({|): suggest b (field of B) when inside object literal arg", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a:2, b: {b:5}}]
fun test(inout b: B) { b.b = 2 }
test({})
`;
      const pos = { line: 6, character: 6 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B) inside test({})");
    });

    it("test(inout a2: A): nested test({b:{|}) suggests b (field of B)", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
fun test(inout a2: A) { a2.b.b = 5 }
test({b:{}})
`;
      const pos = { line: 5, character: 10 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B) inside nested test({b:{}})");
    });

    it("test({b:{|}}): cursor inside b:{} suggests b not a (prefix may include closing })", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
fun test(inout a2: A) { a2.b.b = 5 }
test({b:{}})
`;
      const pos = { line: 5, character: 11 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B) inside b:{}, not a");
      assert.notInclude(labels, "a", "Should NOT suggest a when inside nested b:{}");
    });

    it("test({b:|,a:5}): after colon should NOT suggest a (field name) when completing value for b:", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a:2, b: {b:5}}]
fun test(inout a2: A) { a2.b.b = 5 }
test({b:,a:5})
`;
      const pos = { line: 5, character: 10 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.notInclude(labels, "a", "Should NOT suggest a (field of A) when completing value for b: - expect B values like { or c[0].b");
    });

    it("test({b:{},a:5}): cursor inside b:{} suggests b not a (comma inside object)", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
fun test(inout a2: A) { a2.b.b = 5 }
test({b:{},a:5})
`;
      const pos = { line: 5, character: 10 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B) inside b:{}, not a");
      assert.notInclude(labels, "a", "Should NOT suggest a (field of A) when inside nested b:{}");
    });

    it("object value after colon: {a:| suggests values", async () => {
      const content = `
type A = { a: int }
var x: int = 10
var b: A = {a:
`;
      const pos = { line: 4, character: 14 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest x for int value");
    });
  });

  describe("Member access completion", () => {
    it("obj.| suggests members", async () => {
      const content = `
type T = { vals:int[3], name: str }
var obj:T = { vals:[10,20,30], name: "x" }
obj.`;
      const pos = { line: 4, character: 4 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "vals");
      assert.include(labels, "name");
    });

    it("c[0].b.| suggests B members", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a: 1, b: {b: 1}}]
c[0].b.`;
      const pos = { line: 4, character: 8 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B)");
    });
  });

  describe("Nested object and array edge cases", () => {
    it("var c: A = {a:2, b: {| suggests b (field of B)", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A = {a:2, b: {
`;
      const pos = { line: 4, character: 22 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B) in nested object literal");
    });

    it("array of objects pts[0].| suggests Point fields", async () => {
      const content = `
type Point = { x: int, y: int }
var pts: Point[2] = [{x:1,y:2}, {x:3,y:4}]
pts[0].
`;
      const pos = { line: 3, character: 8 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x");
      assert.include(labels, "y");
    });

  });

  describe("Array literal completion", () => {
    it("var c: A[2] = [|] suggests elements", async () => {
      const content = `
type A = { a: int }
var c: A[2] = []
`;
      const pos = { line: 3, character: 15 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      assert.isAtLeast(items.length, 1);
    });
  });

  describe("General completion", () => {
    it("top-level: suggests keywords, types, vars", async () => {
      const content = `
type A = { a: int }
var x: int = 1
`;
      const pos = { line: 3, character: 0 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "var");
      assert.include(labels, "fun");
      assert.include(labels, "type");
    });

    it("test([{ | }]): suggest fields of A inside nested array/object arg", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
fun test(inout d: A[2]) { d[0].a = 5 }
test([{}])
`;
      const pos = { line: 4, character: 6 }; // Inside the {}
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "a", "Should suggest field 'a' of A inside test([{}])");
      assert.include(labels, "b", "Should suggest field 'b' of A inside test([{}])");
    });
  });
});
