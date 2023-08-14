#ifndef RETURNSTATEMENTSYNTAX_H
#define RETURNSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"

#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

#include "../../expression/ExpressionSyntax.h"

class ReturnStatementSyntax : public StatementSyntax {
private:
  std::shared_ptr<SyntaxToken<std::any>> _returnKeyword;
  std::shared_ptr<ExpressionSyntax> _expression;

public:
  ReturnStatementSyntax(std::shared_ptr<SyntaxToken<std::any>> returnKeyword,
                        std::shared_ptr<ExpressionSyntax> expression);

  std::shared_ptr<SyntaxToken<std::any>> getReturnKeyword() const;
  std::shared_ptr<ExpressionSyntax> getExpression() const;

  std::vector<std::shared_ptr<SyntaxNode>> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;

  std::string getLineNumberAndColumn() const override;
};

#endif // RETURNSTATEMENTSYNTAX_H
