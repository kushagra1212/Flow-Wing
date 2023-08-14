#include "BinaryExpressionSyntax.h"

BinaryExpressionSyntax::BinaryExpressionSyntax(
    std::shared_ptr<ExpressionSyntax> left,
    std::shared_ptr<SyntaxToken<std::any>> operatorToken,
    std::shared_ptr<ExpressionSyntax> right) {
  this->_left = left;
  this->_operatorToken = operatorToken;
  this->_right = right;
}

SyntaxKindUtils::SyntaxKind BinaryExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BinaryExpression;
}

std::shared_ptr<ExpressionSyntax> BinaryExpressionSyntax::getLeft() {
  return this->_left;
}

std::shared_ptr<SyntaxToken<std::any>>
BinaryExpressionSyntax::getOperatorToken() {
  return this->_operatorToken;
}

std::shared_ptr<ExpressionSyntax> BinaryExpressionSyntax::getRight() {
  return this->_right;
}

std::vector<std::shared_ptr<SyntaxNode>> BinaryExpressionSyntax::getChildren() {

  std::vector<std::shared_ptr<SyntaxNode>> children = {
      this->_left, this->_operatorToken, this->_right};
  return children;
}

std::string BinaryExpressionSyntax::getLineNumberAndColumn() const {
  return this->_left->getLineNumberAndColumn();
}
