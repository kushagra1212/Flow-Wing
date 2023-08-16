#pragma once
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include <any>
#include <string>

template <typename T> class LiteralExpressionSyntax : public ExpressionSyntax {

private:
  std::unique_ptr<SyntaxToken<std::any>> _token;
  T _value;

public:
  LiteralExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> token,
                          T value);

  std::string getKindText();
  T getValue();

  std::unique_ptr<SyntaxToken<std::any>> getToken();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;

  std::unique_ptr<SyntaxToken<std::any>> &getTokenPtr();
};