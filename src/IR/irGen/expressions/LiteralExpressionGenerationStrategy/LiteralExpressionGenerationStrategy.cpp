#include "LiteralExpressionGenerationStrategy.h"

LiteralExpressionGenerationStrategy::LiteralExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *LiteralExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)expression;
  std::any value = literalExpression->getValue();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  llvm::Value *val = _llvmValueConverter->convertToLLVMValue(
      value, literalExpression->getSyntaxKind());

  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Literal Type " +
        SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));
    return nullptr;
  }

  return val;
}
