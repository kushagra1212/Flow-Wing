#ifndef INDEXEXPRESSIONSYNTAX_H
#define INDEXEXPRESSIONSYNTAX_H
#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../VariableExpressionSyntax.h"

class IndexExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<VariableExpressionSyntax> _identifierExpression;
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _indexExpression;

public:
  IndexExpressionSyntax(
      std::unique_ptr<VariableExpressionSyntax> identifierExpression,
      std::unique_ptr<LiteralExpressionSyntax<std::any>> indexExpression);

  std::unique_ptr<VariableExpressionSyntax> &getIndexIdentifierExpressionPtr();
  std::unique_ptr<LiteralExpressionSyntax<std::any>> &getIndexEpressionPtr();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;
};

#endif // INDEXEXPRESSIONSYNTAX_H
