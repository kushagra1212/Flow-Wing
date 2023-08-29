#include "BoundBreakStatement.h"

BoundBreakStatement::BoundBreakStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundBreakStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BreakStatement;
}

std::vector<BoundNode *> BoundBreakStatement::getChildren() {
  return this->_children;
}