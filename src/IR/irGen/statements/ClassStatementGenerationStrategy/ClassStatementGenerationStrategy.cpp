
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

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      customTypeStatementGenerationStrategy =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0; i < boundClassStatement->getCustomTypesRef().size();
       i++) {
    BoundCustomTypeStatement *customTypeStatement =
        static_cast<BoundCustomTypeStatement *>(
            boundClassStatement->getCustomTypesRef()[i].get());
    std::string typeName = boundClassStatement->getClassName() +
                           "_:" + customTypeStatement->getTypeNameAsString();

    customTypeStatement->setTypeNameAsString(typeName);

    customTypeStatementGenerationStrategy->generateForClassElement(
        customTypeStatement, boundClassStatement->getClassName());
  }

  std::unique_ptr<Class> classObject =
      std::make_unique<Class>(boundClassStatement->getClassName());
  for (auto &keyPair : boundClassStatement->getKeyPairsRef()) {
    classObject->addKeyTypePair(keyPair.first, keyPair.second);
  }
  std::vector<llvm::Type *> classElements = {};

  for (int64_t i = 0; i < boundClassStatement->getMemberVariablesRef().size();
       i++) {

    classElements.push_back(
        customTypeStatementGenerationStrategy->getClassElementType(
            boundClassStatement->getMemberVariablesRef()[i]
                ->getTypeExpression()
                .get(),
            boundClassStatement->getClassName()));
    classObject->setElementIndex(
        boundClassStatement->getMemberVariablesRef()[i]->getVariableName(), i);
  }

  //? Pointer to VTable
  //! Using Alernate Approach
  //   classElements.push_back(llvm::Type::getInt8PtrTy(*TheContext));

  llvm::StructType *classType = llvm::StructType::create(
      *TheContext, classElements, boundClassStatement->getClassName());

  _codeGenerationContext->_classLLVMTypes[boundClassStatement->getClassName()] =
      classType;
  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);
  uint64_t count = 0;

  for (int64_t i = 0; i < boundClassStatement->getMemberFunctionsRef().size();
       i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundClassStatement->getMemberFunctionsRef()[i].get());

    if (!fd->isOnlyDeclared()) {
      llvm::Function *F = functionDeclarationGenerationStrategy->generate(
          fd, {llvm::Type::getInt8PtrTy(*TheContext)},
          boundClassStatement->getClassName());
      classObject->insertFunctionType(fd->getFunctionNameRef(), F);
      classObject->setVTableElementIndex(fd->getFunctionNameRef(), count);
      count++;
    }
  }

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