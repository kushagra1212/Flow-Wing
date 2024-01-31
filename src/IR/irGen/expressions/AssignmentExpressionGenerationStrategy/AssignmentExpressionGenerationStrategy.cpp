#include "AssignmentExpressionGenerationStrategy.h"

AssignmentExpressionGenerationStrategy::AssignmentExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleTypedPrmitiveGlobalVariableAssignment(
        llvm::GlobalVariable *variable, const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {
  if (!_codeGenerationContext->getMapper()->isEquivalentType(
          variableType, rhsValue->getType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable Assignment " + variableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()));

    return nullptr;
  }

  Builder->CreateStore(rhsValue, variable);
  return nullptr;
}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleUnTypedPrmitiveGlobalVariableAssignment(
        llvm::GlobalVariable *variable, const std::string &variableName,
        llvm::Value *rhsValue) {
  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      variable, rhsValue, rhsValue->getType(),
      FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX + variableName);

  return nullptr;
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handlePrimitiveGlobalVariableAssignment(
    llvm::GlobalVariable *variable, const std::string &variableName,
    const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue) {
  // Handle Static Primitive Global Variable (TYPED)
  if (_codeGenerationContext->getMapper()->isPrimitiveType(variableType)) {
    return handleTypedPrmitiveGlobalVariableAssignment(variable, variableName,
                                                       variableType, rhsValue);
  }

  // Handle Dynamic Primitive Global Variable (DYNAMIC)

  return handleUnTypedPrmitiveGlobalVariableAssignment(variable, variableName,
                                                       rhsValue);
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleGlobalLiteralExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());
  if (!canGenerateLiteralExpressionAssignment(assignmentExpression)) {
    return nullptr;
  }

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return assignObject(_previousGlobalVariable, 0, _variableName);
  }

  // Handle Static Container Global Variable (TYPED)
  if (_variableType != SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE &&
      !_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {
    if (assignmentExpression->getRightPtr().get()->getKind() ==
            BinderKindUtils::VariableExpression ||
        assignmentExpression->getRightPtr().get()->getKind() ==
            BinderKindUtils::CallExpression) {
      auto assignStrategy =
          std::make_unique<ContainerAssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

      assignStrategy->setVariable(_previousGlobalVariable);
      assignStrategy->setContainerName(_variableName);

      return assignStrategy->generateGlobalExpression(
          assignmentExpression->getRightPtr().get());
    }

    auto strategy = _expressionGenerationFactory->createStrategy(
        assignmentExpression->getRightPtr().get()->getKind());

    auto bracketdStrategy =
        dynamic_cast<BracketedExpressionGenerationStrategy *>(strategy.get());

    if (!bracketdStrategy) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected bracketed expression in assignment expression");
      return nullptr;
    }

    bracketdStrategy->setPreviousGlobalVariable(_previousGlobalVariable);
    bracketdStrategy->setContainerName(_variableName);

    return strategy->generateGlobalExpression(
        assignmentExpression->getRightPtr().get());
  }

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
          ->generateExpression(assignmentExpression->getRightPtr().get());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  if (!rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value not found in assignment expression ");

    return nullptr;
  }
  return handlePrimitiveGlobalVariableAssignment(
      _previousGlobalVariable, _variableName, _variableType, rhsValue);
}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleTypedPrmitiveLocalVariableAssignment(
        const std::string &variableName,
        const SyntaxKindUtils::SyntaxKind &variableType,
        llvm::Value *rhsValue) {
  if (!_codeGenerationContext->getMapper()->isEquivalentType(
          variableType, rhsValue->getType())) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable Assignment " + variableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()));

    return nullptr;
  }

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  _codeGenerationContext->getNamedValueChain()->updateNamedValue(variableName,
                                                                 rhsValue);

  Builder->CreateStore(rhsValue, v);

  return rhsValue;
}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleUnTypedPrmitiveLocalVariableAssignment(
        const std::string &variableName, llvm::Value *rhsValue) {
  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  _codeGenerationContext->getNamedValueChain()->updateNamedValue(variableName,
                                                                 rhsValue);

  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      v, rhsValue, rhsValue->getType(), variableName);
  return rhsValue;
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handlePrimitiveLocalVariableAssignment(
    const std::string &variableName,
    const SyntaxKindUtils::SyntaxKind &variableType, llvm::Value *rhsValue) {
  // Handle Static Primitive Local Variable (TYPED)
  if (_codeGenerationContext->getMapper()->isPrimitiveType(variableType)) {
    return handleTypedPrmitiveLocalVariableAssignment(variableName,
                                                      variableType, rhsValue);
  }

  // Handle Dynamic Primitive Local Variable (DYNAMIC)
  return handleUnTypedPrmitiveLocalVariableAssignment(variableName, rhsValue);
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleLiteralExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {
  if (!canGenerateLiteralExpressionAssignment(assignmentExpression)) {
    return nullptr;
  }
  if (_isGlobal) {
    return handleGlobalLiteralExpressionAssignment(assignmentExpression);
  }

  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return assignObject(_allocaInst, 0, _variableName);
  }
  // Handle Static Container local Variable (TYPED)
  if (_variableType == SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    // Container Copy
    if (assignmentExpression->getRightPtr().get()->getKind() ==
        BinderKindUtils::VariableExpression) {
      auto assignStrategy =
          std::make_unique<ContainerAssignmentExpressionGenerationStrategy>(
              _codeGenerationContext);

      assignStrategy->setVariable(_allocaInst);
      assignStrategy->setContainerName(_variableName);

      return assignStrategy->generateExpression(
          assignmentExpression->getRightPtr().get());
    }

    auto strategy = _expressionGenerationFactory->createStrategy(
        assignmentExpression->getRightPtr().get()->getKind());

    auto bracketdStrategy =
        dynamic_cast<BracketedExpressionGenerationStrategy *>(strategy.get());

    if (!bracketdStrategy) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected bracketed expression in assignment expression");
      return nullptr;
    }

    bracketdStrategy->setContainerName(_variableName);
    bracketdStrategy->setAllocatedVariable(_allocaInst);
    return strategy->generateExpression(
        assignmentExpression->getRightPtr().get());
  }

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
          ->generateExpression(assignmentExpression->getRightPtr().get());

  if (!rhsValue) {
    _codeGenerationContext->callREF(
        "Right hand side value not found in assignment expression ");

    return nullptr;
  }

  return handlePrimitiveLocalVariableAssignment(_variableName, _variableType,
                                                rhsValue);
}

