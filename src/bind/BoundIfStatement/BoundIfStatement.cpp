#include "BoundIfStatement.h"

BoundIfStatement::BoundIfStatement(
    std::string lineAndColumn, std::unique_ptr<BoundExpression> condition,
    std::unique_ptr<BoundStatement> thenStatement,
    std::unique_ptr<BoundStatement> elseStatement) {
  this->_lineAndColumn = lineAndColumn;
  this->_condition = std::move(condition);
  this->_thenStatement = std::move(thenStatement);
  this->_elseStatement = std::move(elseStatement);

  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_thenStatement.get());
  this->_children.push_back(this->_elseStatement.get());
}

std::unique_ptr<BoundExpression> BoundIfStatement::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BoundStatement> BoundIfStatement::getThenStatement() {
  return std::move(_thenStatement);
}

std::unique_ptr<BoundStatement> BoundIfStatement::getElseStatement() {
  return std::move(_elseStatement);
}
BinderKindUtils::BoundNodeKind BoundIfStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::IfStatement;
}

std::string BoundIfStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

std::vector<BoundNode *> BoundIfStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundIfStatement::getConditionPtr() {
  return this->_condition;
}
std::unique_ptr<BoundStatement> &BoundIfStatement::getThenStatementPtr() {
  return this->_thenStatement;
}
std::unique_ptr<BoundStatement> &BoundIfStatement::getElseStatementPtr() {
  return this->_elseStatement;
}