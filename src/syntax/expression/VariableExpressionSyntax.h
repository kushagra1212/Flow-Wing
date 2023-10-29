#pragma once
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class VariableExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;

public:
  VariableExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  std::unique_ptr<LiteralExpressionSyntax<std::any>> getIdentifier();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getIdentifierPtr();
};
