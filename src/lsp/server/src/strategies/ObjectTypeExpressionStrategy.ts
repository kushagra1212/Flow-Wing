import { ObjectTypeExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";

export class ObjectTypeExpressionStrategy implements ExpressionStrategy {
  literalExpressionStrategy = new LiteralExpressionStrategy();

  getExpressionAsString(expression: {
    ObjectTypeExpression: ObjectTypeExpression[];
  }): string {
    const literalExpression =
      expression["ObjectTypeExpression"][0]["LiteralExpression"][0];
    return this.literalExpressionStrategy.getExpressionAsString(
      literalExpression
    );
  }
}
