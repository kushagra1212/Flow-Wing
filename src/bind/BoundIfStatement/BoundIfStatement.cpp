#include "BoundIfStatement.h"

BoundIfStatement::BoundIfStatement(const std::string &lineAndColumn,
                                   BoundExpression *condition,
                                   BoundStatement *thenStatement,
                                   BoundStatement *elseStatement)
    : _condition(condition), _thenStatement(thenStatement),
      _elseStatement(elseStatement) {
  this->_lineAndColumn = lineAndColumn;
}

BinderKindUtils::BoundNodeKind BoundIfStatement::getKind() {

  return BinderKindUtils::BoundNodeKind::IfStatement;
}

BoundExpression *BoundIfStatement::getCondition() const { return _condition; }

BoundStatement *BoundIfStatement::getThenStatement() const {
  return _thenStatement;
}

BoundStatement *BoundIfStatement::getElseStatement() const {
  return _elseStatement;
}

std::string BoundIfStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

std::vector<BoundNode *> BoundIfStatement::getChildren() {
  std::vector<BoundNode *> children;
  children.push_back(_condition);
  children.push_back(_thenStatement);
  children.push_back(_elseStatement);
  return children;
}
BoundIfStatement::~BoundIfStatement() {
  if (_condition != nullptr) {
    delete _condition;
    _condition = nullptr;
  }

  if (_thenStatement != nullptr) {
    delete _thenStatement;
    _thenStatement = nullptr;
  }

  if (_elseStatement != nullptr) {
    delete _elseStatement;
    _elseStatement = nullptr;
  }
}
