#include "ContainerExpressionGenerationStrategy.h"

ContainerExpressionGenerationStrategy::ContainerExpressionGenerationStrategy(
    CodeGenerationContext *context, std::vector<uint64_t> actualSizes,
    llvm::Type *elementType, const std::string &containerName)
    : ExpressionGenerationStrategy(context), _actualSizes(actualSizes),
      _elementType(elementType), _containerName(containerName),
      _isGlobal(false) {

  _totalSize = std::accumulate(_actualSizes.begin(), _actualSizes.end(), 1,
                               std::multiplies<uint64_t>());
}

llvm::Value *ContainerExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundContainerExpression *containerExpression =
      static_cast<BoundContainerExpression *>(expression);

  if (!canGenerateExpression(containerExpression))
    return nullptr;

  llvm::ArrayType *arrayType = nullptr;

  llvm::Constant *_defaultVal = nullptr;

  if (!llvm::isa<llvm::StructType>(_elementType)) {
    _defaultVal = llvm::cast<llvm::Constant>(
        _codeGenerationContext->getMapper()->getDefaultValue(_elementType));
  } else {
    _defaultVal = llvm::Constant::getNullValue(_elementType);
  }

  _codeGenerationContext->getMultiArrayType(arrayType, _actualSizes,
                                            _elementType);

  if (!_allocaInst) {
    llvm::AllocaInst *alloc =
        Builder->CreateAlloca(arrayType, nullptr, _containerName);
    _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                            alloc);
    _codeGenerationContext->setArraySizeMetadata(alloc, _actualSizes);
    _codeGenerationContext->setArrayElementTypeMetadata(alloc, _elementType);
    _allocaInst = alloc;
  }

  // Fill the array with default values

  std::unique_ptr<FillExpressionGenerationStrategy>
      fillExpressionGenerationStrategy =
          std::make_unique<FillExpressionGenerationStrategy>(
              _codeGenerationContext, _actualSizes, _elementType,
              _containerName);

  fillExpressionGenerationStrategy->createExpression(arrayType, _allocaInst,
                                                     _defaultVal, _totalSize);

  return createExpression(arrayType, _allocaInst, containerExpression);
}

const bool ContainerExpressionGenerationStrategy::canGenerateExpression(
    BoundContainerExpression *containerExpression) {

  _sizeToFill = containerExpression->getElementsRef().size();

  if (_sizeToFill > _totalSize) {
    _codeGenerationContext->getLogger()->LogError(
        "Container " + _containerName + " size mismatch. Expected " +
        std::to_string(_totalSize) + " but got " + std::to_string(_sizeToFill));
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

  _isGlobal = true;

  llvm::ArrayType *arrayType = nullptr;

  // Create a default value for the array

  llvm::Constant *_defaultVal = nullptr;

  if (!llvm::isa<llvm::StructType>(_elementType)) {
    _defaultVal = llvm::cast<llvm::Constant>(
        _codeGenerationContext->getMapper()->getDefaultValue(_elementType));
  } else {
    _defaultVal = llvm::Constant::getNullValue(_elementType);
  }

  _codeGenerationContext->getMultiArrayTypeForGlobal(
      arrayType, _defaultVal, _actualSizes, _elementType);
  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalWeakLinkage,
      _defaultVal, _containerName);

  _codeGenerationContext->setArraySizeMetadata(_globalVariable, _actualSizes);
  _codeGenerationContext->setArrayElementTypeMetadata(_globalVariable,
                                                      _elementType);

  return createGlobalExpression(arrayType, _globalVariable,
                                containerExpression);
}

llvm::Value *ContainerExpressionGenerationStrategy::createLocalExpression(
    llvm::Type *arrayType, llvm::AllocaInst *_allocaInst,
    BoundContainerExpression *containerExpression) {

  _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                          _allocaInst);

  return createExpression(arrayType, _allocaInst, containerExpression);
}

