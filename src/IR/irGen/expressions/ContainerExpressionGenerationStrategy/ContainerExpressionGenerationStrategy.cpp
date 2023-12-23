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

  if (!canGenerateExpression(containerExpression))
    return nullptr;

  // Allocate memory on the stack for the array
  llvm::Type *arrayType = llvm::ArrayType::get(_elementType, _actualSize);

  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, _containerName);

  // Fill the array with default values
  llvm::Constant *defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  std::unique_ptr<FillExpressionGenerationStrategy>
      fillExpressionGenerationStrategy =
          std::make_unique<FillExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSize, _elementType,
              _containerName);

  fillExpressionGenerationStrategy->createExpression(
      arrayType, arrayAlloca, defaultVal,
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), _actualSize));

  return createExpression(arrayType, arrayAlloca, containerExpression);
}

const bool ContainerExpressionGenerationStrategy::canGenerateExpression(
    BoundContainerExpression *containerExpression) {

  _sizeToFill = containerExpression->getElementsRef().size();

  if (_sizeToFill > _actualSize) {
    _codeGenerationContext->getLogger()->LogError(
        "Container " + _containerName + " size mismatch. Expected " +
        std::to_string(_actualSize) + " but got " +
        std::to_string(_sizeToFill));
    return false;
  }

  return true;
}

llvm::Value *ContainerExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundContainerExpression *containerExpression =
      static_cast<BoundContainerExpression *>(expression);

  if (!canGenerateExpression(containerExpression))
    return nullptr;

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = llvm::ArrayType::get(_elementType, _actualSize);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(arrayType), _containerName);

  return createGlobalExpression(arrayType, _globalVariable,
                                containerExpression);
}

llvm::Value *ContainerExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::AllocaInst *_allocaInst,
    BoundContainerExpression *containerExpression) {

  for (uint64_t i = 0; i < _sizeToFill; i++) {
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
        arrayType, _allocaInst, {Builder->getInt32(0), Builder->getInt64(i)});
    Builder->CreateStore(itemValue, elementPtr);
  }

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          _allocaInst);

  return _allocaInst;
}

llvm::Value *ContainerExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable,
    BoundContainerExpression *containerExpression) {

  for (uint64_t i = 0; i < _sizeToFill; i++) {

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
    // Compute the address of the i-th element

    llvm::Value *elementPtr =
        Builder->CreateGEP(arrayType, _globalVariable,
                           {Builder->getInt32(0), Builder->getInt64(i)});

    Builder->CreateStore(itemValue, elementPtr);
  }
  return nullptr;
}