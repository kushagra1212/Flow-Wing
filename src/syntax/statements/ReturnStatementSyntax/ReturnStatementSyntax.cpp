#include "ReturnStatementSyntax.h"

ReturnStatementSyntax::ReturnStatementSyntax(
    std::unique_ptr<SyntaxToken<std::any>> returnKeyword)
    : _returnKeyword(std::move(returnKeyword)) {}

const std::vector<SyntaxNode *> &ReturnStatementSyntax::getChildren() {
  if (_children.empty()) {
    // Add children

    if (_returnKeyword)
      _children.push_back(_returnKeyword.get());

    for (const auto &expression : _expressionList) {
      _children.push_back(expression.get());
    }
  }

  return this->_children;
}

const SyntaxKindUtils::SyntaxKind ReturnStatementSyntax::getKind() const {
  return SyntaxKindUtils::SyntaxKind::ReturnStatement;
}

const DiagnosticUtils::SourceLocation
ReturnStatementSyntax::getSourceLocation() const {
  if (_returnKeyword)
    return _returnKeyword->getSourceLocation();

  for (const auto &expression : _expressionList) {
    return expression->getSourceLocation();
  }

  return DiagnosticUtils::SourceLocation();
}
