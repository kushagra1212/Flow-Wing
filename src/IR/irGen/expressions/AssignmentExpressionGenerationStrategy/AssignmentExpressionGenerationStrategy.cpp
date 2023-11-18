#include "AssignmentExpressionGenerationStrategy.h"

AssignmentExpressionGenerationStrategy::AssignmentExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleGlobalLiteralExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  std::any value =
      ((BoundLiteralExpression<std::any> *)assignmentExpression->getLeftPtr()
           .get())
          ->getValue();
  std::string variableName = std::any_cast<std::string>(value);

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
  Utils::type variableType = assignmentExpression->getVariable().type;
  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getGlobalTypeMap()[variableName] !=
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              rhsValue->getType())) {

    std::string errorStr = _codeGenerationContext->getLogger()->getLLVMErrorMsg(
        "Type mismatch in variable Assignment " + variableName +
            " Expected type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
            " but got type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(
                rhsValue->getType()),
        assignmentExpression->getLocation());
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(errorStr)});
    return nullptr;
  }

  llvm::GlobalVariable *oldVariable =
      TheModule->getGlobalVariable(variableName);

  if (!oldVariable) {

    _codeGenerationContext->getLogger()->LogError(
        "Global Variable not found in assignment expression ");

    return nullptr;
  }

  llvm::Value *loadedValue = Builder->CreateLoad(oldVariable->getValueType(),
                                                 oldVariable, variableName);

  llvm::Value *updatedValue = Builder->CreateInsertValue(
      loadedValue, rhsValue,
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType()));

  _codeGenerationContext->getGlobalTypeMap()[variableName] =
      _codeGenerationContext->getDynamicType()->getIndexofMemberType(
          rhsValue->getType());

  Builder->CreateStore(updatedValue, oldVariable);
  return nullptr;
}

llvm::Value *
AssignmentExpressionGenerationStrategy::handleLiteralExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  std::any value =
      ((BoundLiteralExpression<std::any> *)assignmentExpression->getLeftPtr()
           .get())
          ->getValue();
  std::string variableName = std::any_cast<std::string>(value);

  llvm::Value *oldValue =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(variableName);

  if (!oldValue) {
    // Variable not found, handle error

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      this->generateGlobalExpression(assignmentExpression);
      return nullptr;
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression ");

    return nullptr;
  }

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

  Utils::type variableType = assignmentExpression->getVariable().type;

  if (variableType != Utils::type::UNKNOWN &&
      _codeGenerationContext->getGlobalTypeMap()[variableName] !=
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              rhsValue->getType())) {
    std::string errorStr = _codeGenerationContext->getLogger()->getLLVMErrorMsg(
        "Type mismatch in variable Assignment " + variableName +
            " Expected type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(variableType) +
            " but got type " +
            _codeGenerationContext->getMapper()->getLLVMTypeName(
                rhsValue->getType()),
        assignmentExpression->getLocation());
    Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
        {Builder->CreateGlobalStringPtr(errorStr)});
    return nullptr;
  }

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

    _codeGenerationContext->getLogger()->LogError(
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
    _codeGenerationContext->getLogger()->LogError(
        "Index value not found in assignment expression ");

    return nullptr;
  }

  llvm::Value *loadedElementValue =
      _expressionGenerationFactory->createStrategy(indexExpression->getKind())
          ->generateExpression(indexExpression);

  if (!loadedElementValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Index value not found in assignment expression ");

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

// TODO: Implement global index expression assignment
llvm::Value *
AssignmentExpressionGenerationStrategy::handleGlobalIndexExpressionAssignment(
    BoundAssignmentExpression *assignmentExpression) {
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      assignmentExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "TODO: Implement global index expression assignment ");

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
    return this->handleGlobalLiteralExpressionAssignment(assignmentExpression);
  } else if (auto boundIndexExpression = dynamic_cast<BoundIndexExpression *>(
                 assignmentExpression->getLeftPtr().get())) {
    return this->handleGlobalIndexExpressionAssignment(assignmentExpression);
  }

  _codeGenerationContext->getLogger()->LogError(
      "Left hand side value not found in assignment expression ");

  return nullptr;
}
