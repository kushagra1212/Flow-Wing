#include "EmptyStatementSyntax.h"

EmptyStatementSyntax::EmptyStatementSyntax() {}

const SyntaxKindUtils::SyntaxKind EmptyStatementSyntax::getKind() const {
  return SyntaxKindUtils::EmptyStatement;
}

const std::vector<SyntaxNode *> &EmptyStatementSyntax::getChildren() {
  return _children;
}

const DiagnosticUtils::SourceLocation EmptyStatementSyntax::getSourceLocation()
    const {
  return DiagnosticUtils::SourceLocation();
}