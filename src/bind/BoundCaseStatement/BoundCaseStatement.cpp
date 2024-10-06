#include "BoundCaseStatement.h"

BoundCaseStatement::BoundCaseStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundCaseStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundCaseStatement;
}

std::vector<BoundNode *> BoundCaseStatement::getChildren() {
  if (_children.empty()) {
    if (_caseExpression)
      _children.emplace_back(_caseExpression.get());

    if (_bodyStatement)
      _children.emplace_back(_bodyStatement.get());
  }

  return _children;
}
