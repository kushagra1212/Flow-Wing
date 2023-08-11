#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    const std::string &lineAndColumn, std::vector<BoundStatement *> statements,
    bool global) {
  this->statements = statements;
  this->global = global;
  this->_lineAndColumn = lineAndColumn;
}
BoundBlockStatement::BoundBlockStatement(
    const std::string &lineAndColumn,
    std::vector<BoundStatement *> statements) {
  BoundBlockStatement(lineAndColumn, statements, false);
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

std::string BoundBlockStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}

BoundBlockStatement::~BoundBlockStatement() {
  for (auto statement : statements) {
    if (statement != nullptr) {
      delete statement;
      statement = nullptr;
    }
  }
  statements.clear();
}
