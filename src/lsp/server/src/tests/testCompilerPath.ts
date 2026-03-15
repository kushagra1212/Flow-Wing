import * as path from "path";
import * as fs from "fs";

/**
 * Repo root when tests run via "yarn test" from src/lsp (cwd is src/lsp/server).
 */
export function getTestRepoRoot(): string {
  return path.resolve(process.cwd(), "..", "..", "..");
}

/**
 * Resolves the FlowWing compiler path for LSP tests.
 * - Uses FLOWWING_COMPILER_PATH if set (CI or local override).
 * - Otherwise resolves repo-relative build/sdk/bin/FlowWing from cwd.
 * This makes tests pass on CI (Linux/macOS/Windows) and locally without hardcoding /Users/... paths.
 */
export function getTestCompilerPath(): string {
  const fromEnv = process.env.FLOWWING_COMPILER_PATH;
  if (fromEnv && fromEnv.length > 0) {
    return fromEnv;
  }
  const repoRoot = getTestRepoRoot();
  const exe = process.platform === "win32" ? "FlowWing.exe" : "FlowWing";
  return path.join(repoRoot, "build", "sdk", "bin", exe);
}

/**
 * Path to tests/fixtures/LatestTests (repo-relative).
 */
export function getTestFixturesDir(): string {
  return path.join(getTestRepoRoot(), "tests", "fixtures", "LatestTests");
}

/**
 * Returns the compiler path for tests if the binary exists, otherwise the path anyway
 * (callers can check existence if needed).
 */
export function getTestCompilerPathOrSkip(): string {
  const p = getTestCompilerPath();
  if (!fs.existsSync(p)) {
    throw new Error(
      `FlowWing compiler not found at ${p}. Build the project (e.g. make test-aot) or set FLOWWING_COMPILER_PATH.`
    );
  }
  return p;
}
