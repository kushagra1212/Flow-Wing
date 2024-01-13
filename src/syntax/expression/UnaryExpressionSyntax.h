#ifndef UnaryExpressionSyntax_h__
#define UnaryExpressionSyntax_h__

#include "../SyntaxToken.h"
#include "ExpressionSyntax.h"
class UnaryExpressionSyntax : public ExpressionSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _operatorToken;
  std::unique_ptr<ExpressionSyntax> _operand;

 public:
  UnaryExpressionSyntax(std::unique_ptr<SyntaxToken<std::any>> operatorToken,
                        std::unique_ptr<ExpressionSyntax> operand);

  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const std::vector<SyntaxNode *> &getChildren() override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getOperatorTokenPtr();
  std::unique_ptr<ExpressionSyntax> &getOperandPtr();
};

#endif  // UnaryExpressionSyntax_h__