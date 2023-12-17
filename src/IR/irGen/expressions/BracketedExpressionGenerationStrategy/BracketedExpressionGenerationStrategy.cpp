#include "BracketedExpressionGenerationStrategy.h"

BracketedExpressionGenerationStrategy::BracketedExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *BracketedExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  throw std::runtime_error("Not implemented");
}
llvm::Value *BracketedExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  throw std::runtime_error("Not implemented");
}

// Specialized for BoundBracketedExpression

// template <typename... Args>
// llvm::Value *BracketedExpressionGenerationStrategy::wrappedExpression(
//     BoundBracketedExpression *bracketedExpression, Args... args) {

//   return _expressionGenerationFactory
//       ->createStrategy(bracketedExpression->getExpressionRef().get()->getKind(),
//                        args...)
//       ->generateExpression(bracketedExpression->getExpressionRef().get());
// }