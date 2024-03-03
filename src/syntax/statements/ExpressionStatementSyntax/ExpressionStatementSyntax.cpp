#include "ExpressionStatementSyntax.h"

ExpressionStatementSyntax::ExpressionStatementSyntax(
    std::unique_ptr<ExpressionSyntax> expression) {
  this->_expression = std::move(expression);
}

std::unique_ptr<ExpressionSyntax> ExpressionStatementSyntax::getExpression() {
  return std::move(this->_expression);
}
std::unique_ptr<ExpressionSyntax> &
ExpressionStatementSyntax::getExpressionPtr() {
  return this->_expression;
}
const SyntaxKindUtils::SyntaxKind ExpressionStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
}

const std::vector<SyntaxNode *> &ExpressionStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_expression.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ExpressionStatementSyntax::getSourceLocation() const {
  return this->_expression->getSourceLocation();
}