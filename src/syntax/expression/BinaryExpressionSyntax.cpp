#include "BinaryExpressionSyntax.h"

BinaryExpressionSyntax::BinaryExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left,
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> right) {
  this->_left = std::move(left);
  this->_operatorToken = std::move(operatorToken);
  this->_right = std::move(right);

  // Add children

  this->_children.push_back(_left.get());
  this->_children.push_back(_operatorToken.get());
  this->_children.push_back(_right.get());
}

std::unique_ptr<ExpressionSyntax> BinaryExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::unique_ptr<SyntaxToken<std::any>>
BinaryExpressionSyntax::getOperatorToken() {
  return std::move(this->_operatorToken);
}

std::unique_ptr<ExpressionSyntax> BinaryExpressionSyntax::getRight() {
  return std::move(this->_right);
}

SyntaxKindUtils::SyntaxKind BinaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BinaryExpression;
}

std::vector<SyntaxNode *> BinaryExpressionSyntax::getChildren() {

  return this->_children;
}

std::string BinaryExpressionSyntax::getLineNumberAndColumn() {
  return this->_left->getLineNumberAndColumn();
}

std::unique_ptr<ExpressionSyntax> &BinaryExpressionSyntax::getLeftPtr() {
  return this->_left;
}

std::unique_ptr<SyntaxToken<std::any>> &
BinaryExpressionSyntax::getOperatorTokenPtr() {
  return this->_operatorToken;
}

std::unique_ptr<ExpressionSyntax> &BinaryExpressionSyntax::getRightPtr() {
  return this->_right;
}