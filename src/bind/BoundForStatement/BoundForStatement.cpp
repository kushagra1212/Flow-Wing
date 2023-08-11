#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(const std::string &lineAndColumn,
                                     BoundStatement *initialization,

                                     BoundExpression *upperBound,
                                     BoundStatement *statement)
    : initialization((initialization)), upperBound(upperBound),
      statement((statement)) {
  this->_lineAndColumn = lineAndColumn;
}

BoundStatement *BoundForStatement::getInitialization() const {

  return this->initialization;
}

BoundStatement *BoundForStatement::getStatement() const {

  return this->statement;
}

BinderKindUtils::BoundNodeKind BoundForStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::ForStatement;
}

BoundExpression *BoundForStatement::getUpperBound() const {

  return this->upperBound;
}

std::string BoundForStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::vector<BoundNode *> BoundForStatement::getChildren() {
  std::vector<BoundNode *> children;
  children.push_back(initialization);
  children.push_back(statement);
  children.push_back(upperBound);
  return children;
}

BoundForStatement::~BoundForStatement() {
  if (initialization != nullptr) {
    delete initialization;
    initialization = nullptr;
  }

  if (statement != nullptr) {
    delete statement;
    statement = nullptr;
  }

  if (upperBound != nullptr) {
    delete upperBound;
    upperBound = nullptr;
  }
}
