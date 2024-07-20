import { CompletionItem } from "vscode-languageserver";
import { ProgramStructure, Stack } from "../ds/stack";
import {
  CompletionItemStrategy,
  CompletionItemStrategyParams,
} from "../strategies/CompletionItemStrategy";

export class CompletionItemService {
  private strategy: CompletionItemStrategy;

  constructor(strategy: CompletionItemStrategy) {
    this.strategy = strategy;
  }

  public getCompletionItems(
    completionItemParams: CompletionItemStrategyParams
  ): CompletionItem[] {
    return this.strategy.getCompletionItems(completionItemParams);
  }
}
