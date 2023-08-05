#include "BoundIfStatement.h"

BoundIfStatement::BoundIfStatement(BoundExpression *condition,
                                   BoundStatement *thenStatement,
                                   BoundStatement *elseStatement)
    : _condition(condition), _thenStatement(thenStatement),
      _elseStatement(elseStatement) {}

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

std::vector<BoundNode *> BoundIfStatement::getChildren() {
  std::vector<BoundNode *> children;
  children.push_back(_condition);
  children.push_back(_thenStatement);
  children.push_back(_elseStatement);
  return children;
}

BoundIfStatement::~BoundIfStatement() {
  delete _condition;
  delete _thenStatement;
  delete _elseStatement;
}
