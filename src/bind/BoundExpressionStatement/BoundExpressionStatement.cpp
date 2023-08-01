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

BoundExpressionStatement::~BoundExpressionStatement() { delete expression; }