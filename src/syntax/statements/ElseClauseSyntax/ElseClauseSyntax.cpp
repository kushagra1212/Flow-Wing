#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(SyntaxToken<std::any> *elseKeyword,
                                   StatementSyntax *statement)
    : elseKeyword(elseKeyword), statement(statement) {}

SyntaxToken<std::any> *ElseClauseSyntax::getElseKeyword() const {

  return elseKeyword;
}

StatementSyntax *ElseClauseSyntax::getStatement() const { return statement; }

SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

std::vector<SyntaxNode *> ElseClauseSyntax::getChildren() {
  return {elseKeyword, statement};
}
