#include "BoundObjectTypeExpression.h"

BoundObjectTypeExpression::BoundObjectTypeExpression(
    const DiagnosticUtils::SourceLocation &location,
    const SyntaxKindUtils::SyntaxKind &type)
    : BoundTypeExpression(location, type), _typeName("") {}

std::vector<BoundNode *> BoundObjectTypeExpression::getChildren() {
  if (this->_children.empty()) {
    this->_children.push_back(this->_objectTypeIdentifier.get());
  }

  return this->_children;
}

BinderKindUtils::BoundNodeKind BoundObjectTypeExpression::getKind() const {
  return BinderKindUtils::BoundObjectTypeExpression;
}