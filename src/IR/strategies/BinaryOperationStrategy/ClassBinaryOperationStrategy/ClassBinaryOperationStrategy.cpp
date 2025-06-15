
#include "ClassBinaryOperationStrategy.h"

ClassBinaryOperationStrategy::ClassBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *ClassBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *ClassBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {
  llvm::Value *result = Builder->getInt32(1);

  if (!OperationSupport::isSupported(OperationSupport::ClassStrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for class type ");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return Builder->CreateLogicalAnd(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return Builder->CreateLogicalOr(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {

    llvm::Value *_val = Builder->CreateICmpEQ(
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), rhsValue));
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    llvm::Value *_val = Builder->CreateICmpNE(
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), rhsValue));

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }

  default: {

    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for class type ");
    break;
  }
  }

  return nullptr;
}
