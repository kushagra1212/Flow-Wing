#include "ContinueStatementSyntax.h"

ContinueStatementSyntax::ContinueStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> continueKeyword) {
  this->_continueKeyword = std::move(continueKeyword);

  // Add children
  _children.push_back(_continueKeyword.get());
}

std::unique_ptr<SyntaxToken<std::any>>
ContinueStatementSyntax::getContinueKeyword() {
  return std::move(_continueKeyword);
}

std::vector<SyntaxNode *> ContinueStatementSyntax::getChildren() {
  return this->_children;
}

SyntaxKindUtils::SyntaxKind ContinueStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContinueKeyword;
}

std::string ContinueStatementSyntax::getLineNumberAndColumn() {
  return _continueKeyword->getLineNumberAndColumn();
}

std::unique_ptr<SyntaxToken<std::any>> &
ContinueStatementSyntax::getContinueKeywordPtr() {
  return _continueKeyword;
}