#include "BreakStatementSyntax.h"

BreakStatementSyntax::BreakStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> breakKeyword)
    : _breakKeyword(breakKeyword) {}

std::shared_ptr<SyntaxToken<std::any>>
BreakStatementSyntax::getBreakKeyword() const {
  return _breakKeyword;
}

std::vector<std::shared_ptr<SyntaxNode>> BreakStatementSyntax::getChildren() {
  return {_breakKeyword};
}

SyntaxKindUtils::SyntaxKind BreakStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BreakKeyword;
}

std::string BreakStatementSyntax::getLineNumberAndColumn() const {
  return _breakKeyword->getLineNumberAndColumn();
}
