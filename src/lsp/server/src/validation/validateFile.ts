import { ChildProcess, exec } from "child_process";
import { parseErrorAndExtractLocation } from "../utils";
import { ErrorResult } from "../utils/types";
import { fileUtils } from "../utils/fileUtils";
import { flowWingConfig } from "../config/config";

export const validateFile = (
  filePath: string
): Promise<Partial<ErrorResult>> => {
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
      if (stderr) {
        let errorResult = parseErrorAndExtractLocation(stderr);
        const ERROR_JSON_FILE_PATH = fileUtils.getTempFilePath({
          fileName: flowWingConfig.temp.errorFileName,
        });

        try {
          const errorObject = await fileUtils.readJsonFile<
            ErrorResult["errorObject"]
          >(ERROR_JSON_FILE_PATH);
          errorResult = { ...errorResult, errorObject };
        } catch (err) {
          console.error(
            `Error reading error file: ${ERROR_JSON_FILE_PATH}`,
            err
          );
          reject(err);
          return;
        }

        resolve(errorResult);
        return;
      }
      resolve({ hasError: false });
    });
  });
};
