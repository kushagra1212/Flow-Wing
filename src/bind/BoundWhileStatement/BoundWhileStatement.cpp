#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(

    const std::string &lineAndColumn, BoundExpression *condition,
    BoundStatement *body)
    : _condition(condition), _body(body) {
  this->_lineAndColumn = lineAndColumn;
}

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

std::string BoundWhileStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
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
