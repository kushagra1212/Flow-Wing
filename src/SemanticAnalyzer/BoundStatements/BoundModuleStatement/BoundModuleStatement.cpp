#include "BoundModuleStatement.h"

BoundModuleStatement::BoundModuleStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundModuleStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundModuleStatement;
}

std::vector<BoundNode *> BoundModuleStatement::getChildren() {
  if (this->_children.empty()) {

    for (auto &m : _customTypeStatements) {
      _children.push_back(m.get());
    }

    for (auto &m : _variableDeclarationStatements) {
      _children.push_back(m.get());
    }
    for (auto &m : _functionStatements) {
      _children.push_back(m.get());
    }

    for (auto &m : _classStatements) {
      _children.push_back(m.get());
    }
  }
  return this->_children;
}
