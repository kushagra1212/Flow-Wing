#include "Int32UnaryOperationStrategy.h"

Int32UnaryOperationStrategy::Int32UnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *Int32UnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *Int32UnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {
  llvm::Value *result = Builder->getInt32(1);

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::Int32StrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for int32 type ");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {
    return Builder->CreateNeg(val);
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {
    return val;
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    llvm::Value *isZero = Builder->CreateICmpEQ(
        val, llvm::ConstantInt::get(Builder->getInt32Ty(), 0));

    return isZero;
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {
    return Builder->CreateNot(val);
    break;
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for int32 type ");
    break;
  }
  }

  return nullptr;
}