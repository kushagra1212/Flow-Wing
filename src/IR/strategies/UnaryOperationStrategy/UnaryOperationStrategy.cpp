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

  llvm::Type *type = val->getType();

  TypeMapper *typeMapper = this->_codeGenerationContext->getMapper().get();
  switch (unaryExpression->getOperatorPtr()) {
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {

    return Builder->CreateAdd(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)));
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {

    return Builder->CreateSub(
        llvm::ConstantInt::get(*TheContext, llvm::APInt(32, 0, true)), val);
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {

    if (typeMapper->isInt32Type(type) || typeMapper->isDoubleType(type) ||
        typeMapper->isFloatType(type)) {
      // Convert non-boolean values to boolean (true if zero, false if non-zero)
      return Builder->CreateICmpEQ(
          val, llvm::Constant::getNullValue(val->getType()));
    } else if (typeMapper->isStringType(type)) {

      auto stringLengthFunc =
          TheModule->getFunction(INNERS::FUNCTIONS::STRING_LENGTH);

      if (!stringLengthFunc) {
        // Function not found, handle error
        _codeGenerationContext->getLogger()->LogError(
            "function " + INNERS::FUNCTIONS::STRING_LENGTH + " not found");
        return nullptr;
      }
      // Get the string length
      llvm::Value *v = Builder->CreateCall(
          stringLengthFunc, {_stringTypeConverter->convertExplicit(val)});

      // Compare the string Length to Zero

      //! For String
      return Builder->CreateICmpEQ(v, llvm::ConstantInt::get(v->getType(), 0));
    } else if (typeMapper->isBoolType(type)) {
      // For boolean values, perform logical NOT
      return Builder->CreateNot(val);
    } else if (typeMapper->isNirastValue(val)) {
      return Builder->CreateICmpNE(
          val, llvm::Constant::getNullValue(val->getType()));
    }
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {

    return Builder->CreateXor(
        val, llvm::ConstantInt::get(*TheContext, llvm::APInt(32, -1, true)));
  }
  default: {
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->LogError(
      "Unsupported Unary Expression Type ");

  return nullptr;
}
