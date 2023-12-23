#ifndef INDEXEXPRESSIONSYNTAX_H
#define INDEXEXPRESSIONSYNTAX_H
#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class IndexExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::unique_ptr<ExpressionSyntax> _indexExpression;

public:
  IndexExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression,
      std::unique_ptr<ExpressionSyntax> indexExpression);

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &
  getIndexIdentifierExpressionPtr();
  std::unique_ptr<ExpressionSyntax> &getIndexEpressionPtr();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;
};

#endif // INDEXEXPRESSIONSYNTAX_H
