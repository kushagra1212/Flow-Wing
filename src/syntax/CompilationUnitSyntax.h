#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "MemberSyntax.h"
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
#include "statements/StatementSyntax.h"
class CompilationUnitSyntax {
private:
  std::vector<std::shared_ptr<MemberSyntax>> members;
  std::shared_ptr<SyntaxToken<std::any>> endOfFileToken;

public:
  CompilationUnitSyntax(std::vector<std::shared_ptr<MemberSyntax>> members,
                        std::shared_ptr<SyntaxToken<std::any>> endOfFileToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<std::shared_ptr<MemberSyntax>> getMembers();

public:
  std::shared_ptr<SyntaxToken<std::any>> getEndOfFileToken();

public:
  std::vector<std::shared_ptr<SyntaxNode>> getChildren();
};
#endif