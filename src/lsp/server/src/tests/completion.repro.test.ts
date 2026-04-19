/**
 * Tests for utils - filterCompletionItemsByPrefix, checkForFunctionSignatures, makeCodeCompleteForLsp
 */

import { assert } from "chai";
import {
  filterCompletionItemsByPrefix,
  checkForFunctionSignatures,
  makeCodeCompleteForLsp,
  getDefinedSymbolsFromContent,
  getIdentifierAtPosition,
  tryRepairContentForSem,
  tryRepairCallForSem,
} from "../utils";
import { CompletionItem } from "vscode-languageserver";
import { Token } from "../types";

function tok(v: string, line = 0, col = 0): Token {
  return { value: v, lineNumber: line, columnNumber: col };
}

describe("checkForFunctionSignatures", () => {
  it("returns hasFunctionSignature when cursor is after comma in funName(1,)", () => {
    // Tokens for: funName(1,|) where | is cursor
    const tokens = [
      tok("funName", 4, 8),
      tok("(", 4, 15),
      tok("1", 4, 16),
      tok(",", 4, 17),
    ];
    const result = checkForFunctionSignatures(tokens);

    assert.isTrue(result.hasFunctionSignature);
    assert.equal(result.data?.argumentNumber, 2);
    assert.equal(result.data?.argumentPrefix, "");
    assert.equal(result.word, "funName");
  });

  it("returns argumentPrefix when typing after comma: funName(1,2.)", () => {
    const tokens = [
      tok("funName", 4, 8),
      tok("(", 4, 15),
      tok("1", 4, 16),
      tok(",", 4, 17),
      tok("2", 4, 18),
      tok(".", 4, 19),
    ];
    const result = checkForFunctionSignatures(tokens);

    assert.isTrue(result.hasFunctionSignature);
    assert.equal(result.data?.argumentNumber, 2);
    assert.equal(result.data?.argumentPrefix, "2.");
  });

  it("returns hasFunctionSignature when cursor is right after opening paren (funName()", () => {
    const tokens = [tok("funName", 4, 8), tok("(", 4, 15)];
    const result = checkForFunctionSignatures(tokens);

    assert.isTrue(result.hasFunctionSignature);
    assert.equal(result.data?.argumentNumber, 1);
    assert.equal(result.data?.argumentPrefix, "");
    assert.equal(result.word, "funName");
  });

  it("returns argumentPrefix for first arg when typing identifier: println(funNa)", () => {
    const tokens = [tok("println", 4, 0), tok("(", 4, 7), tok("funNa", 4, 8)];
    const result = checkForFunctionSignatures(tokens);

    assert.isTrue(result.hasFunctionSignature);
    assert.equal(result.data?.argumentNumber, 1);
    assert.equal(result.data?.argumentPrefix, "funNa");
    assert.equal(result.word, "println");
  });

  it("returns argumentPrefix for first arg when typing identifier: println(funNam)", () => {
    const tokens = [tok("println", 4, 0), tok("(", 4, 7), tok("funNam", 4, 8)];
    const result = checkForFunctionSignatures(tokens);

    assert.isTrue(result.hasFunctionSignature);
    assert.equal(result.data?.argumentNumber, 1);
    assert.equal(result.data?.argumentPrefix, "funNam");
    assert.equal(result.word, "println");
  });
});

describe("makeCodeCompleteForLsp", () => {
  it("closes unclosed paren: funName( -> funName()", () => {
    assert.equal(makeCodeCompleteForLsp("funName("), "funName()");
  });

  it("adds placeholder when ending with comma: funName(1, -> funName(1,0)", () => {
    assert.equal(makeCodeCompleteForLsp("funName(1,"), "funName(1,0)");
  });

  it("returns content unchanged when already complete", () => {
    assert.equal(makeCodeCompleteForLsp("funName()"), "funName()");
    assert.equal(makeCodeCompleteForLsp("funName(1,2)"), "funName(1,2)");
  });
});

