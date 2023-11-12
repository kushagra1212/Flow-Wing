#include "AssignmentExpressionGenerationStrategy.h"

AssignmentExpressionGenerationStrategy::AssignmentExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *AssignmentExpressionGenerationStrategy::handleAssignmentExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      static_cast<BoundAssignmentExpression *>(expression);

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

  llvm::GlobalVariable *oldVariable =
      TheModule->getGlobalVariable(variableName);

  if (!oldVariable) {

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in assignment expression ");

    return nullptr;
  }

  if (auto constDataArray = llvm::dyn_cast<llvm::ConstantDataArray>(rhsValue)) {

    if (_codeGenerationContext->getMapper()->isStringType(rhsValue->getType()))
      Builder->CreateStore(rhsValue, oldVariable);
    else {

      _codeGenerationContext->getLogger()->LogError(
          "Assigning " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()) +
          " to String is not allowed in Global "
          "assignment expression ");
    }

  } else {

    if (rhsValue->getType() == oldVariable->getValueType())
      Builder->CreateStore(rhsValue, oldVariable);
    else {
      _codeGenerationContext->getLogger()->LogError(
          "Assigning " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              rhsValue->getType()) +
          " to " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(
              oldVariable->getValueType()) +
          " is not allowed in Global "
          "assignment expression ");
    }
  }

  return nullptr;
}

llvm::Value *AssignmentExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundAssignmentExpression *assignmentExpression =
      (BoundAssignmentExpression *)expression;

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

llvm::Value *AssignmentExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  return this->handleAssignmentExpression(expression);
}
