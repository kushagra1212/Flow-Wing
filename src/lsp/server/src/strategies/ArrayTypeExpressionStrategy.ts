import { ArrayTypeExpression, PrimitiveTypeExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";
import { ObjectTypeExpressionStrategy } from "./ObjectTypeExpressionStrategy";
import { PrimitiveTypeExpressionStrategy } from "./PrimitiveTypeExpressionStrategy";

export class ArrayTypeExpressionStrategy implements ExpressionStrategy {
  private literalExpressionStrategy = new LiteralExpressionStrategy();
  private objectTypeExpressionStrategy = new ObjectTypeExpressionStrategy();
  private primitiveTypeExpressionStrategy =
    new PrimitiveTypeExpressionStrategy();
  getExpressionAsString(expression: {
    ArrayTypeExpression: ArrayTypeExpression;
  }): string {
    const expr = expression["ArrayTypeExpression"];
    let typeName = "";
    if (expr && "ObjectTypeExpression" in expr[0]) {
      typeName = this.objectTypeExpressionStrategy.getExpressionAsString(
        expr[0]
      );
    } else if (expr) {
      typeName = this.primitiveTypeExpressionStrategy.getExpressionAsString({
        PrimitiveTypeExpression: [expr[0] as PrimitiveTypeExpression],
      });
    }

    if (typeName) {
      let indexes = "";
      for (let i = 1; i < expr.length; i++) {
        const literalExpression = expr[i];
        indexes +=
          "[" +
          this.literalExpressionStrategy.getExpressionAsString(
            literalExpression["LiteralExpression"][0]
          ) +
          "]";
      }

      return typeName + indexes;
    }

    return "";
  }
}
