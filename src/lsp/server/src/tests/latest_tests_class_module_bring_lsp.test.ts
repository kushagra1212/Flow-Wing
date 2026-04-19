/**
 * LSP integration tests aligned with LatestTests: ClassTests, ModuleTests, BringTests.
 * Covers hover, autocomplete (sem + full `getObjectSuggestion` path), go-to-definition,
 * and file navigation using real fixtures and the same compiler + sem pipeline as the editor.
 */

import { assert } from "chai";
import * as path from "path";
import * as fs from "fs";
import * as os from "os";
import { TextDocument } from "vscode-languageserver-textdocument";
import { TextDocuments } from "vscode-languageserver";
import { flowWingConfig } from "../config";
import { getObjectSuggestion } from "../handlers/onCompletion";
import { getSemPathForDocument, validateFile } from "../services/documentService";
import { createDiagnostic } from "../services/diagnosticService";
import {
  getHoverFromSem,
  getSymbolAtPosition,
  getDeclarationForSymbol,
  getModuleMemberNamesFromSem,
  getCompletionItemsFromSem,
  getModuleQualifiedCompletionItems,
  getSignatureHelpFromSem,
  getExpectedParamTypeFromSem,
  getCompletionItemsForFunctionArgument,
  getBringListDeclarationLocation,
  isSemFormat,
} from "../services/semService";
import { CompletionItemKind } from "vscode-languageserver";
import { fileUtils } from "../utils/fileUtils";
import { fileURLToPath } from "url";
import { getImportedFileUri } from "../utils";
import { getTestCompilerPath, getTestFixturesDir, pathToFileUri } from "./testCompilerPath";

const FIXTURES = getTestFixturesDir();
const COMPILER = getTestCompilerPath();

const mockDocuments = (doc: TextDocument) => {
  const docs = new TextDocuments(TextDocument);
  (docs as unknown as { get: (u: string) => TextDocument | undefined }).get = (
    uri: string
  ) => (uri === doc.uri ? doc : undefined);
  return docs;
};

function completionLabels(items: { label?: string }[]): string[] {
  return items.map((i) => i.label).filter((x): x is string => x != null && x !== "");
}

