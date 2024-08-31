#include "MultipleVariableDeclarationSyntax.h"

MultipleVariableDeclarationSyntax::MultipleVariableDeclarationSyntax() {}

const SyntaxKindUtils::SyntaxKind
MultipleVariableDeclarationSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::MultipleVariableDeclaration;
}
const std::vector<SyntaxNode *> &
MultipleVariableDeclarationSyntax::getChildren() {
  if (_children.empty()) {
    for (const auto &item : _variableDeclarationList) {
      _children.push_back(item.get());
    }
  }

  return _children;
}
const DiagnosticUtils::SourceLocation
MultipleVariableDeclarationSyntax::getSourceLocation() const {
  for (const auto &item : _variableDeclarationList)
    return item->getSourceLocation();

  return DiagnosticUtils::SourceLocation();
}