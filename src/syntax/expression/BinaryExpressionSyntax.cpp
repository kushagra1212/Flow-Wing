#include "BinaryExpressionSyntax.h"

BinaryExpressionSyntax::BinaryExpressionSyntax(
    ExpressionSyntax *left, SyntaxToken<std::any> *operatorToken,
    ExpressionSyntax *right) {
  this->left = left;
  this->operatorToken = operatorToken;
  this->right = right;
  children.push_back(this->left);
  children.push_back(this->operatorToken);
  children.push_back(this->right);
}

SyntaxKindUtils::SyntaxKind BinaryExpressionSyntax::getKind() {
  return SyntaxKindUtils::SyntaxKind::BinaryExpression;
}

ExpressionSyntax *BinaryExpressionSyntax::getLeft() { return this->left; }

SyntaxToken<std::any> *BinaryExpressionSyntax::getOperatorToken() {
  return this->operatorToken;
}

ExpressionSyntax *BinaryExpressionSyntax::getRight() { return this->right; }

std::vector<SyntaxNode *> BinaryExpressionSyntax::getChildren() {
  return children;
}

std::string BinaryExpressionSyntax::getLineNumberAndColumn() const {
  return this->left->getLineNumberAndColumn();
}

BinaryExpressionSyntax::~BinaryExpressionSyntax() {
  if (this->left != nullptr) {
    delete this->left;
    this->left = nullptr;
  }

  if (this->operatorToken != nullptr) {
    delete this->operatorToken;
    this->operatorToken = nullptr;
  }

  if (this->right != nullptr) {
    delete this->right;
    this->right = nullptr;
  }
}
