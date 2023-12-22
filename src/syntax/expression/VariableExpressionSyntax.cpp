
#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression) {
  this->_identifierExpression = std::move(identifierExpression);

  // Add children
  this->_children.push_back(this->_identifierExpression.get());
}

std::unique_ptr<LiteralExpressionSyntax<std::any>>
VariableExpressionSyntax::getIdentifier() {
  return std::move(this->_identifierExpression);
}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableExpression;
}

std::vector<SyntaxNode *> VariableExpressionSyntax::getChildren() {

  return this->_children;
}

DiagnosticUtils::SourceLocation
VariableExpressionSyntax::getSourceLocation() const {
  return this->_identifierExpression->getSourceLocation();
}

std::unique_ptr<LiteralExpressionSyntax<std::any>> &
VariableExpressionSyntax::getIdentifierPtr() {
  return this->_identifierExpression;
}