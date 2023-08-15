#include "BoundWhileStatement.h"

BoundWhileStatement::BoundWhileStatement(

    std::string lineAndColumn, std::unique_ptr<BoundExpression> condition,
    std::unique_ptr<BoundStatement> body)
    : _condition(std::move(condition)), _body(std::move(body)) {
  this->_lineAndColumn = lineAndColumn;

  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_body.get());
}

std::unique_ptr<BoundExpression> BoundWhileStatement::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BoundStatement> BoundWhileStatement::getBody() {
  return std::move(_body);
}

BinderKindUtils::BoundNodeKind BoundWhileStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::WhileStatement;
}

std::vector<BoundNode *> BoundWhileStatement::getChildren() {
  return this->_children;
}

std::string BoundWhileStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}
