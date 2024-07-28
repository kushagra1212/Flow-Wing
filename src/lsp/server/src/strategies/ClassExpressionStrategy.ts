import { ClassStatement } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class ClassExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: ClassStatement): string {
    if (expression[1]["IdentifierToken"])
      return expression[1]["IdentifierToken"].value;

    if (expression[2]["IdentifierToken"])
      return expression[2]["IdentifierToken"].value;

    return "";
  }
}
