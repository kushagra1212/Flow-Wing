#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundStatement> initialization,

    std::shared_ptr<BoundExpression> upperBound,
    std::shared_ptr<BoundStatement> statement)
    : _initialization((initialization)), _upperBound(upperBound),
      _statement((statement)) {
  this->_lineAndColumn = lineAndColumn;
}

std::shared_ptr<BoundStatement> BoundForStatement::getInitialization() const {

  return this->_initialization;
}

std::shared_ptr<BoundStatement> BoundForStatement::getStatement() const {

  return this->_statement;
}

BinderKindUtils::BoundNodeKind BoundForStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::ForStatement;
}

std::shared_ptr<BoundExpression> BoundForStatement::getUpperBound() const {

  return this->_upperBound;
}

std::string BoundForStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::vector<std::shared_ptr<BoundNode>> BoundForStatement::getChildren() {
  std::vector<std::shared_ptr<BoundNode>> children = {_initialization,
                                                      _statement, _upperBound};

  return children;
}
