/*
 * FlowWing Compiler
 * Copyright (C) 2023-2025 Kushagra Rathore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include "UnaryExpressionGenerationStrategy.h"

UnaryExpressionGenerationStrategy::UnaryExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

void UnaryExpressionGenerationStrategy::declare(BoundExpression *expression) {
  BoundUnaryExpression *unaryExpression =
      static_cast<BoundUnaryExpression *>(expression);

  llvm::StructType *dynamicValueStructType =
      llvm::StructType::getTypeByName(*_codeGenerationContext->getContext(),
                                      DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

  llvm::AllocaInst *dynamicValueVariableAddress = Builder->CreateAlloca(
      dynamicValueStructType, nullptr, "m_unarydynamicValueVariableAddress");

  dynamicValueVariableAddress->setAlignment(llvm::Align(8));

  unaryExpression->setDynamicValueVariableAddress(dynamicValueVariableAddress);
}

llvm::Value *UnaryExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundUnaryExpression *unaryExpression =
      static_cast<BoundUnaryExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      unaryExpression->getLocation());

  bool isClassType = false;
  int8_t isDynamicValue = 0;

  llvm::Value *value = ExpressionSupport::getExpressionValue(
      _codeGenerationContext, unaryExpression->getOperandPtr().get(),
      isClassType, isDynamicValue);

  if (value == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Unary Expression Type ");

    return nullptr;
  }

  if (isDynamicValue) {
    llvm::AllocaInst *dynamicValueVariableAddress =
        unaryExpression->getDynamicValueVariableAddress();

    DYNAMIC_VALUE_HANDLER::generateDynamicDispatch(
        value, _codeGenerationContext, Builder,
        [&](llvm::Value *resolvedValue) {
          DEBUG_LOG("Resolved value ",
                    _codeGenerationContext->getMapper()->getLLVMTypeName(
                        resolvedValue->getType()));

          llvm::Value *result = performOperation(
              resolvedValue, unaryExpression->getOperator(), isClassType, true);

          if (result) {
            DYNAMIC_VALUE_HANDLER::assignRHSValueToLHSDynamicValue(
                dynamicValueVariableAddress, "dynamicValueVariableAddress",
                result, _codeGenerationContext, Builder);
          }
        });

    llvm::StructType *dynamicValueType = llvm::StructType::getTypeByName(
        *_codeGenerationContext->getContext(),
        DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE);

    _codeGenerationContext->getValueStackHandler()->push(
        "", dynamicValueVariableAddress,
        DYNAMIC_VALUE::TYPE::DYNAMIC_VALUE_TYPE, dynamicValueType);

    return dynamicValueVariableAddress;
  }

  llvm::Value *res =
      performOperation(value, unaryExpression->getOperator(), isClassType);
  _codeGenerationContext->getValueStackHandler()->popAll();
  if (res != nullptr) {
    _codeGenerationContext->getValueStackHandler()->push("", res, "constant",
                                                         res->getType());
  }

  return res;
}

llvm::Value *UnaryExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundUnaryExpression *unaryExpression =
      static_cast<BoundUnaryExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      unaryExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Unary Expression is not allowed in global scope ");

  return nullptr;
}

llvm::Value *UnaryExpressionGenerationStrategy::performOperation(
    llvm::Value *value, BinderKindUtils::BoundUnaryOperatorKind unaryOp,
    bool isClassType, bool skipUnsupportedOperation) {
  llvm::Value *result = nullptr;

  SyntaxKindUtils::SyntaxKind operationStrategy =
      selectOperationStrategy(value, isClassType);

  auto needToPerformOperation = [&](bool isSupported) {
    return !(skipUnsupportedOperation && !isSupported);
  };

  switch (operationStrategy) {
  case SyntaxKindUtils::SyntaxKind::NirastKeyword: {

    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::NirastStrategyTag{}, unaryOp);

    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _nirastUnaryOperationStrategy->performOperation(value, unaryOp);
    }

    break;
  }

  case SyntaxKindUtils::SyntaxKind::StrKeyword: {

    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::StringStrategyTag{}, unaryOp);

    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _stringUnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_stringTypeConverter.get(), value),
          unaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::Deci32Keyword: {

    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::FloatStrategyTag{}, unaryOp);

    if (needToPerformOperation(isUnaryOperationSupported)) {

      result = _floatUnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_floatTypeConverter.get(), value),
          unaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::DeciKeyword: {
    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::DoubleStrategyTag{}, unaryOp);

    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _doubleUnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_doubleTypeConverter.get(), value),
          unaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::BoolKeyword: {
    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::BoolStrategyTag{}, unaryOp);
    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _boolUnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), value),
          unaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::Int8Keyword: {
    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::Int8StrategyTag{}, unaryOp);
    if (needToPerformOperation(isUnaryOperationSupported)) {

      result = _int32UnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), value),
          unaryOp);
    }
    break;
  }
  case SyntaxKindUtils::SyntaxKind::ClassKeyword: {
    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::ClassStrategyTag{}, unaryOp);
    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _classUnaryOperationStrategy->performOperation(value, unaryOp);
    }
    break;
  }
  default: {
    const bool isUnaryOperationSupported = UnaryOperationSupport::isSupported(
        UnaryOperationSupport::Int32StrategyTag{}, unaryOp);

    if (needToPerformOperation(isUnaryOperationSupported)) {
      result = _int32UnaryOperationStrategy->performOperation(
          _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), value),
          unaryOp);
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
UnaryExpressionGenerationStrategy::selectOperationStrategy(llvm::Value *value,
                                                           int8_t isClassType) {

  llvm::Type *type = value->getType();

  TypeMapper *_typeMapper = _codeGenerationContext->getMapper().get();

  DEBUG_LOG("Class type detected", _typeMapper->getLLVMTypeName(type));

  if (isClassType) {
    return SyntaxKindUtils::SyntaxKind::ClassKeyword;
  }

  if (_typeMapper->isNirastValue(value)) {
    return SyntaxKindUtils::SyntaxKind::NirastKeyword;
  }

  if (_typeMapper->isStringType(type)) {
    return SyntaxKindUtils::SyntaxKind::StrKeyword;
  }

  if (_typeMapper->isFloatType(type)) {
    return SyntaxKindUtils::SyntaxKind::Deci32Keyword;
  }
  if (_typeMapper->isDoubleType(type)) {
    return SyntaxKindUtils::SyntaxKind::DeciKeyword;
  }

  if (_typeMapper->isBoolType(type)) {
    return SyntaxKindUtils::SyntaxKind::BoolKeyword;
  }
  if (_typeMapper->isInt8Type(type)) {
    return SyntaxKindUtils::SyntaxKind::Int8Keyword;
  }

  return SyntaxKindUtils::SyntaxKind::Int32Keyword;
}