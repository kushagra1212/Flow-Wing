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

    if (v && llvm::isa<llvm::ArrayType>(v->getAllocatedType())) {
      return v;
    }

    if (variable) {
      return this->handleGlobalVariable(variableName, variable);
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable " + variableName + " not found in variable expression ");

    return nullptr;
  }

  // When Local Variable is not a dynamic type
  if (v->getAllocatedType() !=
      _codeGenerationContext->getDynamicType()->get()) {

    llvm::Value *value =
        Builder->CreateLoad(variableValue->getType(), v, variableName);

    return variableValue;
  }

  // Get the dynamic type of the variable

  llvm::Value *value = Builder->CreateLoad(
      variableValue->getType(),
      Builder->CreateStructGEP(
          _codeGenerationContext->getDynamicType()->get(), v,
          _codeGenerationContext->getDynamicType()->getIndexofMemberType(
              variableValue->getType())));

  return value;
}

llvm::Value *VariableExpressionGenerationStrategy::handleGlobalVariable(
    const std::string &variableName, llvm::GlobalVariable *variable) {

  // when Global Variable is not a dynamic type
  if (variable->getValueType() !=
      _codeGenerationContext->getDynamicType()->get()) {
    return Builder->CreateLoad(variable->getValueType(), variable,
                               variableName);
  }

  if (llvm::isa<llvm::StructType>(variable->getValueType())) {
    llvm::Value *loadedValue =
        Builder->CreateLoad(variable->getValueType(), variable, variableName);

    // Extract the boolean value from the structure
    llvm::Value *innerValue = Builder->CreateExtractValue(
        loadedValue,
        _codeGenerationContext
            ->getGlobalTypeMap()[variableName]); // 4 is the index of the
                                                 // boolean field

    return innerValue;
  }

  if (llvm::isa<llvm::ArrayType>(variable->getValueType())) {

    return variable;
  }

  llvm::Value *loaded =
      Builder->CreateLoad(variable->getValueType(), variable, variableName);
  llvm::Value *zero =
      llvm::ConstantInt::get(llvm::Type::getInt32Ty(*TheContext), 0);
  llvm::Value *indices[] = {zero, zero};
  llvm::Value *strPtr = Builder->CreateInBoundsGEP(
      variable->getValueType(), variable, indices, "str_ptr");

  llvm::Value *elementPtr = Builder->CreateBitCast(
      strPtr, llvm::IntegerType::getInt8PtrTy((*TheContext)), "element_ptr");

  return elementPtr;
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