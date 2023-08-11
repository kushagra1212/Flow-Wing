#include "GlobalStatementSyntax.h"

GlobalStatementSyntax::GlobalStatementSyntax(StatementSyntax *statement) {
  _statement = statement;
}

StatementSyntax *GlobalStatementSyntax::getStatement() const {
  return _statement;
}

SyntaxKindUtils::SyntaxKind GlobalStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::GlobalStatement;
}

std::vector<SyntaxNode *> GlobalStatementSyntax::getChildren() {
  std::vector<SyntaxNode *> children = {};
  children.push_back(_statement);
  return children;
}

std::string GlobalStatementSyntax::getLineNumberAndColumn() const {
  return _statement->getLineNumberAndColumn();
}

GlobalStatementSyntax::~GlobalStatementSyntax() {
  if (_statement != nullptr) {
    delete _statement;
    _statement = nullptr;
  }
}
