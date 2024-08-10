#include "BoundMultipleVariableDeclaration.h"

BoundMultipleVariableDeclaration::BoundMultipleVariableDeclaration(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind
BoundMultipleVariableDeclaration::getKind() const {
  return BinderKindUtils::BoundNodeKind::
      BoundMultipleVariableDeclarationStatement;
}

std::vector<BoundNode *> BoundMultipleVariableDeclaration::getChildren() {
  if (_children.size() > 0) {
    return _children;
  }

  for (const auto &variableDeclaration : _variableDeclarationList) {
    _children.push_back(variableDeclaration.get());
  }

  return _children;
}
