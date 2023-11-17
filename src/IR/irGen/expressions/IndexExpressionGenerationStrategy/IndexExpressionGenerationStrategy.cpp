#include "IndexExpressionGenerationStrategy.h"

IndexExpressionGenerationStrategy::IndexExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *IndexExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      indexExpression->getLocation());

  llvm::Value *value =
      _expressionGenerationFactory
          ->createStrategy(
              indexExpression->getBoundIdentifierExpression().get()->getKind())
          ->generateExpression(
              indexExpression->getBoundIdentifierExpression().get());

  llvm::Value *indexValue =
      _expressionGenerationFactory
          ->createStrategy(
              indexExpression->getBoundIndexExpression().get()->getKind())
          ->generateExpression(
              indexExpression->getBoundIndexExpression().get());

  std::string variableName = std::any_cast<std::string>(
      ((BoundLiteralExpression<std::any> *)indexExpression
           ->getBoundIdentifierExpression()
           ->getIdentifierExpressionPtr()
           .get())
          ->getValue());

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);
  if (llvm::ArrayType *arrayType =
          llvm::dyn_cast<llvm::ArrayType>(v->getAllocatedType())) {
    llvm::Type *elementType = arrayType->getElementType();
    const uint64_t size = arrayType->getNumElements();

    llvm::Value *arrayPtr = v;
    llvm::Value *elementPtr =
        Builder->CreateGEP(arrayType, arrayPtr,
                           {Builder->getInt32(0),
                            _int32TypeConverter->convertExplicit(indexValue)});

    return Builder->CreateLoad(elementType, elementPtr);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable not found in variable expression ");

  return nullptr;
}

llvm::Value *IndexExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->generateExpression(expression);
}