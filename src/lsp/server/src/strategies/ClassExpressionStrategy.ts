import { ClassStatement } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class ClassExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: ClassStatement): string {
    if (!expression[1]["IdentifierToken"]) return "";

    return expression[1]["IdentifierToken"].value;
  }
}
