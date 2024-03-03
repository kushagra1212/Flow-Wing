#include "TypeExpressionSyntax.h"

TypeExpressionSyntax::TypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : _type(std::move(type)) {}

const SyntaxKindUtils::SyntaxKind TypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::PrimitiveTypeExpression;
}

const std::vector<SyntaxNode *> &TypeExpressionSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_type.get());
  }

  return _children;
}

const DiagnosticUtils::SourceLocation TypeExpressionSyntax::getSourceLocation()
    const {
  return {};
}