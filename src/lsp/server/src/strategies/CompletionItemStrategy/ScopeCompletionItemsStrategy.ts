import { CompletionItem } from "vscode-languageserver";
import { CompletionItemStrategy, CompletionItemStrategyParams } from ".";
import { ProgramStructure, Stack } from "../../ds/stack";
import { reverseStack } from "../../utils";

export class ScopeCompletionItemsStrategy implements CompletionItemStrategy {
  public getCompletionItems({
    stack,
    identifier,
    expressionName,
    closestScope = true,
  }: CompletionItemStrategyParams): CompletionItem[] {
    const reversedStack = reverseStack(stack);

    let result: CompletionItem[] = [];

    while (!reversedStack.isEmpty()) {
      const current = reversedStack?.pop();
      stack.push(current);
      if (result?.length && !closestScope) continue;

      const completionItem = current[expressionName].get(identifier);

      if (completionItem) {
        if (completionItem["classCompletionItem"]) {
          result = [completionItem["classCompletionItem"]];
        } else if ((completionItem as CompletionItem[])?.length > 0) {
          result = completionItem as CompletionItem[];
        } else {
          result = [completionItem as CompletionItem];
        }
      }
    }

    return result;
  }
}
