import { Position } from "vscode-languageserver";
import { TextDocument } from "vscode-languageserver-textdocument";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { ErrorResult } from "../utils/types";
import {
  getFileFullPath,
  makeCodeCompleteForLsp,
  parseErrorAndExtractLocation,
  tryRepairCallForSem,
  tryRepairContentForSem,
  tryRepairDotForSem,
} from "../utils";
import { createDiagnostic } from "./diagnosticService";
import { logger } from "./loggerService";
import { _Connection } from "vscode-languageserver";
import { execFile } from "child_process";
import { randomBytes } from "crypto";
import { promises as fs } from "fs";
import * as path from "path";
import * as os from "os";

const semCache = new Map<string, string>();
const astCache = new Map<string, string>();

/** Clears all internal caches (used for testing and cache invalidation). */
export const clearDocumentCache = () => {
  semCache.clear();
  astCache.clear();
};

export const validateTextDocument = async (
  textDocument: TextDocument,
  connection: _Connection | null = null
): Promise<void> => {
  if (!textDocument) return;

  try {
    const text = textDocument.getText();
    const tempPath = await fileUtils.createTempFile({
      fileName: getFileFullPath(textDocument.uri) + ".fg",
      data: text,
    });

    const result = await validateFile(textDocument.uri, tempPath);

    const diagnostics =
      result.errorObject?.error && result.errorObject
        ? [createDiagnostic(result.errorObject, textDocument)]
        : [];

    if (connection) {
      connection.sendDiagnostics({
        uri: textDocument.uri,
        diagnostics,
      });
    }
  } catch (err) {
    connection?.console?.error?.(
      `FlowWing LSP: validateTextDocument failed: ${err}`
    );
  }
};

export const doesFlowWingCompilerExist = async (): Promise<boolean> => {
  return new Promise((resolve, reject) => {
    execFile(
      flowWingConfig.flowWingPath,
      ["--version"],
      (error, stdout, stderr) => {
        if (error || stderr) {
          console.error(`Compilation error: ${error.message}`);
          return resolve(false);
        }
        resolve(true);
      }
    );
  });
};

/** Emit types supported by the compiler. */
export type EmitType = "tokens" | "ast" | "sem";

const EMIT_OUTPUT_FILES: Record<EmitType, string> = {
  tokens: "tokens.json",
  ast: "ast.json",
  sem: "semantic_tree.json",
};

/**
 * Runs the FlowWing compiler with --emit and --output-dir.
 * Returns the path to the output file.
 */
export const runCompilerWithEmit = async (
  filePath: string,
  emit: EmitType,
  outputDir: string
): Promise<string> => {
  // Don't gate on doesFlowWingExist - it may be false due to async init race.
  // Let the compiler run; it will reject with ENOENT if not found.
  await fs.mkdir(outputDir, { recursive: true });

  const outputFile = EMIT_OUTPUT_FILES[emit];
  const args = [
    `--file=${filePath}`,
    `--emit=${emit}`,
    `--output-dir=${outputDir}`,
  ];

  return new Promise((resolve, reject) => {
    const childProcess = execFile(
      flowWingConfig.flowWingPath,
      args,
      async (error, stdout, stdErr) => {
        const outputPath = path.join(outputDir, outputFile);
        if (error) {
          // If the compiler generated an output file despite the error (e.g. semantic errors),
          // we prefer to use it rather than failing completely.
          try {
            await fs.access(outputPath);
            resolve(outputPath);
            return;
          } catch {
            reject(error);
            return;
          }
        }
        resolve(outputPath);
      }
    );

    childProcess.on("error", reject);

    const timeout = setTimeout(() => {
      if (!childProcess.killed) {
        childProcess.kill("SIGTERM");
        reject(new Error("Compiler timeout"));
      }
    }, 15000);

    childProcess.on("exit", () => clearTimeout(timeout));
  });
};

/**
 * Runs the compiler with --emit=sem and returns the path to semantic_tree.json.
 * Prefer sem over ast for better type info and symbols. Falls back to ast if sem fails.
 */
