
#ifndef __SYNTAXNODE_H__
#define __SYNTAXNODE_H__
#include "../Common.h"
#include "SyntaxKindUtils.h"
class SyntaxNode {

public:
  int lineNumber;
  int position;
  virtual SyntaxKindUtils::SyntaxKind getKind() = 0;

public:
  virtual std::vector<std::shared_ptr<SyntaxNode>> getChildren() = 0;

  virtual std::string getLineNumberAndColumn() const = 0;
};
#endif