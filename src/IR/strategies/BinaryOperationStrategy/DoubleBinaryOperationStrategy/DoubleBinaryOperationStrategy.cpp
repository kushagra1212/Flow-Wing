
#include "DoubleBinaryOperationStrategy.h"

DoubleBinaryOperationStrategy::DoubleBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *DoubleBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  std::string errorMessage = "";
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {

    return Builder->CreateFAdd(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction: {

    return Builder->CreateFSub(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication: {

    return Builder->CreateFMul(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    return Builder->CreateFDiv(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus: {

    errorMessage = "Modulus is not supported for double type ";
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd: {

    errorMessage = "Bitwise And is not supported for double type ";
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr: {

    errorMessage = "Bitwise Or is not supported for double type ";
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor: {

    errorMessage = "Bitwise Xor is not supported for double type ";
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd: {

    errorMessage = "Logical And is not supported for double type ";
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr: {

    errorMessage = "Logical Or is not supported for double type ";
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {

    return Builder->CreateFCmpOEQ(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    return Builder->CreateFCmpONE(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Less: {

    return Builder->CreateFCmpOLT(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {

    return Builder->CreateFCmpOLE(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater: {

    return Builder->CreateFCmpOGT(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals: {

    return Builder->CreateFCmpOGE(lhsValue, rhsValue);
  }

  default: {
    errorMessage = "Unsupported binary operator for double type";
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(), errorMessage));

  return nullptr;
}