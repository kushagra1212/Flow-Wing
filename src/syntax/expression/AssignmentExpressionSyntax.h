#pragma once
#include "../../Common.h"
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  SyntaxToken *identifierToken;
  SyntaxToken *operatorToken;
  ExpressionSyntax *right;

public:
  AssignmentExpressionSyntax(SyntaxToken *identifierToken,
                             SyntaxToken *operatorToken,
                             ExpressionSyntax *right);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  SyntaxToken *getIdentifierToken();

public:
  SyntaxToken *getOperatorToken();

public:
  ExpressionSyntax *getRight();
};
