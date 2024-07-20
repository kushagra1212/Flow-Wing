import { VariableDeclaration } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class VariableDeclarationExpressionStrategy
  implements ExpressionStrategy
{
  getExpressionAsString(expression: VariableDeclaration): string {
    let index = 0;
    if (expression[index]["VarKeyword"] || expression[index]["ConstKeyword"])
      index++;

    if (expression[index]["InOutKeyword"]) index++;

    return expression[index]["IdentifierToken"].value;
  }
}
