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

  _codeGenerationContext->getValueStackHandler()->push("", val, "constant",
                                                       val->getType());

  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Literal Type " +
        SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));
    return nullptr;
  }

  return val;
}

llvm::Value *LiteralExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)expression;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Literal Expression is not allowed in global scope ");

  return nullptr;
}

llvm::Value *LiteralExpressionGenerationStrategy::generateTypedExpression(
    BoundExpression *expression, SyntaxKindUtils::SyntaxKind variableType) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)expression;
  std::any value = literalExpression->getValue();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  llvm::Value *val = _llvmValueConverter->convertToTypedLLVMValue(
      value, literalExpression->getSyntaxKind(), variableType);

  _codeGenerationContext->getValueStackHandler()->push("", val, "constant",
                                                       val->getType());
  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Literal Type " +
        SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));
    return nullptr;
  }

  return val;
}
