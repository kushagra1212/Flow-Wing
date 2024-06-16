#include "ObjectExpressionGenerationStrategy.h"

ObjectExpressionGenerationStrategy::ObjectExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ObjectExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  _codeGenerationContext->getValueStackHandler()->popAll();
  createExpressionNPDefault(_variable, _typeName);

  if (expression->getKind() == BinderKindUtils::VariableExpression) {
    return generateVariableExp(expression);
  } else if (expression->getKind() == BinderKindUtils::CallExpression) {
    return generateCallExp(expression);
  }

  llvm::Value *res = this->createExpressionNP(expression, _variable, _typeName);

  //   if (llvm::isa<llvm::AllocaInst>(_variable)) {
  //     llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(_variable);
  //     llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext,
  //     _typeName); llvm::StringRef Kind = "TN"; allocaInst->setMetadata(Kind,
  //     llvm::MDNode::get(*TheContext, argInfoMD));
  //   }
  return res;
}

llvm::Value *ObjectExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  this->_variableIsGlobal = true;
  _codeGenerationContext->getValueStackHandler()->popAll();

  createExpressionNPDefault(_variable, _typeName);
  std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy>
      objectAssignmentGES =
          std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  if (!(_codeGenerationContext->getType(_typeName).getStructType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an object type " + Utils::getActualTypeName(_typeName));
    return nullptr;
  }

  return objectAssignmentGES->assignObject(
      static_cast<BoundObjectExpression *>(expression), _variable,
      (_codeGenerationContext->getType(_typeName).getStructType()),
      _variable->getName().str());
  // if (expression->getKind() == BinderKindUtils::VariableExpression) {
  //   return generateVariableExp(expression);
  // } else if (expression->getKind() == BinderKindUtils::CallExpression) {
  //   return generateCallExp(expression);
  // }

  // llvm::Value *res = this->createExpressionNP(expression, _variable,
  // _typeName);

  //   if (llvm::isa<llvm::GlobalVariable>(_variable)) {
  //     llvm::GlobalVariable *globalVariable =
  //         llvm::cast<llvm::GlobalVariable>(_variable);
  //     llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext,
  //     _typeName); llvm::StringRef Kind = "TN";
  //     globalVariable->setMetadata(Kind,
  //                                 llvm::MDNode::get(*TheContext, argInfoMD));
  //   }

  // return res;
  return nullptr;
}

llvm::Value *ObjectExpressionGenerationStrategy::generateCallExp(
    BoundExpression *expression) {

  llvm::Value *rhsValue =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  if (!(_codeGenerationContext->getType(_typeName).getStructType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an object type," + Utils::getActualTypeName(_typeName));
    return nullptr;
  }

  llvm::StructType *lhsStructType =
      (_codeGenerationContext->getType(_typeName).getStructType());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());
  if (!rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value not found in assignment expression ");
    return nullptr;
  }
  llvm::CallInst *calledInst = llvm::cast<llvm::CallInst>(rhsValue);
  auto *calledFunction = calledInst->getCalledFunction();
  llvm::StructType *structType = nullptr;
  _codeGenerationContext->getReturnedObjectType(calledFunction, structType);

  _codeGenerationContext->getValueStackHandler()->popAll();

  if (!structType) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value expected to be an object of type " +
        lhsStructType->getStructName().str());
  }

  if (lhsStructType->getStructName() != structType->getStructName()) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value expected to be an object of type " +
        lhsStructType->getStructName().str() + " but got " +
        structType->getStructName().str());
    return nullptr;
  }
  llvm::LoadInst *loaded = Builder->CreateLoad(structType, calledInst);
  Builder->CreateStore(loaded, _variable);
  return nullptr;
}

