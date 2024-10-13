#include "BoundTypeExpression.h"

BoundTypeExpression::BoundTypeExpression(
    const DiagnosticUtils::SourceLocation &location,
    const SyntaxKindUtils::SyntaxKind &type)
    : BoundExpression(location), _type(type) {}

const std::type_info &BoundTypeExpression::getType() { return typeid(_type); }

BinderKindUtils::BoundNodeKind BoundTypeExpression::getKind() const {
  return BinderKindUtils::BoundTypeExpression;
}

std::vector<BoundNode *> BoundTypeExpression::getChildren() { return {}; }
