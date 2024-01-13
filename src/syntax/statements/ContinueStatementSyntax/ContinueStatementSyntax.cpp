#include "ContinueStatementSyntax.h"

ContinueStatementSyntax::ContinueStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> continueKeyword) {
  this->_continueKeyword = std::move(continueKeyword);
}

std::unique_ptr<SyntaxToken<std::any>>
ContinueStatementSyntax::getContinueKeyword() {
  return std::move(_continueKeyword);
}

const std::vector<SyntaxNode *> &ContinueStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_continueKeyword.get());
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ContinueStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ContinueKeyword;
}

const DiagnosticUtils::SourceLocation
ContinueStatementSyntax::getSourceLocation() const {
  return _continueKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
ContinueStatementSyntax::getContinueKeywordPtr() {
  return _continueKeyword;
}