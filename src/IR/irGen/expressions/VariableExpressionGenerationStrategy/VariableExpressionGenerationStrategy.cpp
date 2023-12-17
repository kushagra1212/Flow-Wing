#include "VariableExpressionGenerationStrategy.h"

VariableExpressionGenerationStrategy::VariableExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *VariableExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableExpression->getLocation());

  std::string variableName = std::any_cast<std::string>(
      ((BoundLiteralExpression<std::any> *)variableExpression
           ->getIdentifierExpressionPtr()
           .get())
          ->getValue());

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  llvm::Value *variableValue =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(variableName);

  if (!variableValue) {
    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      return this->handleGlobalDeclaredVariable(variableName, variable);
    }
    // When Local Variable is an array type
    if (v && llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
      return v;
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression ");

    return nullptr;
  }

  // When Local Variable is not a dynamic type
  if (!_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {

    llvm::Value *value =
        Builder->CreateLoad(variableValue->getType(), v, variableName);

    return variableValue;
  }

  // When Local Variable is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {

    return Builder->CreateLoad(
        variableValue->getType(),
        Builder->CreateStructGEP(
            _codeGenerationContext->getDynamicType()->get(), v,
            _codeGenerationContext->getDynamicType()->getIndexofMemberType(
                variableValue->getType())));
  }

  // When Local Variable is a struct type
  if (llvm::isa<llvm::StructType>(v->getAllocatedType())) {
    return v;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");

  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::handleGlobalDeclaredVariable(
    const std::string &variableName, llvm::GlobalVariable *variable) {

  // when Global Variable (Value) is an array type
  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {
    return variable;
  }

  // when Global Variable (Value) is not a dynamic type
  if (!_codeGenerationContext->getDynamicType()->isDyn(
          variable->getValueType())) {
    return Builder->CreateLoad(variable->getValueType(), variable,
                               variableName);
  }

  // when Global Variable (Value) is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(
          variable->getValueType())) {
    llvm::Value *loadedValue =
        Builder->CreateLoad(variable->getValueType(), variable, variableName);

    // Extract the  value from the structure
    llvm::Value *innerValue = Builder->CreateExtractValue(
        loadedValue, _codeGenerationContext->getGlobalTypeMap()[variableName]);

    return innerValue;
  }

  // When Global Variable (Value) is a struct type
  if (llvm::isa<llvm::StructType>(variable->getValueType())) {
    return variable;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");
  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundVariableExpression *variableExpression =
      static_cast<BoundVariableExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      variableExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Variable Expression is not allowed in global scope ");

  return nullptr;
}