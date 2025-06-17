#include "NirastUnaryOperationStrategy.h"

NirastUnaryOperationStrategy::NirastUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *NirastUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *NirastUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::NirastStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for Nirast type");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    return Builder->getTrue();
  }
  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for Nirast type");
    break;
  }
  }

  return nullptr;
}