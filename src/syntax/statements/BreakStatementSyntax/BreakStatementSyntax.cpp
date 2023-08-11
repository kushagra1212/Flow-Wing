#include "BreakStatementSyntax.h"

BreakStatementSyntax::BreakStatementSyntax(SyntaxToken<std::any> *breakKeyword)
    : _breakKeyword(breakKeyword) {}

BreakStatementSyntax::~BreakStatementSyntax() {
  if (_breakKeyword != nullptr) {
    delete _breakKeyword;
    _breakKeyword = nullptr;
  }
}

SyntaxToken<std::any> *BreakStatementSyntax::getBreakKeyword() const {
  return _breakKeyword;
}

std::vector<SyntaxNode *> BreakStatementSyntax::getChildren() {
  return {_breakKeyword};
}

SyntaxKindUtils::SyntaxKind BreakStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BreakKeyword;
}

std::string BreakStatementSyntax::getLineNumberAndColumn() const {
  return _breakKeyword->getLineNumberAndColumn();
}
