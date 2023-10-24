
#ifndef MEMBER_SYNTAX_H
#define MEMBER_SYNTAX_H
#include "SyntaxNode.h"
class MemberSyntax : public SyntaxNode {
  bool isExposed = false;

public:
  MemberSyntax(const bool &isExposed) : isExposed(isExposed) {}

  bool getIsExposed() const { return isExposed; }
};

#endif // MEMBER_SYNTAX_H