llvm::Value *ObjectExpressionGenerationStrategy::generateVariableExp(
    BoundExpression *expression) {
  std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy> strategy =
      std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
          _codeGenerationContext);
  llvm::Value *rhsValue =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  llvm::StructType *parStructType =
      (_codeGenerationContext->getType(_typeName).getStructType());

  if (!parStructType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an object type " + Utils::getActualTypeName(_typeName));
    return nullptr;
  }

  if (!_codeGenerationContext->getValueStackHandler()->isStructType()) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a object of type " + Utils::getActualTypeName(_typeName));
    _codeGenerationContext->getValueStackHandler()->popAll();
    return nullptr;
  }

  if (_codeGenerationContext->getValueStackHandler()->getTypeName() !=
      _typeName) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a object of type " + Utils::getActualTypeName(_typeName) +
        " but got " +
        _codeGenerationContext->getValueStackHandler()->getTypeName());
    _codeGenerationContext->getValueStackHandler()->popAll();
    return nullptr;
  }

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  _codeGenerationContext->getValueStackHandler()->popAll();

  return strategy->copyObject(parStructType, _variable, rhsPtr);
}

llvm::Value *ObjectExpressionGenerationStrategy::createExpressionNP(
    BoundExpression *expression, llvm::Value *variable,
    const std::string &typeName) {
  BoundObjectExpression *parObjectExpression =
      static_cast<BoundObjectExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  llvm::StructType *parStructType =
      (_codeGenerationContext->getType(typeName).getStructType());

  if (!parStructType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected an object type, " + Utils::getActualTypeName(typeName));
    return nullptr;
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getType(typeName).getCustomType();

  std::unordered_map<std::string, BoundTypeExpression *> propertiesMap;
  std::unordered_map<std::string, uint64_t> propertiesMapIndexed;

  uint64_t index = 0;
  const std::string KEY_PREFIX = typeName;
  if (_codeGenerationContext->_classTypes.find(Utils::getActualTypeName(
          typeName)) != _codeGenerationContext->_classTypes.end()) {
    for (const auto &[bLitExpr, bExpr] :
         _codeGenerationContext->_classTypes[Utils::getActualTypeName(typeName)]
             ->getKeyTypePairs()) {
      std::string propertyName =
          std::any_cast<std::string>(bLitExpr->getValue());
      propertiesMap[propertyName] = bExpr;
      propertiesMapIndexed[propertyName] = index;
      index++;
    }

  } else {
    for (const auto &[bLitExpr, bExpr] :
         boundCustomTypeStatement->getKeyPairs()) {
      std::string propertyName =
          KEY_PREFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());

      propertiesMap[propertyName] = bExpr.get();
      propertiesMapIndexed[propertyName] = index;
      index++;
    }
  }

  for (const auto &[bLitExpr, bExpr] :
       parObjectExpression->getKeyValuePairs()) {
    std::string propertyName =
        KEY_PREFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());

    uint64_t indexValue = propertiesMapIndexed[propertyName];
    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bLitExpr->getLocation());

    if (propertiesMap.find(propertyName) == propertiesMap.end()) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " + typeName);
      return nullptr;
    }

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bExpr->getLocation());

    // if ((propertiesMap[propertyName]->getSyntaxType() ==
    //          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
    //      bExpr->getKind() != BinderKindUtils::BoundObjectExpression) or
    //     (bExpr->getKind() == BinderKindUtils::BoundObjectExpression &&
    //      propertiesMap[propertyName]->getSyntaxType() !=
    //          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE)) {
    //   _codeGenerationContext->getLogger()->LogError(
    //       "Type of property '" + propertyName +
    //       "' does not match type of property in type " + typeName);

    //   return nullptr;
    // }

    std::string key = propertyName;
    const int64_t index = _codeGenerationContext->getType(key).getIndex();

    if (index == -1) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " + typeName);
      return nullptr;
    }

    llvm::Value *rhs = nullptr;

    llvm::Value *innerElementPtr =
        Builder->CreateStructGEP(parStructType, variable, indexValue);

    _codeGenerationContext->getValueStackHandler()->popAll();
    if (propertiesMap[propertyName]->getSyntaxType() ==
            SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
        bExpr->getKind() == BinderKindUtils::BoundObjectExpression) {
      BoundObjectExpression *innerObjectExpression =
          static_cast<BoundObjectExpression *>(bExpr.get());

      BoundObjectTypeExpression *boundObjectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(propertiesMap[propertyName]);

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          innerObjectExpression->getLocation());
      llvm::StructType *innerElementType =
          (_codeGenerationContext
               ->getType(boundObjectTypeExpression->getTypeName())
               .getStructType());

      if (!innerElementType) {

        _codeGenerationContext->getLogger()->LogError(
            "Type of property '" + propertyName +
            "' does not match type of property in type " +
            Utils::getActualTypeName(typeName) + " Expected an object type");

        return nullptr;
      }

      std::string var_name = variable->getName().str() + "." + propertyName;
      // llvm::Value *var = nullptr;

      // if (_variableIsGlobal) {
      // var = new llvm::GlobalVariable(
      //     *TheModule, llvm::PointerType::get(*TheContext, 0), false,
      //     llvm::GlobalValue::ExternalLinkage,
      //     llvm::Constant::getNullValue(
      //         llvm::PointerType::get(*TheContext, 0)),
      //     var_name);

      // Builder->CreateStore(elementPtr, var);

      // } else {
      // var = Builder->CreateAlloca(elementType, nullptr, var_name);
      // llvm::AllocaInst *v = llvm::cast<llvm::AllocaInst>(var);

      // v->setMetadata(FLOWWING::IR::CONSTANTS::IS_EXISTS,
      //                llvm::MDNode::get(
      //                    *TheContext, llvm::MDString::get(*TheContext,
      //                    "-")));

      // _codeGenerationContext->getAllocaChain()->setAllocaInst(var_name, v);
      // }

      this->createExpressionNP(innerObjectExpression, innerElementPtr,
                               innerElementType->getName().str());
    } else {
      std::unique_ptr<AssignmentExpressionGenerationStrategy> assignmentEGS =
          std::make_unique<AssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

      assignmentEGS->handleAssignExpression(
          innerElementPtr, parStructType->getElementType(index),
          variable->getName().str() + "." + propertyName, bExpr.get());
    }

    // else if (propertiesMap[propertyName]->getSyntaxType() ==
    //              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE &&
    //          (bExpr->getKind() == BinderKindUtils::BoundBracketedExpression
    //          ||
    //           bExpr->getKind() == BinderKindUtils::CallExpression)) {

    //   std::unique_ptr<LiteralExpressionGenerationStrategy>
    //       literalExpressionGenerationStrategy =
    //           std::make_unique<LiteralExpressionGenerationStrategy>(
    //               _codeGenerationContext);

    //   BoundArrayTypeExpression *boundArrayTypeExpression =
    //       static_cast<BoundArrayTypeExpression
    //       *>(propertiesMap[propertyName]);

    //   std::unique_ptr<ContainerDeclarationStatementGenerationStrategy>
    //       containerDeclarationStatementGenerationStrategy =
    //           std::make_unique<ContainerDeclarationStatementGenerationStrategy>(
    //               _codeGenerationContext);

    //   containerDeclarationStatementGenerationStrategy->setAllocaInst(
    //       (innerElementPtr));

    //   containerDeclarationStatementGenerationStrategy->generateCommonStatement(
    //       boundArrayTypeExpression,
    //       variable->getName().str() + "." + propertyName, bExpr.get());
    // }
    // else if (propertiesMap[propertyName]->getSyntaxType() ==
    //              SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE &&
    //          bExpr->getKind() == BinderKindUtils::VariableExpression) {

    //   llvm::ArrayType *arrayType =
    //       llvm::cast<llvm::ArrayType>(parStructType->getElementType(index));
    //   llvm::Type *elementType = arrayType->getElementType();
    //   llvm::Type *type = arrayType;

    //   std::vector<uint64_t> sizes;
    //   while (llvm::ArrayType *arrayType =
    //              llvm::dyn_cast<llvm::ArrayType>(type)) {
    //     sizes.push_back(arrayType->getNumElements());
    //     type = arrayType->getElementType();
    //   }

    //   auto assignStrategy =
    //       std::make_unique<ContainerAssignmentExpressionGenerationStrategy>(
    //           _codeGenerationContext);

    //   assignStrategy->setVariable(innerElementPtr);
    //   assignStrategy->setContainerName(variable->getName().str() + "." +
    //                                    propertyName);

    //   assignStrategy->createExpressionForObject(bExpr.get(), arrayType,
    //                                             innerElementPtr, sizes,
    //                                             type);
    // }
    // else if (propertiesMap[propertyName]->getSyntaxType() ==
    //              SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
    //          bExpr->getKind() == BinderKindUtils::VariableExpression) {
    //   rhs = _expressionGenerationFactory->createStrategy(bExpr->getKind())
    //             ->generateExpression(bExpr.get());
    //   if (!_codeGenerationContext->getValueStackHandler()->isStructType()) {
    //     _codeGenerationContext->getLogger()->LogError(
    //         "Expected a object of type " + _typeName);
    //     _codeGenerationContext->getValueStackHandler()->popAll();
    //     return nullptr;
    //   }
    //   llvm::StructType *rhsStructType = llvm::cast<llvm::StructType>(
    //       _codeGenerationContext->getValueStackHandler()->getLLVMType());

    //   BoundObjectTypeExpression *boundObjectTypeExpression =
    //       static_cast<BoundObjectTypeExpression
    //       *>(propertiesMap[propertyName]);

    //   llvm::StructType *lshStructType =
    //       (_codeGenerationContext->getTypeChain()->getType(
    //           boundObjectTypeExpression->getTypeName()));

    //   if (lshStructType->getStructName() != rhsStructType->getStructName()) {
    //     _codeGenerationContext->getLogger()->LogError(
    //         "Expected a object of type " +
    //         Utils::CE(lshStructType->getStructName().str()) +
    //         " but got object of type " +
    //         Utils::CE(rhsStructType->getStructName().str()));
    //     return nullptr;
    //   }
    //   std::unique_ptr<ObjectAssignmentExpressionGenerationStrategy> strategy
    //   =
    //       std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
    //           _codeGenerationContext);
    //   strategy->copyOject(
    //       lshStructType, innerElementPtr,
    //       _codeGenerationContext->getValueStackHandler()->getValue());

    //   _codeGenerationContext->getValueStackHandler()->popAll();
    // }
    // else if (propertiesMap[propertyName]->getSyntaxType() ==
    //          SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    //   _codeGenerationContext->getLogger()->LogError(
    //       "Expected a object of type " + _typeName);
    //   return nullptr;
    // }
    // else {
    //   rhs = _expressionGenerationFactory->createStrategy(bExpr->getKind())
    //             ->generateExpression(bExpr.get());

    //   if (!rhs) {
    //     _codeGenerationContext->getLogger()->LogError(
    //         "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
    //         " not found in type " + typeName);
    //     return nullptr;
    //   }

    //   if (_codeGenerationContext->getMapper()->isPrimitiveType(
    //           rhs->getType()) &&
    //       _codeGenerationContext->getMapper()->isPrimitiveType(
    //           parStructType->getElementType(index)) &&
    //       rhs->getType() != parStructType->getElementType(index)) {
    //     _codeGenerationContext->getLogger()->LogError(
    //         "Type of property " +
    //         std::any_cast<std::string>(bLitExpr->getValue()) +
    //         " does not match type in type " + typeName + " Expected " +
    //         Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
    //             parStructType->getElementType(index))) +
    //         " but got " +
    //         Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
    //             rhs->getType())));

    //     return nullptr;
    //   }

    //   Builder->CreateStore(rhs, innerElementPtr);
    // }
    indexValue++;
  }

  return nullptr;
}

