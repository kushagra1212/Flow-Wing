#ifndef RETURNSTATEMENTSYNTAX_H
#define RETURNSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"

#include "../../SyntaxToken.h"
#include "../StatementSyntax.h"

#include "../../expression/ExpressionSyntax.h"

class ReturnStatementSyntax : public StatementSyntax {
private:
  SyntaxToken<std::any> *_returnKeyword;
  ExpressionSyntax *_expression;

public:
  ReturnStatementSyntax(SyntaxToken<std::any> *returnKeyword,
                        ExpressionSyntax *expression);

  ~ReturnStatementSyntax();

  SyntaxToken<std::any> *getReturnKeyword() const;
  ExpressionSyntax *getExpression() const;

  std::vector<SyntaxNode *> getChildren() override;
  SyntaxKindUtils::SyntaxKind getKind() override;
};

#endif // RETURNSTATEMENTSYNTAX_H
