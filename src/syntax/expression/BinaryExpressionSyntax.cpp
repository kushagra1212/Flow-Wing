#include "../SyntaxToken.cpp"
#include "ExpressionSyntax.h"

class BinaryExpressionSyntax : public ExpressionSyntax {

private:
  ExpressionSyntax *left;
  SyntaxToken *operatorToken;
  ExpressionSyntax *right;

public:
  std::vector<SyntaxNode *> children;
  BinaryExpressionSyntax(ExpressionSyntax *left, SyntaxToken *operatorToken,
                         ExpressionSyntax *right) {
    this->left = left;
    this->operatorToken = operatorToken;
    this->right = right;
    children.push_back(this->left);
    children.push_back(this->operatorToken);
    children.push_back(this->right);
  }

public:
  SyntaxKindUtils::SyntaxKind getKind() {
    return SyntaxKindUtils::BinaryExpression;
  }

public:
  ExpressionSyntax *getLeft() { return this->left; }

public:
  SyntaxToken *getOperatorToken() { return this->operatorToken; }

public:
  ExpressionSyntax *getRight() { return this->right; }

public:
  std::vector<SyntaxNode *> getChildren() { return children; }
};