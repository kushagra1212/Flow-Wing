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

  llvm::Value *indexValue =
      _expressionGenerationFactory
          ->createStrategy(
              indexExpression->getBoundIndexExpression().get()->getKind())
          ->generateExpression(
              indexExpression->getBoundIndexExpression().get());

  if (!_codeGenerationContext->getMapper()->isInt32Type(
          indexValue->getType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Index value must be of type int32");
    return nullptr;
  }

  std::string variableName = std::any_cast<std::string>(
      (indexExpression->getBoundIdentifierExpression().get())->getValue());

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  if (!v) {
    // Variable not found, handle error

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      this->generateGlobalExpression(indexExpression);
      return nullptr;
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression ");

    return nullptr;
  }

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
      "Variable" + variableName + " not found in variable expression ");

  return nullptr;
}

// TODO: Implement global index expression generation strategy
llvm::Value *IndexExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundIndexExpression *indexExpression =
      static_cast<BoundIndexExpression *>(expression);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      indexExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "TODO: Implement global index expression generation strategy");

  return nullptr;
}
