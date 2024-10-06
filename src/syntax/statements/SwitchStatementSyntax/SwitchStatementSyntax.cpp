#include "SwitchStatementSyntax.h"

const std::vector<SyntaxNode *> &SwitchStatementSyntax::getChildren() {
  if (_children.empty()) {
    if (_switchToken)
      _children.emplace_back(_switchToken.get());

    if (_switchExpression)
      _children.emplace_back(_switchExpression.get());

    if (_openCurlyToken)
      _children.emplace_back(_openCurlyToken.get());

    for (const auto &caseStatement : _caseStatements)
      _children.emplace_back(caseStatement.get());

    if (_closeCurlyToken)
      _children.emplace_back(_closeCurlyToken.get());
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind SwitchStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::SwitchStatementSyntax;
}

const DiagnosticUtils::SourceLocation
SwitchStatementSyntax::getSourceLocation() const {
  if (_switchToken)
    return _switchToken->getSourceLocation();

  if (_switchExpression)
    return _switchExpression->getSourceLocation();

  if (_openCurlyToken)
    return _openCurlyToken->getSourceLocation();

  for (const auto &caseStatement : _caseStatements)
    return caseStatement->getSourceLocation();

  if (_closeCurlyToken)
    return _closeCurlyToken->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}
