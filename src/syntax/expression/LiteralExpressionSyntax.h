#pragma once
#include <any>
#include <string>

#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"

template <typename T>
class LiteralExpressionSyntax : public ExpressionSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _token;
  T _value;

 public:
  LiteralExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> token,
                          T value);
  const std::string getKindText();
  const SyntaxKindUtils::SyntaxKind getSyntaxKind();
  const T &getValue();

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getTokenPtr();
};
