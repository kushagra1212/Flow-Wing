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

#include "FloatBinaryOperationStrategy.h"

FloatBinaryOperationStrategy::FloatBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context) {};

llvm::Value *FloatBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {
  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *FloatBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {

  if (!OperationSupport::isSupported(OperationSupport::FloatStrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for float type ");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {

    return Builder->CreateFAdd(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction: {

    return Builder->CreateFSub(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication: {

    return Builder->CreateFMul(lhsValue, rhsValue);
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {
    // llvm::Value *isZero = Builder->CreateFCmpOEQ(
    //     rhsValue, llvm::ConstantFP::get(*TheContext, llvm::APFloat(0.0)));

    // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    // llvm::BasicBlock *ifBlock =
    //     llvm::BasicBlock::Create(*TheContext, "if",
    //     currentBlock->getParent());
    // llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
    //     *TheContext, "else", currentBlock->getParent());

    // // Create a conditional branch
    // Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // // Set up the 'if' block
    // Builder->SetInsertPoint(ifBlock);
    // Builder->CreateCall(
    //     TheModule->getFunction(INNERS::FUNCTIONS::RAISE_EXCEPTION),
    //     {Builder->CreateGlobalStringPtr(
    //         _codeGenerationContext->getLogger()->getLLVMErrorMsg(
    //             "Floating point division by zero is not allowed",
    //             binaryExpression->getLocation()))});

    // Builder->CreateBr(elseBlock);

    // Builder->SetInsertPoint(elseBlock);

    return Builder->CreateFDiv(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {

    return Builder->CreateFCmpOEQ(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    return Builder->CreateFCmpONE(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Less: {

    return Builder->CreateFCmpOLT(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {

    return Builder->CreateFCmpOLE(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater: {

    return Builder->CreateFCmpOGT(lhsValue, rhsValue);
  }

  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals: {

    return Builder->CreateFCmpOGE(lhsValue, rhsValue);
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for float type ");
    break;
  }
  }

  return nullptr;
}