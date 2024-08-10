#include "MultipleAssignmentExpressionSyntax.h"

MultipleAssignmentExpressionSyntax::MultipleAssignmentExpressionSyntax() {}

const SyntaxKindUtils::SyntaxKind
MultipleAssignmentExpressionSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::MultipleAssignmentExpression;
}

const std::vector<SyntaxNode *> &
MultipleAssignmentExpressionSyntax::getChildren() {
  if (_children.size() > 0)
    return _children;

  for (const auto &assignmentExpr : _assignmentExprList) {
    _children.push_back(assignmentExpr.get());
  }
  return _children;
}

const DiagnosticUtils::SourceLocation
MultipleAssignmentExpressionSyntax::getSourceLocation() const {
  for (const auto &assignmentExpr : _assignmentExprList) {
    return assignmentExpr->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}