#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    std::vector<BoundStatement *> statements, bool global) {
  this->statements = statements;
  this->global = global;
}
BoundBlockStatement::BoundBlockStatement(
    std::vector<BoundStatement *> statements) {
  BoundBlockStatement(statements, false);
}
BinderKindUtils::BoundNodeKind BoundBlockStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BlockStatement;
}

std::vector<BoundStatement *> BoundBlockStatement::getStatements() {
  return statements;
}

bool BoundBlockStatement::getGlobal() const { return this->global; }

std::vector<BoundNode *> BoundBlockStatement::getChildren() {
  std::vector<BoundNode *> children;
  for (BoundNode *statement : statements) {
    children.push_back(statement);
  }
  return children;
}

BoundBlockStatement::~BoundBlockStatement() {
  for (auto statement : statements) {
    delete statement;
  }
}