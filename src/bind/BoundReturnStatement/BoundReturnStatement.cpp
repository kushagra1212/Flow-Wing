#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(const std::string &lineAndColumn,
                                           BoundExpression *expression)
    : _expression(expression) {
  this->_lineAndColumn = lineAndColumn;
}

BoundReturnStatement::~BoundReturnStatement() {
  if (_expression != nullptr) {
    delete _expression;
    _expression = nullptr;
  }
}

BinderKindUtils::BoundNodeKind BoundReturnStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ReturnStatement;
}

std::vector<BoundNode *> BoundReturnStatement::getChildren() {
  return std::vector<BoundNode *>{(BoundNode *)_expression};
}

std::string BoundReturnStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundExpression *BoundReturnStatement::getReturnExpression() const {
  return _expression;
}
