#ifndef PARENTHESIZEDEXPRESSIONSYNTAX_H
#define PARENTHESIZEDEXPRESSIONSYNTAX_H
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  SyntaxToken<std::any> *openParenthesisToken;
  ExpressionSyntax *expression;
  SyntaxToken<std::any> *closeParenthesisToken;

public:
  std::vector<SyntaxNode *> children;

  ParenthesizedExpressionSyntax(SyntaxToken<std::any> *openParenthesisToken,
                                ExpressionSyntax *expression,
                                SyntaxToken<std::any> *closeParenthesisToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  SyntaxToken<std::any> *getOpenParenthesisToken();

public:
  ExpressionSyntax *getExpression();

public:
  SyntaxToken<std::any> *getCloseParenthesisToken();

public:
  std::vector<SyntaxNode *> getChildren();
};
#endif