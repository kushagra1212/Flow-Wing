#include "ContainerExpressionGenerationStrategy.h"

ContainerExpressionGenerationStrategy::ContainerExpressionGenerationStrategy(
    CodeGenerationContext *context, uint64_t actualSize,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSize(actualSize),
      _elementType(elementType), _containerName(containerName) {}

llvm::Value *ContainerExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundContainerExpression *containerExpression =
      static_cast<BoundContainerExpression *>(expression);
  uint64_t size = containerExpression->getElementsRef().size();

  // Allocate memory on the stack for the array
  llvm::Type *arrayType = llvm::ArrayType::get(_elementType, _actualSize);
  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, _containerName);

  for (uint64_t i = 0; i < size; i++) {
    BoundExpression *entryExp = containerExpression->getElementsRef()[i].get();

    llvm::Value *itemValue =
        _expressionGenerationFactory->createStrategy(entryExp->getKind())
            ->generateExpression(entryExp);

    if (_elementType && _elementType != itemValue->getType()) {
      std::string elementTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

      std::string itemValueTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              itemValue->getType());

      _codeGenerationContext->getLogger()->LogError(
          _containerName + " Container item type mismatch. Expected " +
          elementTypeName + " but got " + itemValueTypeName);

      return nullptr;
    }

    // Store the items in the allocated memory
    llvm::Value *elementPtr = Builder->CreateGEP(
        arrayType, arrayAlloca, {Builder->getInt32(0), Builder->getInt32(i)});
    Builder->CreateStore(llvm::dyn_cast<llvm::Constant>(itemValue), elementPtr);
  }

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

llvm::Value *ContainerExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundContainerExpression *containerExpression =
      static_cast<BoundContainerExpression *>(expression);
  uint64_t size = containerExpression->getElementsRef().size();

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = llvm::ArrayType::get(_elementType, _actualSize);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(arrayType), _containerName);

  for (uint64_t i = 0; i < size; i++) {

    llvm::Value *itemValue =
        _expressionGenerationFactory
            ->createStrategy(
                containerExpression->getElementsRef()[i].get()->getKind())
            ->generateExpression(
                containerExpression->getElementsRef()[i].get());

    if (_elementType && _elementType != itemValue->getType()) {
      std::string elementTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

      std::string itemValueTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              itemValue->getType());

      _codeGenerationContext->getLogger()->LogError(
          _containerName + " Container item type mismatch. Expected " +
          elementTypeName + " but got " + itemValueTypeName);

      return nullptr;
    }

    llvm::Value *loadedValue = Builder->CreateLoad(arrayType, _globalVariable);
    llvm::Value *updatedValue = Builder->CreateInsertValue(
        loadedValue, llvm::dyn_cast<llvm::Constant>(itemValue), (uint)i);

    Builder->CreateStore(updatedValue, _globalVariable);
  }

  return nullptr;
}