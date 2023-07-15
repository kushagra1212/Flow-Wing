#pragma once
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include <any>
#include <string>

template <typename T> class LiteralExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken *token;
  T value;

public:
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