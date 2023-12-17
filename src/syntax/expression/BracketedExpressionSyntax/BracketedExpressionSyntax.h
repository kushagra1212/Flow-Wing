#ifndef __FLOWWING_BRACKETED_EXPRESSION_SYNTAX_H__
#define __FLOWWING_BRACKETED_EXPRESSION_SYNTAX_H__
#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"

class BracketedExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<ExpressionSyntax> _expression;

public:
  // Overrides
  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  // Setters
  auto setExpression(std::unique_ptr<ExpressionSyntax> expression) -> void;

  // Getters
  auto getExpressionRef() const -> const std::unique_ptr<ExpressionSyntax> &;
};

#endif // __FLOWWING_BRACKETED_EXPRESSION_SYNTAX_H__
