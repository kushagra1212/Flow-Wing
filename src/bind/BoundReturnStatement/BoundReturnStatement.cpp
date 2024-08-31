#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

BinderKindUtils::BoundNodeKind BoundReturnStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ReturnStatement;
}
std::vector<BoundNode *> BoundReturnStatement::getChildren() {
  if (this->_children.empty()) {
    for (auto &expr : this->_returnExpressionList) {
      this->_children.push_back(expr.get());
    }
  }

  return this->_children;
}