export const getSemPathForDocument = async (
  document: TextDocument,
  options?: { position?: { line: number; character: number }; partialId?: string }
): Promise<string | null> => {
  return getSemPathForFile(document.uri, document.getText(), options);
};

/** Internal helper to generate repair candidates for semantic/AST analysis. */
const getRepairCandidates = (
  content: string,
  options?: { position?: Position; partialId?: string }
): string[] => {
  const candidates: string[] = [content];
  const completed = makeCodeCompleteForLsp(content);
  candidates.push(completed);

  if (options?.position) {
    // Truncation repair: removes trailing garbage/errors after cursor
    const lines = content.split("\n");
    const prefixLines = lines.slice(0, options.position.line);
    const lastLinePrefix = lines[options.position.line]?.slice(0, options.position.character) ?? "";
    const truncatedContent = [...prefixLines, lastLinePrefix].join("\n");
    candidates.push(makeCodeCompleteForLsp(truncatedContent));

    // Dot repair
    const dotRepaired = tryRepairDotForSem(content, options.position);
    if (dotRepaired) {
      candidates.push(dotRepaired);
      candidates.push(makeCodeCompleteForLsp(dotRepaired));
    }
  }

  if (options?.position && options?.partialId) {
    const repaired = tryRepairContentForSem(content, options.partialId, options.position);
    if (repaired) candidates.push(makeCodeCompleteForLsp(repaired));
  }

  const callRepaired = tryRepairCallForSem(content);
  if (callRepaired) candidates.push(makeCodeCompleteForLsp(callRepaired));

  const callRepairedFromCompleted = tryRepairCallForSem(completed);
  if (callRepairedFromCompleted && callRepairedFromCompleted !== completed) {
    candidates.push(callRepairedFromCompleted);
  }

  return Array.from(new Set(candidates)); // Unique candidates
};

/** Gets SEM path without identifier repair (for object_value, object_member). */
export const getSemPathForFileNoRepair = async (
  uriOrBasename: string,
  content: string,
  options?: { position?: Position }
): Promise<string | null> => {
  const basename = uriOrBasename.includes("file:")
    ? getFileFullPath(uriOrBasename)
    : uriOrBasename.replace(/[^a-zA-Z0-9_-]/g, "_");
  const outputDir = path.join(
    os.tmpdir(),
    `flowwing-lsp-sem-${Date.now()}-${randomBytes(4).toString("hex")}`
  );

  const contentHash = content.length + "_" + content.slice(-20);
  const contentCacheKey = uriOrBasename + "@" + contentHash + "_sem_norepair";
  const uriCacheKey = uriOrBasename + "_sem_norepair";

  // 1. Try content-specific cache first
  const cachedContent = semCache.get(contentCacheKey);
  if (cachedContent) return cachedContent;

  const candidates = getRepairCandidates(content, options);

  for (const data of candidates) {
    try {
      const tempPath = await fileUtils.createTempFile({
        fileName: basename + ".fg",
        data,
      });
      const result = await runCompilerWithEmit(tempPath, "sem", outputDir);
      if (result) {
        semCache.set(contentCacheKey, result);
        semCache.set(uriCacheKey, result);
        return result;
      }
    } catch {
      continue;
    }
  }

  // 3. Fallback to latest successful result
  return semCache.get(uriCacheKey) || null;
};

