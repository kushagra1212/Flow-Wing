#include "BoundTypeExpression.h"

BoundTypeExpression::BoundTypeExpression(
    const DiagnosticUtils::SourceLocation &location, Utils::type type)
    : BoundExpression(location), _type(type) {}

const std::type_info &BoundTypeExpression::getType() {
  return typeid(Utils::type);
}

BinderKindUtils::BoundNodeKind BoundTypeExpression::getKind() const {
  return BinderKindUtils::BoundTypeExpression;
}

std::vector<BoundNode *> BoundTypeExpression::getChildren() { return {}; }
