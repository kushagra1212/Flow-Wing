#pragma once

#include "../BoundExpression/BoundExpression.h"
#include <llvm/IR/IRBuilder.h>

class BoundUnaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundUnaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _operand;
  llvm::AllocaInst *_dynamicValueVariableAddress = nullptr;

public:
  BoundUnaryExpression(const DiagnosticUtils::SourceLocation &location,
                       BinderKindUtils::BoundUnaryOperatorKind op,
                       std::unique_ptr<BoundExpression> operand);

  const std::type_info &getType() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  std::unique_ptr<BoundExpression> &getOperandPtr();

  BinderKindUtils::BoundUnaryOperatorKind &getOperator();

  llvm::AllocaInst *getDynamicValueVariableAddress();

  void
  setDynamicValueVariableAddress(llvm::AllocaInst *dynamicValueVariableAddress);
};