#pragma once
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"

template <typename T> class LiteralExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken *token;
  T value;

public:
  std::vector<SyntaxNode *> children;
  LiteralExpressionSyntax(SyntaxToken *token, T value);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::string getKindText();

public:
  SyntaxToken *getToken();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  T getValue();
};