#include "ObjectTypeExpressionSyntax.h"

ObjectTypeExpressionSyntax::ObjectTypeExpressionSyntax(
    std::unique_ptr<SyntaxToken<std::any>> type)
    : TypeExpressionSyntax(std::move(type)) {}

SyntaxKindUtils::SyntaxKind ObjectTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectTypeExpression;
}

std::vector<SyntaxNode *> ObjectTypeExpressionSyntax::getChildren() {
  if (_children.size() > 0) return _children;

  _children.push_back(this->getTypeRef().get());
  _children.push_back(_objectTypeIdentifier.get());
  return _children;
}

DiagnosticUtils::SourceLocation ObjectTypeExpressionSyntax::getSourceLocation()
    const {
  return this->_objectTypeIdentifier->getSourceLocation();
}