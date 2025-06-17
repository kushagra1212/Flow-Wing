#include "BinaryExpressionGenerationStrategy.h"

BinaryExpressionGenerationStrategy::BinaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

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

  llvm::Value *lhsValue = ExpressionSupport::getExpressionValue(
      _codeGenerationContext, binaryExpression->getLeftPtr().get(), isClassType,
      isLHSDynamicValue);

  llvm::Value *rhsValue = ExpressionSupport::getExpressionValue(
      _codeGenerationContext, binaryExpression->getRightPtr().get(),
      isClassType, isRHSDynamicValue);

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
          DEBUG_LOG("Resolved lhs type",
                    _codeGenerationContext->getMapper()->getLLVMTypeName(
                        resolvedLhsValue->getType()));
          DYNAMIC_VALUE_HANDLER::generateDynamicDispatch(
              rhsValue, _codeGenerationContext, Builder,
              [&](llvm::Value *resolvedRhsValue) {
                DEBUG_LOG("Resolved rhs type",
                          _codeGenerationContext->getMapper()->getLLVMTypeName(
                              resolvedRhsValue->getType()));

                llvm::Value *result = performOperation(
                    resolvedLhsValue, resolvedRhsValue,
                    binaryExpression->getOperator(), isClassType, true);

                if (result) {

                  DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
                      dynamicValueVariableAddress,
                      "dynamicValueVariableAddress", result,
                      _codeGenerationContext, Builder);
                }
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

  result = performOperation(lhsValue, rhsValue, binaryExpression->getOperator(),
                            isClassType);

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
    BinderKindUtils::BoundBinaryOperatorKind binaryOp, bool isClassType,
    bool skipUnsupportedOperation) {
  llvm::Value *result = nullptr;

  SyntaxKindUtils::SyntaxKind operationStrategy =
      selectOperationStrategy(lhsValue, rhsValue, isClassType);

  auto needToPerformOperation = [&](bool isSupported) {
    return !(skipUnsupportedOperation && !isSupported);
  };

  switch (operationStrategy) {
  case SyntaxKindUtils::SyntaxKind::NirastKeyword: {

    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::NirastStrategyTag{}, binaryOp);

    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _nirastBinaryOperationStrategy->performOperation(
          lhsValue, rhsValue, binaryOp);
    }

    break;
  }
    // TODO: NULL CHeck

    //! When lhs or rhs is null
    // TODO: Implement runtime null checking
    //? input -> lhs (null | value) | rhs (null | value)
    //? output -> true | false
    //? Method -> CreateIsNull

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {

    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::StringStrategyTag{}, binaryOp);

    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _stringBinaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_stringTypeConverter.get(),
                                           lhsValue),
          _typeSpecificValueVisitor->visit(_stringTypeConverter.get(),
                                           rhsValue),
          binaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {

    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::FloatStrategyTag{}, binaryOp);

    if (needToPerformOperation(isBinaryOperationSupported)) {

      result = _floatBinaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), lhsValue),
          _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), rhsValue),
          binaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::DoubleStrategyTag{}, binaryOp);

    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _doubleBinaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(),
                                           lhsValue),
          _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(),
                                           rhsValue),
          binaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::BoolStrategyTag{}, binaryOp);
    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _boolBinaryOperationStrategy->performOperation(
          lhsValue, rhsValue, binaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::Int8StrategyTag{}, binaryOp);
    if (needToPerformOperation(isBinaryOperationSupported)) {

      result = _int32BinaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_int8TypeConverter.get(), lhsValue),
          _typeSpecificValueVisitor->visit(_int8TypeConverter.get(), rhsValue),
          binaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::ClassKeyword: {
    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::ClassStrategyTag{}, binaryOp);
    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _classBinaryOperationStrategy->performOperation(
          lhsValue, rhsValue, binaryOp);
    }
    break;
  }
  default: {
    const bool isBinaryOperationSupported = OperationSupport::isSupported(
        OperationSupport::Int32StrategyTag{}, binaryOp);

    if (needToPerformOperation(isBinaryOperationSupported)) {
      result = _int32BinaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
          _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
          binaryOp);
    }
    break;
  }
  }

  if (skipUnsupportedOperation) {
    _codeGenerationContext->getValueStackHandler()->popAll();
    return result;
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

SyntaxKindUtils::SyntaxKind
BinaryExpressionGenerationStrategy::selectOperationStrategy(
    llvm::Value *lhsValue, llvm::Value *rhsValue, bool isClassType) {

  llvm::Type *lhsType = lhsValue->getType();
  llvm::Type *rhsType = rhsValue->getType();

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  DEBUG_LOG("Class type detected", _typeMapper->getLLVMTypeName(lhsType),
            _typeMapper->getLLVMTypeName(rhsType));
  if (isClassType) {
    return SyntaxKindUtils::SyntaxKind::ClassKeyword;
  }

  if ((_typeMapper->isNirastValue(lhsValue) ||
       _typeMapper->isNirastValue(rhsValue))) {
    return SyntaxKindUtils::SyntaxKind::NirastKeyword;
  }

  if (_typeMapper->isStringType(lhsType) ||
      _typeMapper->isStringType(rhsType)) {
    return SyntaxKindUtils::SyntaxKind::StrKeyword;
  }

  if (_typeMapper->isFloatType(lhsType) || _typeMapper->isFloatType(rhsType)) {
    return SyntaxKindUtils::SyntaxKind::Deci32Keyword;
  }
  if (_typeMapper->isDoubleType(lhsType) ||
      _typeMapper->isDoubleType(rhsType)) {
    return SyntaxKindUtils::SyntaxKind::DeciKeyword;
  }

  if (_typeMapper->isBoolType(lhsType) && _typeMapper->isBoolType(rhsType)) {
    return SyntaxKindUtils::SyntaxKind::BoolKeyword;
  }
  if (_typeMapper->isInt8Type(lhsType) && _typeMapper->isInt8Type(rhsType)) {
    return SyntaxKindUtils::SyntaxKind::Int8Keyword;
  }

  return SyntaxKindUtils::SyntaxKind::Int32Keyword;
}