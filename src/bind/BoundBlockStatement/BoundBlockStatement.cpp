#include "BoundBlockStatement.h"
BoundBlockStatement::BoundBlockStatement(
    const std::string &lineAndColumn,
    std::vector<std::shared_ptr<BoundStatement>> statements, bool global) {
  this->_statements = statements;
  this->_global = global;
  this->_lineAndColumn = lineAndColumn;
}
BoundBlockStatement::BoundBlockStatement(
    const std::string &lineAndColumn,
    std::vector<std::shared_ptr<BoundStatement>> statements) {
  BoundBlockStatement(lineAndColumn, statements, false);
}
BinderKindUtils::BoundNodeKind BoundBlockStatement::getKind() {
  return BinderKindUtils::BoundNodeKind::BlockStatement;
}

std::vector<std::shared_ptr<BoundStatement>>
BoundBlockStatement::getStatements() {
  return _statements;
}

bool BoundBlockStatement::getGlobal() const { return this->_global; }

std::vector<std::shared_ptr<BoundNode>> BoundBlockStatement::getChildren() {
  std::vector<std::shared_ptr<BoundNode>> children;
  for (std::shared_ptr<BoundNode> statement : _statements) {
    children.push_back(statement);
  }
  return children;
}

std::string BoundBlockStatement::getLineNumberAndColumn() const {
  return this->_lineAndColumn;
}
