#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../../utils/Utils.h"
#include "../BinderKindUtils.h"
#include "../BoundExpression.h"
#include "../BoundSourceLocation/BoundSourceLocation.h"
#include "../BoundVariableDeclaration/BoundVariableDeclaration.h"

class BoundAssignmentExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;
  BoundVariableDeclaration *_variable;
  bool _needDefaulInitilization;

public:
  BoundAssignmentExpression(const DiagnosticUtils::SourceLocation &location,
                            BoundVariableDeclaration *variable,
                            std::unique_ptr<BoundExpression> left,
                            BinderKindUtils::BoundBinaryOperatorKind op,
                            std::unique_ptr<BoundExpression> right,
                            bool needDefaulInitilization = false);

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  std::unique_ptr<BoundExpression> getLeft();

  std::unique_ptr<BoundExpression> getRight();

  const std::type_info &getType() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundBinaryOperatorKind &getOperatorPtr();

  std::unique_ptr<BoundExpression> &getLeftPtr();

  std::unique_ptr<BoundExpression> &getRightPtr();

  BoundVariableDeclaration *getVariable();

  inline bool getNeedDefaulInitilization() { return _needDefaulInitilization; }
};

#endif // ASSIGNMENT_EXPRESSION_H