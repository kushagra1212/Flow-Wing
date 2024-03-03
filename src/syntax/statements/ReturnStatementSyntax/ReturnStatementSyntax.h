#ifndef RETURNSTATEMENTSYNTAX_H
#define RETURNSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ReturnStatementSyntax : public StatementSyntax {
 private:
  std::unique_ptr<SyntaxToken<std::any>> _returnKeyword;
  std::unique_ptr<ExpressionSyntax> _expression;

 public:
  ReturnStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> returnKeyword,
                        std::unique_ptr<ExpressionSyntax> expression);

  std::unique_ptr<SyntaxToken<std::any>> getReturnKeyword();
  std::unique_ptr<ExpressionSyntax> getExpression();

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  std::unique_ptr<SyntaxToken<std::any>> &getReturnKeywordPtr();
  std::unique_ptr<ExpressionSyntax> &getExpressionPtr();
};

#endif  // RETURNSTATEMENTSYNTAX_H
