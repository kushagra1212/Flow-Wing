#pragma once
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class VariableExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;

public:
  VariableExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  SyntaxKindUtils::SyntaxKind getKind();

  std::unique_ptr<LiteralExpressionSyntax<std::any>> getIdentifier();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};
