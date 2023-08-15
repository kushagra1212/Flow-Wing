#ifndef RETURNSTATEMENTSYNTAX_H
#define RETURNSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"

#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

#include "../../expression/ExpressionSyntax.h"

class ReturnStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _returnKeyword;
  std::unique_ptr<ExpressionSyntax> _expression;

public:
  ReturnStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> returnKeyword,
                        std::unique_ptr<ExpressionSyntax> expression);

  std::unique_ptr<SyntaxToken<std::any>> getReturnKeyword();
  std::unique_ptr<ExpressionSyntax> getExpression();

  std::vector<SyntaxNode *> getChildren() override;

  SyntaxKindUtils::SyntaxKind getKind() const override;

  std::string getLineNumberAndColumn() override;
};

#endif // RETURNSTATEMENTSYNTAX_H
