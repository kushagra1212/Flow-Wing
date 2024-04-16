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

  return handleDynamicPrimitiveVariableAssignment(variable, variableName,
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
    auto assignStrategy =
        std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);

    return assignStrategy->generateGlobalExpression(assignmentExpression);
  }

  // Handle Static Container Global Variable (TYPED)
  if (_variableType != SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE &&
      !_codeGenerationContext->getMapper()->isPrimitiveType(_variableType)) {

    auto assignStrategy =
        std::make_unique<ContainerAssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);

    return assignStrategy->generateGlobalExpression(assignmentExpression);

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

    return bracketdStrategy->generateGlobalExpression(
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
    auto assignStrategy =
        std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);

    return assignStrategy->generateExpression(assignmentExpression);
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
    return bracketdStrategy->generateExpression(
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

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getLeftPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getLeftPtr().get());
  llvm::Value *lhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *lhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    _codeGenerationContext->getLogger()->LogError(
        "Assignment to constant  is not supported");
    return nullptr;
  }
  llvm::Value *lhsValue = Builder->CreateLoad(lhsType, lhsPtr);
  _codeGenerationContext->getValueStackHandler()->popAll();

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getRightPtr().get());

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = Builder->CreateLoad(rhsType, rhsPtr);
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  if (!rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Right hand side value not found in assignment expression ");
    return nullptr;
  }

  if (!lhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value not found in assignment expression ");
    return nullptr;
  }
  if (llvm::isa<llvm::ArrayType>(lhsType) &&
      llvm::isa<llvm::ArrayType>(rhsType)) {

    if (_codeGenerationContext->verifyArrayType(
            llvm::cast<llvm::ArrayType>(lhsType),
            llvm::cast<llvm::ArrayType>(rhsType)) == EXIT_FAILURE)
      return nullptr;
  }

  Builder->CreateStore(rhsValue, lhsPtr);

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
  return handleAssignmentExpression(assignmentExpression);
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

int8_t AssignmentExpressionGenerationStrategy::populateLHS(
    BoundAssignmentExpression *&assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _lhsTypeKind =
      assignmentExpression->getVariable()->getTypeExpression()->getSyntaxType();

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getLeftPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getLeftPtr().get());
  _lhsPtr = _codeGenerationContext->getValueStackHandler()->getValue();
  _lhsType = _codeGenerationContext->getValueStackHandler()->getLLVMType();
  _codeGenerationContext->getValueStackHandler()->popAll();

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    _codeGenerationContext->getLogger()->LogError(
        "Assignment to constant  is not supported in assignment expression ");
    return EXIT_FAILURE;
  }

  if (assignmentExpression->getLeftPtr()->getKind() !=
      BinderKindUtils::VariableExpression) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value must be a variable in assignment expression ");
    return EXIT_FAILURE;
  }

  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(
          assignmentExpression->getLeftPtr().get());

  _lhsVariableName = variableExpression->getVariableNameRef();

  return EXIT_SUCCESS;
}

llvm::Value *AssignmentExpressionGenerationStrategy::handleAssignmentByVariable(
    BoundVariableExpression *variableExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableExpression->getLocation());

  _expressionGenerationFactory->createStrategy(variableExpression->getKind())
      ->generateExpression(variableExpression);

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();
  } else {
    rhsValue = Builder->CreateLoad(rhsType, rhsPtr);
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  if (_lhsTypeKind == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE) {

    return handleDynamicPrimitiveVariableAssignment(_lhsPtr, _lhsVariableName,
                                                    rhsValue);
  }

  if (llvm::isa<llvm::StructType>(_lhsType) &&
      llvm::isa<llvm::StructType>(rhsType)) {
    if (_codeGenerationContext->verifyStructType(
            llvm::cast<llvm::StructType>(_lhsType),
            llvm::cast<llvm::StructType>(rhsType)) == EXIT_FAILURE) {
      return nullptr;
    }

    return Builder->CreateStore(rhsValue, _lhsPtr);
  }

  if (llvm::isa<llvm::ArrayType>(_lhsType) &&
      llvm::isa<llvm::ArrayType>(rhsType)) {

    if (_codeGenerationContext->verifyArrayType(
            llvm::cast<llvm::ArrayType>(_lhsType),
            llvm::cast<llvm::ArrayType>(rhsType)) == EXIT_FAILURE)
      return nullptr;

    return Builder->CreateStore(rhsValue, _lhsPtr);
  }

  if (_lhsType != rhsType) {

    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in variable Assignment " + _lhsVariableName +
        " Expected type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsTypeKind) +
        " but got type " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType));

    return nullptr;
  }

  return Builder->CreateStore(rhsValue, _lhsPtr);
}

