#pragma once
#include "../../Common.h"
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  LiteralExpressionSyntax<std::any> *left;
  SyntaxToken<std::any> *operatorToken;
  ExpressionSyntax *right;

public:
  AssignmentExpressionSyntax(LiteralExpressionSyntax<std::any> *left,
                             SyntaxToken<std::any> *operatorToken,
                             ExpressionSyntax *right);

  ~AssignmentExpressionSyntax();

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  SyntaxToken<std::any> *getOperatorToken();

public:
  ExpressionSyntax *getRight();

public:
  LiteralExpressionSyntax<std::any> *getLeft();

public:
  std::string getLineNumberAndColumn() const override;
};
