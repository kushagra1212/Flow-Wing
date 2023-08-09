#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement() {}

BoundContinueStatement::~BoundContinueStatement() = default;

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<BoundNode *> BoundContinueStatement::getChildren() {
  return std::vector<BoundNode *>{};
}
