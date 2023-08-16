#pragma once
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {

public:
  std::unique_ptr<ExpressionSyntax> _expression;
  ExpressionStatementSyntax(std::unique_ptr<ExpressionSyntax> expression);

  std::unique_ptr<ExpressionSyntax> getExpression();

  std::unique_ptr<ExpressionSyntax> &getExpressionPtr();
  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};