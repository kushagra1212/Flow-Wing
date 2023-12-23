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

  llvm::Value *loadedValue =
      Builder->CreateLoad(variable->getValueType(), variable, variableName);

  Builder->CreateStore(rhsValue, variable);
  return nullptr;
}

llvm::Value *AssignmentExpressionGenerationStrategy::
    handleUnTypedPrmitiveGlobalVariableAssignment(
        llvm::GlobalVariable *variable, const std::string &variableName,
        llvm::Value *rhsValue) {

  llvm::Value *loadedValue =
      Builder->CreateLoad(variable->getValueType(), variable, variableName);

  llvm::Value *updatedValue = Builder->CreateInsertValue(
      loadedValue, rhsValue,
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType()));

  _codeGenerationContext->getGlobalTypeMap()[variableName] =
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType());

  Builder->CreateStore(updatedValue, variable);
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

  Builder->CreateStore(
      rhsValue,
      Builder->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), v,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              rhsValue->getType())));

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
llvm::Value *
AssignmentExpressionGenerationStrategy::handleIndexExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  BoundIndexExpression *indexExpression = static_cast<BoundIndexExpression *>(
      assignmentExpression->getLeftPtr().get());

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(assignmentExpression->getRightPtr().get()->getKind())
          ->generateExpression(assignmentExpression->getRightPtr().get());

  if (!rhsValue) {
    // Error generating IR for the right-hand side expression

    _codeGenerationContext->callREF(
        "Right hand side value not found in assignment expression ");

    return nullptr;
  }

  llvm::Value *indexValue =
      _expressionGenerationFactory
          ->createStrategy(
              indexExpression->getBoundIndexExpression().get()->getKind())
          ->generateExpression(
              indexExpression->getBoundIndexExpression().get());

  if (!indexValue) {

    _codeGenerationContext->callREF(
        "Index value not found in assignment expression");

    return nullptr;
  }

  llvm::Value *loadedElementValue =
      _expressionGenerationFactory->createStrategy(indexExpression->getKind())
          ->generateExpression(indexExpression);

  if (!loadedElementValue) {
    _codeGenerationContext->callREF(
        "Index value not found in assignment expression");

    return nullptr;
  }

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

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  if (!v) {
    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {

      return this->handleGlobalIndexExpressionAssignment(
          variable, indexValue, rhsValue, variableName);
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression , " + variableName);

    return nullptr;
  }

  // Get Element pointer
  llvm::Value *elementPtr = Builder->CreateGEP(
      v->getAllocatedType(), v,
      {Builder->getInt32(0), _int32TypeConverter->convertExplicit(indexValue)});

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

llvm::Value *
AssignmentExpressionGenerationStrategy::handleGlobalIndexExpressionAssignment(
    llvm::GlobalVariable *variable, llvm::Value *indexValue, llvm::Value *rhs,
    const std::string &variableName) {

  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {

    llvm::ArrayType *arrayType =
        llvm::dyn_cast<llvm::ArrayType>(variable->getValueType());

    llvm::Type *elementType = arrayType->getElementType();
    const uint64_t size = arrayType->getNumElements();

    llvm::Value *loadedValue =
        Builder->CreateLoad(variable->getValueType(), variable, variableName);

    llvm::Function *function = Builder->GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB =
        llvm::BasicBlock::Create(*TheContext, "then", function);
    llvm::BasicBlock *elseBB =
        llvm::BasicBlock::Create(*TheContext, "else", function);
    llvm::BasicBlock *mergeBB =
        llvm::BasicBlock::Create(*TheContext, "merge", function);

    // TODO: TO 64 Bit
    llvm::Value *isLessThan = Builder->CreateICmpSLT(
        indexValue,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), size, true),
        "isLessThan");

    llvm::Value *isGreaterThan = Builder->CreateICmpSGE(
        indexValue,
        llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0, true),
        "isGreaterThan");

    llvm::Value *isWithinBounds =
        Builder->CreateAnd(isLessThan, isGreaterThan, "isWithinBounds");

    // Create the conditional branch
    Builder->CreateCondBr(isWithinBounds, thenBB, elseBB);

    // In the then block, you can continue with the array access
    Builder->SetInsertPoint(thenBB);

    llvm::Value *ptr = Builder->CreateGEP(elementType, variable, indexValue);

    Builder->CreateStore(rhs, ptr);

    Builder->CreateBr(mergeBB);

    Builder->SetInsertPoint(elseBB);

    _codeGenerationContext->callREF("Index out of bounds of '" + variableName +
                                    "' in index expression, array size is " +
                                    std::to_string(size));

    Builder->CreateBr(mergeBB);

    // Continue from the merge block
    Builder->SetInsertPoint(mergeBB);

    return rhs;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable not found in assignment expression ");

  return nullptr;
}
llvm::Value *AssignmentExpressionGenerationStrategy::generateGlobalExpression(
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

    _previousGlobalVariable = TheModule->getGlobalVariable(_variableName);
    _allocaInst =
        _codeGenerationContext->getAllocaChain()->getAllocaInst(_variableName);
    if (_previousGlobalVariable) {
      _isGlobal = true;
      return true;
    }
    if (_allocaInst) {
      return true;
    }
    _codeGenerationContext->callREF(
        "Variable not found in assignment expression , " + _variableName);

    return false;
  }

  return true;
}