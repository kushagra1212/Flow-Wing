#include "ClassStatementSyntax.h"

ClassStatementSyntax::ClassStatementSyntax() {}
const SyntaxKindUtils::SyntaxKind ClassStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ClassStatement;
}

const std::vector<SyntaxNode *> &ClassStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    if (_exposeKeyword)
      _children.push_back(_exposeKeyword.get());

    if (_classKeyword)
      _children.push_back(_classKeyword.get());

    if (_classNameIdentifier)
      _children.push_back(_classNameIdentifier.get());

    if (_extendsKeyword)
      _children.push_back(_extendsKeyword.get());

    if (_parentClassNameIdentifier)
      _children.push_back(_parentClassNameIdentifier.get());

    for (const auto &type : _customTypeStatements) {
      _children.push_back(type.get());
    }

    for (const auto &m : _classDataMembers) {
      _children.push_back(m.get());
    }
    for (const auto &m : _classMemberFunctions) {
      _children.push_back(m.get());
    }
  }

  return this->_children;
}

const DiagnosticUtils::SourceLocation
ClassStatementSyntax::getSourceLocation() const {

  if (_exposeKeyword)
    return _exposeKeyword->getSourceLocation();

  if (_classKeyword)
    return _classKeyword->getSourceLocation();

  if (_classNameIdentifier)
    return _classNameIdentifier->getSourceLocation();

  if (_extendsKeyword)
    return _extendsKeyword->getSourceLocation();

  if (_parentClassNameIdentifier)
    return _parentClassNameIdentifier->getSourceLocation();

  for (const auto &m : _customTypeStatements) {
    return m->getSourceLocation();
  }

  for (const auto &m : _classDataMembers) {
    return m->getSourceLocation();
  }

  for (const auto &m : _classMemberFunctions) {
    return m->getSourceLocation();
  }
  return DiagnosticUtils::SourceLocation();
}
