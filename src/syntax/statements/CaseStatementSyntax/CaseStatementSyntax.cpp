#include "CaseStatementSyntax.h"

const std::vector<SyntaxNode *> &CaseStatementSyntax::getChildren() {
  if (_children.empty()) {
    if (_caseToken)
      _children.emplace_back(_caseToken.get());

    if (_defaultToken)
      _children.emplace_back(_defaultToken.get());

    if (_caseExpression)
      _children.emplace_back(_caseExpression.get());

    if (_colonToken)
      _children.emplace_back(_colonToken.get());

    if (_blockStatement)
      _children.emplace_back(_blockStatement.get());
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind CaseStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::CaseStatementSyntax;
}

const DiagnosticUtils::SourceLocation
CaseStatementSyntax::getSourceLocation() const {

  if (_caseToken)
    return _caseToken->getSourceLocation();

  if (_defaultToken)
    return _defaultToken->getSourceLocation();

  if (_caseExpression)
    return _caseExpression->getSourceLocation();

  if (_colonToken)
    return _colonToken->getSourceLocation();

  if (_blockStatement)
    return _blockStatement->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
