#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
class BoundAssignmentExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;
  Utils::Variable _variable;

public:
  BoundAssignmentExpression(const DiagnosticUtils::SourceLocation &location,
                            Utils::Variable variable,
                            std::unique_ptr<BoundExpression> left,
                            BinderKindUtils::BoundBinaryOperatorKind op,
                            std::unique_ptr<BoundExpression> right);

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  std::unique_ptr<BoundExpression> getLeft();

  std::unique_ptr<BoundExpression> getRight();

  const std::type_info &getType();

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundBinaryOperatorKind &getOperatorPtr();

  std::unique_ptr<BoundExpression> &getLeftPtr();

  std::unique_ptr<BoundExpression> &getRightPtr();

  const Utils::Variable getVariable() const;
};

#endif // ASSIGNMENT_EXPRESSION_H