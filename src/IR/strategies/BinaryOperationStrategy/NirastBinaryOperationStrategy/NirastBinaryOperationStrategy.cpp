#include "NirastBinaryOperationStrategy.h"

NirastBinaryOperationStrategy::NirastBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *NirastBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();
  std::string errorMessage = "";
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {

    if (lhsValue ==
        llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*TheContext))) {
      return Builder->CreateNot(rhsValue);
    }

    if (rhsValue ==
        llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*TheContext))

    ) {
      return Builder->CreateNot(lhsValue);
    }

    if (lhsValue == llvm::ConstantPointerNull::get(
                        llvm::Type::getInt8PtrTy(*TheContext)) &&
        rhsValue == llvm::ConstantPointerNull::get(
                        llvm::Type::getInt8PtrTy(*TheContext))) {

      return Builder->getTrue();
    }

    errorMessage = "Unsupported equality operator for Nirast ";

    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {
    if (lhsValue ==
        llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*TheContext))) {
      return rhsValue;
    }

    if (rhsValue ==
        llvm::ConstantPointerNull::get(llvm::Type::getInt8PtrTy(*TheContext))) {
      return (lhsValue);
    }

    if (lhsValue == llvm::ConstantPointerNull::get(
                        llvm::Type::getInt8PtrTy(*TheContext)) &&
        rhsValue == llvm::ConstantPointerNull::get(
                        llvm::Type::getInt8PtrTy(*TheContext))) {

      return Builder->getTrue();
    }

    errorMessage = "Unsupported not-equality operator for Nirast ";
    break;
  }
  default: {

    errorMessage = "Unsupported binary operator for Nirast ";
    break;
  }
  }

  _codeGenerationContext->getLogger()->LogError(errorMessage);
  return nullptr;
}