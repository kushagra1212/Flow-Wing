#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifierExpression,
    const bool isConstant,
    std::unique_ptr<TypeExpressionSyntax> variableTypeExpr)
    : _identifierExpression(std::move(identifierExpression)),
      _variableTypeExpr(std::move(variableTypeExpr)), _isConstant(isConstant) {}

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
