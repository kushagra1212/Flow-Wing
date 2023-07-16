#pragma once
#include "../../Common.h"
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  ExpressionSyntax *left;
  SyntaxToken<std::any> *operatorToken;
  ExpressionSyntax *right;

public:
  AssignmentExpressionSyntax(ExpressionSyntax *left,
                             SyntaxToken<std::any> *operatorToken,
                             ExpressionSyntax *right);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  SyntaxToken<std::any> *getOperatorToken();

public:
  ExpressionSyntax *getRight();

public:
  ExpressionSyntax *getLeft();
};
