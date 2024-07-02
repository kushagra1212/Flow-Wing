
#ifndef __SYNTAXNODE_H__
#define __SYNTAXNODE_H__
#include "../Common.h"
#include "../diagnostics/DiagnosticUtils/DiagnosticUtils.h"
#include "SyntaxKindUtils.h"
class SyntaxNode {
public:
  int lineNumber;
  int columnNumber;
  int length;
  std::string absoluteFilePath;
  std::vector<SyntaxNode *> _children;

  virtual ~SyntaxNode() = default;
  virtual const SyntaxKindUtils::SyntaxKind getKind() const = 0;

  virtual const std::vector<SyntaxNode *> &getChildren() = 0;

  virtual const DiagnosticUtils::SourceLocation getSourceLocation() const = 0;
};
#endif