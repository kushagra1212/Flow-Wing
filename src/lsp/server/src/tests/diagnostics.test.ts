/**
 * Tests for diagnostics - error parsing and diagnostic creation
 */

import { assert } from "chai";
import { parseErrorAndExtractLocation } from "../utils";
import { createDiagnostic } from "../services/diagnosticService";
import { TextDocument } from "vscode-languageserver-textdocument";

describe("diagnostics", () => {
  describe("parseErrorAndExtractLocation", () => {
    it("parses FunctionArgumentCountMismatch error from compiler stderr", () => {
      const stderr = `[Error:FunctionArgumentCountMismatch] : Line 4:8 "The function 'funName(Function: <(int, deci) -> int>)' expects at least 2 arguments, but only 0 were provided."`;
      const result = parseErrorAndExtractLocation(stderr);

      assert.isTrue(result.hasError);
      assert.equal(result.lineNumber, 4); // 0-based (compiler uses 0-based)
      assert.equal(result.columnNumber, 8);
      assert.include(result.errorMessage!, "expects at least 2 arguments");
      assert.exists(result.errorObject);
    });

    it("parses error with ANSI color codes (deColorize)", () => {
      const stderr = `\x1b[1m[Error:VariableNotFound]\x1b[0m : Line 1:0 "Variable 'x' does not exist."`;
      const result = parseErrorAndExtractLocation(stderr);

      assert.isTrue(result.hasError);
      assert.equal(result.lineNumber, 1); // 0-based
      assert.equal(result.columnNumber, 0);
      assert.include(result.errorMessage!, "does not exist");
    });

    it("returns hasError false when no match", () => {
      const result = parseErrorAndExtractLocation("some other output");
      assert.isFalse(result.hasError);
    });
  });

  describe("createDiagnostic", () => {
    it("creates diagnostic with correct range for FunctionArgumentCountMismatch", () => {
      const errorResult = parseErrorAndExtractLocation(
        `[Error:FunctionArgumentCountMismatch] : Line 4:8 "The function expects 2 arguments."`
      );
      if (!errorResult.errorObject) {
        assert.fail("expected errorObject");
        return;
      }

      const doc = TextDocument.create(
        "file:///test.fg",
        "flowwing",
        1,
        "fun funName(a:int, b:deci) -> int {\n    return 2\n}\n\nprintln(funName())"
      );
      const diagnostic = createDiagnostic(errorResult.errorObject, doc);

      assert.equal(diagnostic.severity, 1); // Error
      assert.equal(diagnostic.range.start.line, 4); // 0-based (compiler uses 0-based)
      assert.equal(diagnostic.range.start.character, 8);
      assert.include(diagnostic.message, "expects");
    });
  });
});
