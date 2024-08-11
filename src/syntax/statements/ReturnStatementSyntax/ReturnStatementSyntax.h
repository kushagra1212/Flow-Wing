#ifndef RETURNSTATEMENTSYNTAX_H
#define RETURNSTATEMENTSYNTAX_H

#include "../../SyntaxNode.h"
#include "../../SyntaxToken.h"
#include "../../expression/ExpressionSyntax.h"
#include "../StatementSyntax.h"

class ReturnStatementSyntax : public StatementSyntax {
private:
  std::unique_ptr<SyntaxToken<std::any>> _returnKeyword;
  std::vector<std::unique_ptr<ExpressionSyntax>> _expressionList;

public:
  ReturnStatementSyntax(std::unique_ptr<SyntaxToken<std::any>> returnKeyword);

  /*
    Overrides
  */

  const std::vector<SyntaxNode *> &getChildren() override;
  const SyntaxKindUtils::SyntaxKind getKind() const override;
  const DiagnosticUtils::SourceLocation getSourceLocation() const override;

  /*
    Setters
  */
  inline auto addReturnExpression(std::unique_ptr<ExpressionSyntax> expression)
      -> void {
    _expressionList.push_back(std::move(expression));
  }

  /*
    Getters
  */

  inline auto getReturnExpressionListRef() const
      -> const std::vector<std::unique_ptr<ExpressionSyntax>> & {
    return _expressionList;
  }

  inline auto getReturnKeywordRef() const
      -> const std::unique_ptr<SyntaxToken<std::any>> & {
    return _returnKeyword;
  }
};

#endif // RETURNSTATEMENTSYNTAX_H
