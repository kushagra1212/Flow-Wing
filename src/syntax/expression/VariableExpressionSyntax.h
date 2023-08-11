#pragma once
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class VariableExpressionSyntax : public ExpressionSyntax {
private:
  LiteralExpressionSyntax<std::any> *identifierExpression;

public:
  VariableExpressionSyntax(
      LiteralExpressionSyntax<std::any> *identifierExpression);

  ~VariableExpressionSyntax();

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  LiteralExpressionSyntax<std::any> *getIdentifier();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  std::string getLineNumberAndColumn() const override;
};
