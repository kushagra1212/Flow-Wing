#include "ClassUnaryOperationStrategy.h"

ClassUnaryOperationStrategy::ClassUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *ClassUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *ClassUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {
  llvm::Value *result = Builder->getInt32(1);

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::ClassStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for class type ");
    return nullptr;
  }

  switch (unaryOperator) {

  default: {

    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for class type ");
    break;
  }
  }

  return nullptr;
}
