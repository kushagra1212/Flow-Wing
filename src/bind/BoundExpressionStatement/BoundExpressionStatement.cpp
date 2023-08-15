#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> expression) {

  this->_expression = std::move(expression);
  this->_lineAndColumn = lineAndColumn;

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

std::string BoundExpressionStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
