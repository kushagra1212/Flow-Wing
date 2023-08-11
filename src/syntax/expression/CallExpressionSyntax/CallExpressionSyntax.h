#ifndef CALL_EXPRESSION_SYNTAX_H
#define CALL_EXPRESSION_SYNTAX_H

#include "../../SyntaxKindUtils.h"
#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../ExpressionSyntax.h"
#include "../LiteralExpressionSyntax.h"

class CallExpressionSyntax : public ExpressionSyntax {
public:
  CallExpressionSyntax(LiteralExpressionSyntax<std::any> *identifier,
                       SyntaxToken<std::any> *openParenthesisToken,
                       std::vector<ExpressionSyntax *> arguments,
                       SyntaxToken<std::any> *closeParenthesisToken);

  ~CallExpressionSyntax();

  LiteralExpressionSyntax<std::any> *getIdentifier() const;
  SyntaxToken<std::any> *getOpenParenthesisToken() const;
  std::vector<ExpressionSyntax *> getArguments() const;
  SyntaxToken<std::any> *getCloseParenthesisToken() const;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() const override;

private:
  LiteralExpressionSyntax<std::any> *_identifier;
  SyntaxToken<std::any> *_openParenthesisToken;
  std::vector<ExpressionSyntax *> _arguments;
  SyntaxToken<std::any> *_closeParenthesisToken;
};

#endif // CALL_EXPRESSION_SYNTAX_H
