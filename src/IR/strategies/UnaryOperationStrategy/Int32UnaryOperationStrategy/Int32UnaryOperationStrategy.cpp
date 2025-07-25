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


#include "Int32UnaryOperationStrategy.h"

Int32UnaryOperationStrategy::Int32UnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *Int32UnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *Int32UnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {
  llvm::Value *result = Builder->getInt32(1);

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::Int32StrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for int32 type ");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::Negation: {
    return Builder->CreateNeg(val);
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::Identity: {
    return val;
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    llvm::Value *isZero = Builder->CreateICmpEQ(
        val, llvm::ConstantInt::get(Builder->getInt32Ty(), 0));

    return isZero;
    break;
  }
  case BinderKindUtils::BoundUnaryOperatorKind::BitwiseNegation: {
    return Builder->CreateNot(val);
    break;
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for int32 type ");
    break;
  }
  }

  return nullptr;
}