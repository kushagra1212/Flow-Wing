#include "BoundContinueStatement.h"

BoundContinueStatement::BoundContinueStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundContinueStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ContinueStatement;
}

std::vector<BoundNode *> BoundContinueStatement::getChildren() {
  return this->_children;
}
