#pragma once
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ExpressionStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<ExpressionSyntax> _expression;

 public:
  ExpressionStatementSyntax(std::unique_ptr<ExpressionSyntax> expression);

  std::unique_ptr<ExpressionSyntax> getExpression();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<ExpressionSyntax> &getExpressionPtr();
};