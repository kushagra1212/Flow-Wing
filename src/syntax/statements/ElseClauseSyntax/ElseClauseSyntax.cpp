#include "ElseClauseSyntax.h"

ElseClauseSyntax::ElseClauseSyntax(
    std::unique_ptr<SyntaxToken<std::any>> elseKeyword,
    std::unique_ptr<BlockStatementSyntax> statement) {
  this->_elseKeyword = std::move(elseKeyword);
  this->_statement = std::move(statement);
}

std::unique_ptr<SyntaxToken<std::any>> ElseClauseSyntax::getElseKeyword() {
  return std::move(_elseKeyword);
}

std::unique_ptr<BlockStatementSyntax> ElseClauseSyntax::getStatement() {
  return std::move(_statement);
}

const SyntaxKindUtils::SyntaxKind ElseClauseSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ElseClause;
}

const std::vector<SyntaxNode *> &ElseClauseSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    _children.push_back(_elseKeyword.get());
    _children.push_back(_statement.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ElseClauseSyntax::getSourceLocation() const {
  return this->_elseKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &ElseClauseSyntax::getElseKeywordRef() {
  return this->_elseKeyword;
}
std::unique_ptr<BlockStatementSyntax> &ElseClauseSyntax::getStatementRef() {
  return this->_statement;
}
