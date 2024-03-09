#include "BreakStatementSyntax.h"

BreakStatementSyntax::BreakStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> breakKeyword) {
  this->_breakKeyword = std::move(breakKeyword);
}

std::unique_ptr<SyntaxToken<std::any>> BreakStatementSyntax::getBreakKeyword() {
  return std::move(_breakKeyword);
}
const SyntaxKindUtils::SyntaxKind BreakStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BreakStatement;
}

const std::vector<SyntaxNode *> &BreakStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    _children.push_back(_breakKeyword.get());
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
BreakStatementSyntax::getSourceLocation() const {
  return _breakKeyword->getSourceLocation();
}

std::unique_ptr<SyntaxToken<std::any>> &
BreakStatementSyntax::getBreakKeywordPtr() {
  return _breakKeyword;
}
