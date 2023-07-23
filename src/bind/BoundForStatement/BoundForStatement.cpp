#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(
    BoundVariableDeclaration *variableDeclaration,

    BoundExpression *upperBound, BoundStatement *statement)
    : variableDeclaration((variableDeclaration)), upperBound(upperBound),
      statement((statement)) {}

BoundVariableDeclaration *BoundForStatement::getVariableDeclaration() const {

  return this->variableDeclaration;
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
