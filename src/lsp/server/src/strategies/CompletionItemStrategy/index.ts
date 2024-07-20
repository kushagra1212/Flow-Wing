import { CompletionItem } from "vscode-languageserver";
import { ProgramStructure, Stack } from "../../ds/stack";

export type CompletionItemStrategyParams = {
  stack: Stack<ProgramStructure>;
  identifier?: string;
  expressionName?: keyof ProgramStructure;
  closestScope?: boolean;
};

export interface CompletionItemStrategy {
  getCompletionItems(
    completionItemParams: CompletionItemStrategyParams
  ): CompletionItem[];
}
