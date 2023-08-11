#include "ContinueStatementSyntax.h"

ContinueStatementSyntax::ContinueStatementSyntax(
    SyntaxToken<std::any> *continueKeyword)
    : _continueKeyword(continueKeyword) {}

ContinueStatementSyntax::~ContinueStatementSyntax() {
  if (_continueKeyword != nullptr) {
    delete _continueKeyword;
    _continueKeyword = nullptr;
  }
}

SyntaxToken<std::any> *ContinueStatementSyntax::getContinueKeyword() const {
  return _continueKeyword;
}

std::vector<SyntaxNode *> ContinueStatementSyntax::getChildren() {
  return {_continueKeyword};
}

SyntaxKindUtils::SyntaxKind ContinueStatementSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::ContinueKeyword;
}

std::string ContinueStatementSyntax::getLineNumberAndColumn() const {
  return _continueKeyword->getLineNumberAndColumn();
}
