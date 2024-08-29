import { CustomTypeStatement } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";

export class CustomTypeExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: CustomTypeStatement): string {
    if (expression?.[0]?.["LiteralExpression"]) {
      const res = new LiteralExpressionStrategy().getExpressionAsString(
        expression[0]["LiteralExpression"][0]
      );

      return res?.substring(0, res?.lastIndexOf("."));
    }

    if (expression?.[1]?.["LiteralExpression"]) {
      const res = new LiteralExpressionStrategy().getExpressionAsString(
        expression[1]["LiteralExpression"][0]
      );

      return res.substring(0, res.lastIndexOf("."));
    }

    return "";
  }
}
