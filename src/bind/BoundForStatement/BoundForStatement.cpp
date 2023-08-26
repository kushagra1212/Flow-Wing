#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(
    std::string lineAndColumn, std::unique_ptr<BoundStatement> initialization,
    std::unique_ptr<BoundExpression> upperBound,
    std::unique_ptr<BoundExpression> boundStepExpression,
    std::unique_ptr<BoundStatement> statement) {
  this->_lineAndColumn = lineAndColumn;
  this->_initialization = std::move(initialization);
  this->_upperBound = std::move(upperBound);
  this->_boundStepExpression = std::move(boundStepExpression);
  this->_statement = std::move(statement);

  this->_children.push_back(this->_initialization.get());
  this->_children.push_back(this->_upperBound.get());

  if (this->_boundStepExpression != nullptr)
    this->_children.push_back(this->_boundStepExpression.get());
  this->_children.push_back(this->_statement.get());
}

std::unique_ptr<BoundStatement> BoundForStatement::getInitialization() {

  return std::move(this->_initialization);
}

std::unique_ptr<BoundStatement> BoundForStatement::getStatement() {

  return std::move(this->_statement);
}

std::unique_ptr<BoundExpression> BoundForStatement::getUpperBound() {

  return std::move(this->_upperBound);
}

std::unique_ptr<BoundExpression> BoundForStatement::getStepExpression() {

  return std::move(this->_boundStepExpression);
}
BinderKindUtils::BoundNodeKind BoundForStatement::getKind() const {

  return BinderKindUtils::BoundNodeKind::ForStatement;
}

std::string BoundForStatement::getLineNumberAndColumn() {
  return this->_lineAndColumn;
}

std::vector<BoundNode *> BoundForStatement::getChildren() {

  return this->_children;
}

std::unique_ptr<BoundStatement> &BoundForStatement::getInitializationPtr() {
  return this->_initialization;
}

std::unique_ptr<BoundStatement> &BoundForStatement::getStatementPtr() {
  return this->_statement;
}

std::unique_ptr<BoundExpression> &BoundForStatement::getUpperBoundPtr() {
  return this->_upperBound;
}

std::unique_ptr<BoundExpression> &BoundForStatement::getStepExpressionPtr() {
  return this->_boundStepExpression;
}