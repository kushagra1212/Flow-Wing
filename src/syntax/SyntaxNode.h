
#ifndef __SYNTAXNODE_H__
#define __SYNTAXNODE_H__
#include "../Common.h"
#include "../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "SyntaxKindUtils.h"
class SyntaxNode {

public:
  int lineNumber;
  int columnNumber;

  std::vector<SyntaxNode *> _children;

  virtual SyntaxKindUtils::SyntaxKind getKind() const = 0;

  virtual std::vector<SyntaxNode *> getChildren() = 0;

  virtual DiagnosticUtils::SourceLocation getSourceLocation() const = 0;
};
#endif