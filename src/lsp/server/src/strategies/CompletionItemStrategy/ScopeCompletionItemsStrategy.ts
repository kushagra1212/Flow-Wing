import { CompletionItem } from "vscode-languageserver";
import { CompletionItemStrategy, CompletionItemStrategyParams } from ".";
import { reverseStack } from "../../utils";

export class ScopeCompletionItemsStrategy implements CompletionItemStrategy {
  public getCompletionItems({
    programCtx,
    identifier,
    expressionName,
    closestScope = true,
  }: CompletionItemStrategyParams): CompletionItem[] {
    const reversedStack = reverseStack(programCtx.stack);

    let result: CompletionItem[] = [];

    while (!reversedStack.isEmpty()) {
      const current = reversedStack?.pop();
      programCtx.stack.push(current);
      if (result?.length && !closestScope) continue;

      const completionItem = (
        current[expressionName] as Map<
          string,
          CompletionItem[] | CompletionItem
        >
      ).get(identifier);

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

    if (programCtx.rootProgram.functions.get(identifier)) {
      result = [programCtx.rootProgram.functions.get(identifier)];
    }
    if (
      programCtx.isInsideClass() &&
      programCtx.rootProgram.classes
        .get(programCtx.getCurrentParsingClassName())
        .functions.get(identifier)
    ) {
      result = [
        programCtx.rootProgram.classes
          .get(programCtx.getCurrentParsingClassName())
          .functions.get(identifier),
      ];
    }
    return result;
  }
}
