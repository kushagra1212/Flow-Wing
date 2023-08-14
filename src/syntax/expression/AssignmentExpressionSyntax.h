#pragma once
#include "../../Common.h"
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
#include "LiteralExpressionSyntax.h"
class AssignmentExpressionSyntax : public ExpressionSyntax {
private:
  std::shared_ptr<LiteralExpressionSyntax<std::any>> left;
  std::shared_ptr<SyntaxToken<std::any>> operatorToken;
  std::shared_ptr<ExpressionSyntax> right;

public:
  AssignmentExpressionSyntax(
      std::shared_ptr<LiteralExpressionSyntax<std::any>> left,
      std::shared_ptr<SyntaxToken<std::any>> operatorToken,
      std::shared_ptr<ExpressionSyntax> right);

public:
  SyntaxKindUtils::SyntaxKind getKind();

public:
  std::vector<std::shared_ptr<SyntaxNode>> getChildren();

public:
  std::shared_ptr<SyntaxToken<std::any>> getOperatorToken();

public:
  std::shared_ptr<ExpressionSyntax> getRight();

public:
  std::shared_ptr<LiteralExpressionSyntax<std::any>> getLeft();

public:
  std::string getLineNumberAndColumn() const override;
};
