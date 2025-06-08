#include "BinaryExpressionGenerationStrategy.h"

BinaryExpressionGenerationStrategy::BinaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *BinaryExpressionGenerationStrategy::getExpressionValue(
    BoundExpression *expression, bool &isClassType, int8_t &isDynamicValue) {
  _codeGenerationContext->getValueStackHandler()->popAll();
  llvm::Value *value =
      _expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (_codeGenerationContext->getValueStackHandler()->isDynamicValueType()) {
    isDynamicValue = 1;
  }

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

void BinaryExpressionGenerationStrategy::declare(BoundExpression *expression) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)expression;

  llvm::StructType *dynamicValueStructType =
      llvm::StructType::getTypeByName(*_codeGenerationContext->getContext(),
                                      DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

  llvm::AllocaInst *dynamicValueVariableAddress = Builder->CreateAlloca(
      dynamicValueStructType, nullptr, "m_binarydynamicValueVariableAddress");

  dynamicValueVariableAddress->setAlignment(llvm::Align(8));

  binaryExpression->setDynamicValueVariableAddress(dynamicValueVariableAddress);
}

llvm::Value *BinaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundBinaryExpression *binaryExpression = (BoundBinaryExpression *)expression;

  bool isClassType = false;
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      binaryExpression->getLocation());
  _codeGenerationContext->getValueStackHandler()->popAll();

  int8_t isLHSDynamicValue = 0, isRHSDynamicValue = 0;

  llvm::Value *lhsValue = this->getExpressionValue(
      binaryExpression->getLeftPtr().get(), isClassType, isLHSDynamicValue);

  llvm::Value *rhsValue = this->getExpressionValue(
      binaryExpression->getRightPtr().get(), isClassType, isRHSDynamicValue);

  if (!lhsValue || !rhsValue) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Binary Expression Type ");
    return nullptr;
  }

  if (isLHSDynamicValue || isRHSDynamicValue) {
    llvm::AllocaInst *dynamicValueVariableAddress =
        binaryExpression->getDynamicValueVariableAddress();

    if (!isLHSDynamicValue) {
      DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
          dynamicValueVariableAddress, "lhsDynamicValue", lhsValue,
          _codeGenerationContext, Builder);
      lhsValue = dynamicValueVariableAddress;
    } else if (!isRHSDynamicValue) {
      DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
          dynamicValueVariableAddress, "rhsDynamicValue", rhsValue,
          _codeGenerationContext, Builder);
      rhsValue = dynamicValueVariableAddress;
    }

    DYNAMIC_VALUE_HANDLER::generateDynamicDispatch(
        lhsValue, _codeGenerationContext, Builder,
        [&](llvm::Value *resolvedLhsValue) {
          DYNAMIC_VALUE_HANDLER::generateDynamicDispatch(
              rhsValue, _codeGenerationContext, Builder,
              [&](llvm::Value *resolvedRhsValue) {
                llvm::Value *result =
                    performOperation(resolvedLhsValue, resolvedRhsValue,
                                     binaryExpression->getOperator());
                DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
                    dynamicValueVariableAddress, "dynamicValueVariableAddress",
                    result, _codeGenerationContext, Builder);
              });
        });

    llvm::StructType *dynamicValueType = llvm::StructType::getTypeByName(
        *_codeGenerationContext->getContext(),
        DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

    _codeGenerationContext->getValueStackHandler()->push(
        "", dynamicValueVariableAddress,
        DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE, dynamicValueType);

    return dynamicValueVariableAddress;
  }

  llvm::Value *result = nullptr;

  result =
      performOperation(lhsValue, rhsValue, binaryExpression->getOperator());

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

llvm::Value *BinaryExpressionGenerationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOp) {
  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  llvm::Value *result = nullptr;

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  if ((_typeMapper->isNirastValue(lhsValue) ||
       _typeMapper->isNirastValue(rhsValue))) {
    result = _nirastBinaryOperationStrategy->performOperation(
        lhsValue, rhsValue, binaryOp);
  }
  // TODO: NULL CHeck

  //! When lhs or rhs is null
  // TODO: Implement runtime null checking
  //? input -> lhs (null | value) | rhs (null | value)
  //? output -> true | false
  //? Method -> CreateIsNull

  else if (_typeMapper->isStringType(lhsType) ||
           _typeMapper->isStringType(rhsType)) {
    result = _stringBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), rhsValue),
        binaryOp);
  } else if (_typeMapper->isFloatType(lhsType) ||
             _typeMapper->isFloatType(rhsType)) {
    result = _floatBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), rhsValue),
        binaryOp);
  } else if (_typeMapper->isDoubleType(lhsType) ||
             _typeMapper->isDoubleType(rhsType)) {
    result = _doubleBinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(), rhsValue),
        binaryOp);
  } else if (_typeMapper->isBoolType(lhsType) &&
             _typeMapper->isBoolType(rhsType)) {
    result = _boolBinaryOperationStrategy->performOperation(lhsValue, rhsValue,
                                                            binaryOp);
  } else if (_typeMapper->isInt8Type(lhsType) &&
             _typeMapper->isInt8Type(rhsType)) {
    result = _int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int8TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int8TypeConverter.get(), rhsValue),
        binaryOp);
  } else {
    result = _int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
        binaryOp);
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
