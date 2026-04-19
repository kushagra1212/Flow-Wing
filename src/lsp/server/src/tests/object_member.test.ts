import { assert } from "chai";
import { TextDocument } from "vscode-languageserver-textdocument";
import { TextDocuments } from "vscode-languageserver";
import { getObjectSuggestion } from "../handlers/onCompletion";
import { flowWingConfig } from "../config";
import { getTestCompilerPath } from "./testCompilerPath";

describe("Object and Member Completion Reproduction", () => {
  const compilerPath = getTestCompilerPath();

  before(function () {
    flowWingConfig.flowWingPath = compilerPath;
  });

  beforeEach(function () {
    // Compiler invocations can be slow when tests run in parallel
    this.timeout(10000);
  });

  const mockDocuments = (doc: TextDocument) => {
    const docs = new TextDocuments(TextDocument);
    (docs as any).get = (uri: string) => (uri === doc.uri ? doc : undefined);
    return docs;
  };

  it("should provide suggestions for members of object type: b.", async () => {
    const content = `
type A = {
    a: int
}
var b: A = {a: 2}
b.
`;
    // b. is on line 5 (0-indexed)
    const position = { line: 5, character: 2 }; 
    const uri = "file:///test_member.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);
    
    const labels = items.map(i => i.label);
    assert.include(labels, "a", "Should suggest member 'a' for 'b.'");
  });

  it("should provide suggestions for members inside object literal: var b: A = {", async () => {
    const content = `
type A = {
    a: int
}
var temp: A = {a:1}
var b: A = {
`;
    // Line 6, character 12 is after '{'
    const position = { line: 6, character: 12 }; 
    const uri = "file:///test_start.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);
    
    const labels = items.map(i => i.label);
    assert.include(labels, "a", "Should suggest member 'a' inside '{'");
  });

  it("should provide suggestions after colon in object literal: {a:}", async () => {
    const content = `
type A = {
    a: int
}
var x: int = 10
var b: A = {a:
`;
    // Line 6, character 14 is after 'a:'
    const position = { line: 6, character: 14 }; 
    const uri = "file:///test_literal.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);
    
    const labels = items.map(i => i.label);
    // Should at least suggest 'x' or keywords
    assert.include(labels, "x", "Should suggest 'x' for value of 'a'");
  });

  it("should suggest only B fields inside b:{} (empty nested object)", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A = {b:{}}
`;
    // Line 3, character 15 = inside the inner {}
    const position = { line: 3, character: 15 };
    const uri = "file:///test_empty_nested.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);

    const labels = items.map(i => i.label);
    assert.include(labels, "b", "Should suggest 'b' (field of B)");
    assert.notInclude(labels, "a", "Should NOT suggest 'a' (field of A) when inside B");
  });

  it("should provide suggestions for nested object literal: {a:2, b: {", async () => {
    const content = `
type B = {
    b: int
}
type A = {
    a: int
    b: B
}
var c: A = {a:2, b: {
`;
    // Line 8, character 20 is after '{' - inside nested object (type B), not top-level (type A)
    const position = { line: 8, character: 20 };
    const uri = "file:///test_nested.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);

    const labels = items.map(i => i.label);
    assert.include(labels, "b", "Should suggest member 'b' of type B inside nested '{'");
    assert.notInclude(labels, "a", "Should NOT suggest 'a' (field of A) when inside B object literal");
  });

  it("should provide completions inside array even when error exists elsewhere (println(c.b.b))", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a: 1, b: {b: 1}}]
println(c.b.b)
`;
    // Line 3, char 33 = after } before ] - add second element. c.b.b is invalid (c is array)
    const position = { line: 3, character: 33 };
    const uri = "file:///test_array_error.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);

    assert.isAtLeast(items.length, 1, "Should provide completions despite error elsewhere");
  });

  it("should provide suggestions inside array literal: var c: A[2] = []", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = []
`;
    // Line 3, character 15 = inside []
    const position = { line: 3, character: 15 };
    const uri = "file:///test_array.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);

    const labels = items.map(i => i.label);
    // Should suggest values (variables, object literal start, etc.) - at least some completions
    assert.isAtLeast(items.length, 1, "Should suggest completions inside array literal");
    // Keywords or symbols like 'var', 'type', object-related suggestions
    assert.isTrue(
      labels.some((l) => ["var", "type", "fun", "{", "a", "b", "c"].includes(l)),
      "Should suggest relevant completions for array element"
    );
  });

  it("should provide suggestions for c[0].b. (array index + member access)", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A[2] = [{a: 1, b: {b: 1}}]
c[0].b.
`;
    // Line 4 (0-indexed), character 8 = after c[0].b.
    const position = { line: 4, character: 8 };
    const uri = "file:///test_array_member.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
      textDocument: { uri },
      position,
    }, docs);

    const labels = items.map((i) => i.label);
    assert.include(labels, "b", "Should suggest member 'b' of type B for c[0].b.");
  });

  it("should suggest only A members (a, b) for d[0]. (array index + member access)", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
var d: A[2] = [{a:1, b:{b:2}}]
d[0].
`;
    const position = { line: 4, character: 6 };
    const uri = "file:///test_array_member_d.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
      textDocument: { uri },
      position,
    }, docs);

    const labels = items.map((i) => i.label);
    assert.include(labels, "a", "Should suggest member 'a' of type A for d[0].");
    assert.include(labels, "b", "Should suggest member 'b' of type A for d[0].");
    assert.notInclude(labels, "fun", "Should NOT suggest keywords when in member access");
    assert.notInclude(labels, "type", "Should NOT suggest keywords when in member access");
  });

  it("should suggest A members for d[0]. when d is function param (inside body)", async () => {
    const content = `
type B = { b: int }
type A = { a: int, b: B }
fun test(inout d: A[2]) {
  d[0].
}
`;
    const position = { line: 4, character: 6 };
    const uri = "file:///test_param_d0_member.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
      textDocument: { uri },
      position,
    }, docs);

    const labels = items.map((i) => i.label);
    assert.include(labels, "a", "Should suggest member 'a' for d[0]. when d is param");
    assert.include(labels, "b", "Should suggest member 'b' for d[0]. when d is param");
  });

  it("should provide suggestions for d[0].b. (parameter + array + nested member)", async () => {
    const content = `
type B = {
    b: int
}
type A = {
    a: int
    b: B
}

var c: A[2] = [{a:2,b:{b:5}}]

fun test(inout d: A[2]) {
    d[0].b. 
}
`;
    // Line 12, character 11 = after d[0].b.
    const position = { line: 12, character: 11 };
    const uri = "file:///test_user_repro.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
      textDocument: { uri },
      position,
    }, docs);

    const labels = items.map((i) => i.label);
    assert.include(labels, "b", "Should suggest member 'b' of type B for d[0].b.");
  });

  it("should provide suggestions for second member: {a:2, ", async () => {
    const content = `
type B = {
    b: int
}
type A = {
    a: int
    b: B
}
var c: A = {a:2, 
`;
    // Line 8, character 16 is after ','
    const position = { line: 8, character: 16 }; 
    const uri = "file:///test_comma.fg";
    const document = TextDocument.create(uri, "flowwing", 0, content);
    const docs = mockDocuments(document);

    const items = await getObjectSuggestion({
        textDocument: { uri },
        position
    }, docs);
    
    const labels = items.map(i => i.label);
    assert.include(labels, "b", "Should suggest member 'b' after ','");
  });
});
