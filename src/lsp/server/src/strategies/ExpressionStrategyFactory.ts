import { ArrayTypeExpressionStrategy } from "./ArrayTypeExpressionStrategy";
import { BracketedExpressionStrategy } from "./BracketedExpressionStrategy";
import { CallExpressionStrategy } from "./CallExpressionStrategy";
import { ClassExpressionStrategy } from "./ClassExpressionStrategy";
import { CustomTypeExpressionStrategy } from "./CustomTypeExpressionStrategy";
import { ExpressionStrategy } from "./ExpressionStrategy";
import { FunctionDeclarationExpressionStrategy } from "./FunctionDeclarationExpressionStrategy";
import { LiteralExpressionStrategy } from "./LiteralExpressionStrategy";
import { ObjectTypeExpressionStrategy } from "./ObjectTypeExpressionStrategy";
import { PrimitiveTypeExpressionStrategy } from "./PrimitiveTypeExpressionStrategy";
import { VariableDeclarationExpressionStrategy } from "./VariableDeclarationExpressionStrategy";
import { FunctionTypeExpressionStrategy } from "./FunctionTypeExpressionStrategy";

export class ExpressionStrategyFactory {
  static createStrategy(expression: any): ExpressionStrategy {
    if (!expression) return null;
    if (expression["PrimitiveTypeExpression"]) {
      return new PrimitiveTypeExpressionStrategy();
    } else if (expression["ArrayTypeExpression"]) {
      return new ArrayTypeExpressionStrategy();
    } else if (expression["ObjectTypeExpression"]) {
      return new ObjectTypeExpressionStrategy();
    } else if (expression["IdentifierToken"] || expression["NumberToken"]) {
      return new LiteralExpressionStrategy();
    } else if (expression["VariableDeclaration"]) {
      return new VariableDeclarationExpressionStrategy();
    } else if (expression["CustomTypeStatement"]) {
      return new CustomTypeExpressionStrategy();
    } else if (expression["BracketedExpression"]) {
      return new BracketedExpressionStrategy();
    } else if (expression["FunctionDeclarationSyntax"]) {
      return new FunctionDeclarationExpressionStrategy();
    } else if (expression["CallExpression"]) {
      return new CallExpressionStrategy();
    } else if (expression["ClassStatement"]) {
      return new ClassExpressionStrategy();
    } else if (expression["FunctionTypeExpression"]) {
      return new FunctionTypeExpressionStrategy();
    } else {
      return null;
    }
  }
}
