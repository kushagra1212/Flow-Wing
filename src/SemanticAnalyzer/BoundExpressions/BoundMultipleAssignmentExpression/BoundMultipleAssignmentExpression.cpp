#include "BoundMultipleAssignmentExpression.h"

BoundMultipleAssignmentExpression::BoundMultipleAssignmentExpression(
    const DiagnosticUtils::SourceLocation &location)
    : BoundExpression(location) {}

BinderKindUtils::BoundNodeKind
BoundMultipleAssignmentExpression::getKind() const {
  return BinderKindUtils::BoundNodeKind::BoundMultipleAssignmentExpression;
}

std::vector<BoundNode *> BoundMultipleAssignmentExpression::getChildren() {
  if (_children.empty()) {
    for (auto &assignment : _assignmentList) {
      _children.push_back(assignment.get());
    }
  }

  return _children;
}