#include "ObjectTypeExpressionSyntax.h"

ObjectTypeExpressionSyntax::ObjectTypeExpressionSyntax(Utils::type type)
    : TypeExpressionSyntax(type) {}

SyntaxKindUtils::SyntaxKind ObjectTypeExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ObjectTypeExpression;
}

std::vector<SyntaxNode *> ObjectTypeExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;
  _children.push_back(_objectTypeIdentifier.get());
  return _children;
}
