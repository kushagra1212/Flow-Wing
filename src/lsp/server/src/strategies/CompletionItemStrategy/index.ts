import { CompletionItem } from "vscode-languageserver";
import { ProgramStructure, Stack } from "../../ds/stack";
import { ProgramContext } from "../../ds/programContext";

export type CompletionItemStrategyParams = {
  programCtx: ProgramContext;
  identifier?: string;
  expressionName?: keyof ProgramStructure;
  closestScope?: boolean;
};

export interface CompletionItemStrategy {
  getCompletionItems(
    completionItemParams: CompletionItemStrategyParams
  ): CompletionItem[];
}
