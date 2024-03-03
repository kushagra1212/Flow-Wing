#include "ObjectExpressionSyntax.h"

const SyntaxKindUtils::SyntaxKind ObjectExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectExpression;
}
const std::vector<SyntaxNode *> &ObjectExpressionSyntax::getChildren() {
  if (_children.empty()) {
    for (auto &attribute : _attributes) {
      _children.push_back(attribute.get());
    }
  }

  return _children;
}
const DiagnosticUtils::SourceLocation
ObjectExpressionSyntax::getSourceLocation() const {
  if (_attributes.size() > 0) return _attributes[0]->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}