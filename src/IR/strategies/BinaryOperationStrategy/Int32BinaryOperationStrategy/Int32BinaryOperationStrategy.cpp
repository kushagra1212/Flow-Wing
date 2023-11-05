
#include "Int32BinaryOperationStrategy.h"

Int32BinaryOperationStrategy::Int32BinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *Int32BinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  llvm::IRBuilder<> *Builder = this->_codeGenerationContext->getBuilder();
  llvm::Value *result = Builder->getInt32(1);

  std::string errorMessage = "";
  switch (binaryExpression->getOperator()) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {
    return result = Builder->CreateAdd(lhsValue, rhsValue);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return result = Builder->CreateSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return result = Builder->CreateMul(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {
    return Builder->CreateSDiv(lhsValue, rhsValue);
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    return Builder->CreateSRem(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return Builder->CreateOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return Builder->CreateXor(lhsValue, rhsValue);
    break;

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

  case BinderKindUtils::BoundBinaryOperatorKind::Equals:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpEQ(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpNE(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Less: {
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSLT(lhsValue, rhsValue));
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSLE(lhsValue, rhsValue));
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater:
    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSGT(lhsValue, rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals:

    return _typeSpecificValueVisitor->visit(
        _boolTypeConverter.get(), Builder->CreateICmpSGE(lhsValue, rhsValue));
    break;
  default: {

    errorMessage = "Unsupported binary operator for int type ";
    break;
  }
  }

  this->_codeGenerationContext->getLogger()->logLLVMError(
      llvm::createStringError(llvm::inconvertibleErrorCode(), errorMessage));

  return nullptr;
}