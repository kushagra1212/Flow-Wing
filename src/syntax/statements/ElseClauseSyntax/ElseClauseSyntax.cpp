#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(SyntaxToken<std::any> *elseKeyword,
                                   BlockStatementSyntax *statement)
    : elseKeyword(elseKeyword), statement(statement) {}

SyntaxToken<std::any> *ElseClauseSyntax::getElseKeyword() const {

  return elseKeyword;
}

BlockStatementSyntax *ElseClauseSyntax::getStatement() const {
  return statement;
}

SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

std::vector<SyntaxNode *> ElseClauseSyntax::getChildren() {
  return {elseKeyword, (SyntaxNode *)statement};
}

std::string ElseClauseSyntax::getLineNumberAndColumn() const {
  return elseKeyword->getLineNumberAndColumn();
}

ElseClauseSyntax::~ElseClauseSyntax() {
  if (elseKeyword != nullptr) {
    delete elseKeyword;
    elseKeyword = nullptr;
  }

  if (statement != nullptr) {
    delete statement;
    statement = nullptr;
  }
}
