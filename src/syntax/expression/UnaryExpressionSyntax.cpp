#include "UnaryExpressionSyntax.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(
    SyntaxToken<std::any> *operatorToken, ExpressionSyntax *operand) {

  this->operatorToken = operatorToken;
  this->operand = operand;
  children.push_back(this->operatorToken);
  children.push_back(this->operand);
}

SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

SyntaxToken<std::any> *UnaryExpressionSyntax::getOperatorToken() {
  return this->operatorToken;
}

ExpressionSyntax *UnaryExpressionSyntax::getOperand() { return this->operand; }

std::vector<SyntaxNode *> UnaryExpressionSyntax::getChildren() {
  return children;
}