export const getSemPathForFile = async (
  uriOrBasename: string,
  content: string,
  options?: { position?: Position; partialId?: string }
): Promise<string | null> => {
  const basename = uriOrBasename.includes("file:")
    ? getFileFullPath(uriOrBasename)
    : uriOrBasename.replace(/[^a-zA-Z0-9_-]/g, "_");
  const outputDir = path.join(os.tmpdir(), `flowwing-lsp-sem-${Date.now()}-${randomBytes(4).toString("hex")}`);

  const candidates = getRepairCandidates(content, options);

  const contentHash = content.length + "_" + content.slice(-20); // Simple hash-like key
  const contentCacheKey = uriOrBasename + "@" + contentHash;
  const uriCacheKey = uriOrBasename;

  // 1. Try content-specific cache first
  const cachedContent = semCache.get(contentCacheKey);
  if (cachedContent) {
    logger.debug("document", "getSemPath", "content cache hit", contentCacheKey);
    return cachedContent;
  }

  // 2. Try compiling candidates
  for (const data of candidates) {
    try {
      const tempPath = await fileUtils.createTempFile({
        fileName: basename + ".fg",
        data,
      });
      const result = await runCompilerWithEmit(tempPath, "sem", outputDir);
      if (result) {
        semCache.set(contentCacheKey, result);
        semCache.set(uriCacheKey, result); // Also save as latest successful fallback for this URI
        logger.debug("document", "getSemPath", "resolved", result);
        return result;
      }
    } catch (e) {
      logger.trace("document", "getSemPath", "candidate failed", String(e));
      continue;
    }
  }

  // 3. Fallback to latest successful result for this URI if all candidates failed
  const fallback = semCache.get(uriCacheKey);
  if (fallback) {
    logger.debug("document", "getSemPath", "fallback to latest successful", uriCacheKey);
    return fallback;
  }

  return null;
};

/**
 * Runs the compiler with --emit=ast and returns the path to ast.json.
 * Use for completion, hover, signature help, etc.
 */
export const getAstPathForDocument = async (
  document: TextDocument,
  options?: { position?: { line: number; character: number }; partialId?: string }
): Promise<string | null> => {
  return getAstPathForFile(document.uri, document.getText(), options);
};

export const getAstPathForDocumentNoRepair = async (
  document: TextDocument,
  options?: { position?: Position }
): Promise<string | null> => {
  return getAstPathForFileNoRepair(document.uri, document.getText(), options);
};

/** Gets AST path without identifier repair (for object_value, object_member). */
export const getAstPathForFileNoRepair = async (
  uriOrBasename: string,
  content: string,
  options?: { position?: Position }
): Promise<string | null> => {
  const basename = uriOrBasename.includes("file:")
    ? getFileFullPath(uriOrBasename)
    : uriOrBasename.replace(/[^a-zA-Z0-9_-]/g, "_");
  const outputDir = path.join(
    os.tmpdir(),
    `flowwing-lsp-ast-${Date.now()}-${randomBytes(4).toString("hex")}`
  );

  const contentHash = content.length + "_" + content.slice(-20);
  const contentCacheKey = uriOrBasename + "@" + contentHash + "_ast_norepair";
  const uriCacheKey = uriOrBasename + "_ast_norepair";

  // 1. Try content-specific cache first
  const cachedContent = astCache.get(contentCacheKey);
  if (cachedContent) return cachedContent;

  const candidates = getRepairCandidates(content, options);

  for (const data of candidates) {
    try {
      const tempPath = await fileUtils.createTempFile({
        fileName: basename + ".fg",
        data,
      });
      const result = await runCompilerWithEmit(tempPath, "ast", outputDir);
      if (result) {
        astCache.set(contentCacheKey, result);
        astCache.set(uriCacheKey, result);
        return result;
      }
    } catch {
      continue;
    }
  }
  
  // 3. Fallback to latest successful result
  return astCache.get(uriCacheKey) || null;
};

/**
 * Runs the compiler with --emit=ast for file content, returns path to ast.json.
 * Use when the file is not an open document (e.g. imported modules).
 */
