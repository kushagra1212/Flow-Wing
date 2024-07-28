import { CompletionItem } from "vscode-languageserver";
import { CompletionItemStrategy, CompletionItemStrategyParams } from ".";
import { reverseStack } from "../../utils";
import { ProgramStructure } from "../../ds/stack";

export class AllCompletionItemsStrategy implements CompletionItemStrategy {
  public getCompletionItems({
    programCtx,
  }: CompletionItemStrategyParams): CompletionItem[] {
    const reversedStack = reverseStack(programCtx.stack);
    const result: CompletionItem[] = [];
    const mapping: ProgramStructure = {
      variableDeclarations: new Map(),
      customTypes: new Map(),
      classes: new Map(),
      functions: new Map(),
      callExpression: new Map(),
      variableExpressions: new Map(),
      others: new Map(),
    };

    if (reversedStack.peek().others?.size) {
      reversedStack.peek().others?.forEach((value, key) => {
        result.push(value);
      });
    }

    while (!reversedStack.isEmpty()) {
      const current = reversedStack?.pop();
      programCtx.stack.push(current);
      current.variableDeclarations.forEach((value, key) => {
        mapping.variableDeclarations.set(key, value);
      });

      current.customTypes.forEach((value, key) => {
        mapping.customTypes.set(key, value);
      });

      current.classes.forEach((value, key) => {
        mapping.classes.set(key, value);
      });

      // current.callExpression.forEach((value, key) => {
      //   mapping.callExpression.set(key, value);
      // });
      // current.variableExpressions.forEach((value, key) => {
      //   mapping.variableExpressions.set(key, value);
      // });
    }

    programCtx.rootProgram.functions.forEach((value, key) => {
      mapping.functions.set(key, value);
    });
    if (programCtx.isInsideClass()) {
      programCtx.rootProgram.classes
        .get(programCtx.getCurrentParsingClassName())
        .functions.forEach((value, key) => {
          mapping.functions.set(key, value);
        });
    }

    // Update Result

    if (mapping.variableDeclarations)
      result.push(...Array.from(mapping.variableDeclarations.values()));

    if (mapping.customTypes)
      result.push(...Array.from(mapping.customTypes.values()));

    if (mapping.functions)
      result.push(...Array.from(mapping.functions.values()));

    // if (mapping.variableExpressions) {
    //   for (const value of mapping.variableExpressions.values()) {
    //     result.push(...Array.from(value));
    //   }
    // }

    if (mapping.classes) {
      Array.from(mapping.classes.values()).forEach((value) => {
        result.push(value.classCompletionItem);
      });
    }

    // if (mapping.callExpression)
    //   result.push(...Array.from(mapping.callExpression.values()));

    return result;
  }
}
