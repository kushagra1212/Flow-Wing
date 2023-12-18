#include "FillExpressionGenerationStrategy.h"

FillExpressionGenerationStrategy::FillExpressionGenerationStrategy(
    CodeGenerationContext *context, uint64_t actualSize,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSize(actualSize),
      _elementType(elementType), _containerName(containerName) {}

llvm::Value *FillExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Allocate memory on the stack for the array
  llvm::Type *arrayType = llvm::ArrayType::get(_elementType, _actualSize);
  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, _containerName);

  return createExpression(arrayType, arrayAlloca);
}

llvm::Value *FillExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::AllocaInst *arrayAlloca) {
  // Get And Set Default Value

  llvm::Constant *defaultVal = llvm::cast<llvm::Constant>(
      _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

  for (uint64_t i = 0; i < _actualSize; i++) {

    // Store the items in the allocated memory
    llvm::Value *elementPtr = Builder->CreateGEP(
        arrayType, arrayAlloca, {Builder->getInt32(0), Builder->getInt32(i)});
    Builder->CreateStore(defaultVal, elementPtr);
  }

  llvm::Constant *constElement = llvm::dyn_cast<llvm::Constant>(_elementToFill);

  for (uint64_t i = 0; i < _sizeToFill; i++) {

    // Store the items in the allocated memory
    llvm::Value *elementPtr = Builder->CreateGEP(
        arrayType, arrayAlloca, {Builder->getInt32(0), Builder->getInt32(i)});
    Builder->CreateStore(constElement, elementPtr);
  }

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

llvm::Value *FillExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  if (!canGenerateExpression(expression))
    return nullptr;

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = llvm::ArrayType::get(_elementType, _actualSize);

  // Create a default value for the array
  std::vector<llvm::Constant *> defaultValues(
      _actualSize,
      llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType)));
  llvm::Constant *defaultArray =
      llvm::ConstantArray::get(arrayType, defaultValues);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      defaultArray, _containerName);

  return createGlobalExpression(arrayType, _globalVariable);

  return nullptr;
}

llvm::Value *FillExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable) {

  for (uint64_t i = 0; i < _sizeToFill; i++) {

    llvm::Value *loadedValue = Builder->CreateLoad(arrayType, _globalVariable);
    llvm::Value *updatedValue = Builder->CreateInsertValue(
        loadedValue, llvm::dyn_cast<llvm::Constant>(_elementToFill), (uint)i);

    Builder->CreateStore(updatedValue, _globalVariable);
  }

  return nullptr;
}

bool FillExpressionGenerationStrategy::canGenerateExpression(
    BoundExpression *expression) {

  BoundFillExpression *fillExpression =
      static_cast<BoundFillExpression *>(expression);

  llvm::Value *sizeToFillVal = nullptr;

  if (fillExpression->getSizeToFillRef().get())
    sizeToFillVal =
        _expressionGenerationFactory
            ->createStrategy(fillExpression->getSizeToFillRef()->getKind())
            ->generateExpression(fillExpression->getSizeToFillRef().get());

  _sizeToFill = 0;

  if (sizeToFillVal) {
    if (llvm::ConstantInt *constInt =
            llvm::dyn_cast<llvm::ConstantInt>(sizeToFillVal)) {
      _sizeToFill = constInt->getZExtValue();
    } else {
      _codeGenerationContext->getLogger()->LogError(
          "Size to fill must be a integer value.");
      return false;
    }
  }

  _elementToFill =
      _expressionGenerationFactory
          ->createStrategy(fillExpression->getElementToFillRef()->getKind())
          ->generateExpression(fillExpression->getElementToFillRef().get());

  if (!_elementToFill) {
    _codeGenerationContext->getLogger()->LogError(
        "Element to fill must be a Value.");
    return false;
  }

  if (_elementType && _elementType != _elementToFill->getType()) {
    std::string elementTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

    std::string itemValueTypeName =
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            _elementToFill->getType());

    _codeGenerationContext->getLogger()->LogError(
        _containerName + " Container item type mismatch. Expected " +
        elementTypeName + " but got " + itemValueTypeName);

    return false;
  }

  if (sizeToFillVal) {
    if (_sizeToFill > _actualSize) {
      _codeGenerationContext->getLogger()->LogError(
          "Size to fill must be less than or equal to the actual size of the "
          "container.");
      return false;
    }

    if (_sizeToFill < 1) {
      _codeGenerationContext->getLogger()->LogError(
          "Size to fill must be greater than 0.");
      return false;
    }
  } else {
    _sizeToFill = _actualSize;
  }

  return true;
}