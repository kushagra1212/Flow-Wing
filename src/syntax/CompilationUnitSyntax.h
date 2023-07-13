#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
class CompilationUnitSyntax {
private:
  ExpressionSyntax *expression;
  SyntaxToken *endOfFileToken;

public:
  std::vector<std::string> logs;
  CompilationUnitSyntax(std::vector<std::string> &logs,
                        ExpressionSyntax *expression,
                        SyntaxToken *endOfFileToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  ExpressionSyntax *getExpression();

public:
  SyntaxToken *getEndOfFileToken();
};
#endif