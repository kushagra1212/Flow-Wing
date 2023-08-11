#pragma once
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {
private:
  ExpressionSyntax *expression;

public:
  ExpressionStatementSyntax(ExpressionSyntax *expression);

  ~ExpressionStatementSyntax();

  SyntaxKindUtils::SyntaxKind getKind();

  std::vector<SyntaxNode *> getChildren();

  ExpressionSyntax *getExpression();

  std::string getLineNumberAndColumn() const override;
};