type Location = {
  column: number;
  length: number;
  line: number;
};

type DiagnosticLevel = "Error" | "Warning" | "Info" | "Debug";
type DiagnosticType =
  | "Lexical"
  | "Syntactic"
  | "Semantic"
  | "CodeGen"
  | "Runtime"
  | "Linker"
  | "Fatal";

export type ErrorObject = {
  error: boolean;
  level: DiagnosticLevel;
  location: Location;
  message: string;
  type: DiagnosticType;
};

export type ErrorResult = {
  lineNumber: number;
  columnNumber: number;
  errorMessage: string;
  stdoutWithoutColors: string;
  location: RegExpExecArray | null;
  hasError: boolean;
  rawError?: string;
  errorObject: ErrorObject;
};
