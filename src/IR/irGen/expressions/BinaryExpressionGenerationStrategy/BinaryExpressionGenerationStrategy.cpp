#include "BinaryExpressionGenerationStrategy.h"

BinaryExpressionGenerationStrategy::BinaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *BinaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)expression;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      binaryExpression->getLocation());

  llvm::Value *lhsValue =
      _expressionGenerationFactory
          ->createStrategy(binaryExpression->getLeftPtr().get()->getKind())
          ->generateExpression(binaryExpression->getLeftPtr().get());

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  llvm::Value *rhsValue =
      _expressionGenerationFactory
          ->createStrategy(binaryExpression->getRightPtr().get()->getKind())
          ->generateExpression(binaryExpression->getRightPtr().get());

  if (!lhsValue || !rhsValue) {

    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Binary Expression Type ");
    return nullptr;
  }

  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  llvm::Value *result = nullptr;
  if (_typeMapper->isStringType(lhsType) ||
      _typeMapper->isStringType(rhsType)) {

    result = _stringBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), rhsValue),
        binaryExpression);

  } else if (_typeMapper->isDoubleType(lhsType) ||
             _typeMapper->isDoubleType(rhsType)) {

    result = _doubleBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(), rhsValue),
        binaryExpression);

  } else if (_typeMapper->isBoolType(lhsType) &&
             _typeMapper->isBoolType(rhsType)) {

    result = _boolBinaryOperationStrategy->performOperation(lhsValue, rhsValue,
                                                            binaryExpression);

  } else {

    result = _int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
        binaryExpression);
  }

  return result;
}

llvm::Value *BinaryExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundBinaryExpression *binaryExpression =
      static_cast<BoundBinaryExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      binaryExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Binary Expression is not allowed in global scope ");

  return nullptr;
}
