#include "EmptyStatementSyntax.h"

EmptyStatementSyntax::EmptyStatementSyntax() {}

SyntaxKindUtils::SyntaxKind EmptyStatementSyntax::getKind() const {
  return SyntaxKindUtils::EmptyStatement;
}

std::vector<SyntaxNode *> EmptyStatementSyntax::getChildren() { return {}; }

DiagnosticUtils::SourceLocation
EmptyStatementSyntax::getSourceLocation() const {
  return DiagnosticUtils::SourceLocation();
}