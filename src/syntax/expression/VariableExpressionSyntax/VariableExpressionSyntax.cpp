#include "VariableExpressionSyntax.h"

VariableExpressionSyntax::VariableExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression,
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
    if (_variableTypeExpr)
      _children.push_back(_variableTypeExpr.get());

    if (_moduleNameorCallExpression)
      _children.push_back(_moduleNameorCallExpression.get());

    if (_newKeyword) {
      _children.push_back(_newKeyword.get());
    }

    if (_selfKeyword)
      _children.push_back(_selfKeyword.get());

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
  if (_identifierExpression)
    return _identifierExpression->getSourceLocation();
  if (_variableTypeExpr)
    return _variableTypeExpr->getSourceLocation();

  if (_moduleNameorCallExpression)
    return _moduleNameorCallExpression->getSourceLocation();

  if (_newKeyword) {
    return _newKeyword->getSourceLocation();
  }

  if (_selfKeyword)
    return _selfKeyword->getSourceLocation();

  if (_dotExpressionList.size()) {
    for (const auto &item : _dotExpressionList) {
      return item->getSourceLocation();
    }
  }

  return DiagnosticUtils::SourceLocation();
}
