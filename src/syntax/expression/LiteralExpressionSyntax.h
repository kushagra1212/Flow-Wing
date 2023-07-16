#pragma once
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include <any>
#include <string>

template <typename T> class LiteralExpressionSyntax : public ExpressionSyntax {

private:
  SyntaxToken<std::any> *token;
  T value;

public:
  LiteralExpressionSyntax(SyntaxToken<std::any> *token, T value);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::string getKindText();

public:
  SyntaxToken<std::any> *getToken();

public:
  std::vector<SyntaxNode *> getChildren();

public:
  T getValue();
};