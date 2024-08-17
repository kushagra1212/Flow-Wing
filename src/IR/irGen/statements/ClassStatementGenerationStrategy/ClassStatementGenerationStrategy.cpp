
#include "ClassStatementGenerationStrategy.h"

ClassStatementGenerationStrategy::ClassStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}
llvm::Value *
ClassStatementGenerationStrategy::generateStatement(BoundStatement *statement) {
  return nullptr;
}

llvm::Value *
ClassStatementGenerationStrategy::generateClassType(BoundStatement *statement) {
  BoundClassStatement *boundClassStatement =
      static_cast<BoundClassStatement *>(statement);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundClassStatement->getLocation());
  _codeGenerationContext->setCurrentClassName(
      boundClassStatement->getClassName());

  DEBUG_LOG("LLVM: Declaring Class: " + boundClassStatement->getClassName());

  _codeGenerationContext->addClass(
      boundClassStatement->getClassName(),
      std::make_unique<Class>(boundClassStatement->getClassName(),
                              boundClassStatement));

  auto classObject =
      _codeGenerationContext->_classTypes[boundClassStatement->getClassName()];

  //! Initialize parent class
  {
    classObject->setParentClassName(boundClassStatement->getParentClassName());

    classObject->setParent(
        _codeGenerationContext->_classTypes[classObject->getParentClassName()]);
  }

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      customTypeStatementGenerationStrategy =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0; i < boundClassStatement->getCustomTypesRef().size();
       i++) {
    customTypeStatementGenerationStrategy->generateCustomType(
        boundClassStatement->getCustomTypesRef()[i].get());

    BoundCustomTypeStatement *boundCustomTypeStatement =
        static_cast<BoundCustomTypeStatement *>(
            boundClassStatement->getCustomTypesRef()[i].get());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundCustomTypeStatement->getLocation());

    std::string typeName = boundCustomTypeStatement->getTypeNameAsString();

    if (!_codeGenerationContext->getFlowWingType(typeName).getStructType()) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected an object type " + Utils::getActualTypeName(typeName),
          boundCustomTypeStatement->getLocation());
      return nullptr;
    }

    classObject->addMemberVariableTypeName(typeName);
    {
      size_t index = 0;

      for (auto &[boundLiteralExpression, bTE] :
           boundCustomTypeStatement->getKeyPairs()) {

        const std::string propertyName =
            std::any_cast<std::string>(boundLiteralExpression->getValue());

        const std::string key = typeName + "." + propertyName;
        _codeGenerationContext->_typesMap[key] =
            FlowWing::Type::TypeBuilder().setName(key).setIndex(index).build();
        classObject->addMemberVariableTypeName(key);

        index++;
      }
    }
  }

  std::vector<llvm::Type *> classElements = {};

  classObject->addKeyTypePair(nullptr, nullptr);

  for (auto &keyPair : boundClassStatement->getKeyPairsRef()) {
    classObject->addKeyTypePair(keyPair.first, keyPair.second);
  }

  classElements.push_back(llvm::Type::getInt8PtrTy(*TheContext));

  classObject->setElementIndex(
      boundClassStatement->getClassName() + "::vTableElement", 0);

  for (int64_t i = 0;
       i < boundClassStatement->getAllMemberVariablesRef().size(); i++) {
    classElements.push_back(customTypeStatementGenerationStrategy->getType(
        boundClassStatement->getAllMemberVariablesRef()[i]
            ->getTypeExpression()
            .get()));
    classObject->setElementIndex(
        boundClassStatement->getAllMemberVariablesRef()[i]->getVariableName(),
        i + 1);
  }

  llvm::StructType *classType = llvm::StructType::create(
      *TheContext, classElements, boundClassStatement->getClassName());

  _codeGenerationContext->_classLLVMTypes[boundClassStatement->getClassName()] =
      classType;
  classObject->setClassType(classType);
  std::unique_ptr<FunctionDeclarationGenerationStrategy>
      functionDeclarationGenerationStrategy =
          std::make_unique<FunctionDeclarationGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0; i < boundClassStatement->getMemberFunctionsRef().size();
       i++) {
    BoundFunctionDeclaration *fd = static_cast<BoundFunctionDeclaration *>(
        boundClassStatement->getMemberFunctionsRef()[i].get());

    if (!fd->isOnlyDeclared()) {
      llvm::Function *F = functionDeclarationGenerationStrategy->generate(
          fd, {llvm::Type::getInt8PtrTy(*TheContext)},
          boundClassStatement->getClassName());

      classObject->insertFunctionType(fd->getFunctionNameRef(),
                                      F->getFunctionType());
    }
  }
  {
    //! Create vTableType

    uint64_t inde = 0;
    _codeGenerationContext->createVTableMapEntry(
        classObject->getVTableElementsMap(),
        boundClassStatement->getClassName(), inde);

    std::vector<llvm::Type *> vTableElements(
        classObject->getVTableElementsMap().size(),
        llvm::Type::getInt8PtrTy(*TheContext));
    classObject->setVTableType(llvm::StructType::create(
        *TheContext, vTableElements,
        boundClassStatement->getClassName() + "::" + "VTableType"));

    //!

    classObject->createVTable(classType->getStructName().str(), TheModule);
  }

  // Reset current class name
  _codeGenerationContext->resetCurrentClassName();

  return nullptr;
}
llvm::Value *ClassStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *statement) {

  return nullptr;
}