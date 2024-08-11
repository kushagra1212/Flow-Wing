#ifndef __BOUND_RETURN_STATEMENT_H
#define __BOUND_RETURN_STATEMENT_H

#include "../BoundExpression.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement, public BoundSourceLocation {
private:
  std::vector<std::unique_ptr<BoundExpression>> _returnExpressionList;

public:
  BoundReturnStatement(const DiagnosticUtils::SourceLocation &location);

  /*
    Overrides
  */

  BinderKindUtils::BoundNodeKind getKind() const override;
  std::vector<BoundNode *> getChildren() override;

  /*
    Getters
  */
  inline auto getReturnExpressionListRef() const
      -> const std::vector<std::unique_ptr<BoundExpression>> & {
    return _returnExpressionList;
  }

  /*
    Setters
  */
  inline void addReturnExpression(std::unique_ptr<BoundExpression> expression) {
    _returnExpressionList.push_back(std::move(expression));
  }
};

#endif // __BOUND_RETURN_STATEMENT_H