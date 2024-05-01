#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<ExpressionSyntax> identifierExpression,
    const bool isConstant,
    std::unique_ptr<TypeExpressionSyntax> variableTypeExpr)
    : _identifierExpression(std::move(identifierExpression)),
      _variableTypeExpr(std::move(variableTypeExpr)), _isConstant(isConstant) {}

const SyntaxKindUtils::SyntaxKind VariableExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::VariableExpressionSyntax;
}

const std::vector<SyntaxNode *> &VariableExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_identifierExpression.get());
    _children.push_back(_variableTypeExpr.get());

    if (_dotExpressionList.size()) {
      for (const auto &item : _dotExpressionList) {
        _children.push_back(item.get());
      }
    }
  }
  return _children;
}

const DiagnosticUtils::SourceLocation
VariableExpressionSyntax::getSourceLocation() const {
  return _identifierExpression->getSourceLocation();
}
