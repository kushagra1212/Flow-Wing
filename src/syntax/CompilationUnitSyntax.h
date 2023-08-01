#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "MemberSyntax.h"
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
#include "statements/StatementSyntax.h"
class CompilationUnitSyntax {
private:
  std::vector<MemberSyntax *> members;
  SyntaxToken<std::any> *endOfFileToken;

public:
  std::vector<std::string> logs;
  CompilationUnitSyntax(std::vector<std::string> &logs,
                        std::vector<MemberSyntax *> members,
                        SyntaxToken<std::any> *endOfFileToken);
  ~CompilationUnitSyntax();

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<MemberSyntax *> getMembers();

public:
  SyntaxToken<std::any> *getEndOfFileToken();
};
#endif