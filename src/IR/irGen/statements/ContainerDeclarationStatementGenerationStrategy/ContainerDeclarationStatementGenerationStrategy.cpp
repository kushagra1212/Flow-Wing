#include "ContainerDeclarationStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

ContainerDeclarationStatementGenerationStrategy::
    ContainerDeclarationStatementGenerationStrategy(
        CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateCommonStatement() {

  this->calcActualContainerSize(_arrayTypeExpression);

  if (_arrayTypeExpression->isTrivialType()) {
    _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        _arrayTypeExpression->getElementType());

  } else {
    BoundObjectTypeExpression *objectTypeExpression =
        static_cast<BoundObjectTypeExpression *>(
            _arrayTypeExpression->getNonTrivialElementType().get());

    _elementType =
        _codeGenerationContext->getType(objectTypeExpression->getTypeName())
            .getStructType();
  }

  llvm::ArrayType *arrayType = nullptr;

  _codeGenerationContext->getMultiArrayType(arrayType, _actualSizes,
                                            _elementType);

  llvm::Constant *_defaultVal = llvm::Constant::getNullValue(arrayType);

  std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentStrategy =
      std::make_unique<AssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);

  llvm::Value *ptr = nullptr;

  // if (_isDeclarationNeeded) {
  ptr = _codeGenerationContext->createMemoryGetPtr(arrayType, _containerName,
                                                   _memoryKind);
  assignmentStrategy->initDefaultValue(arrayType, ptr);
  _variableDeclExpr->setLLVMVariable({ptr, arrayType});
  //   return ptr;
  // } else {
  _codeGenerationContext->getAllocaChain()->setPtr(_containerName,
                                                   {ptr, arrayType});

  if (!_initializer)
    return ptr;

  return assignmentStrategy->handleAssignExpression(
      ptr, arrayType, _containerName, _initializer);
  // }
}

void ContainerDeclarationStatementGenerationStrategy::initialize(
    BoundVariableDeclaration *contVarDec) {
  _containerName = contVarDec->getVariableName();
  _initializer = contVarDec->getInitializerPtr().get();
  _arrayTypeExpression = static_cast<BoundArrayTypeExpression *>(
      contVarDec->getTypeExpression().get());
  _memoryKind = contVarDec->getMemoryKind();
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  _variableDeclExpr = static_cast<BoundVariableDeclaration *>(statement);

  if (_variableDeclExpr->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    _variableDeclExpr->setMemoryKind(BinderKindUtils::MemoryKind::Stack);

  initialize(_variableDeclExpr);

  return this->generateCommonStatement();
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  _variableDeclExpr = static_cast<BoundVariableDeclaration *>(statement);

  if (_variableDeclExpr->getMemoryKind() == BinderKindUtils::MemoryKind::None)
    _variableDeclExpr->setMemoryKind(BinderKindUtils::MemoryKind::Global);

  initialize(_variableDeclExpr);

  return this->generateCommonStatement();
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::declareLocal(
    BoundStatement *statement) {

  _isDeclarationNeeded = true;
  return this->generateStatement(statement);
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::declareGlobal(
    BoundStatement *statement) {

  _isDeclarationNeeded = true;
  return this->generateGlobalStatement(statement);
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateCommonStatement(
    BoundArrayTypeExpression *arrayTypeExpression,
    const std::string &containerName, BoundExpression *initializer) {

  _containerName = containerName;
  _initializer = initializer;
  _arrayTypeExpression = arrayTypeExpression;
  _memoryKind = BinderKindUtils::MemoryKind::Stack;

  return this->generateCommonStatement();
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateCommonStatement(
    std ::vector<uint64_t> actualSizes, llvm::Type *arrayElementType,
    const std::string &containerName, BoundExpression *initializer) {

  _actualSizes = actualSizes;
  _containerName = containerName;

  _elementType = arrayElementType;

  BinderKindUtils::BoundNodeKind kind = initializer->getKind();

  switch (kind) {
  case BinderKindUtils::BoundNodeKind::BoundBracketedExpression: {
    return generateBracketLocalExpression(
        (BoundBracketedExpression *)initializer);
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    if (!canGenerateCallExpression(initializer)) {
      return nullptr;
    }
    llvm::ArrayType *arrayType = nullptr;

    llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
        _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

    _codeGenerationContext->getMultiArrayType(arrayType, _actualSizes,
                                              _elementType);

    if (!_allocaInst) {
      llvm::AllocaInst *alloca =
          Builder->CreateAlloca(arrayType, nullptr, _containerName);

      _codeGenerationContext->getAllocaChain()->setPtr(_containerName,
                                                       {alloca, arrayType});
      _allocaInst = alloca;
    }

    // Fill the array with default values

    // Store the result of the call in the localVariable variable
    Builder->CreateStore(_loadedValue, _allocaInst);

    return nullptr;
  }

  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Container Expression Type ");
    break;
  }
  }
  return nullptr;
}

const bool
ContainerDeclarationStatementGenerationStrategy::canGenerateCallExpression(
    BoundExpression *callExp) {
  llvm::Value *value =
      _expressionGenerationFactory->createStrategy(callExp->getKind())
          ->generateExpression(callExp);

  llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(value);
  auto *calledFunction = calledInst->getCalledFunction();
  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<uint64_t> actualSizes;
  _codeGenerationContext->getRetrunedArrayType(calledFunction, arrayType,
                                               elementType, actualSizes);

  if (elementType != _elementType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType) +
        " but function " + calledFunction->getName().str() +
        " is returning array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(elementType));

    return false;
  }

  if (actualSizes.size() != _actualSizes.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Dimensions of the Containers Must Be same, Expected array to be "
        "of " +
        std::to_string(_actualSizes.size()) + " Dimension but found " +
        "array of " + std::to_string(actualSizes.size()) + " Dimension");

    return false;
  }

  for (uint64_t i = 0; i < actualSizes.size(); i++) {
    if (actualSizes[i] != _actualSizes[i]) {
      _codeGenerationContext->getLogger()->LogError(
          "Dimensions of the Containers must be same, Expected array's " +
          std::to_string(i) +
          " th Dimension  to "
          "be "
          "equal to " +
          std::to_string(_actualSizes[i]) + ", but found " +
          std::to_string(actualSizes[i]));

      return false;
    }
  }

  _loadedValue = Builder->CreateLoad(arrayType, calledInst);

  return true;
}

const bool
ContainerDeclarationStatementGenerationStrategy::canGenerateVariableExpression(
    BoundExpression *exp) {

  _expressionGenerationFactory->createStrategy(exp->getKind())
      ->generateExpression(exp);

  if (!_codeGenerationContext->getValueStackHandler()->isArrayType()) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType));
    return false;
  }

  llvm::Value *value =
      _codeGenerationContext->getValueStackHandler()->getValue();

  llvm::ArrayType *arrayType = llvm::cast<llvm::ArrayType>(
      _codeGenerationContext->getValueStackHandler()->getLLVMType());

  _loadedValue = Builder->CreateLoad(arrayType, value);
  _codeGenerationContext->getValueStackHandler()->popAll();
  llvm::Type *elementType = arrayType;
  std::vector<uint64_t> actualSizes;
  _codeGenerationContext->createArraySizesAndArrayElementType(actualSizes,
                                                              elementType);

  if (elementType != _elementType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an array of " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_elementType) +
        " but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(elementType));

    return false;
  }

  if (actualSizes.size() != _actualSizes.size()) {
    _codeGenerationContext->getLogger()->LogError(
        "Dimensions of the Containers Must Be same, Expected array to be "
        "of " +
        std::to_string(_actualSizes.size()) + " Dimension but found " +
        "array of " + std::to_string(actualSizes.size()) + " Dimension");

    return false;
  }

  for (uint64_t i = 0; i < actualSizes.size(); i++) {
    if (actualSizes[i] != _actualSizes[i]) {
      _codeGenerationContext->getLogger()->LogError(
          "Dimensions of the Containers must be same, Expected array's " +
          std::to_string(i) +
          " th Dimension  to "
          "be "
          "equal to " +
          std::to_string(_actualSizes[i]) + ", but found " +
          std::to_string(actualSizes[i]));

      return false;
    }
  }

  return true;
}