// CONTAINER ASSIGNMENT EXPRESSION GENERATION STRATEGY

llvm::Value *
AssignmentExpressionGenerationStrategy::handleIndexExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  BoundIndexExpression *indexExpression = static_cast<BoundIndexExpression *>(
      assignmentExpression->getLeftPtr().get());

  _variableType =
      assignmentExpression->getVariable()->getTypeExpression()->getSyntaxType();

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
          ->generateExpression(assignmentExpression->getRightPtr().get());

  if (!rhsValue) {
    // Error generating IR for the right-hand side expression

    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value not found in assignment expression ");

    return nullptr;
  }

  for (const auto &index : indexExpression->getBoundIndexExpressions()) {
    llvm::Value *indexValue =
        _expressionGenerationFactory->createStrategy(index.get()->getKind())
            ->generateExpression(index.get());

    indexValue = _int32TypeConverter->convertExplicit(indexValue);

    if (!_codeGenerationContext->getMapper()->isInt32Type(
            indexValue->getType())) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected index value to be of type int but got " +
          Utils::CE(_codeGenerationContext->getMapper()->getLLVMTypeName(
              indexValue->getType())));
      return nullptr;
    }
    _indices.push_back(indexValue);
  }

  llvm::Value *loadedElementValue =
      _expressionGenerationFactory->createStrategy(indexExpression->getKind())
          ->generateExpression(indexExpression);

  if (!loadedElementValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Index value not found in assignment expression");

    return nullptr;
  }

  // ? Is a container

  if (_variableType != SyntaxKindUtils::SyntaxKind::NBU_ARRAY_TYPE) {
    _codeGenerationContext->getLogger()->LogError(
        "Cannot assign to non array variable" + _variableName);
    return nullptr;
  }

  // Typed Container

  if (rhsValue->getType() != loadedElementValue->getType()) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in assignment expression, expected " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            loadedElementValue->getType()) +
        " but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()) +
        " ");

    return nullptr;
  }

  std::string variableName = std::any_cast<std::string>(
      (indexExpression->getBoundIdentifierExpression().get())->getValue());

  llvm::AllocaInst *alloca =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);
  llvm::Type *arrayType = nullptr;

  llvm::Value *v = nullptr;

  if (!alloca) {  // Error Already Handled Look at the index
                  // expression Up :)
    llvm::GlobalVariable *gv = TheModule->getGlobalVariable(
        variableName);  // Error was handled before
                        // in the index expression (var loadedElementValue)

    arrayType = llvm::cast<llvm::ArrayType>(gv->getValueType());
    v = gv;
  } else {
    arrayType = llvm::cast<llvm::ArrayType>(alloca->getAllocatedType());
    v = alloca;
  }

  std::vector<llvm::Value *> indexList = {Builder->getInt32(0)};

  for (auto index : _indices) {
    indexList.push_back(index);
  }

  // Get Element pointer
  llvm::Value *elementPtr = Builder->CreateGEP(arrayType, v, indexList);

  Builder->CreateStore(rhsValue, elementPtr);

  return rhsValue;
}

