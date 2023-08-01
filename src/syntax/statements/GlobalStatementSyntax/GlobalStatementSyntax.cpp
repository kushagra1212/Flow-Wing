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

GlobalStatementSyntax::~GlobalStatementSyntax() { delete _statement; }
