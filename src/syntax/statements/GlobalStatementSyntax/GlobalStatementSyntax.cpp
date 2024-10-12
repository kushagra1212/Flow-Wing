#include "GlobalStatementSyntax.h"

GlobalStatementSyntax::GlobalStatementSyntax(
    std::unique_ptr<StatementSyntax> statement) {
  this->_statement = std::move(statement);
}

std::unique_ptr<StatementSyntax> GlobalStatementSyntax::getStatement() {
  return std::move(_statement);
}

const SyntaxKindUtils::SyntaxKind GlobalStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::GlobalStatement;
}

const std::vector<SyntaxNode *> &GlobalStatementSyntax::getChildren() {
  if (_children.empty()) {
    _children.push_back(_statement.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
GlobalStatementSyntax::getSourceLocation() const {
  return _statement->getSourceLocation();
}

std::unique_ptr<StatementSyntax> &GlobalStatementSyntax::getStatementPtr() {
  return _statement;
}