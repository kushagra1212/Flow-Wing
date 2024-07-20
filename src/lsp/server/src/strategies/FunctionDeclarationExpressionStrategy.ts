import { FunctionDeclaration } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class FunctionDeclarationExpressionStrategy
  implements ExpressionStrategy
{
  getExpressionAsString(expression: FunctionDeclaration): string {
    if (expression[0]["IdentifierToken"])
      return expression[0]["IdentifierToken"].value;

    if (!expression[1]["IdentifierToken"]) return "";

    return expression[1]["IdentifierToken"].value;
  }
}
