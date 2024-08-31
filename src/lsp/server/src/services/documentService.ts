import { TextDocument } from "vscode-languageserver-textdocument";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { ErrorResult } from "../utils/types";
import { getFileFullPath, parseErrorAndExtractLocation } from "../utils";
import { createDiagnostic } from "./diagnosticService";
import { _Connection } from "vscode-languageserver";
import { exec } from "child_process";

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

  const command = `${flowWingConfig.compiler.flowWingPath} --file=${filePath} -O=${SYNTAX_FILE_PATH}`;

  return new Promise((resolve, reject) => {
    exec(command, async (error, stdout, stderr) => {
      if (error) {
        console.error(`Compilation error: ${error.message}`);
        return;
      }

      if (!stderr) {
        resolve({ hasError: false });
        return;
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
        return;
      } catch (err) {
        console.error(`Error reading error file: ${ERROR_JSON_FILE_PATH}`, err);
        reject(err);
        return;
      }
    });
  });
};

const formatFile = (filePath: string): Promise<string> => {
  const command = `${flowWingConfig.compiler.flowWingPath} --file=${filePath} --format`;

  return new Promise((resolve, reject) => {
    exec(command, async (error, stdout, stderr) => {
      if (error) {
        console.error(`Error formating: ${error.message}`);
        reject(error);
        return;
      }
      resolve("Successfully formatted flowwing code");
    });
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
