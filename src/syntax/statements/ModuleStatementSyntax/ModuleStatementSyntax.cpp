#include "ModuleStatementSyntax.h"

const SyntaxKindUtils::SyntaxKind ModuleStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ModuleStatement;
}

const DiagnosticUtils::SourceLocation
ModuleStatementSyntax::getSourceLocation() const {

  if (_moduleKeyword)
    return _moduleKeyword->getSourceLocation();

  if (_openBracketToken)
    return _openBracketToken->getSourceLocation();

  if (_moduleName)
    return _moduleName->getSourceLocation();

  if (_closeBracketToken)
    return _closeBracketToken->getSourceLocation();

  for (const auto &s : _statements) {
    return s->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}

const std::vector<SyntaxNode *> &ModuleStatementSyntax::getChildren() {
  if (_children.empty()) {

    //! BUG: Not Showing up as Chiild in lsp
    // if (_moduleKeyword)
    //   this->_children.push_back(_moduleKeyword.get());

    if (_openBracketToken)
      this->_children.push_back(_openBracketToken.get());

    if (_moduleName)
      this->_children.push_back(_moduleName.get());

    if (_closeBracketToken)
      this->_children.push_back(_closeBracketToken.get());

    for (const auto &s : _statements) {
      _children.push_back(s.get());
    }
  }

  return this->_children;
}