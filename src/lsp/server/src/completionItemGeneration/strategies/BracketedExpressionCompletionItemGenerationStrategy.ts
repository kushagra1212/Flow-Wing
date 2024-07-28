import { CompletionItem, CompletionItemKind } from "vscode-languageserver";
import { CompletionItemGenerationFactory } from "../completionItemGenerationFactory";
import { CompletionItemGenerationStrategy } from "./CompletionItemGenerationStrategy";
import { BracketedExpressionStrategy } from "../../strategies/BracketedExpressionStrategy";
import { BracketedExpression } from "../../types";
import { LiteralExpressionStrategy } from "../../strategies/LiteralExpressionStrategy";
import { ExpressionStrategyFactory } from "../../strategies/ExpressionStrategyFactory";
import { getMarkSyntaxHighlightMarkdown } from "../../utils";

export class BracketedExpressionCompletionItemGenerationStrategy extends CompletionItemGenerationStrategy {
  public generateCompletionItems(): CompletionItem[] {
    this.result.name = new BracketedExpressionStrategy().getExpressionAsString(
      this.syntaxObj["BracketedExpression"]
    );

    this.result.completionItem = this.createCompletionItem(
      this.syntaxObj["BracketedExpression"]
    );
    this.programCtx.stack
      ?.peek()
      ?.callExpression?.set(this.result.name, this.result.completionItem);

    return [];
  }

  public createCompletionItem(
    bracketedExpression: BracketedExpression
  ): CompletionItem {
    let bracketedExpressionString = "";
    let variableName = "";
    if (bracketedExpression?.[0]?.["LiteralExpression"]?.[0]) {
      variableName = new LiteralExpressionStrategy().getExpressionAsString(
        bracketedExpression[0]["LiteralExpression"][0]
      );
      bracketedExpressionString += variableName + ": ";
    }

    const strategy = ExpressionStrategyFactory.createStrategy(
      bracketedExpression[1]
    );
    const typeName =
      strategy?.getExpressionAsString(bracketedExpression[1]) || "";
    bracketedExpressionString += typeName;

    return {
      label: variableName,
      kind: CompletionItemKind.TypeParameter,
      data: { typeName: typeName },
      detail: bracketedExpressionString,
      documentation: {
        kind: "markdown",
        value: getMarkSyntaxHighlightMarkdown(bracketedExpressionString),
      },
    };
  }
}
