
#include "BoolBinaryOperationStrategy.h"

BoolBinaryOperationStrategy::BoolBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *BoolBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  llvm::IRBuilder<> *Builder = this->_codeGenerationContext->getBuilder();
  llvm::Value *result = nullptr;
  std::string errorMessage = "";

  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition:
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor: {

    std::unique_ptr<Int32BinaryOperationStrategy> int32BinaryOperationStrategy =
        std::make_unique<Int32BinaryOperationStrategy>(
            this->_codeGenerationContext);

    result = int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
        binaryExpression);

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), result);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    std::unique_ptr<Int32BinaryOperationStrategy> int32BinaryOperationStrategy =
        std::make_unique<Int32BinaryOperationStrategy>(
            this->_codeGenerationContext);

    result = int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
        binaryExpression);

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), result);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return Builder->CreateLogicalAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return Builder->CreateLogicalOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return Builder->CreateICmpEQ(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return Builder->CreateICmpNE(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less:
    return Builder->CreateICmpSLT(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals:

    return Builder->CreateICmpSLE(lhsValue, rhsValue);
    break;

  case BinderKindUtils ::BoundBinaryOperatorKind::Greater:
    return Builder->CreateICmpSGT(lhsValue, rhsValue);
    break;

  case BinderKindUtils ::BoundBinaryOperatorKind::GreaterOrEquals:

    return Builder->CreateICmpSGE(lhsValue, rhsValue);

  // Add more cases for other binary operators
  default:

    errorMessage = "Unsupported binary operator for bool type ";

    break;
  }
  this->_codeGenerationContext->getLogger()->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(), errorMessage));

  return nullptr;
}