#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<std::string> &logs, StatementSyntax *statement,
    SyntaxToken<std::any> *endOfFileToken) {
  this->statement = statement;
  this->endOfFileToken = endOfFileToken;
  this->logs = logs;
}

SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

StatementSyntax *CompilationUnitSyntax::getStatement() {
  return this->statement;
}

SyntaxToken<std::any> *CompilationUnitSyntax::getEndOfFileToken() {
  return this->endOfFileToken;
}
