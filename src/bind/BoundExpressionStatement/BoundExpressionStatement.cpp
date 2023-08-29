#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> expression)
    : BoundSourceLocation(location) {

  this->_expression = std::move(expression);

  // Add children

  this->_children.push_back(this->_expression.get());
}

std::unique_ptr<BoundExpression> BoundExpressionStatement::getExpression() {
  return std::move(_expression);
}

BinderKindUtils::BoundNodeKind BoundExpressionStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ExpressionStatement;
}

std::vector<BoundNode *> BoundExpressionStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundExpressionStatement::getExpressionPtr() {
  return this->_expression;
}