#include "BracketedExpressionGenerationStrategy.h"

BracketedExpressionGenerationStrategy::BracketedExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

void BracketedExpressionGenerationStrategy::setPreviousGlobalVariable(
    llvm::GlobalVariable *previousGlobalVariable) {
  _previousGlobalVariable = previousGlobalVariable;
}

void BracketedExpressionGenerationStrategy::setAllocatedVariable(
    llvm::AllocaInst *allocaInst) {
  _allocaInst = allocaInst;
}

void BracketedExpressionGenerationStrategy::setContainerName(
    const std::string &containerName) {
  _containerName = containerName;
}

llvm::Value *BracketedExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  if (expression->getKind() !=
      BinderKindUtils::BoundNodeKind::BoundBracketedExpression) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected bracketed expression in assignment expression");
    return nullptr;
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bracketedExpression->getLocation());

  BinderKindUtils::BoundNodeKind kind =
      bracketedExpression->getExpressionRef().get()->getKind();

  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<uint64_t> dimensions;
  if (llvm::isa<llvm::ArrayType>(_allocaInst->getAllocatedType())) {
    arrayType = llvm::cast<llvm::ArrayType>(_allocaInst->getAllocatedType());
    elementType =
        _codeGenerationContext->getArrayElementTypeMetadata(_allocaInst);
    _codeGenerationContext->getArraySizeMetadata(_allocaInst, dimensions);
    if (elementType->isIntegerTy(8)) {
      _codeGenerationContext->getLogger()->LogError(
          "Variable " + _containerName +
          " not found in assignment expression ");
      return nullptr;
    }
  }

  switch ((kind)) {
  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
    BoundContainerExpression *containerExpression =
        static_cast<BoundContainerExpression *>(
            bracketedExpression->getExpressionRef().get());

    std::unique_ptr<ContainerExpressionGenerationStrategy>
        containerExpressionGenerationStrategy =
            std::make_unique<ContainerExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!containerExpressionGenerationStrategy->canGenerateExpression(
            containerExpression)) {
      return nullptr;
    }

    return containerExpressionGenerationStrategy->createLocalExpression(
        arrayType, _allocaInst, containerExpression);
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
    BoundFillExpression *fillExpression = static_cast<BoundFillExpression *>(
        bracketedExpression->getExpressionRef().get());

    std::unique_ptr<FillExpressionGenerationStrategy>
        fillExpressionGenerationStrategy =
            std::make_unique<FillExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!fillExpressionGenerationStrategy->canGenerateExpression(
            fillExpression)) {
      return nullptr;
    }

    return fillExpressionGenerationStrategy->createLocalExpression(arrayType,
                                                                   _allocaInst);
  }

  default:
    break;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + _containerName + " not found in assignment expression ");

  return nullptr;
}
llvm::Value *BracketedExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  if (expression->getKind() !=
      BinderKindUtils::BoundNodeKind::BoundBracketedExpression) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected bracketed expression in assignment expression");

    return nullptr;
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bracketedExpression->getLocation());

  BinderKindUtils::BoundNodeKind kind =
      bracketedExpression->getExpressionRef().get()->getKind();

  if (!_previousGlobalVariable) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + _containerName + " not found in assignment expression ");
    return nullptr;
  }

  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<uint64_t> dimensions;
  if (llvm::isa<llvm::GlobalVariable>(_previousGlobalVariable)) {
    if (llvm::isa<llvm::ArrayType>(_previousGlobalVariable->getValueType())) {
      arrayType =
          llvm::cast<llvm::ArrayType>(_previousGlobalVariable->getValueType());
      elementType = _codeGenerationContext->getArrayElementTypeMetadata(
          _previousGlobalVariable);
      _codeGenerationContext->getArraySizeMetadata(_previousGlobalVariable,
                                                   dimensions);
      if (elementType->isIntegerTy(8)) {
        _codeGenerationContext->getLogger()->LogError(
            "Variable " + _containerName +
            " not found in assignment expression ");
        return nullptr;
      }
    }
  }

  switch ((kind)) {
  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
    BoundContainerExpression *containerExpression =
        static_cast<BoundContainerExpression *>(
            bracketedExpression->getExpressionRef().get());

    std::unique_ptr<ContainerExpressionGenerationStrategy>
        containerExpressionGenerationStrategy =
            std::make_unique<ContainerExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!containerExpressionGenerationStrategy->canGenerateExpression(
            containerExpression)) {
      return nullptr;
    }

    return containerExpressionGenerationStrategy->createGlobalExpression(
        arrayType, _previousGlobalVariable, containerExpression);
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
    BoundFillExpression *fillExpression = static_cast<BoundFillExpression *>(
        bracketedExpression->getExpressionRef().get());

    std::unique_ptr<FillExpressionGenerationStrategy>
        fillExpressionGenerationStrategy =
            std::make_unique<FillExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!fillExpressionGenerationStrategy->canGenerateExpression(
            fillExpression)) {
      return nullptr;
    }

    return fillExpressionGenerationStrategy->createGlobalExpression(
        arrayType, _previousGlobalVariable);
  }

  default:
    break;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + _containerName + " not found in assignment expression ");

  return nullptr;
}

llvm::Value *BracketedExpressionGenerationStrategy::assignBracketExpression(
    BoundBracketedExpression *&bracketedExpression, llvm::Value *&lhsPtr,
    llvm::ArrayType *arrayType, std::string &containerName) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bracketedExpression->getLocation());

  BinderKindUtils::BoundNodeKind kind =
      bracketedExpression->getExpressionRef().get()->getKind();

  llvm::Type *elementType = arrayType;
  std::vector<uint64_t> dimensions;
  _codeGenerationContext->createArraySizesAndArrayElementType(dimensions,
                                                              elementType);

  switch ((kind)) {
  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {
    BoundContainerExpression *containerExpression =
        static_cast<BoundContainerExpression *>(
            bracketedExpression->getExpressionRef().get());

    std::unique_ptr<ContainerExpressionGenerationStrategy>
        containerExpressionGenerationStrategy =
            std::make_unique<ContainerExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!containerExpressionGenerationStrategy->canGenerateExpression(
            containerExpression)) {
      return nullptr;
    }

    return containerExpressionGenerationStrategy->createExpression(
        arrayType, lhsPtr, containerExpression);
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {
    BoundFillExpression *fillExpression = static_cast<BoundFillExpression *>(
        bracketedExpression->getExpressionRef().get());

    std::unique_ptr<FillExpressionGenerationStrategy>
        fillExpressionGenerationStrategy =
            std::make_unique<FillExpressionGenerationStrategy>(
                _codeGenerationContext, dimensions, elementType,
                _containerName);

    if (!fillExpressionGenerationStrategy->canGenerateExpression(
            fillExpression)) {
      return nullptr;
    }

    return fillExpressionGenerationStrategy->createExpressionLoopWrapper(
        arrayType, lhsPtr);
  }

  default:
    break;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + _containerName + " not found in assignment expression ");

  return nullptr;
}