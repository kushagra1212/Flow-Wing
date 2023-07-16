#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
class CompilationUnitSyntax {
private:
  ExpressionSyntax *expression;
  SyntaxToken<std::any> *endOfFileToken;

public:
  std::vector<std::string> logs;
  CompilationUnitSyntax(std::vector<std::string> &logs,
                        ExpressionSyntax *expression,
                        SyntaxToken<std::any> *endOfFileToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  ExpressionSyntax *getExpression();

public:
  SyntaxToken<std::any> *getEndOfFileToken();
};
#endif