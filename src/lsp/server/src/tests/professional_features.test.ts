import { assert } from "chai";
import * as path from "path";
import * as fs from "fs";
import { flowWingConfig } from "../config";
import { TextDocument } from "vscode-languageserver-textdocument";
import { getTokensForContext } from "../services/suggestionService";
import { getSemPathForDocument } from "../services/documentService";
import { getHoverFromSem, getCompletionItemsFromSem } from "../services/semService";
import { checkForObjectSuggestions } from "../utils";
import { fileUtils } from "../utils/fileUtils";
import { getTestCompilerPath, getTestFixturesDir } from "./testCompilerPath";

describe("Professional Feature Tests (LatestTests)", () => {
  const compilerPath = getTestCompilerPath();
  const fixturesDir = getTestFixturesDir();

  before(async () => {
    flowWingConfig.flowWingPath = compilerPath;
  });

  describe("Object Suggestions", () => {
    it("should suggest values after a colon in an object literal: {a:}", async () => {
      const content = `
type User = {
    name: str
    age: int
}
var u: User = { name: 
`;
      const position = { line: 5, character: 22 }; // After 'name: '
      const document = TextDocument.create("file:///test_obj_sug.fg", "flowwing", 0, content);

      const tokens = await getTokensForContext(document, position);
      const suggestion = checkForObjectSuggestions(tokens);

      assert.isTrue(suggestion.hasObjectSuggestions, "Should have object suggestions");
      assert.equal(suggestion.word, "name", "Word should be 'name'");
      assert.isTrue(suggestion.data?.isValueCompletion, "Should be value completion after colon");
    });
  });

  describe("Fixture-based Coverage", () => {
    // Array Tests
    it("should handle ArrayTests correctly", async () => {
        const filePath = path.join(fixturesDir, "ArrayTests", "basic.fg");
        if (!fs.existsSync(filePath)) return;
        const content = fs.readFileSync(filePath, "utf-8");
        const document = TextDocument.create("file:///test_array.fg", "flowwing", 0, content);
        const semPath = await getSemPathForDocument(document, { position: { line: 0, character: 0 } });
        assert.isNotNull(semPath, "Should generate SEM for ArrayTests/basic.fg");
    });

    // Object Tests
    it("should handle ObjectTests correctly", async () => {
        const filePath = path.join(fixturesDir, "ObjectTests", "declaration", "all_types.fg");
        if (!fs.existsSync(filePath)) return;
        const content = fs.readFileSync(filePath, "utf-8");
        const document = TextDocument.create("file:///test_all_types.fg", "flowwing", 0, content);
        const semPath = await getSemPathForDocument(document, { position: { line: 0, character: 0 } });
        assert.isNotNull(semPath, "Should generate SEM for ObjectTests/all_types.fg");
    });

    // Nested / Container Tests
    it("should handle ContainerTests correctly", async () => {
        const filePath = path.join(fixturesDir, "ContainerTests", "array_double_nested_padding.fg");
        if (!fs.existsSync(filePath)) return;
        const content = fs.readFileSync(filePath, "utf-8");
        const document = TextDocument.create("file:///test_nested.fg", "flowwing", 0, content);
        const semPath = await getSemPathForDocument(document, { position: { line: 0, character: 0 } });
        assert.isNotNull(semPath, "Should generate SEM for ContainerTests");
    });
  });
});
