#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement() {}

BoundBreakStatement::~BoundBreakStatement() = default;

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<BoundNode *> BoundBreakStatement::getChildren() {
  return std::vector<BoundNode *>{};
}
