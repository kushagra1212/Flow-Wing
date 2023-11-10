#include "UnaryExpressionGenerationStrategy.h"

UnaryExpressionGenerationStrategy::UnaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *UnaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundUnaryExpression *unaryExpression = (BoundUnaryExpression *)expression;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      unaryExpression->getLocation());

  return nullptr;
  //   ExpressionGenerationStrategy *_unaryExpresssionGenerationStrategy =
  //       _codeGenerationContext->getExpressionGenerationStrategy(
  //           unaryExpression->getOperandPtr()->getKind());

  //   llvm::Value *val =
  //   _unaryExpresssionGenerationStrategy->generateExpression(
  //       unaryExpression->getOperandPtr().get());

  //   if (val == nullptr) {
  //     _codeGenerationContext->getLogger()->LogError(
  //         "Unsupported Unary Expression Type ");

  //     return nullptr;
  //   }
  //   return _unaryOperationStrategy->performOperation(val, unaryExpression);
}
