import { CompletionItem } from "vscode-languageserver";
import { CompletionItemStrategy, CompletionItemStrategyParams } from ".";
import { reverseStack } from "../../utils";

export class IdentifierCompletionItemsStrategy
  implements CompletionItemStrategy
{
  public getCompletionItems({
    programCtx,
    identifier,
  }: CompletionItemStrategyParams): CompletionItem[] {
    const reversedStacked = reverseStack(programCtx.stack);
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
      programCtx.stack.push(current);

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

      // if (current.functions.get(identifier))
      //   update(identifier, result, current.functions.get(identifier));

      if (current.classes.get(identifier)) {
        const classCI = current.classes.get(identifier);
        // Maping Class Name with init Function
        if (classCI.functions.get("init"))
          update(identifier, result, classCI.functions.get("init"));

        update(identifier, result, classCI.classCompletionItem);
      }

      // if (current.callExpression.get(identifier))
      //   update(identifier, result, current.callExpression.get(identifier));
    }

    if (programCtx.rootProgram.modules.get(identifier.split("::")[0])) {
      const moduleCI = programCtx.rootProgram.modules.get(
        identifier.split("::")[0]
      );
      if (moduleCI.classes.get(identifier)) {
        if (moduleCI.classes.get(identifier).functions.get("init")) {
          update(
            identifier,
            result,
            moduleCI.classes.get(identifier).functions.get("init")
          );
        }
      }
    }
    if (programCtx.rootProgram.functions.get(identifier))
      update(
        identifier,
        result,
        programCtx.rootProgram.functions.get(identifier)
      );

    if (
      programCtx.isInsideClass() &&
      programCtx.rootProgram.classes
        .get(programCtx.getCurrentParsingClassName())
        .functions.get(identifier)
    ) {
      update(
        identifier,
        result,
        programCtx.rootProgram.classes
          .get(programCtx.getCurrentParsingClassName())
          .functions.get(identifier)
      );
    }
    // if (programCtx.rootProgram.modules.get(identifier.split("::")[0])) {
    //   const moduleCI = programCtx.rootProgram.modules.get(
    //     identifier.split("::")[0]
    //   );

    //   update(identifier, result, moduleCI.moduleCompletionItem);

    //   moduleCI.classes.forEach((value) => {
    //     result.push(value.classCompletionItem);
    //   });

    //   moduleCI.customTypes.forEach((value) => {
    //     result.push(value);
    //   });

    //   moduleCI.functions.forEach((value) => {
    //     result.push(value);
    //   });

    //   moduleCI.variableDeclarations.forEach((value) => {
    //     result.push(value);
    //   });
    // }
    return result;
  }
}
