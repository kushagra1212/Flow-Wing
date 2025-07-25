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