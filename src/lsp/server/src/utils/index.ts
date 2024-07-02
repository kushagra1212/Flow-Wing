import * as fs from "fs";
import * as os from "os";
import { ErrorResult } from "./types";
import { fileUtils } from "./fileUtils";

export const getTempFgCodeFilePath = ({
  fileName,
}: {
  fileName: string;
}): string => {
  const tempDir = os.tmpdir();
  const path = tempDir + "/" + fileName;
  fileUtils.writeFile(path, "");
  return path;
};

export const parseErrorAndExtractLocation = (error: string): ErrorResult => {
  const result: ErrorResult = {
    lineNumber: 0,
    columnNumber: 0,
    errorMessage: "",
    stdoutWithoutColors: "",
    location: null,
    hasError: true,
    errorObject: null,
  };

  // eslint-disable-next-line no-control-regex
  const colorRegex = /\x1b\[[0-9;]*m/g;

  // Remove all colors from the stdout
  result.stdoutWithoutColors = error.replace(colorRegex, "");
  const regex = /Line (\d+):(\d+)\s(.*)/g;
  const ans = regex.exec(result.stdoutWithoutColors);

  if (ans?.length !== 4) {
    return result;
  }

  result.lineNumber = parseInt(ans[1]) - 1; // Convert to 0-based index
  result.columnNumber = parseInt(ans[2]) - 1; // Convert to 0-based index
  result.errorMessage = ans[3];
  const locationRegex = /(Location:)\s(.*)/g;
  result.location = locationRegex.exec(result.stdoutWithoutColors);

  return result;
};
