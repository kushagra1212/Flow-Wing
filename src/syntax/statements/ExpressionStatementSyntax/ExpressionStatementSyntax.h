#pragma once
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {
private:
  ExpressionSyntax *expression;

public:
  ExpressionStatementSyntax(ExpressionSyntax *expression);

  SyntaxKindUtils::SyntaxKind getKind();

  std::vector<SyntaxNode *> getChildren();

  ExpressionSyntax *getExpression();
};