#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(
    std::unique_ptr<SyntaxToken<std::any>> elseKeyword,
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->_elseKeyword = std::move(elseKeyword);
  this->_statement = std::move(statement);

  // Add children

  _children.push_back(_elseKeyword.get());
  _children.push_back(_statement.get());
}

std::unique_ptr<SyntaxToken<std::any>> ElseClauseSyntax::getElseKeyword() {

  return std::move(_elseKeyword);
}

std::unique_ptr<BlockStatementSyntax> ElseClauseSyntax::getStatement() {
  return std::move(_statement);
}

SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

std::vector<SyntaxNode *> ElseClauseSyntax::getChildren() {
  return this->_children;
}

std::string ElseClauseSyntax::getLineNumberAndColumn() {
  return _elseKeyword->getLineNumberAndColumn();
}
