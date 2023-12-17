#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ContainerExpressionGenerationStrategy/ContainerExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  const Utils::type &containerType = containerStatement->getContainerTypeRef();
  uint64_t actualSize = this->getActualContainerSize(containerStatement);
  const std::string &containerName = containerStatement->getVariableNameRef();

  llvm::Type *elementType = nullptr;

  if (containerType != Utils::type::UNKNOWN_CONTAINER) {

    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        Utils::toNonContainerType(containerType));
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(
          containerStatement->getBracketedExpressionRef().get());

  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {

  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {

    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, actualSize, elementType, containerName);

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
  const Utils::type &containerType = containerStatement->getContainerTypeRef();
  uint64_t actualSize = this->getActualContainerSize(containerStatement);
  const std::string &containerName = containerStatement->getVariableNameRef();

  llvm::Type *elementType = nullptr;

  if (containerType != Utils::type::UNKNOWN_CONTAINER) {

    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        Utils::toNonContainerType(containerType));
  }

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(
          containerStatement->getBracketedExpressionRef().get());

  BinderKindUtils::BoundNodeKind bracketedExpressionKind =
      bracketedExpression->getExpressionRef().get()->getKind();

  switch (bracketedExpressionKind) {

  case BinderKindUtils::BoundNodeKind::BoundContainerExpression: {

    std::unique_ptr<ContainerExpressionGenerationStrategy> specificStrategy =
        std::make_unique<ContainerExpressionGenerationStrategy>(
            _codeGenerationContext, actualSize, elementType, containerName);

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

size_t ContainerStatementGenerationStrategy::getActualContainerSize(
    BoundContainerStatement *containerStatement) {

  llvm::Value *sizeValue =
      _expressionGenerationFactory
          ->createStrategy(containerStatement->getContainerSizeExpressionRef()
                               .get()
                               ->getKind())
          ->generateExpression(
              containerStatement->getContainerSizeExpressionRef().get());

  llvm::ConstantInt *sizeConstInt =
      llvm::dyn_cast<llvm::ConstantInt>(sizeValue);
  if (!sizeConstInt) {
    _codeGenerationContext->getLogger()->LogError(
        "Container size must be a constant integer");
    return 0;
  }

  return sizeConstInt->getZExtValue();
}

void ContainerStatementGenerationStrategy::generateContainerItems(
    BoundContainerExpression *containerExpression,
    std::vector<llvm::Constant *> &items, llvm::Type *elementType,
    const std::string &containerName) {

  uint64_t size = containerExpression->getElementsRef().size();

  for (uint64_t i = 0; i < size; i++) {
    BoundExpression *entryExp = containerExpression->getElementsRef()[i].get();

    llvm::Value *itemValue =
        _expressionGenerationFactory->createStrategy(entryExp->getKind())
            ->generateExpression(entryExp);

    if (elementType && elementType != itemValue->getType()) {
      std::string elementTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(elementType);

      std::string itemValueTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              itemValue->getType());

      _codeGenerationContext->getLogger()->LogError(
          containerName + " Container item type mismatch. Expected " +
          elementTypeName + " but got " + itemValueTypeName);

      return;
    }

    items[i] = llvm::dyn_cast<llvm::Constant>(itemValue);
  }
}