llvm::Value *ObjectExpressionGenerationStrategy::createExpressionNPDefault(
    llvm::Value *variable, const std::string &typeName) {

  llvm::StructType *parStructType = llvm::cast<llvm::StructType>(
      _codeGenerationContext->getType(typeName).getStructType());

  if (!parStructType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a object of type " + Utils::getActualTypeName(typeName));
    return nullptr;
  }

  auto boundCustomTypeStatement =
      _codeGenerationContext->getType(typeName).getCustomType();

  uint64_t indexValue = 0;
  if (!boundCustomTypeStatement &&
      _codeGenerationContext->_classTypes.find(Utils::getActualTypeName(
          _typeName)) != _codeGenerationContext->_classTypes.end()) {
    parStructType =
        _codeGenerationContext->_classTypes[Utils::getActualTypeName(_typeName)]
            ->getClassType();
    for (const auto &[bLE, bTE] :
         _codeGenerationContext
             ->_classTypes[Utils::getActualTypeName(_typeName)]
             ->getKeyTypePairs()) {
      handleCreateDef(bLE, parStructType, variable, indexValue, bTE);
      indexValue++;
    }
  } else {
    for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
      auto bLitExpr = bLE.get();
      auto bExpr = bTE.get();
      handleCreateDef(bLitExpr, parStructType, variable, indexValue, bExpr);
      indexValue++;
    }
  }

  return nullptr;
}

