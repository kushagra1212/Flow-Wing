import { ChildProcess, exec } from "child_process";
import { parseErrorAndExtractLocation } from "../utils";
import { ErrorResult } from "../utils/types";

const FLOW_WING_PATH =
  "/Users/apple/code/per/Flow-Wing/targets/aot-compiler/aot-compiler-build/FlowWing";

export const validateFile = (
  filePath: string
): Promise<Partial<ErrorResult>> => {
  const JSON_FILE_PATH = `${filePath.split(".")[0]}.json`;

  const command = `${FLOW_WING_PATH} --file=${filePath} -O=${JSON_FILE_PATH}`;

  return new Promise((resolve, reject) => {
    exec(command, (error, stdout, stderr) => {
      if (error) {
        console.error(`Compilation error: ${error.message}`);
        resolve({ hasError: true, errorMessage: error.message });
        return;
      }
      if (stderr) {
        const errorResult = parseErrorAndExtractLocation(stderr);

        resolve({ ...errorResult, rawError: stderr });
        return;
      }
      console.log(`Compilation successful. Executable created`);
      resolve({ hasError: false });
    });
  });
};
