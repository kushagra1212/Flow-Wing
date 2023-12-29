#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifierExpression,
    const bool isConstant, const Utils::type &variableType)
    : _identifierExpression(std::move(identifierExpression)),
      _variableType(variableType), _isConstant(isConstant) {}

SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax;
}

std::vector<SyntaxNode *> VariableExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_identifierExpression.get());
  }
  return _children;
}

DiagnosticUtils::SourceLocation
VariableExpressionSyntax::getSourceLocation() const {
  return _identifierExpression->getSourceLocation();
}