void ObjectExpressionGenerationStrategy::handleCreateDef(
    BoundLiteralExpression<std::any> *bLitExpr, llvm::StructType *parStructType,
    llvm::Value *variable, uint64_t indexValue, BoundTypeExpression *bExpr) {
  std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());

  llvm::Value *innerElementPtr =
      Builder->CreateStructGEP(parStructType, variable, indexValue);
  if (bExpr->getSyntaxType() == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    BoundObjectTypeExpression *boundObjectTypeExpression =
        static_cast<BoundObjectTypeExpression *>(bExpr);

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundObjectTypeExpression->getLocation());
    llvm::StructType *lshStructType =
        (_codeGenerationContext
             ->getType(boundObjectTypeExpression->getTypeName())
             .getStructType());

    if (!lshStructType) {

      _codeGenerationContext->getLogger()->LogError(
          "Expected an object of type " +
          Utils::getActualTypeName(boundObjectTypeExpression->getTypeName()));
      return;
    }

    this->createExpressionNPDefault(innerElementPtr,
                                    lshStructType->getStructName().str());
  } else if (bExpr->getSyntaxType() ==
             SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {

    llvm::ArrayType *arrayType =
        llvm::cast<llvm::ArrayType>(parStructType->getElementType(indexValue));
    llvm::Type *elementType = arrayType->getElementType();
    llvm::Type *type = arrayType;

    std::vector<uint64_t> sizes;
    while (llvm::ArrayType *arrayType = llvm::dyn_cast<llvm::ArrayType>(type)) {
      sizes.push_back(arrayType->getNumElements());
      type = arrayType->getElementType();
    }

    std::unique_ptr<FillExpressionGenerationStrategy> specificStrategy =
        std::make_unique<FillExpressionGenerationStrategy>(
            _codeGenerationContext, sizes, type,
            variable->getName().str() + "." + propertyName);

    llvm::Constant *_defaultVal = nullptr;

    if (!llvm::isa<llvm::StructType>(type)) {
      _defaultVal = llvm::cast<llvm::Constant>(
          _codeGenerationContext->getMapper()->getDefaultValue(type));

      specificStrategy->createExpressionLoopWithTotalSize(
          arrayType, innerElementPtr, _defaultVal);
    } else {
      // _defaultVal = llvm::Constant::getNullValue(type);
      createExpressionNPDefault(innerElementPtr, type->getStructName().str());
    }
  } else {

    Builder->CreateStore(
        llvm::cast<llvm::Constant>(
            _codeGenerationContext->getMapper()->getDefaultValue(
                parStructType->getElementType(indexValue))),
        innerElementPtr);
  }
}

