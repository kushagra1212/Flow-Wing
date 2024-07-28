import { BracketedExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";

export class BracketedExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: BracketedExpression): string {
    if (expression?.[0]?.["LiteralExpression"]?.[0]) {
      return new LiteralExpressionStrategy().getExpressionAsString(
        expression[0]["LiteralExpression"][0]
      );
    }

    return "";
  }
}
