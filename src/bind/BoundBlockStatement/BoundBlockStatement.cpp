#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    std::vector<BoundStatement *> statements) {
  this->statements = statements;
}

BinderKindUtils::BoundNodeKind BoundBlockStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BlockStatement;
}

std::vector<BoundStatement *> BoundBlockStatement::getStatements() {
  return statements;
}

BoundBlockStatement::~BoundBlockStatement() {
  for (auto statement : statements) {
    delete statement;
  }
}