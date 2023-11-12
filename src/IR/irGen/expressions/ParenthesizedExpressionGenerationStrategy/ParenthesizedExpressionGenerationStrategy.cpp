#include "ParenthesizedExpressionGenerationStrategy.h"

ParenthesizedExpressionGenerationStrategy::
    ParenthesizedExpressionGenerationStrategy(CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ParenthesizedExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundParenthesizedExpression *parenthesizedExpression =
      static_cast<BoundParenthesizedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      parenthesizedExpression->getLocation());

  return _expressionGenerationFactory
      ->createStrategy(
          parenthesizedExpression->getExpressionPtr().get()->getKind())
      ->generateExpression(parenthesizedExpression->getExpressionPtr().get());
}

llvm::Value *
ParenthesizedExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundParenthesizedExpression *parenthesizedExpression =
      static_cast<BoundParenthesizedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      parenthesizedExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Parenthesized Expression is not allowed in global scope ");

  return nullptr;
}