#pragma once
#include "ExpressionSyntax.h"
class VariableExpressionSyntax : public ExpressionSyntax {
private:
  ExpressionSyntax *identifierExpression;

public:
  VariableExpressionSyntax(ExpressionSyntax *identifierExpression);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  ExpressionSyntax *getIdentifier();

public:
  std::vector<SyntaxNode *> getChildren();
};
