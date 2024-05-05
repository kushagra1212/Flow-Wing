
#include "ClassStatementGenerationStrategy.h"

ClassStatementGenerationStrategy::ClassStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}
llvm::Value *
ClassStatementGenerationStrategy::generateStatement(BoundStatement *statement) {
  return nullptr;
}
llvm::Value *ClassStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  // Add handlers
  _codeGenerationContext->getNamedValueChain()->addHandler(
      new NamedValueTable());
  _codeGenerationContext->getAllocaChain()->addHandler(
      std::make_unique<AllocaTable>());
  _codeGenerationContext->getTypeChain()->addHandler(
      std::make_unique<TypeTable>());
  _codeGenerationContext->getCustomTypeChain()->addHandler(
      std::make_unique<CustomTypeStatementTable>());

  BoundClassStatement *boundClassStatement =
      static_cast<BoundClassStatement *>(statement);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundClassStatement->getLocation());

  std::unique_ptr<Class> classObject =
      std::make_unique<Class>(boundClassStatement->getClassName());

  std::vector<llvm::Type *> vTableElements = {};

  std::vector<llvm::Type *> classElements = {};
  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      customTypeStatementGenerationStrategy =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);
  for (int64_t i = 0; i < boundClassStatement->getMemberVariablesRef().size();
       i++) {

    classElements.push_back(customTypeStatementGenerationStrategy->getType(
        boundClassStatement->getMemberVariablesRef()[i]
            ->getTypeExpression()
            .get()));
    classObject->setElementIndex(
        boundClassStatement->getMemberVariablesRef()[i]->getVariableName(), i);
  }
  classElements.push_back(llvm::Type::getInt8PtrTy(*TheContext));

  llvm::StructType *classType = llvm::StructType::create(
      *TheContext, classElements, boundClassStatement->getClassName());

  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0; i < boundClassStatement->getMemberFunctionsRef().size();
       i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundClassStatement->getMemberFunctionsRef()[i].get());
    vTableElements.push_back(functionDeclarationGenerationStrategy->generate(
        fd, {llvm::Type::getInt8PtrTy(*TheContext)}));
    classObject->setVTableElementIndex(fd->getFunctionNameRef(), i);
  }

  llvm::StructType *_vTableType =
      llvm::StructType::create(*TheContext, vTableElements,
                               "vTable_" + boundClassStatement->getClassName());

  classObject->setVTableType(_vTableType);
  classObject->setClassType(classType);

  _codeGenerationContext->_classTypes[boundClassStatement->getClassName()] =
      std::move(classObject);

  // Remove handlers
  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
  _codeGenerationContext->getTypeChain()->removeHandler();
  _codeGenerationContext->getCustomTypeChain()->removeHandler();
  return nullptr;
}