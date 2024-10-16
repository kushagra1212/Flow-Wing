#ifndef PARENTHESIZEDEXPRESSIONSYNTAX_H
#define PARENTHESIZEDEXPRESSIONSYNTAX_H
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::unique_ptr<ExpressionSyntax> _expression;
  std::unique_ptr<SyntaxToken<std::any>> _closeParenthesisToken;

public:
  ParenthesizedExpressionSyntax(
      std::unique_ptr<SyntaxToken<std::any>> openParenthesisToken,
      std::unique_ptr<ExpressionSyntax> expression,
      std::unique_ptr<SyntaxToken<std::any>> closeParenthesisToken);

  std::unique_ptr<SyntaxToken<std::any>> getOpenParenthesisToken();
  std::unique_ptr<ExpressionSyntax> getExpression();
  std::unique_ptr<SyntaxToken<std::any>> getCloseParenthesisToken();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOpenParenthesisTokenRef();
  std::unique_ptr<ExpressionSyntax> &getExpressionRef();
  std::unique_ptr<SyntaxToken<std::any>> &getCloseParenthesisTokenRef();
};
#endif