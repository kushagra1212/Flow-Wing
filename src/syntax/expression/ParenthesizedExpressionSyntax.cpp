#include "ParenthesizedExpressionSyntax.h"
class ParenthesizedExpressionSyntax : public ExpressionSyntax {
private:
  SyntaxToken *openParenthesisToken;
  ExpressionSyntax *expression;
  SyntaxToken *closeParenthesisToken;

public:
  std::vector<SyntaxNode *> children;

  ParenthesizedExpressionSyntax(SyntaxToken *openParenthesisToken,
                                ExpressionSyntax *expression,
                                SyntaxToken *closeParenthesisToken) {
    this->openParenthesisToken = openParenthesisToken;
    this->expression = expression;
    this->closeParenthesisToken = closeParenthesisToken;
    children.push_back(this->openParenthesisToken);
    children.push_back(this->expression);
    children.push_back(this->closeParenthesisToken);
  }

public:
  SyntaxKindUtils::SyntaxKind getKind() {
    return SyntaxKindUtils::SyntaxKind::ParenthesizedExpression;
  }

public:
  SyntaxToken *getOpenParenthesisToken() { return this->openParenthesisToken; }

public:
  ExpressionSyntax *getExpression() { return this->expression; }

public:
  SyntaxToken *getCloseParenthesisToken() {
    return this->closeParenthesisToken;
  }

public:
  std::vector<SyntaxNode *> getChildren() { return children; }
};