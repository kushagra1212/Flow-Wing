#include "ObjectExpressionSyntax.h"

SyntaxKindUtils::SyntaxKind ObjectExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectExpression;
}
std::vector<SyntaxNode *> ObjectExpressionSyntax::getChildren() {

  if (_children.empty()) {
    for (auto &attribute : _attributes) {
      _children.push_back(attribute.get());
    }
  }

  return _children;
}
DiagnosticUtils::SourceLocation
ObjectExpressionSyntax::getSourceLocation() const {
  if (_attributes.size() > 0)
    return _attributes[0]->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}