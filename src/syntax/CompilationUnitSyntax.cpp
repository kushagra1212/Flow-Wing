#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(
    std::vector<std::string> &logs, ExpressionSyntax *expression,
    SyntaxToken<std::any> *endOfFileToken) {
  this->expression = expression;
  this->endOfFileToken = endOfFileToken;
  this->logs = logs;
}

SyntaxKindUtils::SyntaxKind CompilationUnitSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::CompilationUnit;
}

ExpressionSyntax *CompilationUnitSyntax::getExpression() {
  return this->expression;
}

SyntaxToken<std::any> *CompilationUnitSyntax::getEndOfFileToken() {
  return this->endOfFileToken;
}
