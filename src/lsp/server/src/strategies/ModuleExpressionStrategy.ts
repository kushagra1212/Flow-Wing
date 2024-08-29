import { ModuleStatement } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class ModuleExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: ModuleStatement): string {
    if (expression?.[1]?.["LiteralExpression"]?.[0]?.["IdentifierToken"])
      return expression?.[1]?.["LiteralExpression"]?.[0]?.["IdentifierToken"]
        .value;

    return "";
  }
}
