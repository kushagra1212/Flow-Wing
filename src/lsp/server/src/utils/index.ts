import * as fs from "fs";
import * as os from "os";
import { ErrorResult } from "./types";

export function createFileAndAppend(path: string, text: string) {
  fs.access(path, fs.constants.F_OK, (err) => {
    if (err) {
      // If file does not exist, create it and write text
      fs.writeFile(path, text, (err) => {
        if (err) throw err;
        console.log("File created and text saved!");
      });
    } else {
      // If file already exists, append text
      // clear file before appending
      fs.writeFile(path, "", (err) => {
        if (err) throw err;
      });

      fs.appendFile(path, `\n${text}`, (err) => {
        if (err) throw err;
        console.log("Text appended to existing file!");
      });
    }
  });
}

export const getTempFgCodeFilePath = (fileName: string): string => {
  const tempDir = os.tmpdir();
  const path = tempDir + "/" + fileName;
  createFileAndAppend(path, "");
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
