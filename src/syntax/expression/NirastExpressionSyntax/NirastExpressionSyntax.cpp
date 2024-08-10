#include "NirastExpressionSyntax.h"

NirastExpressionSyntax::NirastExpressionSyntax(
    std::unique_ptr<LiteralExpressionSyntax<std::any>> nirastExpression)
    : _nirastExpression(std::move(nirastExpression)) {}

const SyntaxKindUtils::SyntaxKind NirastExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::NirastExpression;
}
const std::vector<SyntaxNode *> &NirastExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  if (_nirastExpression)
    _children.push_back(_nirastExpression.get());

  return _children;
}
const DiagnosticUtils::SourceLocation
NirastExpressionSyntax::getSourceLocation() const {

  if (_nirastExpression)
    return _nirastExpression->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}