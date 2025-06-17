
#include "FloatUnaryOperationStrategy.h"

FloatUnaryOperationStrategy::FloatUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *FloatUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {
  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *FloatUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::FloatStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for float type ");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    return Builder->CreateFNeg(val);
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {

    return val;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    // 1. Create a constant 0.0 of the same type as val.
    llvm::Value *zero = llvm::ConstantFP::get(val->getType(), 0.0);

    // 2. Compare val to 0.0. The result is an i1 (LLVM boolean).
    llvm::Value *isZero = Builder->CreateFCmpOEQ(val, zero, "iszero");

    return isZero;
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for float type ");
    break;
  }
  }

  return nullptr;
}