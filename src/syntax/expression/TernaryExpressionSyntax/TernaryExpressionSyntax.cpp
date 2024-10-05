
#include "TernaryExpressionSyntax.h"

const SyntaxKindUtils::SyntaxKind TernaryExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::TernaryExpression;
}

const std::vector<SyntaxNode *> &TernaryExpressionSyntax::getChildren() {
  if (_children.empty()) {
    if (_conditionExpression)
      _children.emplace_back(_conditionExpression.get());

    if (_questionToken)
      _children.emplace_back(_questionToken.get());

    if (_trueExpression)
      _children.emplace_back(_trueExpression.get());

    if (_colonToken)
      _children.emplace_back(_colonToken.get());

    if (_falseExpression)
      _children.emplace_back(_falseExpression.get());
  }
  return _children;
}

const DiagnosticUtils::SourceLocation
TernaryExpressionSyntax::getSourceLocation() const {
  if (_conditionExpression)
    return _conditionExpression->getSourceLocation();

  if (_questionToken)
    return _questionToken->getSourceLocation();

  if (_trueExpression)
    return _trueExpression->getSourceLocation();

  if (_colonToken)
    return _colonToken->getSourceLocation();

  if (_falseExpression)
    return _falseExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
