import { assert } from "chai";
import * as path from "path";
import * as fs from "fs";
import * as os from "os";
import { 
  getSemPathForFile, 
  getAstPathForFile,
  runCompilerWithEmit,
  clearDocumentCache
} from "../services/documentService";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { getTestCompilerPath } from "./testCompilerPath";

describe("LSP Robustness and Caching", () => {
  const compilerPath = getTestCompilerPath();
  const testUri = "file:///Users/apple/code/per/Flow-Wing/src/lsp/server/src/tests/robustness_test.fg";

  before(async () => {
    flowWingConfig.flowWingPath = compilerPath;
  });

  beforeEach(() => {
    clearDocumentCache();
  });

  const validCode = `
fun validFunc() -> int {
    return 1
}
`;
  // Junk code that should fail even the parser (no AST emitted)
  const junkCode = `!!! JUNK !!! (((`;

  it("getSemPathForFile caches successful results and falls back on failure", async () => {
    const uniqueUri = `${testUri}_${Date.now()}_sem`;
    
    // 1. First run with valid code to prime the cache
    const firstPath = await getSemPathForFile(uniqueUri, validCode);
    assert.isNotNull(firstPath, "First run with valid code should return a path");

    // 2. Second run with failure (temporarily invalidating compiler path)
    const originalPath = flowWingConfig.flowWingPath;
    flowWingConfig.flowWingPath = "/tmp/invalid_compiler_path";
    try {
      const secondPath = await getSemPathForFile(uniqueUri, junkCode);
      assert.isNotNull(secondPath, "Should return cached path on failure");
      assert.equal(secondPath, firstPath, "Secondary path should be identical to cached path");
    } finally {
      flowWingConfig.flowWingPath = originalPath;
    }
  });

  it("getAstPathForFile caches successful results and falls back on failure", async () => {
    const uniqueUri = `${testUri}_${Date.now()}_ast`;
    
    // 1. First run with valid code to prime the cache
    const firstPath = await getAstPathForFile(uniqueUri, validCode);
    assert.isNotNull(firstPath, "First run with valid code should return a path");

    // 2. Second run with failure
    const originalPath = flowWingConfig.flowWingPath;
    flowWingConfig.flowWingPath = "/tmp/invalid_compiler_path";
    try {
      const secondPath = await getAstPathForFile(uniqueUri, junkCode);
      assert.isNotNull(secondPath, "Should return cached path on failure");
      assert.equal(secondPath, firstPath, "Secondary path should be identical to cached path");
    } finally {
      flowWingConfig.flowWingPath = originalPath;
    }
  });

  it("runCompilerWithEmit resolves even if compiler returns non-zero code but outputs file (Resilience)", async function() {
    // We use a code that has a semantic error.
    // The compiler will exit with 1 because of the semantic error.
    // However, it will still emit the AST before the semantic pass fails.
    const semanticErrorCode = `
fun test() -> int {
    return "string"
}
`;
    const outputDir = path.join(os.tmpdir(), `flowwing-lsp-test-resilience-${Date.now()}`);
    const tempPath = await fileUtils.createTempFile({
      fileName: "resilience.fg",
      data: semanticErrorCode,
    });

    try {
      // Use "ast" because we know it's emitted even if semantic analysis fails
      const astPath = await runCompilerWithEmit(tempPath, "ast", outputDir);
      assert.isNotNull(astPath, "Should return path for AST even if semantic analysis fails later");
      assert.isTrue(fs.existsSync(astPath), "Output file should exist despite non-zero exit code due to late failures");
    } catch (err) {
      assert.fail(`runCompilerWithEmit should not have thrown if file was emitted. Error: ${err}`);
    }
  });
});