llvm::Value *ObjectExpressionGenerationStrategy::createExpression(
    BoundExpression *expression, llvm::Value *variable,
    const std::string &typeName) {
  BoundObjectExpression *parObjectExpression =
      static_cast<BoundObjectExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      expression->getLocation());

  llvm::StructType *parStructType =
      (_codeGenerationContext->getType(typeName).getStructType());

  if (!parStructType) {

    _codeGenerationContext->getLogger()->LogError(
        "Expected an object of type " + Utils::getActualTypeName(typeName));
    return nullptr;
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getType(typeName).getCustomType();

  std::unordered_map<std::string, BoundTypeExpression *> propertiesMap;
  uint64_t index = 0;
  for (const auto &[bLitExpr, bExpr] :
       boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());
    propertiesMap[propertyName] = bExpr.get();
    if (propertiesMap[propertyName]->getSyntaxType() !=
        SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      llvm::Constant *defaultValue =
          llvm::Constant::getNullValue(parStructType->getElementType(index));

      llvm::Value *elementPtr =
          Builder->CreateGEP(parStructType, variable,
                             {Builder->getInt32(0), Builder->getInt32(index)});

      Builder->CreateStore(defaultValue, elementPtr);
      index++;
    }
  }
  const std::string KEY_PREFIX = typeName;
  for (const auto &[bLitExpr, bExpr] :
       parObjectExpression->getKeyValuePairs()) {
    std::string propertyName =
        KEY_PREFIX + "." + std::any_cast<std::string>(bLitExpr->getValue());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bLitExpr->getLocation());

    if (propertiesMap.find(propertyName) == propertiesMap.end()) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + propertyName + " not found in type " +
          Utils::getActualTypeName(typeName));
      return nullptr;
    }

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        bExpr->getLocation());

    if ((propertiesMap[propertyName]->getSyntaxType() ==
             SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE &&
         bExpr->getKind() != BinderKindUtils::BoundObjectExpression) or
        (bExpr->getKind() == BinderKindUtils::BoundObjectExpression &&
         propertiesMap[propertyName]->getSyntaxType() !=
             SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE)) {
      _codeGenerationContext->getLogger()->LogError(
          "Type of property '" + propertyName +
          "' does not match type of property in type " +
          Utils::getActualTypeName(typeName));

      return nullptr;
    }

    std::string key =
        boundCustomTypeStatement->getTypeNameAsString() + "." + propertyName;
    const size_t index = _codeGenerationContext->getType(key).getIndex();

    if (index == -1) {
      _codeGenerationContext->getLogger()->LogError(
          "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
          " not found in type " + typeName);
      return nullptr;
    }

    llvm::Value *rhs = nullptr;

    llvm::Value *elementPtr =
        Builder->CreateGEP(parStructType, variable,
                           {Builder->getInt32(0), Builder->getInt32(index)});

    if (bExpr->getKind() == BinderKindUtils::BoundObjectExpression) {
      BoundObjectExpression *innerObjectExpression =
          static_cast<BoundObjectExpression *>(bExpr.get());

      BoundObjectTypeExpression *boundObjectTypeExpression =
          static_cast<BoundObjectTypeExpression *>(propertiesMap[propertyName]);

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          boundObjectTypeExpression->getLocation());
      llvm::StructType *elementType =
          (_codeGenerationContext
               ->getType(boundObjectTypeExpression->getTypeName())
               .getStructType());
      if (!elementType) {

        _codeGenerationContext->getLogger()->LogError(
            "Expected an object of type " +
            Utils::getActualTypeName(boundObjectTypeExpression->getTypeName()));
        return nullptr;
      }

      std::string var_name = variable->getName().str() + "." + propertyName;
      llvm::Value *var = nullptr;

      if (_variableIsGlobal) {
        var = new llvm::GlobalVariable(
            *TheModule, elementType, false, llvm::GlobalValue::ExternalLinkage,
            llvm::Constant::getNullValue(elementType), var_name);

        llvm::GlobalVariable *g = llvm::cast<llvm::GlobalVariable>(var);

        g->setMetadata(FLOWWING::IR::CONSTANTS::IS_EXISTS,
                       llvm::MDNode::get(
                           *TheContext, llvm::MDString::get(*TheContext, "-")));

      } else {
        var = Builder->CreateAlloca(elementType, nullptr, var_name);
        llvm::AllocaInst *v = llvm::cast<llvm::AllocaInst>(var);

        v->setMetadata(FLOWWING::IR::CONSTANTS::IS_EXISTS,
                       llvm::MDNode::get(
                           *TheContext, llvm::MDString::get(*TheContext, "-")));

        _codeGenerationContext->getAllocaChain()->setPtr(var_name,
                                                         {v, elementType});
      }

      this->createExpression(innerObjectExpression, var,
                             elementType->getName().str());
      Builder->CreateStore(var, elementPtr);
    } else {
      rhs = _expressionGenerationFactory->createStrategy(bExpr->getKind())
                ->generateExpression(bExpr.get());

      if (!rhs) {
        _codeGenerationContext->getLogger()->LogError(
            "Property " + std::any_cast<std::string>(bLitExpr->getValue()) +
            " not found in type " + typeName);
        return nullptr;
      }

      if (_codeGenerationContext->getMapper()->isPrimitiveType(
              rhs->getType()) &&
          _codeGenerationContext->getMapper()->isPrimitiveType(
              parStructType->getElementType(index)) &&
          rhs->getType() != parStructType->getElementType(index)) {
        _codeGenerationContext->getLogger()->LogError(
            "Type of property " +
            std::any_cast<std::string>(bLitExpr->getValue()) +
            " does not match type in type " + typeName + " Expected " +
            Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
                parStructType->getElementType(index))) +
            " but got " +
            Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
                rhs->getType())));

        return nullptr;
      }

      Builder->CreateStore(rhs, elementPtr);
    }
  }

  return nullptr;
}

