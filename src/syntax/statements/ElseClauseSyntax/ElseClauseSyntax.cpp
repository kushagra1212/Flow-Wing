#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(
    std::shared_ptr<SyntaxToken<std::any>> elseKeyword,
    std::shared_ptr<BlockStatementSyntax> statement)
    : _elseKeyword(elseKeyword), _statement(statement) {}

std::shared_ptr<SyntaxToken<std::any>>
ElseClauseSyntax::getElseKeyword() const {

  return _elseKeyword;
}

std::shared_ptr<BlockStatementSyntax> ElseClauseSyntax::getStatement() const {
  return _statement;
}

SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

std::vector<std::shared_ptr<SyntaxNode>> ElseClauseSyntax::getChildren() {
  return {_elseKeyword, _statement};
}

std::string ElseClauseSyntax::getLineNumberAndColumn() const {
  return _elseKeyword->getLineNumberAndColumn();
}
