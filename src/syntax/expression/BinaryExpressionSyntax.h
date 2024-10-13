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

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<ExpressionSyntax> &getLeftRef();
  std::unique_ptr<SyntaxToken<std::any>> &getOperatorTokenRef();
  std::unique_ptr<ExpressionSyntax> &getRightRef();
};
#endif