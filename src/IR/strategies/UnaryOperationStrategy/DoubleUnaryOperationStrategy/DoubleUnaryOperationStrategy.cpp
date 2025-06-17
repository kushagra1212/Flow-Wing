#include "DoubleUnaryOperationStrategy.h"

DoubleUnaryOperationStrategy::DoubleUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *DoubleUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *DoubleUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::DoubleStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for decimal type ");
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
    llvm::Value *zero = llvm::ConstantFP::get(val->getType(), 0.0);

    // 2. Compare val to 0.0. The result is an i1 (LLVM boolean).
    llvm::Value *isZero = Builder->CreateFCmpOEQ(val, zero, "iszero");

    return isZero;
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for decimal type ");
    break;
  }
  }

  return nullptr;
}