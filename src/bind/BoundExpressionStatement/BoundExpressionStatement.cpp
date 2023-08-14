#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> expression) {

  this->_expression = expression;
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundExpressionStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ExpressionStatement;
}

std::shared_ptr<BoundExpression> BoundExpressionStatement::getExpression() {
  return _expression;
}

std::vector<std::shared_ptr<BoundNode>>
BoundExpressionStatement::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{_expression};
}

std::string BoundExpressionStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
