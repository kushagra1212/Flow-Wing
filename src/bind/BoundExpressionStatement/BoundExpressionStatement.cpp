#include "BoundExpressionStatement.h"

BoundExpressionStatement::BoundExpressionStatement(
    BoundExpression *expression) {
  this->expression = expression;
}

BinderKindUtils::BoundNodeKind BoundExpressionStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::ExpressionStatement;
}

BoundExpression *BoundExpressionStatement::getExpression() {
  return expression;
}

std::vector<BoundNode *> BoundExpressionStatement::getChildren() {
  return std::vector<BoundNode *>{expression};
}

BoundExpressionStatement::~BoundExpressionStatement() { delete expression; }