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

  llvm::GlobalVariable *variable = TheModule->getGlobalVariable(variableName);

  llvm::Value *variableValue =
      _codeGenerationContext->getNamedValueChain()->getNamedValue(variableName);

  if (!variableValue) {
    if (variable) {
      return this->handleGlobalVariable(variableName, variable);
    }

    _codeGenerationContext->getLogger()->LogError(
        "Variable not found in variable expression ");

    return nullptr;
  }

  llvm::AllocaInst *v =
      _codeGenerationContext->getAllocaChain()->getAllocaInst(variableName);

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
  if (variable->getValueType()->isIntegerTy(32) ||
      variable->getValueType()->isIntegerTy(64) ||
      variable->getValueType()->isIntegerTy(1) ||
      variable->getValueType()->isFloatTy() ||
      variable->getValueType()->isDoubleTy() ||
      variable->getValueType()->isIntegerTy(8) ||
      variable->getValueType()->isBFloatTy() ||
      variable->getValueType()->isHalfTy() ||
      variable->getValueType()->isFP128Ty() ||
      variable->getValueType()->isX86_FP80Ty() ||
      variable->getValueType()->isPPC_FP128Ty()) {
    llvm::Value *loaded =
        Builder->CreateLoad(variable->getValueType(), variable, variableName);

    return loaded;
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