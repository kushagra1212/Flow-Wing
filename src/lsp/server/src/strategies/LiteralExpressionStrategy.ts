import { LiteralExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class LiteralExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: LiteralExpression): string {
    const typeMap: { [key: string]: string } = {
      NumberToken: "NumberToken",
      IdentifierToken: "IdentifierToken",
    };

    for (const key in typeMap) {
      if (typeMap[key] in expression) {
        return (expression as any)[typeMap[key]].value;
      }
    }

    return "";
  }
}
