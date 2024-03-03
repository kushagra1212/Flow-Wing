#ifndef __FLOW__WING__BOUND__VARIABLE__EXPRESSION__H__
#define __FLOW__WING__BOUND__VARIABLE__EXPRESSION__H__

#include "../BoundVariableExpression.h"

class BoundArrayVariableExpression : public BoundVariableExpression {
 public:
  BoundArrayVariableExpression(
      const DiagnosticUtils::SourceLocation &location,
      std::unique_ptr<BoundLiteralExpression<std::any>> identiferExpression,
      const bool &isConstant, BoundTypeExpression *variableTypeExp);

  virtual const std::type_info &getType() override;
  virtual BinderKindUtils::BoundNodeKind getKind() const override;
  virtual std::vector<BoundNode *> getChildren() override;

  const std::vector<std::unique_ptr<BoundExpression>> &getSizeExpressionsRef()
      const;

  void addSizeExpression(std::unique_ptr<BoundExpression> sizeExpression);

 private:
  std::vector<std::unique_ptr<BoundExpression>> _sizeExpressions;
};

#endif  // __FLOW__WING__BOUND__VARIABLE__EXPRESSION__H__