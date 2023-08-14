#include "GlobalStatementSyntax.h"

GlobalStatementSyntax::GlobalStatementSyntax(
    std::shared_ptr<StatementSyntax> statement) {
  _statement = statement;
}

std::shared_ptr<StatementSyntax> GlobalStatementSyntax::getStatement() const {
  return _statement;
}

SyntaxKindUtils::SyntaxKind GlobalStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::GlobalStatement;
}

std::vector<std::shared_ptr<SyntaxNode>> GlobalStatementSyntax::getChildren() {
  std::vector<std::shared_ptr<SyntaxNode>> children = {_statement};
  return children;
}

std::string GlobalStatementSyntax::getLineNumberAndColumn() const {
  return _statement->getLineNumberAndColumn();
}
