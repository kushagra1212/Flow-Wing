#include "BoundForStatement.h"

BoundForStatement::BoundForStatement(
    BoundVariableDeclaration *variableDeclaration,

    BoundLiteralExpression<std::any> *upperBound, BoundStatement *statement)
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

BoundLiteralExpression<std::any> *BoundForStatement::getUpperBound() const {

  return this->upperBound;
}
