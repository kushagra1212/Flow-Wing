import { TextDocument } from "vscode-languageserver-textdocument";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config";
import { ErrorResult } from "../utils/types";
import { parseErrorAndExtractLocation } from "../utils";
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
      fileName: flowWingConfig.temp.codeFileName,
      data: text,
    });

    const { errorObject } = await validateFile(path);

    const diagnostics = errorObject.error
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

const validateFile = (filePath: string): Promise<Partial<ErrorResult>> => {
  const SYNTAX_FILE_PATH = fileUtils.getTempFilePath({
    fileName: flowWingConfig.temp.syntaxFileName,
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
        fileName: flowWingConfig.temp.errorFileName,
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