export const getAstPathForFile = async (
  uriOrBasename: string,
  content: string,
  options?: { position?: Position; partialId?: string }
): Promise<string | null> => {
  const basename = uriOrBasename.includes("file:")
    ? getFileFullPath(uriOrBasename)
    : uriOrBasename.replace(/[^a-zA-Z0-9_-]/g, "_");
  const outputDir = path.join(os.tmpdir(), `flowwing-lsp-ast-${Date.now()}-${randomBytes(4).toString("hex")}`);

  const contentHash = content.length + "_" + content.slice(-20);
  const contentCacheKey = uriOrBasename + "@" + contentHash;
  const uriCacheKey = uriOrBasename;

  // 1. Try content-specific cache first
  const cachedContent = astCache.get(contentCacheKey);
  if (cachedContent) {
    logger.debug("document", "getAstPath", "content cache hit", contentCacheKey);
    return cachedContent;
  }

  const candidates = getRepairCandidates(content, options);

  for (const data of candidates) {
    try {
      const tempPath = await fileUtils.createTempFile({
        fileName: basename + ".fg",
        data,
      });
      const result = await runCompilerWithEmit(tempPath, "ast", outputDir);
      if (result) {
        astCache.set(contentCacheKey, result);
        astCache.set(uriCacheKey, result); // Also save as latest successful fallback for this URI
        logger.debug("document", "getAstPath", "resolved", result);
        return result;
      }
    } catch (e) {
      logger.trace("document", "getAstPath", "candidate failed", String(e));
      continue;
    }
  }

  // 3. Fallback to latest successful result for this URI if all candidates failed
  const fallback = astCache.get(uriCacheKey);
  if (fallback) {
    logger.debug("document", "getAstPath", "fallback to latest successful", uriCacheKey);
    return fallback;
  }

  return null;
};

/**
 * Runs the FlowWing compiler on a file and parses diagnostics from stderr.
 * Uses the new pipeline-based compiler: --file=<path>
 * Diagnostics are parsed from stderr (format: [Error:Code] : Line X:Y "message")
 * Does not gate on doesFlowWingExist to avoid race with async initialization.
 */
export const validateFile = (
  _textDocUri: string,
  filePath: string
): Promise<Partial<ErrorResult>> => {
  return new Promise((resolve) => {
    const commandArgs = [`--file=${filePath}`];

    const childProcess = execFile(
      flowWingConfig.flowWingPath,
      commandArgs,
      (error, _stdout, stderr) => {
        // Compiler not found or spawn failed: resolve with no diagnostics
        if (error && !stderr) {
          resolve({ hasError: false });
          return;
        }
        if (!stderr || stderr.trim().length === 0) {
          resolve({ hasError: false });
          return;
        }
        const errorResult = parseErrorAndExtractLocation(stderr);
        resolve(errorResult);
      }
    );

    childProcess.on("error", () => {
      // ENOENT etc: compiler not found - resolve with no diagnostics
      resolve({ hasError: false });
    });

    const TIMEOUT_MS = 15000;
    const timeout = setTimeout(() => {
      if (!childProcess.killed) {
        childProcess.kill("SIGTERM");
        resolve({ hasError: false });
      }
    }, TIMEOUT_MS);

    childProcess.on("exit", () => {
      clearTimeout(timeout);
    });
  });
};

const formatFile = (filePath: string): Promise<string> => {
  const commandArgs = [`--file=${filePath}`, `--format`];

  if (!flowWingConfig.doesFlowWingExist) {
    return Promise.reject(new Error("FlowWing not found"));
  }

  return new Promise((resolve, reject) => {
    const childProcess = execFile(
      flowWingConfig.flowWingPath,
      commandArgs,
      (error, stdout, stderr) => {
        if (error) {
          reject(error);
          return;
        }
        if (stderr) {
          reject(new Error(stderr));
          return;
        }
        resolve("ok");
      }
    );

    childProcess.on("error", reject);

    const TIMEOUT_MS = 10000;
    const timeout = setTimeout(() => {
      if (!childProcess.killed) {
        childProcess.kill("SIGTERM");
        reject(new Error("Formatting timeout"));
      }
    }, TIMEOUT_MS);
    childProcess.on("exit", () => clearTimeout(timeout));
  });
};

export const formatFlowWingFile = async (
  textDocUri: string,
  text: string
): Promise<string> => {
  try {
    const tempPath = await fileUtils.createTempFile({
      fileName: getFileFullPath(textDocUri) + "-formatted.fg",
      data: text,
    });
    await formatFile(tempPath);
    return fileUtils.readFile(tempPath);
  } catch {
    // Format fails for invalid/incomplete code (compiler may crash) - return original
    return text;
  }
};
