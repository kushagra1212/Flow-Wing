#include "GlobalStatementSyntax.h"

GlobalStatementSyntax::GlobalStatementSyntax(
    std::unique_ptr<StatementSyntax> statement) {
  this->_statement = std::move(statement);

  _children.push_back(_statement.get());
}

std::unique_ptr<StatementSyntax> GlobalStatementSyntax::getStatement() {
  return std::move(_statement);
}

SyntaxKindUtils::SyntaxKind GlobalStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::GlobalStatement;
}

std::vector<SyntaxNode *> GlobalStatementSyntax::getChildren() {
  return this->_children;
}

std::string GlobalStatementSyntax::getLineNumberAndColumn() {
  return _statement->getLineNumberAndColumn();
}

std::unique_ptr<StatementSyntax> &GlobalStatementSyntax::getStatementPtr() {
  return _statement;
}