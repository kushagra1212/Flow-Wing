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

  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Unary Expression Type ");

    return nullptr;
  }
  llvm::Value *res =
      _unaryOperationStrategy->performOperation(val, unaryExpression);

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