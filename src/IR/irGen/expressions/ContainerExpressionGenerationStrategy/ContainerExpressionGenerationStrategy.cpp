#include "ContainerExpressionGenerationStrategy.h"

// Explicit instantiations for the template class
template class ContainerExpressionGenerationStrategy<uint64_t, llvm::Type *,
                                                     std::string>;

// Explicit instantiations for the template Constructor
template ContainerExpressionGenerationStrategy<uint64_t, llvm::Type *,
                                               std::string>::
    ContainerExpressionGenerationStrategy(CodeGenerationContext *context);

template <typename AS, typename ET, typename CN>
ContainerExpressionGenerationStrategy<AS, ET, CN>::
    ContainerExpressionGenerationStrategy(CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

template <typename AS, typename ET, typename CN>
ContainerExpressionGenerationStrategy<AS, ET, CN>::
    ContainerExpressionGenerationStrategy(CodeGenerationContext *context,
                                          AS actualSize, ET elementType,
                                          CN containerName)
    : ExpressionGenerationStrategy(context), m_actualSize(actualSize),
      m_elementType(elementType), m_containerName(containerName) {}

template <typename AS, typename ET, typename CN>
llvm::Value *ContainerExpressionGenerationStrategy<AS, ET, CN>::
    ContainerExpressionGenerationStrategy::generateExpression(
        BoundExpression *expression) {

  return nullptr;
}
template <typename AS, typename ET, typename CN>
llvm::Value *ContainerExpressionGenerationStrategy<AS, ET, CN>::
    ContainerExpressionGenerationStrategy::generateGlobalExpression(
        BoundExpression *expression) {

  std::cout << "ContainerExpressionGenerationStrategy::generateGlobalExpression"
            << std::endl;

  BoundContainerExpression *containerExpression =
      static_cast<BoundContainerExpression *>(expression);

  uint64_t size = containerExpression->getElementsRef().size();

  std::vector<llvm::Constant *> items(m_actualSize);

  for (uint64_t i = 0; i < size; i++) {
    BoundExpression *entryExp = containerExpression->getElementsRef()[i].get();

    llvm::Value *itemValue =
        _expressionGenerationFactory->createStrategy(entryExp->getKind())
            ->generateExpression(entryExp);

    if (m_elementType && m_elementType != itemValue->getType()) {
      std::string elementTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(m_elementType);

      std::string itemValueTypeName =
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              itemValue->getType());

      _codeGenerationContext->getLogger()->LogError(
          m_containerName + " Container item type mismatch. Expected " +
          elementTypeName + " but got " + itemValueTypeName);

      return nullptr;
    }

    items[i] = llvm::dyn_cast<llvm::Constant>(itemValue);
  }
  // Load and Store the items in the allocated memory

  llvm::ArrayType *arrayType =
      llvm::ArrayType::get(m_elementType, m_actualSize);

  llvm::GlobalVariable *_globalVariable = new llvm::GlobalVariable(
      *TheModule, arrayType, false, llvm::GlobalValue::ExternalLinkage,
      llvm::Constant::getNullValue(arrayType), m_containerName);

  for (uint64_t i = 0; i < m_actualSize; i++) {

    llvm::Value *loadedValue = Builder->CreateLoad(arrayType, _globalVariable);
    llvm::Value *updatedValue =
        Builder->CreateInsertValue(loadedValue, items[i], (uint)i);

    Builder->CreateStore(updatedValue, _globalVariable);
  }
  return nullptr;
}