import { FunctionTypeExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { ExpressionStrategyFactory } from "./ExpressionStrategyFactory";

export class FunctionTypeExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: {
    FunctionTypeExpression: FunctionTypeExpression;
  }): string {
    let returnStr = "";
    let index = 0;

    if (expression?.["FunctionTypeExpression"]?.[index]?.["OpenBracketToken"]) {
      returnStr +=
        expression["FunctionTypeExpression"][index++]["OpenBracketToken"].value;
    }

    if (
      expression?.["FunctionTypeExpression"]?.[index]?.["OpenParenthesisToken"]
    ) {
      returnStr +=
        expression["FunctionTypeExpression"][index++]["OpenParenthesisToken"]
          .value;
    }

    const start = index;

    while (
      !expression?.["FunctionTypeExpression"]?.[index]?.[
        "CloseParenthesisToken"
      ]
    ) {
      if (start !== index) returnStr += ", ";

      returnStr += ExpressionStrategyFactory.createStrategy(
        expression["FunctionTypeExpression"][index]
      ).getExpressionAsString(expression["FunctionTypeExpression"][index++]);
    }

    if (
      expression?.["FunctionTypeExpression"]?.[index]?.["CloseParenthesisToken"]
    ) {
      returnStr +=
        expression["FunctionTypeExpression"][index++]["CloseParenthesisToken"]
          .value;
    }

    returnStr += " ";

    returnStr += " -> ";

    returnStr += ExpressionStrategyFactory.createStrategy(
      expression["FunctionTypeExpression"][index]
    ).getExpressionAsString(expression["FunctionTypeExpression"][index++]);

    if (
      expression?.["FunctionTypeExpression"]?.[index]?.["CloseBracketToken"]
    ) {
      returnStr +=
        expression["FunctionTypeExpression"][index++]["CloseBracketToken"]
          .value;
    }

    return returnStr;
  }
}
