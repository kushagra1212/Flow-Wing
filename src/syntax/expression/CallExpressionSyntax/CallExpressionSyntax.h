#ifndef CALL_EXPRESSION_SYNTAX_H
#define CALL_EXPRESSION_SYNTAX_H

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class CallExpressionSyntax : public ExpressionSyntax {
private:
  std::shared_ptr<LiteralExpressionSyntax<std::any>> _identifier;
  std::shared_ptr<SyntaxToken<std::any>> _openParenthesisToken;
  std::vector<std::shared_ptr<ExpressionSyntax>> _arguments;
  std::shared_ptr<SyntaxToken<std::any>> _closeParenthesisToken;

public:
  CallExpressionSyntax(
      std::shared_ptr<LiteralExpressionSyntax<std::any>> identifier,
      std::shared_ptr<SyntaxToken<std::any>> openParenthesisToken,
      std::vector<std::shared_ptr<ExpressionSyntax>> arguments,
      std::shared_ptr<SyntaxToken<std::any>> closeParenthesisToken);

  std::shared_ptr<LiteralExpressionSyntax<std::any>> getIdentifier() const;
  std::shared_ptr<SyntaxToken<std::any>> getOpenParenthesisToken() const;
  std::vector<std::shared_ptr<ExpressionSyntax>> getArguments() const;
  std::shared_ptr<SyntaxToken<std::any>> getCloseParenthesisToken() const;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // CALL_EXPRESSION_SYNTAX_H
