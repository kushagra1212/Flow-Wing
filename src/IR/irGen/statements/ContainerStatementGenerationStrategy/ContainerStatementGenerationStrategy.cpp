#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {
  auto containerStatement = static_cast<BoundContainerStatement *>(statement);

  const std::string &containerName = containerStatement->getVariableNameRef();

  size_t actualSize = this->getActualContainerSize(containerStatement);

  size_t size = containerStatement->getEntryExpressionsRef().size();

  std::vector<llvm::Constant *> items(actualSize);
  llvm::Type *elementType = nullptr;

  if (containerStatement->getContainerTypeRef() !=
      Utils::type::UNKNOWN_CONTAINER) {

    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        Utils::toNonContainerType(containerStatement->getContainerTypeRef()));
  }

  this->generateContainerItems(containerStatement, items, elementType);

  llvm::Type *arrayType = llvm::ArrayType::get(elementType, actualSize);

  // Allocate memory on the stack for the array
  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, containerName);

  // Store the items in the allocated memory
  for (size_t i = 0; i < actualSize; i++) {
    llvm::Value *elementPtr = Builder->CreateGEP(
        arrayType, arrayAlloca, {Builder->getInt32(0), Builder->getInt32(i)});
    Builder->CreateStore(llvm::dyn_cast<llvm::Constant>(items[i]), elementPtr);
  }

  _codeGenerationContext->getAllocaChain()->setAllocaInst(containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

// TODO: Implement this
llvm::Value *ContainerStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);

  const std::string &containerName = containerStatement->getVariableNameRef();

  uint64_t actualSize = this->getActualContainerSize(containerStatement);

  uint64_t size = containerStatement->getEntryExpressionsRef().size();

  llvm::Type *elementType = nullptr;

  if (containerStatement->getContainerTypeRef() !=
      Utils::type::UNKNOWN_CONTAINER) {

    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        Utils::toNonContainerType(containerStatement->getContainerTypeRef()));
  }
  std::vector<llvm::Constant *> items(actualSize);

  this->generateContainerItems(containerStatement, items, elementType);

  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType = llvm::ArrayType::get(elementType, actualSize);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(arrayType), containerName);

  for (uint64_t i = 0; i < actualSize; i++) {

    llvm::Value *loadedValue = Builder->CreateLoad(arrayType, _globalVariable);
    llvm::Value *updatedValue =
        Builder->CreateInsertValue(loadedValue, items[i], (uint)i);

    Builder->CreateStore(updatedValue, _globalVariable);
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
    BoundContainerStatement *containerStatement,
    std::vector<llvm::Constant *> &items, llvm::Type *elementType) {

  uint64_t size = containerStatement->getEntryExpressionsRef().size();
  const std::string &containerName = containerStatement->getVariableNameRef();

  for (uint64_t i = 0; i < size; i++) {
    BoundExpression *entryExp =
        containerStatement->getEntryExpressionsRef()[i].get();

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