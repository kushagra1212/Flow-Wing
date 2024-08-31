#include "AssignmentExpressionSyntax.h"

AssignmentExpressionSyntax::AssignmentExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> left,
    SyntaxKindUtils::SyntaxKind operatorToken,
    std::unique_ptr<ExpressionSyntax> right, bool needDefaultInitialize)
    : _left(std::move(left)), _right(std::move(right)),
      _operatorTokenKind(operatorToken),
      _needDefaultInitialize(needDefaultInitialize) {}

const SyntaxKindUtils::SyntaxKind AssignmentExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::AssignmentExpression;
}

const std::vector<SyntaxNode *> &AssignmentExpressionSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    if (_left)
      this->_children.push_back(_left.get());

    if (_right)
      this->_children.push_back(_right.get());
  }

  return this->_children;
}
const DiagnosticUtils::SourceLocation
AssignmentExpressionSyntax::getSourceLocation() const {
  if (_left)
    return _left->getSourceLocation();

  if (_right)
    return _right->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getRight() {
  return std::move(this->_right);
}

std::unique_ptr<ExpressionSyntax> AssignmentExpressionSyntax::getLeft() {
  return std::move(this->_left);
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getRightPtr() {
  return this->_right;
}

std::unique_ptr<ExpressionSyntax> &AssignmentExpressionSyntax::getLeftPtr() {
  return this->_left;
}