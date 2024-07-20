import { CompletionItem, CompletionItemKind } from "vscode-languageserver";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { CallExpressionStrategy } from "../../strategies/CallExpressionStrategy";
import { CallExpression } from "../../types";
import { VariableDeclarationCompletionItemGenerationStrategy } from "./VariableDeclarationCompletionItemGenerationStrategy";
import { getMarkSyntaxHighlightMarkdown } from "../../utils";

export class CallExpressionCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new CallExpressionStrategy().getExpressionAsString(
      this.syntaxObj["CallExpression"]
    );
    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["CallExpression"]
    );

    this.programCtx.stack
      ?.peek()
      ?.callExpression?.set(this.result.name, this.result.completionItem);

    this.setClassMembersIfNeeded("callExpression", this.result);
    return [];
  }

  public createCompletionItem(callExpression: CallExpression): CompletionItem {
    let callExpressionStr = "",
      index = 0;

    if (callExpression[index]["IdentifierToken"])
      callExpressionStr += callExpression[index++]["IdentifierToken"].value;

    callExpressionStr += "(";
    let hasCommaAtEnd = false;

    while (callExpression[index]["VariableDeclaration"]) {
      callExpressionStr +=
        new VariableDeclarationCompletionItemGenerationStrategy().createCompletionItem(
          callExpression[index++]["VariableDeclaration"]
        ).detail + ", ";
      hasCommaAtEnd = true;
    }

    if (hasCommaAtEnd)
      callExpressionStr = callExpressionStr.slice(
        0,
        callExpressionStr.length - 2
      );

    callExpressionStr += ")";
    const callerName = new CallExpressionStrategy().getExpressionAsString(
      callExpression
    );

    return {
      label: callerName,
      kind: CompletionItemKind.Function,
      data: callerName,
      detail: callExpressionStr,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(callExpressionStr),
      },
    };
  }
}
