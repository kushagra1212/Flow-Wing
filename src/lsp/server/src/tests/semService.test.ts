/**
 * Tests for semService - completion, hover, definitions, signature help
 */

import * as path from "path";
import * as fs from "fs";
import { assert } from "chai";
import {
  getCompletionItemsFromSem,
  getHoverFromSem,
  getSymbolAtPosition,
  getDeclarationForSymbol,
  getSignatureHelpFromSem,
  isSemFormat,
} from "../services/semService";
import { Position } from "vscode-languageserver";

// Fixtures are in src/tests/fixtures; at runtime __dirname is out/tests
const FIXTURES_DIR = path.join(__dirname, "..", "..", "src", "tests", "fixtures");

function loadFixture(name: string): unknown {
  const p = path.join(FIXTURES_DIR, name);
  const content = fs.readFileSync(p, "utf-8");
  return JSON.parse(content);
}

describe("semService", () => {
  describe("isSemFormat", () => {
    it("returns true for valid sem JSON", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      assert.isTrue(isSemFormat(parsed));
    });

    it("returns false for non-sem JSON", () => {
      assert.isFalse(isSemFormat({}));
      assert.isFalse(isSemFormat({ tree: {} }));
      assert.isFalse(isSemFormat(null));
    });
  });

  describe("getCompletionItemsFromSem", () => {
    it("returns function completions including built-ins and user symbols", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);

      // User-defined from sem
      assert.include(labels, "num", "should include user function num");
      assert.include(labels, "x", "should include user variable x");
      assert.include(labels, "println", "should include built-in println from sem");

      // Built-in functions from store
      assert.include(labels, "print", "should include built-in print");
      assert.include(labels, "println", "should include built-in println");
      assert.include(labels, "input", "should include built-in input");

      // Keywords
      assert.include(labels, "fun", "should include keyword fun");
      assert.include(labels, "var", "should include keyword var");
    });

    it("filters completions by prefix", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "pr",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);
      assert.include(labels, "print");
      assert.include(labels, "println");
      assert.notInclude(labels, "num");
      assert.notInclude(labels, "x");
    });

    it("function items have kind Function and documentation", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "num",
        false,
        "file:///test.fg"
      );

      const numItem = items.find((i) => i.label === "num");
      assert.exists(numItem);
      assert.equal(numItem!.kind, 3); // CompletionItemKind.Function
      assert.exists(numItem!.documentation);
      assert.match(
        (numItem!.documentation as { value?: string }).value ?? "",
        /num/
      );
    });

    it("function autosuggestion: returns print and println when typing 'pr'", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "pr",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);
      assert.include(labels, "print", "typing 'pr' should suggest print");
      assert.include(labels, "println", "typing 'pr' should suggest println");
    });

    it("user-defined function: typing 'funNa' suggests 'funName'", () => {
      const parsed = loadFixture("sem-funName.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "funNa",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);
      assert.include(
        labels,
        "funName",
        "typing 'funNa' should suggest user-defined function funName"
      );
    });

    it("user-defined function: typing 'funNam' suggests 'funName' (similar prefix)", () => {
      const parsed = loadFixture("sem-funName.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "funNam",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);
      assert.include(
        labels,
        "funName",
        "typing 'funNam' should suggest user-defined function funName"
      );
    });

    it("class member method: completion detail omits implicit trailing self parameter", () => {
      const parsed = loadFixture("sem-class-member-method.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "m",
        false,
        "file:///test.fg"
      );
      const mItem = items.find((i) => i.label === "m");
      assert.exists(mItem);
      const doc = (mItem!.documentation as { value?: string }).value ?? "";
      assert.include(doc, "m(x: int)");
      assert.notInclude(doc, "self");
      assert.notInclude(doc, "self: A");
    });

    it("after comma in function call: empty prefix returns completions (funName(1,))", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "",
        false,
        "file:///test.fg"
      );

      const labels = items.map((i) => i.label);
      assert.isAtLeast(items.length, 1, "should return completions when typing after comma");
      assert.include(labels, "println", "should suggest println");
      assert.include(labels, "num", "should suggest user function num");
      assert.include(labels, "x", "should suggest user variable x");
    });

    it("class instance: dot completion lists fields and methods from Class sem type", () => {
      const parsed = {
        sem: {
          tree: {},
          symbols: {
            "0xv": { kind: "Variable", name: "dog", type_id: "0xDog" },
          },
          types: {
            "0xDog": {
              kind: "Class",
              name: "Dog",
              member_fields: [
                { name: "breed", type_id: "0xstr" },
                { name: "age", type_id: "0xint" },
              ],
              methods: [{ name: "getAge", type_id: "0xf" }],
            },
            "0xstr": { kind: "Primitive", name: "str" },
            "0xint": { kind: "Primitive", name: "int" },
            "0xf": {
              kind: "Function",
              name: "",
              parameter_type_ids: [],
              return_type_ids: ["0xint"],
            },
          },
        },
      };
      const items = getCompletionItemsFromSem(
        parsed as Parameters<typeof getCompletionItemsFromSem>[0],
        "dog",
        true,
        "file:///test.fg"
      );
      const labels = items.map((i) => i.label);
      assert.include(labels, "breed");
      assert.include(labels, "age");
      assert.include(labels, "getAge");
    });
  });

  describe("getSymbolAtPosition", () => {
    it("finds symbol at identifier position", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      // Position on "x" in println(x) - line 5, col 8
      const result = getSymbolAtPosition(
        parsed as Parameters<typeof getSymbolAtPosition>[0],
        Position.create(5, 8)
      );

      assert.exists(result);
      assert.equal(result!.symbol.name, "x");
      assert.equal(result!.symbol.kind, "Variable");
    });

    it("finds symbol at call expression (function)", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      // Position inside println( - line 5, col 7
      const result = getSymbolAtPosition(
        parsed as Parameters<typeof getSymbolAtPosition>[0],
        Position.create(5, 7)
      );

      assert.exists(result);
      assert.equal(result!.symbol.name, "println");
      assert.equal(result!.symbol.kind, "Function");
    });
  });

  describe("getHoverFromSem", () => {
    it("resolves hover type for class member path (dog.age)", () => {
      const parsed = {
        sem: {
          tree: {},
          symbols: {
            "0xv": { kind: "Variable", name: "dog", type_id: "0xDog" },
          },
          types: {
            "0xDog": {
              kind: "Class",
              name: "Dog",
              member_fields: [{ name: "age", type_id: "0xint" }],
              methods: [],
            },
            "0xint": { kind: "Primitive", name: "int" },
          },
        },
      };
      const hover = getHoverFromSem(
        parsed as Parameters<typeof getHoverFromSem>[0],
        Position.create(0, 0),
        undefined,
        "dog.age"
      );
      assert.exists(hover);
      assert.include((hover as { value: string }).value, "int");
    });

    it("returns hover for variable", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const hover = getHoverFromSem(
        parsed as Parameters<typeof getHoverFromSem>[0],
        Position.create(5, 8)
      );

      assert.exists(hover);
      assert.match(hover!.value, /x/);
      assert.match(hover!.value, /dynamic/);
    });

    it("returns hover for function with signature", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const hover = getHoverFromSem(
        parsed as Parameters<typeof getHoverFromSem>[0],
        Position.create(5, 2)
      );

      assert.exists(hover);
      assert.match(hover!.value, /println/);
    });

    it("returns hover for function in nested call (e.g. println(funName(...)))", () => {
      const parsed = loadFixture("sem-funName-call.json");
      // Position on "funName" in println(funName(1,)) - line 4, col 8-14
      const hover = getHoverFromSem(
        parsed as Parameters<typeof getHoverFromSem>[0],
        Position.create(4, 10)
      );

      assert.exists(hover);
      assert.match(hover!.value, /funName/);
      assert.match(hover!.value, /int.*deci/);
    });
  });

  describe("getDeclarationForSymbol", () => {
    it("returns declaration location for function", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const loc = getDeclarationForSymbol(
        parsed as Parameters<typeof getDeclarationForSymbol>[0],
        "0x4",
        "file:///test.fg"
      );

      assert.exists(loc);
      assert.equal(loc!.uri, "file:///test.fg");
      assert.exists(loc!.range);
    });
  });

  describe("getSignatureHelpFromSem", () => {
    it("returns signature help for function call", () => {
      const parsed = loadFixture("sem-dynamic-printed.json");
      const sigHelp = getSignatureHelpFromSem(
        parsed as Parameters<typeof getSignatureHelpFromSem>[0],
        Position.create(5, 7),
        0
      );

      assert.exists(sigHelp);
      assert.isAtLeast(sigHelp!.signatures.length, 1);
      assert.match(sigHelp!.signatures[0].label, /println/);
    });

    it("returns signature help with active param when cursor is after comma (funName(1,))", () => {
      const parsed = loadFixture("sem-funName-call.json");
      // Position (4, 17) is after comma in funName(1,) - second argument
      const sigHelp = getSignatureHelpFromSem(
        parsed as Parameters<typeof getSignatureHelpFromSem>[0],
        Position.create(4, 17),
        1
      );

      assert.exists(sigHelp);
      assert.isAtLeast(sigHelp!.signatures.length, 1);
      assert.match(sigHelp!.signatures[0].label, /funName/);
      assert.match(sigHelp!.signatures[0].label, /a.*int/);
      assert.match(sigHelp!.signatures[0].label, /b.*deci/);
      assert.equal(sigHelp!.activeParameter, 1, "should highlight second param (b: deci)");
    });
  });
});
