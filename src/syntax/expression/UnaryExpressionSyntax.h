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

  std::unique_ptr<SyntaxToken<std::any>> getOperatorToken();

  std::unique_ptr<ExpressionSyntax> getOperand();

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::vector<SyntaxNode *> getChildren() override;

  std::string getLineNumberAndColumn() override;
};

#endif // UnaryExpressionSyntax_h__