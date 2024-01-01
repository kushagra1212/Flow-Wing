#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "../../expressions/FillExpressionGenerationStrategy/FillExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  const Utils::type &containerElementType =
      containerStatement->getContainerTypeRef();
  this->calcActualContainerSize(containerStatement);
  _containerName = containerStatement->getVariableNameRef();

  _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
      Utils::toContainerElementType(containerElementType));

  if (containerElementType == Utils::type::UNKNOWN_CONTAINER) {
    _codeGenerationContext->getLogger()->LogError(
        "Container of dynamic type is not supported");

    _elementType = _codeGenerationContext->getDynamicType()->get();
  }

  BinderKindUtils::BoundNodeKind kind =
      containerStatement->getRHSExpressionRef()->getKind();

  switch (kind) {
  case BinderKindUtils::BoundNodeKind::BoundBracketedExpression: {
    return generateBracketLocalExpression(
        (BoundBracketedExpression *)containerStatement->getRHSExpressionRef()
            .get());
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {

    if (!canGenerateCallExpression(
            containerStatement->getRHSExpressionRef().get())) {
      return nullptr;
    }
    llvm::ArrayType *arrayType = nullptr;

    llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
        _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

    _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                              _actualSizes, _elementType);

    llvm::AllocaInst *arrayAlloca =
        Builder->CreateAlloca(arrayType, nullptr, _containerName);

    // Fill the array with default values

    _codeGenerationContext->getAllocaChain()->setAllocaInst(_containerName,
                                                            arrayAlloca);

    // Store the result of the call in the localVariable variable
    Builder->CreateStore(_loadedValue, arrayAlloca);

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

const bool ContainerStatementGenerationStrategy::canGenerateCallExpression(
    BoundExpression *callExp) {
  llvm::Value *value =
      _expressionGenerationFactory->createStrategy(callExp->getKind())
          ->generateExpression(callExp);

  llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(value);
  auto *calledFunction = calledInst->getCalledFunction();
  llvm::ArrayType *arrayType = nullptr;
  llvm::Type *elementType = nullptr;
  std::vector<size_t> actualSizes;
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

llvm::Value *
ContainerStatementGenerationStrategy::generateBracketGlobalExpression(
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
ContainerStatementGenerationStrategy::generateBracketLocalExpression(
    BoundBracketedExpression *bracketedExpression) {
  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {

  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {

    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

    return specificStrategy->generateExpression(
        bracketedExpression->getExpressionRef().get());
  }

  case BinderKindUtils::BoundNodeKind::BoundFillExpression: {

    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, _actualSizes, _elementType, _containerName);

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
llvm::Value *ContainerStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  const Utils::type &containerElementType =
      containerStatement->getContainerTypeRef();
  this->calcActualContainerSize(containerStatement);
  _containerName = containerStatement->getVariableNameRef();

  _elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
      Utils::toContainerElementType(containerElementType));

  if (containerElementType == Utils::type::UNKNOWN_CONTAINER) {
    _codeGenerationContext->getLogger()->LogError(
        "Container of dynamic type is not supported");
    return nullptr;
  }

  BinderKindUtils::BoundNodeKind kind =
      containerStatement->getRHSExpressionRef()->getKind();

  switch (kind) {
  case BinderKindUtils::BoundNodeKind::BoundBracketedExpression: {
    return generateBracketGlobalExpression(
        (BoundBracketedExpression *)containerStatement->getRHSExpressionRef()
            .get());
  }
  case BinderKindUtils::BoundNodeKind::CallExpression: {
    if (!canGenerateCallExpression(
            containerStatement->getRHSExpressionRef().get())) {
      return nullptr;
    }

    llvm::ArrayType *arrayType = nullptr;

    // Create a default value for the array

    llvm::Constant *_defaultVal = llvm::cast<llvm::Constant>(
        _codeGenerationContext->getMapper()->getDefaultValue(_elementType));

    _codeGenerationContext->getMultiArrayType(arrayType, _defaultVal,
                                              _actualSizes, _elementType);
    llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
        *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
        _defaultVal, _containerName);

    _codeGenerationContext->setArraySizeMetadata(_globalVariable, _actualSizes);
    _codeGenerationContext->setArrayElementTypeMetadata(_globalVariable,
                                                        _elementType);

    // Store the result of the call in the _globalVariable variable
    Builder->CreateStore(_loadedValue, _globalVariable);
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

void ContainerStatementGenerationStrategy::calcActualContainerSize(
    BoundContainerStatement *containerStatement) {

  for (uint64_t i = 0;
       i < containerStatement->getContainerSizeExpressions().size(); i++) {
    llvm::Value *sizeValue =
        _expressionGenerationFactory
            ->createStrategy(
                containerStatement->getContainerSizeExpressions()[i]
                    .get()
                    ->getKind())
            ->generateExpression(
                containerStatement->getContainerSizeExpressions()[i].get());

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
