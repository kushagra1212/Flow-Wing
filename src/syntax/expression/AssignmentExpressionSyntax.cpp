#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> left,
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

SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() const {

  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

std::vector<SyntaxNode *> AssignmentExpressionSyntax::getChildren() {

  return this->_children;
}

std::unique_ptr<SyntaxToken<std::any>>
AssignmentExpressionSyntax::getOperatorToken() {
  return std::move(this->_operatorToken);
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getRight() {
  return std::move(this->_right);
}

std::unique_ptr<LiteralExpressionSyntax<std::any>>
AssignmentExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::string AssignmentExpressionSyntax::getLineNumberAndColumn() {
  return this->_left->getLineNumberAndColumn();
}
