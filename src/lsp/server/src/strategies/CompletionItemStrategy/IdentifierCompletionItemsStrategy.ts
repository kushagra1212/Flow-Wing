import { CompletionItem } from "vscode-languageserver";
import { ProgramStructure, Stack } from "../../ds/stack";
import { CompletionItemStrategy, CompletionItemStrategyParams } from ".";
import { reverseStack } from "../../utils";

export class IdentifierCompletionItemsStrategy
  implements CompletionItemStrategy
{
  public getCompletionItems({
    stack,
    identifier,
  }: CompletionItemStrategyParams): CompletionItem[] {
    const reversedStacked = reverseStack(stack);
    const result: CompletionItem[] = [];
    const update = (
      identifier: string,
      result: CompletionItem[],
      newValue: CompletionItem
    ) => {
      const index = result.findIndex((item) => item.label === identifier);

      if (index !== -1) {
        result[index] = newValue;
      } else {
        result.push(newValue);
      }
    };

    while (!reversedStacked.isEmpty()) {
      const current = reversedStacked?.pop();
      stack.push(current);

      if (current.others.get(identifier)) {
        update(identifier, result, current.others.get(identifier));
      }

      if (current.variableDeclarations.get(identifier)) {
        update(
          identifier,
          result,
          current.variableDeclarations.get(identifier)
        );
      }

      if (current.customTypes.get(identifier))
        update(identifier, result, current.customTypes.get(identifier));

      if (current.functions.get(identifier))
        update(identifier, result, current.functions.get(identifier));

      if (current.classes.get(identifier)) {
        const classCI = current.classes.get(identifier);
        // Maping Class Name with init Function
        if (classCI.functions.get("init"))
          update(identifier, result, classCI.functions.get("init"));

        update(identifier, result, classCI.classCompletionItem);
      }

      if (current.callExpression.get(identifier))
        update(identifier, result, current.callExpression.get(identifier));
    }

    return result;
  }
}
