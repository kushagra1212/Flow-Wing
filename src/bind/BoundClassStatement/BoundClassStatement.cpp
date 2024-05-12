#include "BoundClassStatement.h"

BoundClassStatement::BoundClassStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundClassStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundClassStatement;
}

std::vector<BoundNode *> BoundClassStatement::getChildren() {
  if (this->_children.empty()) {

    for (auto &m : _customTypes) {
      _children.push_back(m.get());
    }

    for (auto &m : _memberVariables) {
      _children.push_back(m.get());
    }
    for (auto &m : _memberFunctions) {
      _children.push_back(m.get());
    }
  }
  return this->_children;
}
