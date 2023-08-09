#include "BoundReturnStatement.h"

BoundReturnStatement::BoundReturnStatement(BoundExpression *expression)
    : _expression(expression) {}

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

BoundExpression *BoundReturnStatement::getReturnExpression() const {
  return _expression;
}
