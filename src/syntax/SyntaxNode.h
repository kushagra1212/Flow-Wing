
#ifndef __SYNTAXNODE_H__
#define __SYNTAXNODE_H__
#include "SyntaxKindUtils.cpp"

class SyntaxNode {

public:
  virtual SyntaxKindUtils::SyntaxKind getKind() = 0;

public:
  virtual std::vector<SyntaxNode *> getChildren() = 0;
};
#endif