llvm::Value *AssignmentExpressionGenerationStrategy::handleAssignmentExpression(
    BoundAssignmentExpression *assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  if (populateLHS(assignmentExpression) == EXIT_FAILURE)
    return nullptr;

  BinderKindUtils::BoundNodeKind rhsKind =
      assignmentExpression->getRightPtr()->getKind();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getRightPtr()->getLocation());

  switch (rhsKind) {
  case BinderKindUtils::VariableExpression:
    return handleAssignmentByVariable(static_cast<BoundVariableExpression *>(
        assignmentExpression->getRightPtr().get()));

  case BinderKindUtils::BoundBracketedExpression:
    return handleAssignmentByBracketedExpression(
        static_cast<BoundBracketedExpression *>(
            assignmentExpression->getRightPtr().get()));

  default:
    break;
  }

  if (handleWhenRHSIsConstant(assignmentExpression) == EXIT_SUCCESS)
    return nullptr;

  _codeGenerationContext->getLogger()->LogError(
      "Right hand side value must be a proper value in assignment expression ");

  return nullptr;
}
llvm::Value *AssignmentExpressionGenerationStrategy::
    handleDynamicPrimitiveVariableAssignment(llvm::Value *variable,
                                             const std::string &variableName,
                                             llvm::Value *rhsValue) {
  _codeGenerationContext->getDynamicType()->setMemberValueOfDynVar(
      variable, rhsValue, rhsValue->getType(),
      FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX + variableName);

  return nullptr;
}

int8_t AssignmentExpressionGenerationStrategy::handleWhenRHSIsConstant(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getRightPtr()->getLocation());

  _expressionGenerationFactory
      ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
      ->generateExpression(assignmentExpression->getRightPtr().get());

  llvm::Value *rhsPtr =
      _codeGenerationContext->getValueStackHandler()->getValue();
  llvm::Type *rhsType =
      _codeGenerationContext->getValueStackHandler()->getLLVMType();
  llvm::Value *rhsValue = nullptr;

  if (_codeGenerationContext->getValueStackHandler()->isLLVMConstant()) {
    rhsValue = _codeGenerationContext->getValueStackHandler()->getValue();

    if (_lhsTypeKind == SyntaxKindUtils::SyntaxKind::NBU_UNKNOWN_TYPE)
      handleDynamicPrimitiveVariableAssignment(_lhsPtr, _lhsVariableName,
                                               rhsValue);
    else
      Builder->CreateStore(rhsValue, _lhsPtr);

    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleAssignmentByBracketedExpression(
    BoundBracketedExpression *bracketedExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      bracketedExpression->getLocation());

  if (!llvm::isa<llvm::ArrayType>(_lhsType)) {
    _codeGenerationContext->getLogger()->LogError(
        "Left hand side value must be an array in assignment expression, but "
        "found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(_lhsType));
    return nullptr;
  }

  std::unique_ptr<BracketedExpressionGenerationStrategy>
      bracketedExpressionGenerationStrategy =
          std::make_unique<BracketedExpressionGenerationStrategy>(
              _codeGenerationContext);
  return bracketedExpressionGenerationStrategy->assignBracketExpression(
      bracketedExpression, _lhsPtr, llvm::cast<llvm::ArrayType>(_lhsType),
      _lhsVariableName);
}