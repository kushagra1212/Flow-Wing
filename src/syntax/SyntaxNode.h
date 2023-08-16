
#ifndef __SYNTAXNODE_H__
#define __SYNTAXNODE_H__
#include "../Common.h"
#include "SyntaxKindUtils.h"
class SyntaxNode;
class SyntaxNode {

public:
  int lineNumber;
  int position;

  std::vector<SyntaxNode *> _children;

  virtual SyntaxKindUtils::SyntaxKind getKind() const = 0;

  virtual std::vector<SyntaxNode *> getChildren() = 0;

  virtual std::string getLineNumberAndColumn() = 0;
};
#endif