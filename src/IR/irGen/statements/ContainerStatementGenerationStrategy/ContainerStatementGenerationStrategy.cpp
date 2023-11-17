#include "ContainerStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ContainerStatementGenerationStrategy::ContainerStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ContainerStatementGenerationStrategy::generateStatement(
    BoundStatement *statement) {

  auto containerStatement = static_cast<BoundContainerStatement *>(statement);
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)containerStatement
          ->getIdentifierExpression()
          .get();

  std::any value = literalExpression->getValue();

  std::string containerName = std::any_cast<std::string>(value);

  size_t size = containerStatement->getEntryExpressions().size();

  std::vector<llvm::Constant *> items(size);
  llvm::Type *elementType =
      _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
          containerStatement->getContainerType());

  for (uint64_t i = 0; i < size; i++) {

    llvm::Value *itemValue =
        _expressionGenerationFactory
            ->createStrategy(
                containerStatement->getEntryExpressions()[i].get()->getKind())
            ->generateExpression(
                containerStatement->getEntryExpressions()[i].get());

    if (elementType != itemValue->getType()) {
      std::string elementTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(elementType);

      std::string itemValueTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              itemValue->getType());

      _codeGenerationContext->getLogger()->LogError(
          containerName + " Container item type mismatch. Expected " +
          elementTypeName + " but got " + itemValueTypeName);

      return nullptr;
    }

    items[i] = llvm::dyn_cast<llvm::Constant>(itemValue);
  }

  llvm::Type *arrayType = llvm::ArrayType::get(elementType, size);

  // Allocate memory on the stack for the array
  llvm::AllocaInst *arrayAlloca =
      Builder->CreateAlloca(arrayType, nullptr, containerName);

  // Store the items in the allocated memory
  for (unsigned int i = 0; i < size; i++) {
    llvm::Value *elementPtr = Builder->CreateGEP(
        arrayType, arrayAlloca, {Builder->getInt32(0), Builder->getInt32(i)});
    Builder->CreateStore(items[i], elementPtr);
  }

  _codeGenerationContext->getAllocaChain()->setAllocaInst(containerName,
                                                          arrayAlloca);

  return arrayAlloca;
}

llvm::Value *ContainerStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {
  return this->generateStatement(statement);
}