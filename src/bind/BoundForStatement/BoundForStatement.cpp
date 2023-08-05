#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(BoundStatement *initialization,

                                     BoundExpression *upperBound,
                                     BoundStatement *statement)
    : initialization((initialization)), upperBound(upperBound),
      statement((statement)) {}

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

std::vector<BoundNode *> BoundForStatement::getChildren() {
  std::vector<BoundNode *> children;
  children.push_back(initialization);
  children.push_back(statement);
  children.push_back(upperBound);
  return children;
}

BoundForStatement::~BoundForStatement() {
  delete initialization;
  delete statement;
  delete upperBound;
}
