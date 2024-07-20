import { ExampleSettings } from "./types";

export const defaultSettings: ExampleSettings = { maxNumberOfProblems: 1000 };
export const documentSettings: Map<
  string,
  Thenable<ExampleSettings>
> = new Map();