describe("getIdentifierAtPosition", () => {
  it("extracts partial identifier at cursor: println(funNa|)", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNa)`;
    const id = getIdentifierAtPosition(content, { line: 4, character: 13 });
    assert.equal(id, "funNa");
  });

  it("extracts partial identifier at cursor: println(funNam|)", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNam)`;
    const id = getIdentifierAtPosition(content, { line: 4, character: 14 });
    assert.equal(id, "funNam");
  });

  it("returns empty when cursor is not on identifier", () => {
    const content = "()";
    assert.equal(getIdentifierAtPosition(content, { line: 0, character: 1 }), "");
  });
});

describe("getDefinedSymbolsFromContent", () => {
  it("extracts function names from fun declarations", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNa)`;
    assert.include(getDefinedSymbolsFromContent(content), "funName");
  });
});

describe("tryRepairContentForSem", () => {
  it("replaces partial identifier with defined symbol: funNa -> funName", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNa)`;
    // Position at end of "funNa" (line 4, char 13)
    const repaired = tryRepairContentForSem(content, "funNa", {
      line: 4,
      character: 13,
    });
    assert.exists(repaired);
    assert.include(repaired!, "println(funName)");
  });

  it("replaces partial identifier with defined symbol: funNam -> funName", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNam)`;
    const repaired = tryRepairContentForSem(content, "funNam", {
      line: 4,
      character: 14,
    });
    assert.exists(repaired);
    assert.include(repaired!, "println(funName)");
  });
});

describe("tryRepairCallForSem", () => {
  it("repairs funName() to funName(0, 0.0) when fun expects (a:int, b:deci)", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funName())`;
    const repaired = tryRepairCallForSem(content);
    assert.exists(repaired);
    assert.include(repaired!, "funName(0, 0.0)");
  });

  it("repairs println(funName) to println(funName(0, 0.0)) when funName expects (a:int, b:deci)", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funName)`;
    const repaired = tryRepairCallForSem(content);
    assert.exists(repaired);
    assert.include(repaired!, "funName(0, 0.0)");
  });
});

describe("tryRepairContentForSem + tryRepairCallForSem combo", () => {
  it("println(funNam) -> println(funName(0, 0.0)) for autocomplete when fun expects (a:int, b:deci)", () => {
    const content = `fun funName(a:int, b:deci) -> int {
    return 2
}

println(funNam)`;
    const step1 = tryRepairContentForSem(content, "funNam", {
      line: 4,
      character: 14, // after "funNam" in println(funNam)
    });
    assert.exists(step1);
    assert.include(step1!, "println(funName)");
    const step2 = tryRepairCallForSem(step1!);
    assert.exists(step2);
    assert.include(step2!, "funName(0, 0.0)");
  });
});

describe("filterCompletionItemsByPrefix", () => {
  const items: CompletionItem[] = [
    { label: "funName" },
    { label: "fun" },
    { label: "print" },
    { label: "println" },
  ];

  it("filters items by prefix (typing 'funNa' suggests 'funName')", () => {
    const filtered = filterCompletionItemsByPrefix(items, "funNa");
    const labels = filtered.map((i) => i.label);
    assert.include(labels, "funName");
    assert.notInclude(labels, "print");
    assert.notInclude(labels, "println");
  });

  it("filters items by prefix (typing 'funNam' suggests 'funName')", () => {
    const filtered = filterCompletionItemsByPrefix(items, "funNam");
    const labels = filtered.map((i) => i.label);
    assert.include(labels, "funName");
  });

  it("returns all items when prefix is empty", () => {
    const filtered = filterCompletionItemsByPrefix(items, "");
    assert.lengthOf(filtered, 4);
  });

  it("is case-insensitive", () => {
    const filtered = filterCompletionItemsByPrefix(items, "FUNNA");
    assert.include(filtered.map((i) => i.label), "funName");
  });
});
