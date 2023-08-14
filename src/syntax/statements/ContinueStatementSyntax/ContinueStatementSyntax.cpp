#include "ContinueStatementSyntax.h"

ContinueStatementSyntax::ContinueStatementSyntax(
    std::shared_ptr<SyntaxToken<std::any>> continueKeyword)
    : _continueKeyword(continueKeyword) {}

std::shared_ptr<SyntaxToken<std::any>>
ContinueStatementSyntax::getContinueKeyword() const {
  return _continueKeyword;
}

std::vector<std::shared_ptr<SyntaxNode>>
ContinueStatementSyntax::getChildren() {
  return {_continueKeyword};
}

SyntaxKindUtils::SyntaxKind ContinueStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ContinueKeyword;
}

std::string ContinueStatementSyntax::getLineNumberAndColumn() const {
  return _continueKeyword->getLineNumberAndColumn();
}
