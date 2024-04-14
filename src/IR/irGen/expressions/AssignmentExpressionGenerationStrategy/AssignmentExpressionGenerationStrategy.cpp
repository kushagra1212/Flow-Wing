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
    auto assignStrategy =
        std::make_unique<ObjectAssignmentExpressionGenerationStrategy>(
            _codeGenerationContext);

    return assignStrategy->generateGlobalExpression(assignmentExpression);
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

      return assignStrategy->generateGlobalExpression(assignmentExpression);
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

  if (lhsType != rhsType) {
    _codeGenerationContext->getLogger()->LogError(
        "Type mismatch in assignment expression, expected " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(lhsType) +
        " but found " +
        _codeGenerationContext->getMapper()->getLLVMTypeName(rhsType) + " ");
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
