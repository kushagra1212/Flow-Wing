#ifndef COMPILATION_UNIT_SYNTAX_H
#define COMPILATION_UNIT_SYNTAX_H
#include "MemberSyntax.h"
#include "SyntaxToken.h"
#include "expression/ExpressionSyntax.h"
#include "statements/StatementSyntax.h"
class CompilationUnitSyntax {
 private:
  std::vector<std::unique_ptr<MemberSyntax>> _members;
  std::unique_ptr<SyntaxToken<std::any>> _endOfFileToken = nullptr;
  std::vector<SyntaxNode *> _children;

 public:
  const SyntaxKindUtils::SyntaxKind getKind();

  std::vector<std::unique_ptr<MemberSyntax>> &getMembers();

  void addMember(std::unique_ptr<MemberSyntax> member);
  void setEndOfFileToken(std::unique_ptr<SyntaxToken<std::any>> endOfFileToken);

  const std::vector<SyntaxNode *> &getChildren();

  const std::unique_ptr<SyntaxToken<std::any>> &getEndOfFileTokenRef();
};
#endif