llvm::Value *ContainerDeclarationStatementGenerationStrategy::
    generateBracketGlobalExpression(
        BoundBracketedExpression *bracketedExpression) {
  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {
  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

    return specificStrategy->generateGlobalExpression(
        bracketedExpression->getExpressionRef().get());
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

    return specificStrategy->generateGlobalExpression(
        bracketedExpression->getExpressionRef().get());
  }

  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Container Expression Type ");
    break;
  }
  }

  return nullptr;
}

llvm::Value *
ContainerDeclarationStatementGenerationStrategy::generateBracketLocalExpression(
    BoundBracketedExpression *bracketedExpression) {
  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {
  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

    if (_allocaInst)
      specificStrategy->setAllocaInst(_allocaInst);

    return specificStrategy->generateExpression(
        bracketedExpression->getExpressionRef().get());
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

    if (_allocaInst)
      specificStrategy->setAllocaInst(_allocaInst);

    return specificStrategy->generateExpression(
        bracketedExpression->getExpressionRef().get());
  }

  default: {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Container Expression Type ");
    break;
  }
  }

  return nullptr;
}

void ContainerDeclarationStatementGenerationStrategy::calcActualContainerSize(
    BoundArrayTypeExpression *arrayTypeExpression) {
  for (uint64_t i = 0; i < arrayTypeExpression->getDimensions().size(); i++) {
    llvm::Value *sizeValue =
        _expressionGenerationFactory
            ->createStrategy(
                arrayTypeExpression->getDimensions()[i].get()->getKind())
            ->generateExpression(arrayTypeExpression->getDimensions()[i].get());

    llvm::ConstantInt *sizeConstInt =
        llvm::dyn_cast<llvm::ConstantInt>(sizeValue);
    if (!sizeConstInt) {
      _codeGenerationContext->getLogger()->LogError(
          "Container size must be an integer");
      return;
    }

    _actualSizes.push_back(sizeConstInt->getZExtValue());
  }
}
