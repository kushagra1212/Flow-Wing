#include "BinaryExpressionGenerationStrategy.h"

BinaryExpressionGenerationStrategy::BinaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *BinaryExpressionGenerationStrategy::getExpressionValue(
    BoundExpression *expression, bool &isClassType) {
  llvm::Value *value =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (_codeGenerationContext->getValueStackHandler()->isStructType()) {
    if (!_codeGenerationContext->isValidClassType(llvm::cast<llvm::StructType>(
            _codeGenerationContext->getValueStackHandler()->getLLVMType()))) {
      _codeGenerationContext->getLogger()->LogError(
          "This Binary Expression is not supported for objects");
      return nullptr;
    }

    value = Builder->CreateIsNotNull(Builder->CreateLoad(
        llvm::Type::getInt8PtrTy(*TheContext),
        _codeGenerationContext->getValueStackHandler()->getValue()));
    isClassType = true;
  }
  if (_codeGenerationContext->getValueStackHandler()->isPrimaryType()) {
    value = Builder->CreateLoad(
        _codeGenerationContext->getValueStackHandler()->getLLVMType(),
        _codeGenerationContext->getValueStackHandler()->getValue());
  }
  _codeGenerationContext->getValueStackHandler()->popAll();

  return value;
}

llvm::Value *BinaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)expression;

  bool isClassType = false;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      binaryExpression->getLocation());
  _codeGenerationContext->getValueStackHandler()->popAll();

  llvm::Value *lhsValue = this->getExpressionValue(
      binaryExpression->getLeftPtr().get(), isClassType);

  llvm::Value *rhsValue = this->getExpressionValue(
      binaryExpression->getRightPtr().get(), isClassType);

  if (!lhsValue || !rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Binary Expression Type ");
    return nullptr;
  }

  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  llvm::Value *result = nullptr;

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  if (isClassType && (_typeMapper->isNirastValue(lhsValue) ||
                      _typeMapper->isNirastValue(rhsValue))) {
    result = _nirastBinaryOperationStrategy->performOperation(
        lhsValue, rhsValue, binaryExpression);
  } else if (_typeMapper->isStringType(lhsType) ||
             _typeMapper->isStringType(rhsType)) {
    result = _stringBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), rhsValue),
        binaryExpression);
  } else if (_typeMapper->isFloatType(lhsType) ||
             _typeMapper->isFloatType(rhsType)) {
    result = _floatBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), rhsValue),
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

  if (!result) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Binary Operation !");
    return nullptr;
  }

  _codeGenerationContext->getValueStackHandler()->popAll();

  _codeGenerationContext->getValueStackHandler()->push("", result, "constant",
                                                       result->getType());
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