llvm::Value *ContainerExpressionGenerationStrategy::createExpressionAtom(
    llvm::Type *&arrayType, llvm::Value *&v,
    BoundContainerExpression *containerExpression,
    std::vector<llvm::Value *> &indices, uint64_t index) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      containerExpression->getLocation());

  if (_actualSizes[index] < containerExpression->getElementsRef().size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Container " + _containerName + " size mismatch. Expected " +
        std::to_string(_actualSizes[index]) + " but got " +
        std::to_string(containerExpression->getElementsRef().size()));

    return nullptr;
  }

  for (uint64_t i = 0; i < containerExpression->getElementsRef().size(); i++) {
    indices.push_back(Builder->getInt32(i));

    if (containerExpression->getElementsRef()[i].get()->getKind() ==
        BinderKindUtils::BoundContainerExpression) {
      createExpressionAtom(
          arrayType, v,
          (BoundContainerExpression *)containerExpression->getElementsRef()[i]
              .get(),
          indices, index + 1);
    } else {
      std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
          std::make_unique<AssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

      llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);
      assignmentEGS->handleAssignExpression(
          elementPtr, _elementType, _containerName,
          containerExpression->getElementsRef()[i].get());
    }

    //!!! IMP MAKE USE OF ASSIGNMENT EXPRESSIONS STRATEGY!!!

    // else if (llvm::isa<llvm::StructType>(_elementType) &&
    //          containerExpression->getElementsRef()[i].get()->getKind() ==
    //              BinderKindUtils::BoundObjectExpression) {

    //   std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrategy =
    //       std::make_unique<ObjectExpressionGenerationStrategy>(
    //           _codeGenerationContext);

    //   objExpGenStrategy->setVariable(elementPtr);
    //   objExpGenStrategy->setTypeName(_elementType->getStructName().str());
    //   objExpGenStrategy->generateExpression(
    //       containerExpression->getElementsRef()[i].get());
    // }
    // else if (llvm::isa<llvm::StructType>(_elementType) &&
    //          containerExpression->getElementsRef()[i].get()->getKind() ==
    //              BinderKindUtils::VariableExpression) {
    //   _expressionGenerationFactory
    //       ->createStrategy(
    //           containerExpression->getElementsRef()[i].get()->getKind())
    //       ->generateExpression(containerExpression->getElementsRef()[i].get());
    //   // std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
    //   //     std::make_unique<ObjectExpressionGenerationStrategy>(
    //   //         _codeGenerationContext);

    //   llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);
    //   llvm::Value *_elementToFill = Builder->CreateLoad(
    //       _codeGenerationContext->getValueStackHandler()->getLLVMType(),
    //       _codeGenerationContext->getValueStackHandler()->getValue());
    //   _codeGenerationContext->getValueStackHandler()->popAll();
    //   // objExpGenStrat->generateVariable(elementPtr,
    //   // _elementType->getStructName().str(),
    //   //                                  _elementToFill, _isGlobal);
    //   Builder->CreateStore(_elementToFill, elementPtr);
    // }
    // else {
    //   llvm::Value *itemValue =
    //       _expressionGenerationFactory
    //           ->createStrategy(
    //               containerExpression->getElementsRef()[i].get()->getKind())
    //           ->generateExpression(
    //               containerExpression->getElementsRef()[i].get());

    //   // Compute the address of the i-th element

    //   llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indices);

    //   if (_elementType != itemValue->getType()) {
    //     std::string elementTypeName =
    //         _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType);

    //     std::string itemValueTypeName =
    //         _codeGenerationContext->getMapper()->getLLVMTypeName(
    //             itemValue->getType());

    //     _codeGenerationContext->getLogger()->LogError(
    //         _containerName + " Container item type mismatch. Expected " +
    //         elementTypeName + " but got " + itemValueTypeName);

    //     return nullptr;
    //   }
    //   // Typed Container
    //   Builder->CreateStore(itemValue, elementPtr);
    // }
    indices.pop_back();
  }

  return nullptr;
}

llvm::Value *ContainerExpressionGenerationStrategy::createExpression(
    llvm::Type *arrayType, llvm::Value *v,
    BoundContainerExpression *containerExpression) {
  // UnTyped Container
  if (_codeGenerationContext->getDynamicType()->isDyn(_elementType)) {

    _codeGenerationContext->getLogger()->LogError(
        "Container of dynamic type is not supported");

    return nullptr;

    // std::string containerName = "";

    // if (_isGlobal) {
    //   containerName += FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX;
    // }

    // containerName += _containerName + "_" + std::to_string(i);

    // _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
    //     elementPtr, itemValue, itemValue->getType(), containerName);
  }

  if (containerExpression->getElementsRef().size() == 0) {
    std::unique_ptr<FillExpressionGenerationStrategy>
        fillExpressionGenerationStrategy =
            std::make_unique<FillExpressionGenerationStrategy>(
                _codeGenerationContext, _actualSizes, _elementType,
                _containerName);

    llvm::Constant *_defaultVal = nullptr;

    if (!llvm::isa<llvm::StructType>(_elementType)) {
      _defaultVal = llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(_elementType));
    } else {
      _defaultVal = llvm::Constant::getNullValue(_elementType);
    }

    fillExpressionGenerationStrategy->createExpressionLoop(
        arrayType, v, _defaultVal, _totalSize);
  }

  std::vector<llvm::Value *> indices = {Builder->getInt32(0)};

  createExpressionAtom(arrayType, v, containerExpression, indices, 0);

  return v;
}

llvm::Value *ContainerExpressionGenerationStrategy::createGlobalExpression(
    llvm::Type *arrayType, llvm::GlobalVariable *_globalVariable,
    BoundContainerExpression *containerExpression) {

  _isGlobal = true;

  this->createExpression(arrayType, _globalVariable, containerExpression);
  return nullptr;
}