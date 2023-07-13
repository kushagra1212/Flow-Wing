#ifndef NUMBEREXPRESSIONSYNTAX_H
#define NUMBEREXPRESSIONSYNTAX_H
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class NumberExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken *numberToken;

public:
  std::vector<SyntaxNode *> children;
  NumberExpressionSyntax(SyntaxToken *numberToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::string getKindText();

public:
  SyntaxToken *getNumberToken();

public:
  std::vector<SyntaxNode *> getChildren();
};
#endif