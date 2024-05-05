#include "ClassStatementSyntax.h"

ClassStatementSyntax::ClassStatementSyntax() {}
const SyntaxKindUtils::SyntaxKind ClassStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ClassStatement;
}

const std::vector<SyntaxNode *> &ClassStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children
    if (_classKeyword)
      _children.push_back(_classKeyword.get());

    if (_classNameIdentifier)
      _children.push_back(_classNameIdentifier.get());
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
  if (_classKeyword)
    return _classKeyword->getSourceLocation();

  if (_classNameIdentifier)
    return _classNameIdentifier->getSourceLocation();

  for (const auto &m : _classDataMembers) {
    return m->getSourceLocation();
  }

  for (const auto &m : _classMemberFunctions) {
    return m->getSourceLocation();
  }
  return DiagnosticUtils::SourceLocation();
}
