
#include "BoolUnaryOperationStrategy.h"

BoolUnaryOperationStrategy::BoolUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *BoolUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {
  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *BoolUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {
  llvm::Value *result = nullptr;

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::BoolStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for bool type ");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {

    return Builder->CreateNot(val);
  }
  // Add more cases for other binary operators
  default:

    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for bool type ");
    break;
  }

  return nullptr;
}