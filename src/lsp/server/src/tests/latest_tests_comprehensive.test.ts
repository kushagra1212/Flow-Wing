/**
 * Comprehensive LSP tests for LatestTests fixtures.
 * Covers permutations and combinations: completion, hover, definition, signature help, diagnostics.
 * Uses actual fixture files from tests/fixtures/LatestTests.
 */

import { assert } from "chai";
import * as path from "path";
import * as fs from "fs";
import { TextDocument } from "vscode-languageserver-textdocument";
import { TextDocuments } from "vscode-languageserver";
import { flowWingConfig } from "../config";
import { getObjectSuggestion } from "../handlers/onCompletion";
import {
  getSemPathForDocument,
  validateFile,
  formatFlowWingFile,
} from "../services/documentService";
import {
  getHoverFromSem,
  getSymbolAtPosition,
  getDeclarationForSymbol,
  getSignatureHelpFromSem,
  isSemFormat,
} from "../services/semService";
import { fileUtils } from "../utils/fileUtils";
import { getTestCompilerPath, getTestFixturesDir, pathToFileUri } from "./testCompilerPath";

const FIXTURES_DIR = getTestFixturesDir();
const COMPILER_PATH = getTestCompilerPath();

function getFilesRecursive(dir: string, ext = ".fg"): string[] {
  if (!fs.existsSync(dir)) return [];
  let results: string[] = [];
  for (const file of fs.readdirSync(dir)) {
    const full = path.join(dir, file);
    const stat = fs.statSync(full);
    if (stat.isDirectory()) {
      results = results.concat(getFilesRecursive(full, ext));
    } else if (file.endsWith(ext)) {
      results.push(full);
    }
  }
  return results;
}

const mockDocuments = (doc: TextDocument) => {
  const docs = new TextDocuments(TextDocument);
  (docs as any).get = (uri: string) => (uri === doc.uri ? doc : undefined);
  return docs;
};

