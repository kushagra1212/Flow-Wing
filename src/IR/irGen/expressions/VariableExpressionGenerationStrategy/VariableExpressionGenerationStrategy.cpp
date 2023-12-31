#include "VariableExpressionGenerationStrategy.h"

VariableExpressionGenerationStrategy::VariableExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *
VariableExpressionGenerationStrategy::getTypedPrimitiveLocalVariableValue(
    const std::string &variableName, llvm::Value *variableValue,
    llvm::AllocaInst *v) {

  return Builder->CreateLoad(variableValue->getType(), v, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getUnTypedLocalVariableValue(
    llvm::Value *variableValue, llvm::AllocaInst *v,
    const std::string &variableName) {

  return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
      v, variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getLocalVariableValue(
    const std::string &variableName, llvm::Value *variableValue,
    llvm::AllocaInst *v) {

  // Typed Local Variables

  // When Local Variable is an array type
  if (v && llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
    return v;
  }
  if (!v) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression ");

    return nullptr;
  }

  // When Primitive Local Variable is not a dynamic type
  if (!_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {

    return this->getTypedPrimitiveLocalVariableValue(variableName,
                                                     variableValue, v);
  }

  // When Local Variable is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(v->getAllocatedType())) {
    return this->getUnTypedLocalVariableValue(variableValue, v, variableName);
  }

  // When Local Variable is a struct type
  if (v && llvm::isa<llvm::StructType>(v->getAllocatedType())) {
    return v;
  }

  _codeGenerationContext->getLogger()->LogError(
      "Variable " + variableName + " not found in variable expression ");

  return nullptr;
}

llvm::Value *VariableExpressionGenerationStrategy::getVariableValue(
    const std::string &variableName) {

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

  llvm::Value *variableValue =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(variableName);

  // Get Local Variable Value
  if (!variableValue) {

    if (v) {

      return this->getLocalVariableValue(variableName, variableValue, v);
    }

    llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

    if (variable) {
      return this->getGlobalVariableValue(variableName, variable);
    }
  }

  return this->getLocalVariableValue(variableName, variableValue, v);
}

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

  return this->getVariableValue(variableName);
}

llvm::Value *VariableExpressionGenerationStrategy::getGlobalVariableValue(
    const std::string &variableName, llvm::GlobalVariable *variable) {

  if (!variable) {
    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression ");

    return nullptr;
  }

  // when Global Variable (Value) is a dynamic type
  if (_codeGenerationContext->getDynamicType()->isDyn(
          variable->getValueType())) {

    return _codeGenerationContext->getDynamicType()->getMemberValueOfDynVar(
        variable,
        FLOWWING::UTILS::CONSTANTS::GLOBAL_VARIABLE_PREFIX + variableName);
  }

  // Typed Global Variables

  // when Global Variable (Value) is an array type
  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {
    return variable;
  }

  // When Global Variable (Value) is a struct type
  if (llvm::isa<llvm::StructType>(variable->getValueType())) {
    return variable;
  }

  // when Primitive Typed Global Variable (Value)

  return Builder->CreateLoad(variable->getValueType(), variable, variableName);
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