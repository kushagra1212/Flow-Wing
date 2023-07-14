#include "CompilationUnitSyntax.h"

CompilationUnitSyntax::CompilationUnitSyntax(std::vector<std::string> &logs,
                                             ExpressionSyntax *expression,
                                             SyntaxToken *endOfFileToken) {
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

SyntaxToken *CompilationUnitSyntax::getEndOfFileToken() {
  return this->endOfFileToken;
}