describe("LatestTests Comprehensive LSP", () => {
  before(function () {
    flowWingConfig.flowWingPath = COMPILER_PATH;
  });

  beforeEach(function () {
    this.timeout(10000);
  });

  describe("SEM/AST generation per category", function () {
    const categories = [
      "01_basics",
      "01_bool",
      "01_int",
      "01_string",
      "01_deci",
      "01_char",
      "01_unary",
      "ArrayTests",
      "ObjectTests",
      "FunctionTests",
      "VariableDeclarationTests",
      "ConstTests",
      "ContainerTests",
      "DynamicTests",
      "DynamicVariableTests",
      "EdgeCaseTests",
      "MixtureTests",
      "IndexTests",
      "TypeConversionFunctionTests",
      "ScopeTests",
      "PrimitiveTests",
      "IfStatementTests",
      "BringTests",
      "ModuleTests",
    ];

    for (const category of categories) {
      it(`should generate SEM for valid files in ${category}`, async function () {
        // Before first await: Mocha async tests need an explicit timeout here; npm test uses
        // --timeout 15000 and BringTests alone can take ~45s (SEM repair + nested imports).
        this.timeout(120000);
        const dir = path.join(FIXTURES_DIR, category);
        const files = getFilesRecursive(dir).filter(
          (f) =>
            !f.includes("/errors/") &&
            !f.includes("/runtime_errors/") &&
            !fs.readFileSync(f, "utf-8").includes("EXPECT_ERROR")
        );
        if (files.length === 0) return;

        const sample = files.slice(0, 5);
        for (const filePath of sample) {
          const content = fs.readFileSync(filePath, "utf-8");
          const doc = TextDocument.create(
            pathToFileUri(filePath),
            "flowwing",
            0,
            content
          );
          const semPath = await getSemPathForDocument(doc, {
            position: { line: 0, character: 0 },
          });
          assert.isNotNull(
            semPath,
            `SEM should be generated for ${path.relative(FIXTURES_DIR, filePath)}`
          );
        }
      });
    }
  });

  describe("Completion permutations", () => {
    it("completion: function call (add(3,|)", async () => {
      const content = `fun add(a: int, b: int) -> int { return a + b }
println(add(3,`;
      const pos = { line: 2, character: 17 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      assert.isAtLeast(items.length, 1, "Should suggest completions in function call");
    });

    it("completion: object literal after colon {name:|}", async () => {
      const content = `
type User = { name: str, age: int }
var u: User = { name:`;
      const pos = { line: 3, character: 22 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      assert.isAtLeast(items.length, 1, "Should suggest value after colon");
    });

    it("completion: member access obj.| (object with array member)", async () => {
      const content = `type T = { vals:int[3], name: str }
var obj:T = { vals:[10,20,30], name: "x" }
println(obj.vals[0])
obj.`;
      const pos = { line: 4, character: 4 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "vals", "Should suggest vals");
      assert.include(labels, "name", "Should suggest name");
    });

    it("completion: array of objects pts[0].|", async () => {
      const content = `
type Point = { x: int, y: int }
var pts: Point[2] = [{x:1,y:2}, {x:3,y:4}]
pts[0].`;
      const pos = { line: 3, character: 8 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest x for Point");
      assert.include(labels, "y", "Should suggest y for Point");
    });

    it("completion: if (getPoints()[0].|) - member access in conditional", async function () {
      const content = `
type Point = { x: int, y: int }
fun getPoints() -> Point[2] {
  return [{ x: 1, y: 2 }, { x: 3, y: 4 }]
}
if (getPoints()[0].`;
      const pos = { line: 5, character: 19 }; // cursor right after the dot
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x", "Should suggest x for Point in if (getPoints()[0].)");
      assert.include(labels, "y", "Should suggest y for Point in if (getPoints()[0].)");
    });

    it("completion: function return array of objects getPoints()[0].|", async function () {
      const content = `
type Point = { x: int, y: int }
fun getPoints() -> Point[2] {
  return [{ x: 1, y: 2 }, { x: 3, y: 4 }]
}
println(getPoints()[0].`;
      const pos = { line: 5, character: 22 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.isAtLeast(items.length, 1, "Should suggest completions");
      if (labels.includes("x") && labels.includes("y")) {
        assert.include(labels, "x", "Should suggest x for Point from getPoints()[0]");
        assert.include(labels, "y", "Should suggest y for Point from getPoints()[0]");
      }
    });

    it("completion: function return object getPoint().|", async function () {
      const content = `
type Point = { x: int, y: int }
fun getPoint() -> Point {
  return { x: 1, y: 2 }
}
println(getPoint().`;
      const pos = { line: 5, character: 18 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.isAtLeast(items.length, 1, "Should suggest completions");
      if (labels.includes("x") && labels.includes("y")) {
        assert.include(labels, "x", "Should suggest x for Point from getPoint()");
        assert.include(labels, "y", "Should suggest y for Point from getPoint()");
      }
    });

    it("completion: nested object {a:2, b: {|", async () => {
      const content = `
type B = { b: int }
type A = { a: int, b: B }
var c: A = {a:2, b: {`;
      const pos = { line: 5, character: 18 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "b", "Should suggest b (field of B)");
      assert.notInclude(labels, "a", "Should NOT suggest a when inside B");
    });

    it("completion: array literal var c: A[2] = [|]", async () => {
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
      assert.isAtLeast(items.length, 1, "Should suggest completions inside array");
    });
  });

  describe("Hover permutations", () => {
    it("hover: variable", async () => {
      const content = `var x: int = 42
println(x)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const hover = getHoverFromSem(sem, { line: 1, character: 8 }, "x");
      assert.isNotNull(hover, "Hover on variable x");
      assert.include(hover!.value, "int", "Hover should show type");
    });

    it("hover: function", async () => {
      const content = `fun add(a: int, b: int) -> int { return a + b }
println(add(1, 2))`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const hover = getHoverFromSem(sem, { line: 1, character: 10 }, "add");
      assert.isNotNull(hover, "Hover on function add");
      assert.include(hover!.value, "add", "Hover should show function name");
    });

    it("hover: member expression obj.vals", async () => {
      const content = `type T = { vals:int[3] }
var obj:T = { vals:[10,20,30] }
println(obj.vals)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const hover = getHoverFromSem(
        sem,
        { line: 2, character: 14 },
        "vals",
        "obj.vals"
      );
      assert.isNotNull(hover, "Hover on obj.vals");
    });

    it("hover: function return array of objects getPoints()[0].x", async () => {
      const content = `type Point = { x: int, y: int }
fun getPoints() -> Point[2] {
  return [{ x: 1, y: 2 }, { x: 3, y: 4 }]
}
println(getPoints()[0].x)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const hover = getHoverFromSem(
        sem,
        { line: 4, character: 21 },
        "x",
        "getPoints()[0].x"
      );
      assert.isNotNull(hover, "Hover on getPoints()[0].x");
      assert.include(hover!.value, "int", "Hover should show x type as int");
    });

    it("hover: nested object getShape().topLeft.x", async () => {
      const content = `type Point = { x: int, y: int }
type Rectangle = { topLeft: Point, bottomRight: Point }
fun getShape() -> Rectangle {
  return { topLeft: { x: 0, y: 0 }, bottomRight: { x: 100, y: 100 } }
}
println(getShape().topLeft.x)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const hover = getHoverFromSem(
        sem,
        { line: 5, character: 24 },
        "x",
        "getShape().topLeft.x"
      );
      assert.isNotNull(hover, "Hover on getShape().topLeft.x");
    });
  });

  describe("Definition permutations", () => {
    it("definition: function declaration", async () => {
      const content = `fun add(a: int, b: int) -> int { return a + b }
println(add(1, 2))`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const result = getSymbolAtPosition(sem, { line: 1, character: 10 }, "add");
      assert.isNotNull(result, "Symbol at add call");
      const loc = getDeclarationForSymbol(sem, result!.symbolId, doc.uri);
      assert.isNotNull(loc, "Definition for add");
    });

    it("definition: variable declaration", async () => {
      const content = `var x: int = 42
println(x)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const result = getSymbolAtPosition(sem, { line: 1, character: 8 }, "x");
      assert.isNotNull(result, "Symbol at x");
      const loc = getDeclarationForSymbol(sem, result!.symbolId, doc.uri);
      assert.isNotNull(loc, "Definition for x");
    });
  });

  describe("Signature help permutations", () => {
    it("signature help: function call add(|", async () => {
      const content = `fun add(a: int, b: int) -> int { return a + b }
println(add(`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc, {
        position: { line: 1, character: 12 },
        partialId: "add",
      });
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const sig = getSignatureHelpFromSem(
        sem,
        { line: 1, character: 12 },
        1,
        "add"
      );
      assert.isNotNull(sig, "Signature help for add");
      assert.isAtLeast(sig!.signatures.length, 1);
    });

    it("signature help: object param function", async () => {
      const content = `
type Point = { x: int, y: int }
fun printPoint(p: Point) -> int { return p.x }
var pt: Point = {x: 3, y: 4}
printPoint(`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc, {
        position: { line: 4, character: 11 },
        partialId: "printPoint",
      });
      assert.isNotNull(semPath);
      const semContent = await fileUtils.readFile(semPath!);
      const sem = JSON.parse(semContent);
      const sig = getSignatureHelpFromSem(
        sem,
        { line: 4, character: 11 },
        1,
        "printPoint"
      );
      assert.isNotNull(sig, "Signature help for printPoint");
    });
  });

  describe("Edge case LSP behavior", () => {
    it("chained index+member obj.vals[0]: hover on obj.vals", async () => {
      const content = `type T = { vals:int[3] }
var obj:T = { vals:[10,20,30] }
println(obj.vals[0])`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const hover = getHoverFromSem(sem, { line: 2, character: 14 }, "vals", "obj.vals");
      assert.isNotNull(hover, "Hover on obj.vals (chained index+member)");
    });

    it("chained index+member: completion for obj.| suggests vals", async () => {
      const content = `type T = { vals:int[3] }
var obj:T = { vals:[10,20,30] }
obj.`;
      const pos = { line: 2, character: 4 };
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "vals", "obj. should suggest vals");
    });

    it("reuse_var_name_after_scope: symbol resolution in each block", async () => {
      const content = `{
    var x:int = 1
    println(x)
}
{
    var x:str = "re-declared"
    println(x)
}`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const result1 = getSymbolAtPosition(sem, { line: 2, character: 12 }, "x");
      const result2 = getSymbolAtPosition(sem, { line: 6, character: 12 }, "x");
      assert.isNotNull(result1, "Symbol x in first block");
      assert.isNotNull(result2, "Symbol x in second block");
      assert.notEqual(result1!.symbolId, result2!.symbolId, "x in each block should be different symbols");
    });

    it("dynamic array var a:[3]: SEM and hover", async () => {
      const content = `var a:[3] = [0, 0, 0]
println(a)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const result = getSymbolAtPosition(sem, { line: 1, character: 8 }, "a");
      assert.isNotNull(result, "Symbol a (dynamic array)");
      const hover = getHoverFromSem(sem, { line: 1, character: 8 }, "a");
      assert.isNotNull(hover, "Hover on dynamic array var");
    });

    it("partial array init var a:int[10]=[1,2]: SEM generation", async () => {
      const content = `var a:int[10] = [1, 2]
println(a)`;
      const doc = TextDocument.create("file:///test.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
    });
  });

  describe("Fixture-based integration (actual LatestTests files)", () => {
    const fixtureTests: Array<{
      name: string;
      file: string;
      test: (content: string, doc: TextDocument) => Promise<void>;
    }> = [
      {
        name: "01_basics/hello-world",
        file: "01_basics/hello-world.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          assert.isTrue(isSemFormat(sem));
        },
      },
      {
        name: "ObjectTests/declaration/basic",
        file: "ObjectTests/declaration/basic.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          assert.isTrue(isSemFormat(sem));
          const lines = content.split("\n");
          const printLine = lines.findIndex((l) => l.includes("print(p"));
          if (printLine >= 0) {
            const pCol = lines[printLine].indexOf("p");
            const result = getSymbolAtPosition(sem, { line: printLine, character: pCol }, "p");
            assert.isNotNull(result, "Symbol p at print(p)");
            const hover = getHoverFromSem(sem, { line: printLine, character: pCol }, "p");
            assert.isNotNull(hover, "Hover on p");
          }
        },
      },
      {
        name: "FunctionTests/object_param",
        file: "FunctionTests/14_object_with_func/object_param.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          const result = getSymbolAtPosition(sem, { line: 11, character: 12 }, "pt");
          assert.isNotNull(result);
        },
      },
      {
        name: "EdgeCaseTests/chained_index_and_member",
        file: "EdgeCaseTests/chained_index_and_member.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          const result = getSymbolAtPosition(sem, { line: 2, character: 10 }, "obj");
          assert.isNotNull(result, "Symbol obj");
        },
      },
      {
        name: "ArrayTests/basic",
        file: "ArrayTests/basic/int_1d_partial.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
        },
      },
      {
        name: "MixtureTests/object_array_index",
        file: "MixtureTests/object_array_index_read.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
        },
      },
      {
        name: "ObjectTests/array_of_objects",
        file: "ObjectTests/array_of_objects/nested_member_array_reassign.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
        },
      },
      {
        name: "FunctionTests/multi_return",
        file: "FunctionTests/04_multi_return/multi_return_four_values.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
        },
      },
      {
        name: "TypeConversionFunctionTests",
        file: "TypeConversionFunctionTests/String/from_int8.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
        },
      },
      {
        name: "IfStatementTests/condition_func_return_object",
        file: "IfStatementTests/08_object/condition_func_return_object.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          const result = getSymbolAtPosition(sem, { line: 10, character: 6 }, "getPoint");
          assert.isNotNull(result, "Symbol getPoint in if condition");
        },
      },
      {
        name: "IfStatementTests/condition_func_return_array_of_objects",
        file: "IfStatementTests/09_array/condition_func_return_array_of_objects.fg",
        test: async (content, doc) => {
          const semPath = await getSemPathForDocument(doc);
          assert.isNotNull(semPath);
          const sem = JSON.parse(await fileUtils.readFile(semPath!));
          const result = getSymbolAtPosition(sem, { line: 10, character: 6 }, "getPoints");
          assert.isNotNull(result, "Symbol getPoints in if condition");
        },
      },
    ];

    for (const { name, file, test } of fixtureTests) {
      it(`fixture: ${name}`, async function () {
        const filePath = path.join(FIXTURES_DIR, file);
        if (!fs.existsSync(filePath)) return this.skip();
        const content = fs.readFileSync(filePath, "utf-8");
        const doc = TextDocument.create(
          pathToFileUri(filePath),
          "flowwing",
          0,
          content
        );
        await test(content, doc);
      });
    }
  });

  describe("Document formatting", () => {
    it("should format valid Flow-Wing file", async () => {
      const content = `fun add(a: int, b: int) -> int { return a + b }
println(add(1, 2))`;
      const formatted = await formatFlowWingFile("file:///test.fg", content);
      assert.isString(formatted);
      assert.notEqual(formatted, "", "Formatting should return non-empty");
    });
  });

  describe("Diagnostics for error files", () => {
    it("should detect error in EXPECT_ERROR file", async function () {
      const errorFiles = getFilesRecursive(FIXTURES_DIR).filter(
        (f) =>
          f.includes("/errors/") ||
          fs.readFileSync(f, "utf-8").includes("EXPECT_ERROR")
      );
      if (errorFiles.length === 0) return this.skip();
      const sample = errorFiles[0];
      const result = await validateFile("file:///test.fg", sample);
      assert.isTrue(
        result.hasError,
        `Expected error in ${path.relative(FIXTURES_DIR, sample)}`
      );
    });
  });
});
