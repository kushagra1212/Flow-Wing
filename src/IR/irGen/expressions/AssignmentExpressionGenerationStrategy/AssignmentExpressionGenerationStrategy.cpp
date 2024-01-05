#include "AssignmentExpressionGenerationStrategy.h"

AssignmentExpressionGenerationStrategy::AssignmentExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleTypedPrmitiveGlobalVariableAssignment(llvm::GlobalVariable *variable,
                                                const std::string &variableName,
                                                const Utils::type &variableType,
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
    const Utils::type &variableType, llvm::Value *rhsValue) {

  // Handle Static Primitive Global Variable (TYPED)
  if (Utils::isStaticTypedPrimitiveType(variableType)) {
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

  if (!canGenerateLiteralExpressionAssignment(assignmentExpression)) {
    return nullptr;
  }

  // Handle Static Container Global Variable (TYPED)
  if (Utils::isStaticTypedContainerType(_variableType)) {

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
    handleTypedPrmitiveLocalVariableAssignment(const std::string &variableName,
                                               const Utils::type &variableType,
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
    const std::string &variableName, const Utils::type &variableType,
    llvm::Value *rhsValue) {

  // Handle Static Primitive Local Variable (TYPED)
  if (Utils::isStaticTypedPrimitiveType(variableType)) {
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

  // Handle Static Container local Variable (TYPED)
  if (Utils::isStaticTypedContainerType(_variableType)) {
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
  _variableType = assignmentExpression->getVariable().type;
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

  // Typed Container

  if (!Utils::isDynamicTypedContainerType(_variableType) &&
      rhsValue->getType() != loadedElementValue->getType()) {
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

  if (!alloca) { // Error Already Handled Look at the index
                 // expression Up :)
    llvm::GlobalVariable *gv = TheModule->getGlobalVariable(
        variableName); // Error was handled before
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

  // Untyped Container
  if (Utils::isDynamicTypedContainerType(_variableType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Dynamic typed container not supported in assignment expression");
    return nullptr;
  }

  Builder->CreateStore(rhsValue, elementPtr);

  return rhsValue;
}

llvm::Value *AssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  if (auto boundLiteralExpression =
          dynamic_cast<BoundLiteralExpression<std::any> *>(
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
  _isGlobal = true;
  if (auto boundLiteralExpression =
          dynamic_cast<BoundLiteralExpression<std::any> *>(
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

  std::any value =
      ((BoundLiteralExpression<std::any> *)assignmentExpression->getLeftPtr()
           .get())
          ->getValue();

  _variableName = std::any_cast<std::string>(value);
  llvm::Value *val =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(
          _variableName);
  _variableType = assignmentExpression->getVariable().type;
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
        "Variable not found in assignment expression , " + _variableName);

    return false;
  }

  return true;
}