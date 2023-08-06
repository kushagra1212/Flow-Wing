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

std::vector<BoundNode *> BoundWhileStatement::getChildren() {
  std::vector<BoundNode *> children;
  children.push_back(_condition);
  children.push_back(_body);
  return children;
}
BoundWhileStatement::~BoundWhileStatement() {
  if (_condition != nullptr) {
    delete _condition;
    _condition = nullptr;
  }

  if (_body != nullptr) {
    delete _body;
    _body = nullptr;
  }
}