llvm::Value *AssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

  _rhsExpression = assignmentExpression->getRightPtr().get();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  if (auto boundLiteralExpression = dynamic_cast<BoundVariableExpression *>(
          assignmentExpression->getLeftPtr().get())) {
    return this->handleLiteralExpressionAssignment(assignmentExpression);
  } else if (auto boundIndexExpression = dynamic_cast<BoundIndexExpression *>(
                 assignmentExpression->getLeftPtr().get())) {
    return this->handleIndexExpressionAssignment(assignmentExpression);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Left hand side value not found in assignment expression ");

  return nullptr;
}

llvm::Value *AssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _rhsExpression = assignmentExpression->getRightPtr().get();
  _isGlobal = true;
  if (auto boundLiteralExpression = dynamic_cast<BoundVariableExpression *>(
          assignmentExpression->getLeftPtr().get())) {
    return this->handleLiteralExpressionAssignment(assignmentExpression);
  } else if (auto boundIndexExpression = dynamic_cast<BoundIndexExpression *>(
                 assignmentExpression->getLeftPtr().get())) {
    return this->handleIndexExpressionAssignment(assignmentExpression);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Left hand side value not found in assignment expression ");

  return nullptr;
}

bool AssignmentExpressionGenerationStrategy::
    canGenerateLiteralExpressionAssignment(
        BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _variableExpression = static_cast<BoundVariableExpression *>(
      assignmentExpression->getLeftPtr().get());

  _variableName = _variableExpression->getVariableNameRef();

  llvm::Value *val =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(
          _variableName);
  _variableType =
      assignmentExpression->getVariable()->getTypeExpression()->getSyntaxType();
  _isGlobal = false;

  if (!val) {
    // Variable not found locally, handle error

    _allocaInst =
        _codeGenerationContext->getAllocaChain()->getAllocaInst(_variableName);

    if (_allocaInst) {
      return true;
    }

    _previousGlobalVariable = TheModule->getGlobalVariable(_variableName);

    if (_previousGlobalVariable) {
      _isGlobal = true;
      return true;
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression '" + _variableName + "'");

    return false;
  }

  return true;
}

llvm::Value *AssignmentExpressionGenerationStrategy::assignObject(
    llvm::Value *variableElementPtr, size_t listIndex,
    const std::string &parPropertyKey) {
  llvm::StructType *objTypeType = nullptr;

  if (llvm::isa<llvm::GlobalVariable>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::GlobalVariable>(variableElementPtr))->getValueType());
  } else if (llvm::isa<llvm::AllocaInst>(variableElementPtr)) {
    objTypeType = llvm::cast<llvm::StructType>(
        (llvm::cast<llvm::AllocaInst>(variableElementPtr))->getAllocatedType());
  }
  if (_variableExpression->getDotExpressionList().size() == 0) {
    std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
        std::make_unique<ObjectExpressionGenerationStrategy>(
            _codeGenerationContext);
    objExpGenStrat->setVariable(variableElementPtr);
    objExpGenStrat->setTypeName(objTypeType->getName().str());

    return objExpGenStrat->generateGlobalExpression(_rhsExpression);
  }

  BoundCustomTypeStatement *boundCustomTypeStatement =
      _codeGenerationContext->getCustomTypeChain()->getExpr(
          objTypeType->getStructName().str());

  std::unordered_map<std::string, BoundTypeExpression *> boundTypeExpressionMap;

  for (const auto &[bLE, bTE] : boundCustomTypeStatement->getKeyPairs()) {
    std::string propertyName = std::any_cast<std::string>(bLE->getValue());
    boundTypeExpressionMap[propertyName] = bTE.get();
  }

  std::string propertyKey = std::any_cast<std::string>(
      _variableExpression->getDotExpressionList()[listIndex]->getValue());

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      _variableExpression->getDotExpressionList()[listIndex]->getLocation());

  if (boundTypeExpressionMap.find(propertyKey) ==
      boundTypeExpressionMap.end()) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + objTypeType->getStructName().str());

    return nullptr;
  }
  std::string key =
      boundCustomTypeStatement->getTypeNameAsString() + "." + propertyKey;
  size_t index = _codeGenerationContext->getTypeChain()->getIndex(key);

  llvm::Type *type = objTypeType->getElementType(index);

  if (index == -1) {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " not found in variable " + parPropertyKey +
        " of type " + objTypeType->getStructName().str());

    return nullptr;
  }
  auto logError = [&]() {
    _codeGenerationContext->getLogger()->LogError(
        "Property " + propertyKey + " is not an object in variable " +
        parPropertyKey + " of Type " + objTypeType->getStructName().str());

    return nullptr;
  };

  const bool isNested =
      _variableExpression->getDotExpressionList().size() > listIndex + 1;

  if (isNested && boundTypeExpressionMap[propertyKey]->getSyntaxType() !=
                      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    return logError();
  }
  llvm::Value *elementPtr =
      Builder->CreateStructGEP(objTypeType, variableElementPtr, index);

  if (boundTypeExpressionMap[propertyKey]->getSyntaxType() ==
      SyntaxKindUtils::SyntaxKind::NBU_OBJECT_TYPE) {
    std::unique_ptr<ObjectExpressionGenerationStrategy> objExpGenStrat =
        std::make_unique<ObjectExpressionGenerationStrategy>(
            _codeGenerationContext);

    const std::string var_name =
        variableElementPtr->getName().str() + "." + propertyKey;

    llvm::GlobalVariable *globalVariable =
        TheModule->getGlobalVariable(var_name);

    llvm::AllocaInst *allocaInst =
        _codeGenerationContext->getAllocaChain()->getAllocaInst(var_name);

    llvm::StructType *structType = nullptr;
    if (allocaInst) {
      const bool isStruct =
          llvm::isa<llvm::StructType>(allocaInst->getAllocatedType());

      if (!isStruct) return logError();
      structType = llvm::cast<llvm::StructType>(allocaInst->getAllocatedType());
      if (isNested) return assignObject(allocaInst, listIndex + 1, propertyKey);

      objExpGenStrat->setVariable(allocaInst);

    } else if (globalVariable) {
      const bool isStruct =
          llvm::isa<llvm::StructType>(globalVariable->getValueType());

      if (!isStruct) return logError();

      structType = llvm::cast<llvm::StructType>(globalVariable->getValueType());
      if (isNested)
        return assignObject(globalVariable, listIndex + 1, propertyKey);

      objExpGenStrat->setVariable(globalVariable);
    } else {
      return logError();
    }

    if (_rhsExpression->getKind() != BinderKindUtils::BoundObjectExpression) {
      return logError();
    }

    objExpGenStrat->setTypeName(structType->getName().str());

    return objExpGenStrat->generateGlobalExpression(_rhsExpression);
  }

  llvm::Value *rhsValue =
      _expressionGenerationFactory->createStrategy(_rhsExpression->getKind())
          ->generateExpression(_rhsExpression);

  if (rhsValue->getType() != type) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in assignment expression, expected " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(type) +
        " but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(
            rhsValue->getType()) +
        " ");

    return nullptr;
  }

  Builder->CreateStore(rhsValue, elementPtr);

  return rhsValue;
}