#include "NirastExpressionGenerationStrategy.h"

NirastExpressionGenerationStrategy::NirastExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *NirastExpressionGenerationStrategy::generate() {
  return llvm::Constant::getNullValue(llvm::Type::getInt8PtrTy(*TheContext));
}

llvm::Value *NirastExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  return this->generate();
}
llvm::Value *NirastExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generate();
}