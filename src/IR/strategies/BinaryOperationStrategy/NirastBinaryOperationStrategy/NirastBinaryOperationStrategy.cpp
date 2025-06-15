#include "NirastBinaryOperationStrategy.h"

NirastBinaryOperationStrategy::NirastBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *NirastBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *NirastBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  bool isLhsNirast = _typeMapper->isNirastValue(lhsValue);
  bool isRhsNirast = _typeMapper->isNirastValue(rhsValue);

  llvm::Value *valueOperand = isLhsNirast ? rhsValue : lhsValue;
  llvm::Type *valueType = valueOperand->getType();

  if (!OperationSupport::isSupported(OperationSupport::NirastStrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for Nirast type");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {
    if (isLhsNirast && isRhsNirast) {
      return Builder->getTrue();
    }

    if (valueType->isFloatingPointTy() || valueType->isIntegerTy()) {

      return Builder->getFalse();
    }

    if (lhsValue->getType() == llvm::StructType::getTypeByName(
                                   *_codeGenerationContext->getContext(),
                                   DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) &&
        isLhsNirast

    ) {
      return Builder->CreateIsNull(rhsValue);
    }

    if (rhsValue->getType() == llvm::StructType::getTypeByName(
                                   *_codeGenerationContext->getContext(),
                                   DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) &&
        isRhsNirast

    ) {
      return Builder->CreateIsNull(lhsValue);
    }

    if (valueType->isPointerTy()) {
      return Builder->CreateIsNull(valueOperand);
    }
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {
    // Both are Nirast
    if (isLhsNirast && isRhsNirast) {
      return Builder->getFalse();
    }

    // Compare the value operand to its type-specific "zero" or "null" value
    if (valueType->isFloatingPointTy() || valueType->isIntegerTy()) {

      return Builder->getTrue();
    }

    if (lhsValue->getType() == llvm::StructType::getTypeByName(
                                   *_codeGenerationContext->getContext(),
                                   DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) &&
        isLhsNirast

    ) {
      return Builder->CreateIsNotNull(rhsValue);
    }

    if (rhsValue->getType() == llvm::StructType::getTypeByName(
                                   *_codeGenerationContext->getContext(),
                                   DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE) &&
        isRhsNirast

    ) {
      return Builder->CreateIsNotNull(lhsValue);
    }

    if (valueType->isPointerTy()) {
      return Builder->CreateIsNotNull(valueOperand);
    }
    break;
  }
  default:
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for Nirast type");
    break;
  }

  return nullptr;
}