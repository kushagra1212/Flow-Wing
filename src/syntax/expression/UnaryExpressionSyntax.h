#ifndef UnaryExpressionSyntax_h__
#define UnaryExpressionSyntax_h__

#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class UnaryExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken<std::any> *operatorToken;
  ExpressionSyntax *operand;

public:
  std::vector<SyntaxNode *> children;
  UnaryExpressionSyntax(SyntaxToken<std::any> *operatorToken,
                        ExpressionSyntax *operand);

  ~UnaryExpressionSyntax();

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  SyntaxToken<std::any> *getOperatorToken();

public:
  ExpressionSyntax *getOperand();

public:
  std::vector<SyntaxNode *> getChildren();
};

#endif // UnaryExpressionSyntax_h__