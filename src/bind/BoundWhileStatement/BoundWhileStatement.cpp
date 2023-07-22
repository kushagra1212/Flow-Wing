#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(BoundExpression *condition,
                                         BoundStatement *body)
    : _condition(condition), _body(body) {}

BinderKindUtils::BoundNodeKind BoundWhileStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::WhileStatement;
}

BoundExpression *BoundWhileStatement::getCondition() const {
  return _condition;
}

BoundStatement *BoundWhileStatement::getBody() const { return _body; }
