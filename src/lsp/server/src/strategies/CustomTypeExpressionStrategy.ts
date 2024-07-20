import { CustomTypeStatement } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";

export class CustomTypeExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: CustomTypeStatement): string {
    if (!expression[0]["LiteralExpression"]) {
      return "";
    }

    return new LiteralExpressionStrategy().getExpressionAsString(
      expression[0]["LiteralExpression"][0]
    );
  }
}