llvm::Value *ObjectExpressionGenerationStrategy::generateVariable(
    llvm::Value *variable, const std::string &typeName, llvm::Value *fromVar,
    const bool isGlobal) {

  llvm::StructType *structType =
      (_codeGenerationContext->getType(typeName).getStructType());
  if (!structType) {

    _codeGenerationContext->getLogger()->LogError(
        "Expected an object of type " + Utils::getActualTypeName(typeName));
    return nullptr;
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getType(typeName).getCustomType();

  uint64_t index = 0;

  for (const auto &[bLitExpr, bExpr] :
       boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLitExpr->getValue());

    llvm::Value *elementPtr = Builder->CreateGEP(
        structType, variable, {Builder->getInt32(0), Builder->getInt32(index)});

    llvm::Value *toValue = nullptr;

    llvm::Value *fromElementPtr = Builder->CreateGEP(
        structType, fromVar, {Builder->getInt32(0), Builder->getInt32(index)});

    if (bExpr->getSyntaxType() ==
        SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
      BoundObjectTypeExpression *bOT =
          static_cast<BoundObjectTypeExpression *>(bExpr.get());

      _codeGenerationContext->getLogger()->setCurrentSourceLocation(
          bOT->getLocation());

      llvm::StructType *elementType =
          (_codeGenerationContext->getType(bOT->getTypeName()).getStructType());

      if (!elementType) {

        _codeGenerationContext->getLogger()->LogError(
            "Expected an object of type " +
            Utils::getActualTypeName(bOT->getTypeName()));
        return nullptr;
      }

      std::string var_name = variable->getName().str() + "." + propertyName;

      llvm::Value *fromVarLoaded =
          _codeGenerationContext->getAllocaChain()
              ->getPtr(fromVar->getName().str() + "." + propertyName)
              .first;

      if (!fromVarLoaded) {
        fromVarLoaded = TheModule->getGlobalVariable(fromVar->getName().str() +
                                                     "." + propertyName);
      }
      if (!fromVarLoaded) {
        index++;
        continue;
      }

      if (isGlobal) {
        toValue = TheModule->getGlobalVariable(var_name);
        if (!toValue) {
          toValue = new llvm::GlobalVariable(
              *TheModule, elementType, false,
              llvm::GlobalValue::ExternalLinkage,
              llvm::Constant::getNullValue(elementType), var_name);
        }
      } else {
        toValue =
            _codeGenerationContext->getAllocaChain()->getPtr(var_name).first;
        if (!toValue) {
          toValue = Builder->CreateAlloca(elementType, nullptr, var_name);
          _codeGenerationContext->getAllocaChain()->setPtr(
              var_name, {toValue, elementType});
        }
      }

      this->generateVariable(toValue, bOT->getTypeName(), fromVarLoaded,
                             isGlobal);
      Builder->CreateStore(toValue, elementPtr);

    } else {
      toValue = Builder->CreateLoad(structType->getElementType(index),
                                    fromElementPtr);
      Builder->CreateStore(toValue, elementPtr);
    }

    index++;
  }

  // Set the metadata
  //   llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(variable);
  //   llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext, typeName);
  //   llvm::StringRef Kind = "TN";  // TypeName
  //   allocaInst->setMetadata(Kind, llvm::MDNode::get(*TheContext,
  //   argInfoMD));

  return nullptr;
}

