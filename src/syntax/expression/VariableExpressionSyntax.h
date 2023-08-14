#pragma once
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class VariableExpressionSyntax : public ExpressionSyntax {
private:
  std::shared_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;

public:
  VariableExpressionSyntax(
      std::shared_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::shared_ptr<LiteralExpressionSyntax<std::any>> getIdentifier();

public:
  std::vector<std::shared_ptr<SyntaxNode>> getChildren();

public:
  std::string getLineNumberAndColumn() const override;
};
