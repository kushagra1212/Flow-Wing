import { TextDocument } from "vscode-languageserver-textdocument";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { ErrorResult } from "../utils/types";
import { getFileFullPath, parseErrorAndExtractLocation } from "../utils";
import { createDiagnostic } from "./diagnosticService";
import { _Connection } from "vscode-languageserver";
import { execFile } from "child_process";

export const validateTextDocument = async (
  textDocument: TextDocument,
  connection: _Connection = null
): Promise<void> => {
  if (!textDocument) return;

  try {
    const text = textDocument.getText();
    const path = await fileUtils.createTempFile({
      fileName: getFileFullPath(textDocument.uri) + ".fg",
      data: text,
    });

    const { errorObject } = await validateFile(textDocument.uri, path);

    const diagnostics = errorObject?.error
      ? [createDiagnostic(errorObject, textDocument)]
      : [];

    // Send the computed diagnostics to VS Code.

    if (!connection) return;

    connection.sendDiagnostics({
      uri: textDocument.uri,
      diagnostics,
    });
  } catch (err) {
    console.error("🚀 ~ file: server.ts:validateTextDocument ~ err", err);
  }
};

export const validateFile = (
  textDocUri: string,
  filePath: string
): Promise<Partial<ErrorResult>> => {
  const SYNTAX_FILE_PATH = fileUtils.getTempFilePath({
    fileName: getFileFullPath(textDocUri) + flowWingConfig.temp.syntaxFileExt,
  });

  const commandArgs = [`--file=${filePath}`, `-O=${SYNTAX_FILE_PATH}`];

  return new Promise((resolve, reject) => {
    const childProcess = execFile(
      flowWingConfig.compiler.flowWingPath,
      commandArgs,
      async (error, stdout, stderr) => {
        if (error) {
          console.error(`Compilation error: ${error.message}`);
          return reject(error);
        }

        if (!stderr) {
          return resolve({ hasError: false });
        }

        const ERROR_JSON_FILE_PATH = fileUtils.getTempFilePath({
          fileName:
            getFileFullPath(textDocUri) + flowWingConfig.temp.errorFileExt,
        });

        try {
          const errorResult = parseErrorAndExtractLocation(stderr);

          const errorObject = await fileUtils.readJsonFile<
            ErrorResult["errorObject"]
          >(ERROR_JSON_FILE_PATH);

          resolve({ ...errorResult, errorObject });
        } catch (err) {
          console.error(
            `Error reading error file: ${ERROR_JSON_FILE_PATH}`,
            err
          );
          reject(err);
        }
      }
    );

    childProcess.on("error", (err) => {
      console.error(`Process error: ${err.message}`);
      reject(err);
    });

    childProcess.on("exit", (code, signal) => {
      if (code !== 0) {
        console.error(`Process exited with code: ${code}, signal: ${signal}`);
      }
    });
    const TIMEOUT_MS = 10000; // 10 seconds timeout
    setTimeout(() => {
      if (!childProcess.killed) {
        childProcess.kill();
        reject(new Error("Process timeout"));
      }
    }, TIMEOUT_MS);
  });
};

const formatFile = (filePath: string): Promise<string> => {
  const commandArgs = [`--file=${filePath}`, `--format`];

  return new Promise((resolve, reject) => {
    const childProcess = execFile(
      flowWingConfig.compiler.flowWingPath,
      commandArgs,
      (error, stdout, stderr) => {
        if (error) {
          console.error(`Error formatting: ${error.message}`);
          reject(error);
          return;
        }

        if (stderr) {
          console.error(`Formatting stderr: ${stderr}`);
          reject(
            new Error(`Formatting process encountered an issue: ${stderr}`)
          );
          return;
        }

        resolve("Successfully formatted Flow-Wing code");
      }
    );

    // Handle potential process errors
    childProcess.on("error", (err) => {
      console.error(`Process error: ${err.message}`);
      reject(err);
    });

    childProcess.on("exit", (code, signal) => {
      if (code !== 0) {
        console.error(`Process exited with code: ${code}, signal: ${signal}`);
        reject(
          new Error(`Process exited with code: ${code}, signal: ${signal}`)
        );
      }
    });

    const TIMEOUT_MS = 10000; // 10 seconds timeout
    setTimeout(() => {
      if (!childProcess.killed) {
        childProcess.kill();
        reject(new Error("Formatting process timeout"));
      }
    }, TIMEOUT_MS);
  });
};
export const formatFlowWingFile = async (
  textDocUri: string,
  text: string
): Promise<string> => {
  try {
    const path = await fileUtils.createTempFile({
      fileName: getFileFullPath(textDocUri) + "-formatted.fg",
      data: text,
    });
    await formatFile(path);
    return fileUtils.readFile(path);
  } catch (err) {
    console.error(`Error formatting file: ${textDocUri}`, err);
  }

  return text;
};