// llvm::Value *
// ObjectExpressionGenerationStrategy::generateVariableAccessThroughPtr(
//     llvm::Value *LOADED_VARIABLE, const std::string &typeName,
//     llvm::Value *LOADED) {
//   llvm::StructType *structType =
//       _codeGenerationContext->getTypeChain()->getType(
//           typeName.substr(0, typeName.find(".")));

//   BoundCustomTypeStatement *boundCustomTypeStatement =
//       _codeGenerationContext->getCustomTypeChain()->getExpr(
//           typeName.substr(0, typeName.find(".")));

//   uint64_t index = 0;

//   for (const auto &[bLitExpr, bExpr] :
//        boundCustomTypeStatement->getKeyPairs()) {
//     std::string propertyName =
//     std::any_cast<std::string>(bLitExpr->getValue());

//     llvm::Value *elementPtr =
//         Builder->CreateGEP(structType, LOADED_VARIABLE,
//                            {Builder->getInt32(0), Builder->getInt32(index)});

//     llvm::Value *fromElementPtr = Builder->CreateGEP(
//         structType, LOADED, {Builder->getInt32(0),
//         Builder->getInt32(index)});

//     if (bExpr->getSyntaxType() ==
//         SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
//       BoundObjectTypeExpression *bOT =
//           static_cast<BoundObjectTypeExpression *>(bExpr.get());

