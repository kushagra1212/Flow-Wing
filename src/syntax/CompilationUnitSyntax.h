#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
#include "statements/StatementSyntax.h"
class CompilationUnitSyntax {
private:
  StatementSyntax *statement;
  SyntaxToken<std::any> *endOfFileToken;

public:
  std::vector<std::string> logs;
  CompilationUnitSyntax(std::vector<std::string> &logs,
                        StatementSyntax *statement,
                        SyntaxToken<std::any> *endOfFileToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  StatementSyntax *getStatement();

public:
  SyntaxToken<std::any> *getEndOfFileToken();
};
#endif