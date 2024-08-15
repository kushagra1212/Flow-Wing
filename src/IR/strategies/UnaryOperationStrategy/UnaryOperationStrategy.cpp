#include "UnaryOperationStrategy.h"

llvm::Value *UnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  if (_codeGenerationContext->getValueStackHandler()->isStructType() &&
      _codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
          _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {

    val = Builder->CreateIsNotNull(Builder->CreateLoad(
        llvm::Type::getInt8PtrTy(*TheContext),
        _codeGenerationContext->getValueStackHandler()->getValue()));
  }

  llvm::Value *result = nullptr;
  llvm::Type *type = val->getType();

  TypeMapper *typeMapper = this->_codeGenerationContext->getMapper().get();
  switch (unaryExpression->getOperatorPtr()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {

    result = Builder->CreateAdd(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    result = Builder->CreateSub(
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)), val);
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {

    if (typeMapper->isInt32Type(type) || typeMapper->isDoubleType(type) ||
        typeMapper->isFloatType(type)) {
      // Convert non-boolean values to boolean (true if zero, false if non-zero)
      result = Builder->CreateICmpEQ(
          val, llvm::Constant::getNullValue(val->getType()));
    } else if (typeMapper->isStringType(type)) {
      // Get the string length

      llvm::ArrayRef<llvm::Value *> Args = {
          _stringTypeConverter->convertExplicit(val)};
      llvm::Value *length = Builder->CreateCall(
          TheModule->getFunction(INNERS::FUNCTIONS::STRING_LENGTH), Args);
      val = length;

      // Compare the string Length to Zero
      result = Builder->CreateICmpEQ(
          length, llvm::ConstantInt::get(length->getType(), 0));
    } else if (typeMapper->isBoolType(type)) {
      // For boolean values, perform logical NOT
      result = Builder->CreateNot(val);
    } else if (typeMapper->isNirastValue(val)) {
      result = Builder->CreateICmpNE(
          val, llvm::Constant::getNullValue(val->getType()));
    }
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {

    result = Builder->CreateXor(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, -1, true)));
    break;
  }
  default: {
    break;
  }
  }

  if (!result) {
    this->_codeGenerationContext->getLogger()->logLLVMError(
        llvm::createStringError(llvm::inconvertibleErrorCode(),
                                "Unsupported Unary Expression Type "));
    return nullptr;
  }

  return result;
}
