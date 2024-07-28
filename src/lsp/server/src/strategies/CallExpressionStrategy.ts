import { CallExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class CallExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: CallExpression): string {
    if (!expression[0]["IdentifierToken"]) return "";

    return expression[0]["IdentifierToken"].value;
  }
}
