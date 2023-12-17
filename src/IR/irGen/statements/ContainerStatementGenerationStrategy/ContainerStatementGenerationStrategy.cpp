#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/BracketedExpressionGenerationStrategy/BracketedExpressionGenerationStrategy.h"
#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  return nullptr;
  // auto containerStatement = static_cast<BoundContainerStatement
  // *>(statement);

  // auto containerExpression = static_cast<BoundContainerExpression *>(
  //     containerStatement->getContainerExpressionRef().get());

  // const std::string &containerName =
  // containerStatement->getVariableNameRef();

  // size_t actualSize = this->getActualContainerSize(containerStatement);

  // size_t size = containerExpression->getElementsRef().size();

  // const Utils::type &containerType =
  // containerStatement->getContainerTypeRef();

  // std::vector<llvm::Constant *> items(actualSize);
  // llvm::Type *elementType = nullptr;

  // if (containerType != Utils::type::UNKNOWN_CONTAINER) {

  //   elementType =
  //   _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
  //       Utils::toNonContainerType(containerType));
  // }

  // this->generateContainerItems(containerExpression, items, elementType,
  //                              containerName);

  // llvm::Type *arrayType = llvm::ArrayType::get(elementType, actualSize);

  // // Allocate memory on the stack for the array
  // llvm::AllocaInst *arrayAlloca =
  //     Builder->CreateAlloca(arrayType, nullptr, containerName);

  // // Store the items in the allocated memory
  // for (size_t i = 0; i < actualSize; i++) {
  //   llvm::Value *elementPtr = Builder->CreateGEP(
  //       arrayType, arrayAlloca, {Builder->getInt32(0),
  //       Builder->getInt32(i)});
  //   Builder->CreateStore(llvm::dyn_cast<llvm::Constant>(items[i]),
  //   elementPtr);
  // }

  // _codeGenerationContext->getAllocaChain()->setAllocaInst(containerName,
  //                                                         arrayAlloca);

  // return arrayAlloca;
}

llvm::Value *ContainerStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);

  const Utils::type &containerType = containerStatement->getContainerTypeRef();

  llvm::Type *elementType = nullptr;

  if (containerType != Utils::type::UNKNOWN_CONTAINER) {

    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        Utils::toNonContainerType(containerType));
  }

  uint64_t actualSize = this->getActualContainerSize(containerStatement);
  std::string containerName = containerStatement->getVariableNameRef();

  BoundBracketedExpression *bracketedExpression =
      static_cast<BoundBracketedExpression *>(
          containerStatement->getBracketedExpressionRef().get());

  ExpressionGenerationStrategy *strategy =
      (_expressionGenerationFactory->createStrategy(
           bracketedExpression->getKind()))
          .get();

  if (auto *specificStrategy =
          dynamic_cast<BracketedExpressionGenerationStrategy *>(strategy)) {
    return specificStrategy->wrappedExpression(bracketedExpression, actualSize,
                                               elementType, containerName);
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