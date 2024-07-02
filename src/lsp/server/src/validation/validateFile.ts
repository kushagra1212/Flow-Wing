import { ChildProcess, exec } from "child_process";
import { parseErrorAndExtractLocation } from "../utils";
import { ErrorResult } from "../utils/types";
import { fileUtils } from "../utils/fileUtils";

const FLOW_WING_PATH =
  "/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing";

export const validateFile = (
  filePath: string
): Promise<Partial<ErrorResult>> => {
  const JSON_FILE_PATH = `${filePath.split(".")[0]}.json`;
  const ERROR_JSON_FILE_PATH =
    JSON_FILE_PATH.substring(0, JSON_FILE_PATH.lastIndexOf(".")) + ".err.json";

  const command = `${FLOW_WING_PATH} --file=${filePath} -O=${JSON_FILE_PATH}`;

  return new Promise((resolve, reject) => {
    exec(command, async (error, stdout, stderr) => {
      if (error) {
        console.error(`Compilation error: ${error.message}`);
        return;
      }
      if (stderr) {
        let errorResult = parseErrorAndExtractLocation(stderr);

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