describe("LatestTests LSP: class, module, bring", () => {
  before(() => {
    flowWingConfig.flowWingPath = COMPILER;
  });

  describe("ClassTests — hover, completion, definition", () => {
    const rel = path.join(
      "ClassTests",
      "01_basic",
      "class_new_and_field_read.fg"
    );

    it("hover: class field access (new A()).x shows int", async function () {
      this.timeout(30000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      assert.isTrue(isSemFormat(sem));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("(new A()).x"));
      assert.isAtLeast(lineIdx, 0);
      const col = lines[lineIdx].indexOf(".x") + 1;
      const hover = getHoverFromSem(
        sem,
        { line: lineIdx, character: col },
        "x",
        "(new A()).x"
      );
      assert.isNotNull(hover);
      assert.include(hover!.value, "int");

      const sym = getSymbolAtPosition(
        sem,
        { line: lineIdx, character: col },
        "x"
      );
      assert.isNotNull(sym);
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
    });

    it("completion: member after (new A()).", async function () {
      this.timeout(30000);
      const content = `class A {
  var x: int
}
println((new A()).`;
      const pos = { line: 4, character: 17 };
      const doc = TextDocument.create("file:///class_member.fg", "flowwing", 0, content);
      const items = await getObjectSuggestion(
        { textDocument: { uri: doc.uri }, position: pos },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x");
    });
  });

  /**
   * Autocomplete: sem-backed member lists, module-qualified names, and brought globals.
   * Combines direct sem API checks (deterministic) with getObjectSuggestion (full editor path).
   */
  describe("Autocomplete — class, module, bring", () => {
    describe("ClassTests", () => {
      const basicClass = path.join(
        FIXTURES,
        "ClassTests",
        "01_basic",
        "class_new_and_field_read.fg"
      );
      const memberMethod = path.join(
        FIXTURES,
        "ClassTests",
        "04_member_methods",
        "member_method_implicit_return_like_global_fun.fg"
      );

      it("sem: (new A) member completion lists field x", async function () {
        this.timeout(30000);
        if (!fs.existsSync(basicClass)) return this.skip();
        const doc = TextDocument.create(
          pathToFileUri(basicClass),
          "flowwing",
          0,
          fs.readFileSync(basicClass, "utf-8")
        );
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const items = getCompletionItemsFromSem(sem, "(new A)", true, doc.uri);
        const labels = completionLabels(items);
        assert.include(labels, "x", "class field x");
        const xi = items.find((i) => i.label === "x");
        assert.equal(xi?.kind, CompletionItemKind.Field);
      });

      it("editor: getObjectSuggestion after (new A()). lists x (real file URI)", async function () {
        this.timeout(45000);
        if (!fs.existsSync(basicClass)) return this.skip();
        const content = `class A {
  var x: int
}
println((new A()).`;
        const lines = content.split("\n");
        const pos = {
          line: lines.length - 1,
          character: lines[lines.length - 1].length,
        };
        const doc = TextDocument.create(pathToFileUri(basicClass), "flowwing", 0, content);
        const items = await getObjectSuggestion(
          { textDocument: { uri: doc.uri }, position: pos },
          mockDocuments(doc)
        );
        assert.include(completionLabels(items), "x");
      });

      it("sem: instance a. lists member method addOne", async function () {
        this.timeout(30000);
        if (!fs.existsSync(memberMethod)) return this.skip();
        const doc = TextDocument.create(
          pathToFileUri(memberMethod),
          "flowwing",
          0,
          fs.readFileSync(memberMethod, "utf-8")
        );
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const items = getCompletionItemsFromSem(sem, "a", true, doc.uri);
        const labels = completionLabels(items);
        assert.include(labels, "addOne");
        const mi = items.find((i) => i.label === "addOne");
        assert.equal(mi?.kind, CompletionItemKind.Method);
      });

      it("editor: getObjectSuggestion after a. lists addOne", async function () {
        this.timeout(45000);
        if (!fs.existsSync(memberMethod)) return this.skip();
        const content = `class A {
  fun addOne(x: int) {
    return x + 1
  }
}
var a: A = new A()
println(a.`;
        const lines = content.split("\n");
        const pos = {
          line: lines.length - 1,
          character: lines[lines.length - 1].length,
        };
        const doc = TextDocument.create(pathToFileUri(memberMethod), "flowwing", 0, content);
        const items = await getObjectSuggestion(
          { textDocument: { uri: doc.uri }, position: pos },
          mockDocuments(doc)
        );
        assert.include(completionLabels(items), "addOne");
      });
    });

    describe("ModuleTests", () => {
      const modFun = path.join(
        FIXTURES,
        "ModuleTests",
        "02_functions",
        "module_fun_call.fg"
      );
      const crossMain = path.join(
        FIXTURES,
        "ModuleTests",
        "ModuleImportTest",
        "temp1.fg"
      );

      it("sem: lib:: member names include getN", async function () {
        this.timeout(30000);
        if (!fs.existsSync(modFun)) return this.skip();
        const sourceText = fs.readFileSync(modFun, "utf-8");
        const doc = TextDocument.create(pathToFileUri(modFun), "flowwing", 0, sourceText);
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const names = getModuleMemberNamesFromSem(sem, "lib", sourceText);
        assert.include(names, "getN");
        const items = getModuleQualifiedCompletionItems(sem, "lib", sourceText, "");
        assert.isAtLeast(items.length, 1);
        assert.include(completionLabels(items), "getN");
      });

      it("sem: lib::ge filters to getN", async function () {
        this.timeout(30000);
        if (!fs.existsSync(modFun)) return this.skip();
        const sourceText = fs.readFileSync(modFun, "utf-8");
        const doc = TextDocument.create(pathToFileUri(modFun), "flowwing", 0, sourceText);
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const items = getModuleQualifiedCompletionItems(sem, "lib", sourceText, "ge");
        assert.deepEqual(completionLabels(items), ["getN"]);
      });

      it("editor: cursor after lib:: suggests getN", async function () {
        this.timeout(45000);
        if (!fs.existsSync(modFun)) return this.skip();
        const content = `module [lib]

fun getN() -> int {
  return 7
}

println(lib::`;
        const lines = content.split("\n");
        const pos = {
          line: lines.length - 1,
          character: lines[lines.length - 1].length,
        };
        const doc = TextDocument.create(pathToFileUri(modFun), "flowwing", 0, content);
        const items = await getObjectSuggestion(
          { textDocument: { uri: doc.uri }, position: pos },
          mockDocuments(doc)
        );
        assert.include(completionLabels(items), "getN");
        const itGetN = items.find((i) => i.label === "getN");
        assert.ok(itGetN, "getN completion item");
        assert.ok(
          (itGetN!.detail ?? "").includes("getN") ||
            (itGetN!.label ?? "").includes("getN"),
          "detail or label should describe the module member"
        );
      });

      it("sem: test-module.fg yields test:: members (x) for qualification", async function () {
        this.timeout(45000);
        if (!fs.existsSync(crossMain)) return this.skip();
        const modPath = path.join(
          path.dirname(crossMain),
          "test-module.fg"
        );
        if (!fs.existsSync(modPath)) return this.skip();
        const modSrc = fs.readFileSync(modPath, "utf-8");
        const modDoc = TextDocument.create(
          pathToFileUri(modPath),
          "flowwing",
          0,
          modSrc
        );
        const modSemPath = await getSemPathForDocument(modDoc);
        assert.isNotNull(modSemPath);
        const modSem = JSON.parse(await fileUtils.readFile(modSemPath!));
        const names = getModuleMemberNamesFromSem(modSem, "test", modSrc);
        assert.include(names, "x");
        const items = getModuleQualifiedCompletionItems(modSem, "test", modSrc, "");
        assert.include(completionLabels(items), "x");
      });

      it("editor: cursor after test:: suggests x (brought module)", async function () {
        this.timeout(45000);
        if (!fs.existsSync(crossMain)) return this.skip();
        const content = `
    bring test
    print(test::`;
        const lines = content.split("\n");
        const last = lines.length - 1;
        const pos = { line: last, character: lines[last].length };
        const doc = TextDocument.create(pathToFileUri(crossMain), "flowwing", 0, content);
        const items = await getObjectSuggestion(
          { textDocument: { uri: doc.uri }, position: pos },
          mockDocuments(doc)
        );
        assert.include(completionLabels(items), "x");
      });
    });

    describe("BringTests", () => {
      const bringMain = path.join(FIXTURES, "BringTests", "01_ok", "bring_validates_only.fg");

      it("sem: default completions include brought global only_in_this_file", async function () {
        this.timeout(45000);
        if (!fs.existsSync(bringMain)) return this.skip();
        const doc = TextDocument.create(
          pathToFileUri(bringMain),
          "flowwing",
          0,
          fs.readFileSync(bringMain, "utf-8")
        );
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const items = getCompletionItemsFromSem(sem, "", false, doc.uri);
        assert.include(completionLabels(items), "only_in_this_file");
      });

      it("sem: prefix only_in narrows to only_in_this_file", async function () {
        this.timeout(45000);
        if (!fs.existsSync(bringMain)) return this.skip();
        const doc = TextDocument.create(
          pathToFileUri(bringMain),
          "flowwing",
          0,
          fs.readFileSync(bringMain, "utf-8")
        );
        const semPath = await getSemPathForDocument(doc);
        assert.isNotNull(semPath);
        const sem = JSON.parse(await fileUtils.readFile(semPath!));
        const items = getCompletionItemsFromSem(sem, "only_in", false, doc.uri);
        assert.include(completionLabels(items), "only_in_this_file");
      });

      it("editor: typing only_in suggests brought variable", async function () {
        this.timeout(45000);
        if (!fs.existsSync(bringMain)) return this.skip();
        const content = `bring "bring_ok_lib.fg"

only_in`;
        const lines = content.split("\n");
        const pos = {
          line: lines.length - 1,
          character: lines[lines.length - 1].length,
        };
        const doc = TextDocument.create(pathToFileUri(bringMain), "flowwing", 0, content);
        const items = await getObjectSuggestion(
          { textDocument: { uri: doc.uri }, position: pos },
          mockDocuments(doc)
        );
        assert.include(completionLabels(items), "only_in_this_file");
      });
    });
  });

  describe("ModuleTests — hover, completion, definition", () => {
    const rel = path.join("ModuleTests", "01_basic", "module_var_access.fg");

    it("hover: module member m::x", async function () {
      this.timeout(30000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("m::x"));
      assert.isAtLeast(lineIdx, 0);
      const col = lines[lineIdx].indexOf("x", lines[lineIdx].indexOf("::"));
      const hover = getHoverFromSem(sem, { line: lineIdx, character: col }, "x");
      assert.isNotNull(hover);
      assert.include(hover!.value, "int");

      const sym = getSymbolAtPosition(sem, { line: lineIdx, character: col }, "x");
      assert.isNotNull(sym);
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
    });

    it("go-to-definition: acc::total resolves to var total (cursor on acc, ::, or total)", async function () {
      this.timeout(45000);
      const content = `module [acc]

var total: int = 0

fun add(n: int) -> nthg {
  acc::total = acc::total + n
}`;
      const doc = TextDocument.create("file:///test_mod_acc_total.fg", "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("acc::total"));
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const onAcc = line.indexOf("acc");
      const onTotal = line.indexOf("total");
      const onSecondTotal = line.indexOf("total", onTotal + 1);

      for (const [label, pos] of [
        ["on module name acc", { line: lineIdx, character: onAcc }],
        ["on first total", { line: lineIdx, character: onTotal }],
        ["on second total", { line: lineIdx, character: onSecondTotal }],
      ] as const) {
        const word =
          label === "on module name acc" ? "acc" : "total";
        const sym = getSymbolAtPosition(sem, pos, word);
        assert.isNotNull(sym, label);
        assert.equal(sym!.symbol.name, "total", label);
        assert.equal(sym!.symbol.kind, "Variable", label);
        const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
        assert.isNotNull(loc, `declaration ${label}`);
      }
    });

    it("go-to-definition: real file URI for module_for_counter.fg (not sidecar .flowwing-lsp-*.fg)", async function () {
      this.timeout(45000);
      const counterRel = path.join("ModuleTests", "03_edge_cases", "module_for_counter.fg");
      const filePath = path.join(FIXTURES, counterRel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(pathToFileUri(filePath), "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("acc::total"));
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const sym = getSymbolAtPosition(
        sem,
        { line: lineIdx, character: line.indexOf("total") },
        "total"
      );
      assert.isNotNull(sym);
      assert.equal(sym!.symbol.name, "total");
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
      assert.equal(
        loc!.uri,
        doc.uri,
        "Definition must open the editor file, not deleted .flowwing-lsp sidecar"
      );
      assert.notInclude(loc!.uri, ".flowwing-lsp-");
    });

    it("go-to-definition: parameter identifiers a and b in addThenTriple body jump to signature", async function () {
      this.timeout(45000);
      const twoFnRel = path.join(
        "ModuleTests",
        "03_edge_cases",
        "module_two_functions.fg"
      );
      const filePath = path.join(FIXTURES, twoFnRel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(pathToFileUri(filePath), "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      assert.isTrue(isSemFormat(sem));

      const lines = content.split("\n");
      const sigLineIdx = lines.findIndex((l) => l.includes("addThenTriple(a:"));
      const bodyLineIdx = lines.findIndex((l) => l.includes("triple(a + b)"));
      assert.isAtLeast(sigLineIdx, 0);
      assert.isAtLeast(bodyLineIdx, 0);
      const sigLine = lines[sigLineIdx];
      const bodyLine = lines[bodyLineIdx];
      const expectedAChar = sigLine.indexOf("a", sigLine.indexOf("("));
      const expectedBChar = sigLine.indexOf("b", sigLine.indexOf(","));
      assert.isAtLeast(expectedAChar, 0);
      assert.isAtLeast(expectedBChar, 0);

      const useA = bodyLine.indexOf("a", bodyLine.indexOf("triple("));
      const useB = bodyLine.indexOf("b", bodyLine.indexOf("+"));
      assert.isAtLeast(useA, 0);
      assert.isAtLeast(useB, 0);

      for (const [label, pos, name, expectedChar] of [
        ["use of a", { line: bodyLineIdx, character: useA }, "a", expectedAChar],
        ["use of b", { line: bodyLineIdx, character: useB }, "b", expectedBChar],
      ] as const) {
        const sym = getSymbolAtPosition(sem, pos, name);
        assert.isNotNull(sym, label);
        assert.equal(sym!.symbol.kind, "Parameter", label);
        assert.equal(sym!.symbol.name, name, label);
        const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
        assert.isNotNull(loc, `declaration for ${label}`);
        assert.equal(loc!.uri, doc.uri, label);
        assert.equal(loc!.range.start.line, sigLineIdx, label);
        assert.equal(loc!.range.start.character, expectedChar, label);
      }
    });

    it("signature help + arg completions: maths::addThenTriple( resolves module-qualified name", async function () {
      this.timeout(45000);
      const filePath = path.join(
        FIXTURES,
        "ModuleTests",
        "03_edge_cases",
        "use_module_chained_math.fg"
      );
      if (!fs.existsSync(filePath)) return this.skip();
      // Complete call so --emit=sem succeeds; cursor on first arg (same UX as typing inside `(...)`).
      const content = `bring "module_two_functions.fg"

var n1: int = 1
println(maths::addThenTriple(n1, 2))`;
      const doc = TextDocument.create(pathToFileUri(filePath), "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("maths::addThenTriple"));
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const col = line.indexOf("n1");
      const pos = { line: lineIdx, character: col };

      assert.equal(
        getExpectedParamTypeFromSem(sem, "maths::addThenTriple", 1),
        "int",
        "first parameter type for module-qualified call name"
      );

      const sig = getSignatureHelpFromSem(sem, pos, 1, "maths::addThenTriple");
      assert.isNotNull(sig);
      assert.include(sig!.signatures[0].label, "addThenTriple");
      assert.isAtLeast(sig!.signatures[0].parameters?.length ?? 0, 2);

      const argItems = getCompletionItemsForFunctionArgument(
        sem,
        "maths::addThenTriple",
        1,
        "",
        doc.uri
      );
      const labels = argItems.map((i) => i.label);
      assert.include(labels, "n1", "type-aware completion should list int var n1 for first arg");
    });

    it("signature help + hover: nested println(maths::addThenTriple(...)) uses inner callee when parens close", async function () {
      this.timeout(45000);
      const filePath = path.join(
        FIXTURES,
        "ModuleTests",
        "03_edge_cases",
        "use_module_chained_math.fg"
      );
      if (!fs.existsSync(filePath)) return this.skip();
      const content = `bring "module_two_functions.fg"

println(maths::addThenTriple(1, 100))`;
      const doc = TextDocument.create(pathToFileUri(filePath), "flowwing", 0, content);
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("maths::addThenTriple"));
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const afterFirstComma = line.indexOf(",") + 1;
      const pos = { line: lineIdx, character: afterFirstComma };

      const sig = getSignatureHelpFromSem(sem, pos, 2, "println");
      assert.isNotNull(sig, "Even if tokenizer reports outer println, sem should pick addThenTriple");
      assert.include(sig!.signatures[0].label, "addThenTriple");
      assert.notInclude(sig!.signatures[0].label, "println");

      const hover = getHoverFromSem(sem, pos, "", undefined);
      assert.isNotNull(hover);
      assert.include(hover!.value, "addThenTriple");
      assert.notInclude(hover!.value, "println()");
    });

    it("completion: after m:: suggests module var x", async function () {
      this.timeout(30000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("m::x"));
      const col = lines[lineIdx].indexOf("x", lines[lineIdx].indexOf("::"));
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const items = await getObjectSuggestion(
        {
          textDocument: { uri: doc.uri },
          position: { line: lineIdx, character: col },
        },
        mockDocuments(doc)
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "x");
    });

    it("getModuleMemberNamesFromSem lists x for module m", async function () {
      this.timeout(30000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const names = getModuleMemberNamesFromSem(sem, "m", content);
      assert.include(names, "x");
    });
  });

  describe("ModuleTests — cross-file module (bring test)", () => {
    const rel = path.join("ModuleTests", "ModuleImportTest", "temp1.fg");

    it("go-to-definition: test::x jumps to var x in test-module.fg", async function () {
      this.timeout(45000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const moduleDefPath = path.join(path.dirname(filePath), "test-module.fg");
      assert.isTrue(
        fs.existsSync(moduleDefPath),
        "test-module.fg must sit next to temp1.fg"
      );
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("test::x"));
      assert.isAtLeast(lineIdx, 0);
      const col = lines[lineIdx].indexOf("x", lines[lineIdx].indexOf("::"));
      const sym = getSymbolAtPosition(
        sem,
        { line: lineIdx, character: col },
        "x"
      );
      assert.isNotNull(sym);
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
      assert.equal(
        path.normalize(fileURLToPath(loc!.uri)),
        path.normalize(moduleDefPath),
        "definition should be in test-module.fg, not temp1.fg"
      );
    });
  });

  describe("ModuleTests — class in module (bring + cnt::Counter)", () => {
    const rel = path.join(
      "ModuleTests",
      "04_cross_bring_class",
      "use_class_from_module.fg"
    );

    it("go-to-definition: variable c used after bring + module class", async function () {
      this.timeout(45000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const useLine = lines.findIndex((l) => l.includes("println(c.bump())"));
      assert.isAtLeast(useLine, 0);
      const col = lines[useLine].indexOf("(c.");
      assert.isAtLeast(col, 0);
      const sym = getSymbolAtPosition(
        sem,
        { line: useLine, character: col + 2 },
        "c"
      );
      assert.isNotNull(sym);
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
    });
  });

  describe("BringTests — sem, hover, navigation to brought file", () => {
    const rel = path.join("BringTests", "01_ok", "bring_validates_only.fg");

    it("generates SEM with bring next to real file path (sibling lib)", async function () {
      this.timeout(45000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      assert.isTrue(isSemFormat(sem));
      const names = Object.values(sem.sem?.symbols ?? {}).map((s: { name?: string }) => s.name);
      assert.include(names, "only_in_this_file");
    });

    it("hover: brought variable at call site", async function () {
      this.timeout(45000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("println(only_in_this_file)"));
      assert.isAtLeast(lineIdx, 0);
      const col = lines[lineIdx].indexOf("only_in_this_file");
      const hover = getHoverFromSem(
        sem,
        { line: lineIdx, character: col + 2 },
        "only_in_this_file"
      );
      assert.isNotNull(hover);
      assert.include(hover!.value, "only_in_this_file");
    });

    it("file navigation: sibling bring_ok_lib.fg resolves next to main file", function () {
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return;
      const mainUri = pathToFileUri(filePath);
      const sibling = path.resolve(
        path.dirname(fileURLToPath(mainUri)),
        "bring_ok_lib.fg"
      );
      assert.isTrue(
        fs.existsSync(sibling),
        "bring_ok_lib.fg must sit next to bring_validates_only.fg"
      );
      assert.include(sibling.replace(/\\/g, "/"), "bring_ok_lib.fg");
    });

    it("getImportedFileUri resolves bring target from real file URI", async function () {
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return;
      const mainUri = pathToFileUri(filePath);
      const resolved = await getImportedFileUri("bring_ok_lib.fg", mainUri);
      assert.notEqual(resolved, mainUri, "should resolve to the lib, not bounce to current file");
      const fsPath = fileURLToPath(resolved);
      assert.isTrue(
        fs.existsSync(fsPath),
        `expected existing file, got ${fsPath}`
      );
      assert.include(fsPath.replace(/\\/g, "/"), "bring_ok_lib.fg");
    });

    it("go-to-definition: choosy bring {…} from — identifiers in list jump to file1.fg (vars, fun, class, expose types)", async function () {
      this.timeout(45000);
      const taskRel = path.join(
        "BringTests",
        "BringTestBasicTestAllChoosy",
        "task.fg"
      );
      const filePath = path.join(FIXTURES, taskRel);
      const file1Path = path.join(
        path.dirname(filePath),
        "file1.fg"
      );
      if (!fs.existsSync(filePath) || !fs.existsSync(file1Path)) {
        return this.skip();
      }
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      assert.isTrue(isSemFormat(sem));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) =>
        /bring\s*\{/.test(l)
      );
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const cases: { label: string; character: number }[] = [
        {
          label: "x",
          character: line.indexOf("x", line.indexOf("{")),
        },
        {
          label: "callS",
          character: line.indexOf("callS"),
        },
        {
          label: "A",
          character: line.indexOf(",A,") + 1,
        },
        {
          label: "T",
          character: line.indexOf(",T,") + 1,
        },
        {
          label: "TB",
          character: line.indexOf("TB"),
        },
      ];
      for (const { label, character } of cases) {
        assert.isAtLeast(character, 0, `column for ${label}`);
        const loc = getBringListDeclarationLocation(
          sem,
          doc.uri,
          { line: lineIdx, character },
          content
        );
        assert.isNotNull(loc, `definition for ${label} in bring list`);
        assert.equal(
          path.normalize(fileURLToPath(loc!.uri)),
          path.normalize(file1Path),
          `${label} should resolve to file1.fg`
        );
      }
    });

    it("hover: choosy bring {…} from — shows types/signatures for vars, fun, class, expose types", async function () {
      this.timeout(45000);
      const taskRel = path.join(
        "BringTests",
        "BringTestBasicTestAllChoosy",
        "task.fg"
      );
      const filePath = path.join(FIXTURES, taskRel);
      const file1Path = path.join(path.dirname(filePath), "file1.fg");
      if (!fs.existsSync(filePath) || !fs.existsSync(file1Path)) {
        return this.skip();
      }
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      assert.isTrue(isSemFormat(sem));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => /bring\s*\{/.test(l));
      assert.isAtLeast(lineIdx, 0);
      const line = lines[lineIdx];
      const cases: { label: string; character: number; mustInclude: string[] }[] = [
        {
          label: "x",
          character: line.indexOf("x", line.indexOf("{")),
          mustInclude: ["**x**", "int"],
        },
        {
          label: "callS",
          character: line.indexOf("callS"),
          mustInclude: ["**callS**", "callS(", "nthg"],
        },
        {
          label: "A",
          character: line.indexOf(",A,") + 1,
          mustInclude: ["**A**", "class", "A"],
        },
        {
          label: "T",
          character: line.indexOf(",T,") + 1,
          mustInclude: ["**T**", "Type:", "`"],
        },
        {
          label: "TB",
          character: line.indexOf("TB"),
          mustInclude: ["**TB**", "Type:", "`"],
        },
      ];
      for (const { label, character, mustInclude } of cases) {
        assert.isAtLeast(character, 0, `column for ${label}`);
        const hover = getHoverFromSem(
          sem,
          { line: lineIdx, character },
          label,
          undefined,
          content
        );
        assert.isNotNull(hover, `hover for ${label} in bring list`);
        for (const frag of mustInclude) {
          assert.include(
            hover!.value,
            frag,
            `${label}: expected hover to mention ${frag}`
          );
        }
      }
    });

    it("go-to-definition: use of brought variable jumps to declaration in lib file", async function () {
      this.timeout(45000);
      const filePath = path.join(FIXTURES, rel);
      if (!fs.existsSync(filePath)) return this.skip();
      const libPath = path.join(path.dirname(filePath), "bring_ok_lib.fg");
      assert.isTrue(fs.existsSync(libPath), "bring_ok_lib.fg must exist");
      const content = fs.readFileSync(filePath, "utf-8");
      const doc = TextDocument.create(
        pathToFileUri(filePath),
        "flowwing",
        0,
        content
      );
      const semPath = await getSemPathForDocument(doc);
      assert.isNotNull(semPath);
      const sem = JSON.parse(await fileUtils.readFile(semPath!));
      const lines = content.split("\n");
      const lineIdx = lines.findIndex((l) => l.includes("println(only_in_this_file)"));
      assert.isAtLeast(lineIdx, 0);
      const col = lines[lineIdx].indexOf("only_in_this_file");
      const sym = getSymbolAtPosition(
        sem,
        { line: lineIdx, character: col + 2 },
        "only_in_this_file"
      );
      assert.isNotNull(sym);
      const loc = getDeclarationForSymbol(sem, sym!.symbolId, doc.uri);
      assert.isNotNull(loc);
      const defFs = fileURLToPath(loc!.uri);
      assert.equal(
        path.normalize(defFs),
        path.normalize(libPath),
        "definition should be in bring_ok_lib.fg, not the importing file"
      );
      assert.isAtLeast(loc!.range.start.line, 0);
    });
  });

  /**
   * When file B imports file A via `bring` and A fails semantic analysis, the compiler
   * reports FileContainsErrors on B at the bring site; validateFile / editor diagnostics
   * should show that on the bring line (same pipeline as validateTextDocument).
   */
  describe("Bring diagnostics: error in imported file surfaces on bring line", () => {
    it("FileContainsErrors: diagnostic on bring statement when sibling lib has errors (temp files)", async function () {
      this.timeout(30000);
      const dir = fs.mkdtempSync(path.join(os.tmpdir(), "fw-lsp-bring-err-"));
      try {
        const badLib = path.join(dir, "bad_lib.fg");
        const mainFg = path.join(dir, "main.fg");
        fs.writeFileSync(badLib, "println(undefined_x)\n", "utf8");
        fs.writeFileSync(mainFg, 'bring "bad_lib.fg"\nprintln(0)\n', "utf8");
        const uri = pathToFileUri(mainFg);
        const result = await validateFile(uri, mainFg);
        assert.isTrue(
          result.hasError,
          "main should fail to compile when brought file has errors"
        );
        assert.exists(result.errorObject);
        assert.include(
          result.errorObject!.message,
          "contains errors",
          "stderr should describe the broken imported file"
        );
        assert.equal(
          result.errorObject!.location.line,
          0,
          "0-based line 0 is the bring line"
        );
        const content = fs.readFileSync(mainFg, "utf8");
        const doc = TextDocument.create(uri, "flowwing", 0, content);
        const diag = createDiagnostic(result.errorObject!, doc);
        assert.equal(diag.range.start.line, 0);
        assert.include(diag.message, "bad_lib");
      } finally {
        fs.rmSync(dir, { recursive: true, force: true });
      }
    });

    it("FileContainsErrors: choosy bring {x} from when sibling lib has errors (temp files)", async function () {
      this.timeout(30000);
      const dir = fs.mkdtempSync(path.join(os.tmpdir(), "fw-lsp-bring-err-choosy-"));
      try {
        const badLib = path.join(dir, "bad_lib.fg");
        const mainFg = path.join(dir, "main.fg");
        fs.writeFileSync(badLib, "println(undefined_x)\n", "utf8");
        fs.writeFileSync(
          mainFg,
          'bring {x} from "bad_lib.fg"\nprintln(0)\n',
          "utf8"
        );
        const uri = pathToFileUri(mainFg);
        const result = await validateFile(uri, mainFg);
        assert.isTrue(result.hasError, "choosy main should fail when lib has errors");
        assert.exists(result.errorObject);
        assert.include(result.errorObject!.message, "contains errors");
        assert.equal(
          result.errorObject!.location.line,
          0,
          "0-based line 0 is the choosy bring line"
        );
        const content = fs.readFileSync(mainFg, "utf8");
        const doc = TextDocument.create(uri, "flowwing", 0, content);
        const diag = createDiagnostic(result.errorObject!, doc);
        assert.equal(diag.range.start.line, 0);
        assert.include(diag.message, "bad_lib");
      } finally {
        fs.rmSync(dir, { recursive: true, force: true });
      }
    });

    it("FileContainsErrors: LatestTests fixture maps error to bring line (plain bring \"lib.fg\")", async function () {
      this.timeout(30000);
      const mainPath = path.join(
        FIXTURES,
        "BringTests",
        "11_errors",
        "bring_file_has_errors.fg"
      );
      if (!fs.existsSync(mainPath)) return this.skip();
      const uri = pathToFileUri(mainPath);
      const result = await validateFile(uri, mainPath);
      assert.isTrue(result.hasError);
      assert.exists(result.errorObject);
      assert.include(result.errorObject!.message, "contains errors");
      assert.equal(
        result.errorObject!.location.line,
        1,
        "line 0 is /; EXPECT_ERROR comment; line 1 is bring"
      );
      const content = fs.readFileSync(mainPath, "utf8");
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const diag = createDiagnostic(result.errorObject!, doc);
      assert.equal(diag.range.start.line, 1);
      assert.include(diag.message, "broken_lib");
    });

    it("FileContainsErrors: LatestTests choosy bring {…} from maps error to bring line", async function () {
      this.timeout(30000);
      const mainPath = path.join(
        FIXTURES,
        "BringTests",
        "11_errors",
        "bring_choosy_file_has_errors.fg"
      );
      if (!fs.existsSync(mainPath)) return this.skip();
      const uri = pathToFileUri(mainPath);
      const result = await validateFile(uri, mainPath);
      assert.isTrue(result.hasError);
      assert.exists(result.errorObject);
      assert.include(
        result.errorObject!.message,
        "contains errors",
        "message should indicate the imported file has errors (exact nested diagnostics are not inlined)"
      );
      assert.equal(
        result.errorObject!.location.line,
        1,
        "line 0 is /; EXPECT_ERROR comment; line 1 is choosy bring"
      );
      const content = fs.readFileSync(mainPath, "utf8");
      const doc = TextDocument.create(uri, "flowwing", 0, content);
      const diag = createDiagnostic(result.errorObject!, doc);
      assert.equal(diag.range.start.line, 1);
      assert.include(diag.message, "broken_lib");
    });
  });
});
