#ifndef _NIRASTEXPRESSIONSYNTAX_H
#define _NIRASTEXPRESSIONSYNTAX_H

#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class NirastExpressionSyntax : public ExpressionSyntax {

  std::unique_ptr<LiteralExpressionSyntax<std::any>> _nirastExpression;

public:
  NirastExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> nirastExpression);

  /*
    Overrides
  */

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Getters
  */

  inline auto getNirastExpressionRef() const
      -> const std::unique_ptr<LiteralExpressionSyntax<std::any>> & {
    return _nirastExpression;
  }
};

#endif