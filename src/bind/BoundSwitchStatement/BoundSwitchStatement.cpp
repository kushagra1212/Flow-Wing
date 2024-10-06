#include "BoundSwitchStatement.h"

BoundSwitchStatement::BoundSwitchStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

/*
  Overrides
*/

BinderKindUtils::BoundNodeKind BoundSwitchStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundSwitchStatement;
}

std::vector<BoundNode *> BoundSwitchStatement::getChildren() {
  if (_children.empty()) {
    if (_switchExpression)
      _children.emplace_back(_switchExpression.get());

    for (auto &item : _boundCaseStatements) {
      _children.emplace_back(item.get());
    }

    if (_defaultCaseStatement)
      _children.emplace_back(_defaultCaseStatement.get());
  }

  return _children;
}
