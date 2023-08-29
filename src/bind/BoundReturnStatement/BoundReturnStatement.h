#ifndef BOUNDRETURNSTATEMENT_H
#define BOUNDRETURNSTATEMENT_H

#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundStatement/BoundStatement.h"

class BoundReturnStatement : public BoundStatement, public BoundSourceLocation {

private:
  std::unique_ptr<BoundExpression> _expression;

public:
  BoundReturnStatement(const DiagnosticUtils::SourceLocation &location,
                       std::unique_ptr<BoundExpression> expression);

  std::unique_ptr<BoundExpression> getReturnExpression();

  BinderKindUtils::BoundNodeKind getKind() const;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getReturnExpressionPtr();
};

#endif // BOUNDRETURNSTATEMENT_H