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

std::string UnaryExpressionSyntax::getLineNumberAndColumn() const {
  return this->operatorToken->getLineNumberAndColumn();
}

UnaryExpressionSyntax::~UnaryExpressionSyntax() {
  if (this->operatorToken != nullptr) {
    delete this->operatorToken;
    this->operatorToken = nullptr;
  }

  if (this->operand != nullptr) {
    delete this->operand;
    this->operand = nullptr;
  }
}
