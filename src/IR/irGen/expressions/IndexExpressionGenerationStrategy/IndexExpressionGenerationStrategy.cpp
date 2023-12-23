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
        "Index value must be of type int");
    return nullptr;
  }

  indexValue = _int32TypeConverter->convertExplicit(indexValue);

  std::string variableName = std::any_cast<std::string>(
      (indexExpression->getBoundIdentifierExpression().get())->getValue());

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  if (!v) {
    // Variable not found, handle error

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {

      if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {

        // llvm::ConstantInt *constantInt =
        //     llvm::dyn_cast<llvm::ConstantInt>(indexValue);

        return this->handleGlobalVariable(variable, indexValue, variableName);
      }

      _codeGenerationContext->getLogger()->LogError(
          "Variable not found in assignment expression ");
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression ");

    return nullptr;
  }

  if (llvm::ArrayType *arrayType =
          llvm::dyn_cast<llvm::ArrayType>(v->getAllocatedType())) {
    return this->handleArrayTypeIndexing(variableName, v, indexValue,
                                         arrayType);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable" + variableName + " not found in variable expression ");

  return nullptr;
}

llvm::Value *IndexExpressionGenerationStrategy::handleArrayTypeIndexing(
    const std::string &variableName, llvm::Value *variable,
    llvm::Value *indexValue, llvm::ArrayType *arrayType) {
  llvm::Type *elementType = arrayType->getElementType();
  const uint64_t size = arrayType->getNumElements();

  if (size <= 0) {
    _codeGenerationContext->callREF("Array size must be greater than 0");
    return nullptr;
  }

  llvm::Function *function = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::then", function);
  llvm::BasicBlock *elseBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::else", function);
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(*TheContext, "GlobalIndexExpr::merge", function);

  // TODO: TO 64 Bit
  llvm::Value *isLessThan = Builder->CreateICmpSLT(
      indexValue,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), size, true),
      "GlobalIndexExpr::isLessThan");

  llvm::Value *isGreaterThan = Builder->CreateICmpSGE(
      indexValue,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0, true),
      "GlobalIndexExpr::isGreaterThan");

  llvm::Value *isWithinBounds = Builder->CreateAnd(
      isLessThan, isGreaterThan, "GlobalIndexExpr::isWithinBounds");
  llvm::Value *ptr = Builder->CreateGEP(elementType, variable, indexValue);

  llvm::Value *innerValue = nullptr;
  innerValue = Builder->CreateLoad(elementType, ptr);
  // Create the conditional branch
  Builder->CreateCondBr(isWithinBounds, thenBB, elseBB);

  // In the then block, you can continue with the array access
  Builder->SetInsertPoint(thenBB);

  Builder->CreateBr(mergeBB);

  Builder->SetInsertPoint(elseBB);

  _codeGenerationContext->callREF("Index out of bounds of '" + variableName +
                                  "' in index expression, array size is " +
                                  std::to_string(size));

  Builder->CreateBr(mergeBB);

  // Continue from the merge block
  Builder->SetInsertPoint(mergeBB);

  // Builder->CreateLoad(elementType, innerValue);
  return innerValue;
}

llvm::Value *IndexExpressionGenerationStrategy::handleGlobalVariable(
    llvm::GlobalVariable *variable, llvm::Value *indexValue,
    std::string variableName) {

  indexValue = _int32TypeConverter->convertExplicit(indexValue);
  if (llvm::ArrayType *arrayType =
          llvm::dyn_cast<llvm::ArrayType>(variable->getValueType())) {

    return this->handleArrayTypeIndexing(variableName, variable, indexValue,
                                         arrayType);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable" + variableName + " not found in variable expression ");

  return nullptr;
}

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
