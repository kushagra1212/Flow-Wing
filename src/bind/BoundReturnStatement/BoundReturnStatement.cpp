#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> expression)
    : BoundSourceLocation(location) {
  this->_expression = std::move(expression);

  this->_children.push_back(this->_expression.get());
}

std::unique_ptr<BoundExpression> BoundReturnStatement::getReturnExpression() {
  return std::move(_expression);
}

BinderKindUtils::BoundNodeKind BoundReturnStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ReturnStatement;
}
std::vector<BoundNode *> BoundReturnStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &
BoundReturnStatement::getReturnExpressionPtr() {
  return this->_expression;
}