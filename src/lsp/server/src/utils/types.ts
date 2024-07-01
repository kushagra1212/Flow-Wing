export type ErrorResult = {
  lineNumber: number;
  columnNumber: number;
  errorMessage: string;
  stdoutWithoutColors: string;
  location: RegExpExecArray | null;
  hasError: boolean;
  rawError?: string;
};