//       llvm::StructType *innerStructType =
//           (_codeGenerationContext->getTypeChain()->getType(
//               bOT->getTypeName().substr(0, bOT->getTypeName().find("."))));

//       std::string var_name =
//           LOADED_VARIABLE->getName().str() + "." + propertyName;
//       llvm::LoadInst *inst = Builder->CreateLoad(
//           structType->getElementType(index), fromElementPtr);

//       if (inst->getMetadata(FLOWWING::IR::CONSTANTS::IS_EXISTS)) {
//         llvm::Value *alloca =
//             Builder->CreateAlloca(innerStructType, nullptr, var_name);

//         (llvm::cast<llvm::AllocaInst>(alloca))
//             ->setMetadata(
//                 FLOWWING::IR::CONSTANTS::IS_EXISTS,
//                 llvm::MDNode::get(*TheContext,
//                                   llvm::MDString::get(*TheContext, "-")));

//         _codeGenerationContext->getAllocaChain()->setPtr(
//             var_name, {alloca, innerStructType});

//         this->generateVariableAccessThroughPtr(alloca, bOT->getTypeName(),
//                                                inst);

//         Builder->CreateStore(alloca, elementPtr);
//       }

//     } else {
//       Builder->CreateStore(
//           Builder->CreateLoad(structType->getElementType(index),
//                               fromElementPtr),
//           elementPtr);
//     }
//     index++;
//   }

//   // Set the metadata
//   //   llvm::AllocaInst *allocaInst = llvm::cast<llvm::AllocaInst>(variable);
//   //   llvm::MDString *argInfoMD = llvm::MDString::get(*TheContext,
//   typeName);
//   //   llvm::StringRef Kind = "TN";  // TypeName
//   //   allocaInst->setMetadata(Kind, llvm::MDNode::get(*TheContext,
//   //   argInfoMD));

//   return nullptr;
// }
llvm::AllocaInst *
ObjectExpressionGenerationStrategy::findAllocaInstFromPtr(llvm::Value *ptr) {
  if (llvm::Instruction *inst = llvm::dyn_cast<llvm::Instruction>(ptr)) {
    if (llvm::AllocaInst *allocaInst = llvm::dyn_cast<llvm::AllocaInst>(inst)) {
      return allocaInst;
    } else {
      // If ptr is derived from an instruction (e.g., a GEP), we need to find
      // the original alloca
      for (auto &use : inst->operands()) {
        if (llvm::AllocaInst *allocaInst = findAllocaInstFromPtr(use)) {
          return allocaInst;
        }
      }
    }
  }
  return nullptr;
}
