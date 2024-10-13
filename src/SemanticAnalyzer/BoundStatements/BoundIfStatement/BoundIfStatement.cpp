#include "BoundIfStatement.h"

BoundIfStatement::BoundIfStatement(
    const DiagnosticUtils::SourceLocation &location)
    : BoundSourceLocation(location) {}

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

std::vector<BoundNode *> BoundIfStatement::getChildren() {
  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_thenStatement.get());

  for (auto &orIfStatement : this->_orIfStatements) {
    this->_children.push_back(orIfStatement.get());
  }

  if (this->_elseStatement.get())
    this->_children.push_back(this->_elseStatement.get());

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

std::vector<std::unique_ptr<BoundOrIfStatement>> &
BoundIfStatement::getOrIfStatementsPtr() {
  return this->_orIfStatements;
}

void BoundIfStatement::addCondition(
    std::unique_ptr<BoundExpression> condition) {
  this->_condition = std::move(condition);
}

void BoundIfStatement::addThenStatement(
    std::unique_ptr<BoundStatement> thenStatement) {
  this->_thenStatement = std::move(thenStatement);
}

void BoundIfStatement::addOrIfStatement(
    std::unique_ptr<BoundOrIfStatement> orIfStatement) {
  this->_orIfStatements.push_back(std::move(orIfStatement));
}
void BoundIfStatement::addElseStatement(
    std::unique_ptr<BoundStatement> elseStatement) {
  this->_elseStatement = std::move(elseStatement);
}
