import { FlowWingLspSettings } from "./types";

/** Matches `FlowWing.maxNumberOfProblems` default in package.json (100). */
export const defaultSettings: FlowWingLspSettings = {
  maxNumberOfProblems: 100,
};
export const documentSettings: Map<
  string,
  Thenable<FlowWingLspSettings>
> = new Map();
