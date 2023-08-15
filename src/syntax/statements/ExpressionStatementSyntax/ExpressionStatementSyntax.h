#pragma once
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _expression;

public:
  ExpressionStatementSyntax(std::unique_ptr<ExpressionSyntax> expression);

  std::unique_ptr<ExpressionSyntax> getExpression();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};