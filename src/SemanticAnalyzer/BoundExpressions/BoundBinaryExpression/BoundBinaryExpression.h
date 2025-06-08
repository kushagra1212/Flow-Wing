#pragma once

#include "../BoundExpression/BoundExpression.h"
#include <llvm/IR/IRBuilder.h>

class BoundBinaryExpression : public BoundExpression {
private:
  BinderKindUtils::BoundBinaryOperatorKind _op;
  std::unique_ptr<BoundExpression> _left;
  std::unique_ptr<BoundExpression> _right;
  llvm::AllocaInst *_dynamicValueVariableAddress = nullptr;

public:
  BoundBinaryExpression(const DiagnosticUtils::SourceLocation &location,
                        std::unique_ptr<BoundExpression> left,
                        BinderKindUtils::BoundBinaryOperatorKind op,
                        std::unique_ptr<BoundExpression> right);

  BinderKindUtils::BoundBinaryOperatorKind getOperator();

  std::unique_ptr<BoundExpression> getLeft();

  std::unique_ptr<BoundExpression> getRight();

  const std::type_info &getType() override;

  BinderKindUtils::BoundNodeKind getKind() const override;

  std::vector<BoundNode *> getChildren() override;

  BinderKindUtils::BoundBinaryOperatorKind &getOperatorPtr();

  std::unique_ptr<BoundExpression> &getLeftPtr();

  std::unique_ptr<BoundExpression> &getRightPtr();

  llvm::AllocaInst *getDynamicValueVariableAddress();

  void
  setDynamicValueVariableAddress(llvm::AllocaInst *dynamicValueVariableAddress);
};
