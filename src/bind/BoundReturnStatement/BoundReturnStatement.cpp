#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> expression)
    : _expression(expression) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundReturnStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ReturnStatement;
}

std::vector<std::shared_ptr<BoundNode>> BoundReturnStatement::getChildren() {
  return std::vector<std::shared_ptr<BoundNode>>{_expression};
}

std::string BoundReturnStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::shared_ptr<BoundExpression>
BoundReturnStatement::getReturnExpression() const {
  return _expression;
}
