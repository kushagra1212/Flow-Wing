#include "UnaryExpressionGenerationStrategy.h"

UnaryExpressionGenerationStrategy::UnaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *UnaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundUnaryExpression *unaryExpression =
      static_cast<BoundUnaryExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      unaryExpression->getLocation());

  llvm::Value *val =
      _expressionGenerationFactory
          ->createStrategy(unaryExpression->getOperandPtr().get()->getKind())
          ->generateExpression(unaryExpression->getOperandPtr().get());

  if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
      !_codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
          _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {
    _codeGenerationContext->getLogger()->LogError(
        "This Unary Expression is not supported for objects");
    return nullptr;
  }

  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    val = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }
  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Unary Expression Type ");

    return nullptr;
  }
  llvm::Value *res =
      _unaryOperationStrategy->performOperation(val, unaryExpression);

  _codeGenerationContext->getValueStackHandler()->popAll();

  _codeGenerationContext->getValueStackHandler()->push("", res, "constant",
                                                       res->getType());
  return res;
}

llvm::Value *UnaryExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundUnaryExpression *unaryExpression =
      static_cast<BoundUnaryExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      unaryExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Unary Expression is not allowed in global scope ");

  return nullptr;
}