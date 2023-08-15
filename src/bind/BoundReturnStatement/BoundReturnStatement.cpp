#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> expression) {
  this->_lineAndColumn = lineAndColumn;
  this->_expression = std::move(expression);

  this->_children.push_back(this->_expression.get());
}

std::unique_ptr<BoundExpression> BoundReturnStatement::getReturnExpression() {
  return std::move(_expression);
}

std::string BoundReturnStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundReturnStatement::getKind() const {
  return BinderKindUtils::BoundNodeKind::ReturnStatement;
}
std::vector<BoundNode *> BoundReturnStatement::getChildren() {
  return this->_children;
}