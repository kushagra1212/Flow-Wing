#include "ExpressionStatementSyntax.h"

ExpressionStatementSyntax::ExpressionStatementSyntax(
    std::unique_ptr<ExpressionSyntax> expression) {
  this->_expression = std::move(expression);

  // Add children

  _children.push_back(_expression.get());
}

std::unique_ptr<ExpressionSyntax> ExpressionStatementSyntax::getExpression() {
  return std::move(this->_expression);
}
std::unique_ptr<ExpressionSyntax> &
ExpressionStatementSyntax::getExpressionPtr() {
  return this->_expression;
}
SyntaxKindUtils::SyntaxKind ExpressionStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ExpressionStatement;
}

std::vector<SyntaxNode *> ExpressionStatementSyntax::getChildren() {
  return this->_children;
}

DiagnosticUtils::SourceLocation
ExpressionStatementSyntax::getSourceLocation() const {
  return this->_expression->getSourceLocation();
}