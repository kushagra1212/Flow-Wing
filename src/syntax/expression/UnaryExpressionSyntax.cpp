#include "UnaryExpressionSyntax.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(SyntaxToken *operatorToken,
                                             ExpressionSyntax *operand) {

  this->operatorToken = operatorToken;
  this->operand = operand;
  children.push_back(this->operatorToken);
  children.push_back(this->operand);
}

SyntaxKindUtils::SyntaxKind UnaryExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::UnaryExpression;
}

SyntaxToken *UnaryExpressionSyntax::getOperatorToken() {
  return this->operatorToken;
}

ExpressionSyntax *UnaryExpressionSyntax::getOperand() { return this->operand; }

std::vector<SyntaxNode *> UnaryExpressionSyntax::getChildren() {
  return children;
}