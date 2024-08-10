#include "NirastBinaryOperationStrategy.h"

NirastBinaryOperationStrategy::NirastBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *NirastBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  std::string errorMessage = "";
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return Builder->CreateLogicalAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return Builder->CreateLogicalOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {
    llvm::Value *_val = Builder->CreateICmpEQ(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {
    llvm::Value *_val = Builder->CreateICmpNE(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  default: {

    errorMessage = "Unsupported binary operator for Nirast ";
    break;
  }
  }

  _codeGenerationContext->callREF(errorMessage);
  return nullptr;
}