#include "BoundIfStatement.h"

BoundIfStatement::BoundIfStatement(
    const std::string &lineAndColumn,
    std::shared_ptr<BoundExpression> condition,
    std::shared_ptr<BoundStatement> thenStatement,
    std::shared_ptr<BoundStatement> elseStatement)
    : _condition(condition), _thenStatement(thenStatement),
      _elseStatement(elseStatement) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundIfStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::IfStatement;
}

std::shared_ptr<BoundExpression> BoundIfStatement::getCondition() const {
  return _condition;
}

std::shared_ptr<BoundStatement> BoundIfStatement::getThenStatement() const {
  return _thenStatement;
}

std::shared_ptr<BoundStatement> BoundIfStatement::getElseStatement() const {
  return _elseStatement;
}

std::string BoundIfStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::vector<std::shared_ptr<BoundNode>> BoundIfStatement::getChildren() {
  std::vector<std::shared_ptr<BoundNode>> children;
  children.push_back(_condition);
  children.push_back(_thenStatement);
  children.push_back(_elseStatement);
  return children;
}
