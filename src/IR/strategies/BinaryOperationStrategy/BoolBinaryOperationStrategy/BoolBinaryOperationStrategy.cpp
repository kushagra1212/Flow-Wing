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



#include "BoolBinaryOperationStrategy.h"

BoolBinaryOperationStrategy::BoolBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *BoolBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {
  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *BoolBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOp) {
  llvm::Value *result = nullptr;

  if (!OperationSupport::isSupported(OperationSupport::BoolStrategyTag{},
                                     binaryOp)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " + BinderKindUtils::to_string(binaryOp) +
        " for bool type ");
    return nullptr;
  }

  switch (binaryOp) {

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
        binaryOp);

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), result);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    std::unique_ptr<Int32BinaryOperationStrategy> int32BinaryOperationStrategy =
        std::make_unique<Int32BinaryOperationStrategy>(
            this->_codeGenerationContext);

    result = int32BinaryOperationStrategy->performOperation(
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_int32TypeConverter.get(), rhsValue),
        binaryOp);

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

    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " + BinderKindUtils::to_string(binaryOp) +
        " for bool type ");
    break;
  }

  return nullptr;
}