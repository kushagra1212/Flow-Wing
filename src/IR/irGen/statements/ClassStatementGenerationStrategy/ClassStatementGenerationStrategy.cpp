
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
  _codeGenerationContext->setCurrentClassName(
      boundClassStatement->getClassName());

  std::unique_ptr<Class> classObjectSave = std::make_unique<Class>(
      boundClassStatement->getClassName(), boundClassStatement);

  //! Initialize parent class
  {
    classObjectSave->setParentClassName(
        boundClassStatement->getParentClassName());

    classObjectSave->setParent(
        _codeGenerationContext
            ->_classTypes[classObjectSave->getParentClassName()]
            .get());

    if (classObjectSave->hasParent()) {
      Class *parent = classObjectSave->getParent();
      for (auto &[typeName, type] : parent->getCustomTypeMap()) {
        classObjectSave->addCustomType(typeName, type);
      }

      for (auto &[typeName, customTypeStat] :
           parent->getCustomTypeStatementMap()) {
        classObjectSave->addCustomTypeStatement(typeName, customTypeStat);
      }

      for (auto &[propertyKeyName, propertyIndex] :
           parent->getCustomTypePropertyMap()) {
        classObjectSave->addCustomTypeProperty(propertyKeyName, propertyIndex);
      }
    }
  }

  _codeGenerationContext->_classTypes[boundClassStatement->getClassName()] =
      std::move(classObjectSave);
  auto classObject =
      _codeGenerationContext->_classTypes[boundClassStatement->getClassName()]
          .get();

  std::unique_ptr<CustomTypeStatementGenerationStrategy>
      customTypeStatementGenerationStrategy =
          std::make_unique<CustomTypeStatementGenerationStrategy>(
              _codeGenerationContext);

  for (int64_t i = 0; i < boundClassStatement->getCustomTypesRef().size();
       i++) {
    customTypeStatementGenerationStrategy->generateStatement(
        boundClassStatement->getCustomTypesRef()[i].get());
    BoundCustomTypeStatement *boundCustomTypeStatement =
        static_cast<BoundCustomTypeStatement *>(
            boundClassStatement->getCustomTypesRef()[i].get());

    std::string typeName =
        boundCustomTypeStatement->getTypeNameAsString().substr(
            0, boundCustomTypeStatement->getTypeNameAsString().find("."));
    classObject->addCustomType(
        typeName, _codeGenerationContext->getTypeChain()->getType(typeName));
    classObject->addCustomTypeStatement(
        typeName,
        _codeGenerationContext->getCustomTypeChain()->getExpr(typeName));
    {
      size_t index = 0;

      for (auto &[boundLiteralExpression, bTE] :
           boundCustomTypeStatement->getKeyPairs()) {

        const std::string propertyName =
            std::any_cast<std::string>(boundLiteralExpression->getValue());

        const std::string key = typeName + "." + propertyName;

        classObject->addCustomTypeProperty(key, index);

        index++;
      }
    }
  }

  std::vector<llvm::Type *> classElements = {};

  for (auto &keyPair : boundClassStatement->getKeyPairsRef()) {
    classObject->addKeyTypePair(keyPair.first, keyPair.second);
  }
  classObject->addKeyTypePair(nullptr, nullptr);

  for (int64_t i = 0;
       i < boundClassStatement->getAllMemberVariablesRef().size(); i++) {

    classElements.push_back(customTypeStatementGenerationStrategy->getType(
        boundClassStatement->getAllMemberVariablesRef()[i]
            ->getTypeExpression()
            .get()));
    classObject->setElementIndex(
        boundClassStatement->getAllMemberVariablesRef()[i]->getVariableName(),
        i);
  }

  classElements.push_back(llvm::Type::getInt8PtrTy(*TheContext));
  classObject->setElementIndex(boundClassStatement->getClassName() +
                                   "::vTableElement",
                               classElements.size() - 1);
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

      classObject->insertFunctionType(fd->getFunctionNameRef(),
                                      F->getFunctionType());
      count++;
    }
  }

  //! Create vTableType

  uint64_t inde = 0;
  _codeGenerationContext->createVTableMapEntry(
      classObject->getVTableElementsMap(), boundClassStatement->getClassName(),
      inde);

  std::vector<llvm::Type *> vTableElements(
      classObject->getVTableElementsMap().size(),
      llvm::Type::getInt8PtrTy(*TheContext));
  classObject->setVTableType(llvm::StructType::create(
      *TheContext, vTableElements,
      boundClassStatement->getClassName() + "::" + "VTableType"));

  //!

  classObject->createVTable(classType->getStructName().str(), TheModule);
  classObject->setClassType(classType);

  // Rest
  _codeGenerationContext->resetCurrentClassName();
  // Remove handlers
  _codeGenerationContext->getNamedValueChain()->removeHandler();
  _codeGenerationContext->getAllocaChain()->removeHandler();
  _codeGenerationContext->getTypeChain()->removeHandler();
  _codeGenerationContext->getCustomTypeChain()->removeHandler();
  return nullptr;
}