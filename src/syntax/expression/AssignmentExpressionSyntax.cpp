#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left,
    std::unique_ptr<SyntaxToken<std::any>> operatorToken,
    std::unique_ptr<ExpressionSyntax> right, bool needDefaultInitialize)
    : _left(std::move(left)), _operatorToken(std::move(operatorToken)),
      _right(std::move(right)), _needDefaultInitialize(needDefaultInitialize) {}

const SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

const std::vector<SyntaxNode *> &AssignmentExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    this->_children.push_back(_left.get());
    this->_children.push_back(_operatorToken.get());
    this->_children.push_back(_right.get());
  }

  return this->_children;
}
const DiagnosticUtils::SourceLocation
AssignmentExpressionSyntax::getSourceLocation() const {
  return this->_operatorToken->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>>
AssignmentExpressionSyntax::getOperatorToken() {
  return std::move(this->_operatorToken);
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getRight() {
  return std::move(this->_right);
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::unique_ptr<SyntaxToken<std::any>> &
AssignmentExpressionSyntax::getOperatorTokenPtr() {
  return this->_operatorToken;
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getRightPtr() {
  return this->_right;
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getLeftPtr() {
  return this->_left;
}