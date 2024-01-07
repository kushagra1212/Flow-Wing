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
  std::string getKindText();
  SyntaxKindUtils::SyntaxKind getSyntaxKind();
  T getValue();
  std::unique_ptr<SyntaxToken<std::any>> getToken();

  SyntaxKindUtils::SyntaxKind getKind() const override;
  std::vector<SyntaxNode *> getChildren() override;
  DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getTokenPtr();
};
