import { PrimitiveTypeExpression } from "../types";
import { ExpressionStrategy } from "./ExpressionStrategy";

export class PrimitiveTypeExpressionStrategy implements ExpressionStrategy {
  getExpressionAsString(expression: {
    PrimitiveTypeExpression: PrimitiveTypeExpression[];
  }): string {
    const typeMap: { [key: string]: string } = {
      Int32Keyword: "Int32Keyword",
      DeciKeyword: "DeciKeyword",
      Deci32Keyword: "Deci32Keyword",
      StrKeyword: "StrKeyword",
      BoolKeyword: "BoolKeyword",
      NthgKeyword: "NthgKeyword",
    };

    for (const key in typeMap) {
      if (typeMap[key] in expression["PrimitiveTypeExpression"][0]) {
        return expression["PrimitiveTypeExpression"][0][typeMap[key]].value;
      }
    }

    return "";
  }
}
