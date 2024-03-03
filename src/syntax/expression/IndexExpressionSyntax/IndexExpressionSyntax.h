#ifndef INDEXEXPRESSIONSYNTAX_H
#define INDEXEXPRESSIONSYNTAX_H
#include "../../../Common.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class IndexExpressionSyntax : public ExpressionSyntax {
 private:
  std::unique_ptr<LiteralExpressionSyntax<std::any>> _identifierExpression;
  std::vector<std::unique_ptr<ExpressionSyntax>> _indexExpressions;

 public:
  IndexExpressionSyntax(
      std::unique_ptr<LiteralExpressionSyntax<std::any>> identifierExpression);

  inline auto addIndexExpression(std::unique_ptr<ExpressionSyntax> item)
      -> void {
    this->_indexExpressions.push_back(std::move(item));
  }

  inline auto getIndexExpressionsRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return this->_indexExpressions;
  }

  std::unique_ptr<LiteralExpressionSyntax<std::any>> &
  getIndexIdentifierExpressionPtr();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;
};

#endif  // INDEXEXPRESSIONSYNTAX_H
