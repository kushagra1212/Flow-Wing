#include "BreakStatementSyntax.h"

BreakStatementSyntax::BreakStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> breakKeyword) {
  this->_breakKeyword = std::move(breakKeyword);

  // Add children
  _children.push_back(_breakKeyword.get());
}

std::unique_ptr<SyntaxToken<std::any>> BreakStatementSyntax::getBreakKeyword() {
  return std::move(_breakKeyword);
}
SyntaxKindUtils::SyntaxKind BreakStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::BreakKeyword;
}

std::vector<SyntaxNode *> BreakStatementSyntax::getChildren() {
  return this->_children;
}

std::string BreakStatementSyntax::getLineNumberAndColumn() {
  return _breakKeyword->getLineNumberAndColumn();
}
