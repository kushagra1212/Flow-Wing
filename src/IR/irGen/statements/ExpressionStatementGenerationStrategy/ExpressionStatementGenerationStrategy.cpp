#include "ExpressionStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ExpressionStatementGenerationStrategy::ExpressionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ExpressionStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundExpressionStatement *boundExpressionStatement =
      static_cast<BoundExpressionStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundExpressionStatement->getLocation());

  BoundExpression *boundExpression =
      boundExpressionStatement->getExpressionPtr().get();

  return _expressionGenerationFactory
      ->createStrategy(boundExpression->getKind())
      ->generateExpression(boundExpression);
}

llvm::Value *ExpressionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {

  BoundExpressionStatement *boundExpressionStatement =
      static_cast<BoundExpressionStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundExpressionStatement->getLocation());

  BoundExpression *boundExpression =
      boundExpressionStatement->getExpressionPtr().get();

  return _expressionGenerationFactory
      ->createStrategy(boundExpression->getKind())
      ->generateGlobalExpression(boundExpression);
}