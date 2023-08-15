#ifndef BINARYEXPRESSIONSYNTAX_H
#define BINARYEXPRESSIONSYNTAX_H
#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class BinaryExpressionSyntax : public ExpressionSyntax {

private:
  std::unique_ptr<ExpressionSyntax> _left;
  std::unique_ptr<SyntaxToken<std::any>> _operatorToken;
  std::unique_ptr<ExpressionSyntax> _right;

public:
  BinaryExpressionSyntax(std::unique_ptr<ExpressionSyntax> left,
                         std::unique_ptr<SyntaxToken<std::any>> operatorToken,
                         std::unique_ptr<ExpressionSyntax> right);

  std::unique_ptr<ExpressionSyntax> getLeft();

  std::unique_ptr<SyntaxToken<std::any>> getOperatorToken();

  std::unique_ptr<ExpressionSyntax> getRight();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};
#endif