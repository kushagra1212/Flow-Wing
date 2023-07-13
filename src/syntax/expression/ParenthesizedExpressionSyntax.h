#ifndef PARENTHESIZEDEXPRESSIONSYNTAX_H
#define PARENTHESIZEDEXPRESSIONSYNTAX_H
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  SyntaxToken *openParenthesisToken;
  ExpressionSyntax *expression;
  SyntaxToken *closeParenthesisToken;

public:
  std::vector<SyntaxNode *> children;

  ParenthesizedExpressionSyntax(SyntaxToken *openParenthesisToken,
                                ExpressionSyntax *expression,
                                SyntaxToken *closeParenthesisToken);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  SyntaxToken *getOpenParenthesisToken();

public:
  ExpressionSyntax *getExpression();

public:
  SyntaxToken *getCloseParenthesisToken();

public:
  std::vector<SyntaxNode *> getChildren();
};
#endif