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

  for (const auto &m : _customTypeStatements) {
    return m->getSourceLocation();
  }

  for (const auto &m : _variableStatements) {
    return m->getSourceLocation();
  }

  for (const auto &m : _functionStatements) {
    return m->getSourceLocation();
  }

  for (const auto &m : _classStatements) {
    return m->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}

const std::vector<SyntaxNode *> &ModuleStatementSyntax::getChildren() {
  if (_children.empty()) {
    if (_moduleKeyword)
      this->_children.push_back(_moduleKeyword.get());
    if (_openBracketToken)
      this->_children.push_back(_openBracketToken.get());
    if (_moduleName)
      this->_children.push_back(_moduleName.get());
    if (_closeBracketToken)
      this->_children.push_back(_closeBracketToken.get());

    for (const auto &type : _customTypeStatements) {
      _children.push_back(type.get());
    }

    for (const auto &c : _classStatements) {
      _children.push_back(c.get());
    }

    for (const auto &m : _variableStatements) {
      _children.push_back(m.get());
    }
    for (const auto &m : _functionStatements) {
      _children.push_back(m.get());
    }
  }

  return this->_children;
}