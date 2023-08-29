#include "BoundOrIfStatement.h"

BoundOrIfStatement::BoundOrIfStatement(
    const DiagnosticUtils::SourceLocation &location,
    std::unique_ptr<BoundExpression> condition,
    std::unique_ptr<BoundStatement> thenStatement)
    : BoundSourceLocation(location) {
  this->_condition = std::move(condition);
  this->_thenStatement = std::move(thenStatement);

  this->_children.push_back(this->_condition.get());
  this->_children.push_back(this->_thenStatement.get());
}

std::unique_ptr<BoundExpression> BoundOrIfStatement::getCondition() {
  return std::move(_condition);
}

std::unique_ptr<BoundStatement> BoundOrIfStatement::getThenStatement() {
  return std::move(_thenStatement);
}

BinderKindUtils::BoundNodeKind BoundOrIfStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::OrIfStatement;
}
std::vector<BoundNode *> BoundOrIfStatement::getChildren() {
  return this->_children;
}

std::unique_ptr<BoundExpression> &BoundOrIfStatement::getConditionPtr() {
  return this->_condition;
}
std::unique_ptr<BoundStatement> &BoundOrIfStatement::getThenStatementPtr() {
  return this->_thenStatement;
}