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



#include "ClassBinaryOperationStrategy.h"

ClassBinaryOperationStrategy::ClassBinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *ClassBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *ClassBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator,
    bool isLHSClassType, bool isRHSClassType) {

  if (!OperationSupport::isSupported(OperationSupport::ClassStrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for class type ");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    if (isLHSClassType && isRHSClassType) {
      llvm::Function *function = Builder->GetInsertBlock()->getParent();

      // Basic blocks for the conditional logic
      llvm::BasicBlock *lhsCheckBlock = Builder->GetInsertBlock();
      llvm::BasicBlock *rhsCheckBlock =
          llvm::BasicBlock::Create(*TheContext, "land.rhs", function);
      llvm::BasicBlock *bothNotNullBlock =
          llvm::BasicBlock::Create(*TheContext, "land.bothNotNull", function);
      llvm::BasicBlock *endBlock =
          llvm::BasicBlock::Create(*TheContext, "land.end", function);

      // LHS Check Block
      llvm::Value *lhsIsNotNull = Builder->CreateIsNotNull(lhsValue);
      Builder->CreateCondBr(lhsIsNotNull, rhsCheckBlock, endBlock);

      Builder->SetInsertPoint(rhsCheckBlock);
      llvm::Value *rhsIsNotNull = Builder->CreateIsNotNull(rhsValue);
      Builder->CreateCondBr(rhsIsNotNull, bothNotNullBlock, endBlock);

      Builder->SetInsertPoint(bothNotNullBlock);
      Builder->CreateBr(endBlock);

      Builder->SetInsertPoint(endBlock);
      llvm::PHINode *phi = Builder->CreatePHI(
          llvm::Type::getInt1Ty(*TheContext), 3, "land.result");

      phi->addIncoming(Builder->getFalse(), lhsCheckBlock);
      phi->addIncoming(Builder->getFalse(), rhsCheckBlock);
      phi->addIncoming(Builder->getTrue(), bothNotNullBlock);

      return phi;
    }

    if (isLHSClassType) {
      llvm::Function *function = Builder->GetInsertBlock()->getParent();

      // Basic blocks for the conditional logic
      llvm::BasicBlock *lhsCheckBlock = Builder->GetInsertBlock();
      llvm::BasicBlock *rhsCheckBlock =
          llvm::BasicBlock::Create(*TheContext, "land.rhs", function);
      llvm::BasicBlock *endBlock =
          llvm::BasicBlock::Create(*TheContext, "land.end", function);

      // LHS Check Block
      llvm::Value *lhsIsNotNull = Builder->CreateIsNotNull(lhsValue);
      Builder->CreateCondBr(lhsIsNotNull, rhsCheckBlock, endBlock);

      Builder->SetInsertPoint(rhsCheckBlock);
      Builder->CreateBr(endBlock);

      Builder->SetInsertPoint(endBlock);
      llvm::PHINode *phi = Builder->CreatePHI(
          llvm::Type::getInt1Ty(*TheContext), 3, "land.result");

      phi->addIncoming(Builder->getFalse(), lhsCheckBlock);
      phi->addIncoming(
          _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue),
          rhsCheckBlock);

      return phi;
    }

    return performOperation(rhsValue, lhsValue, binaryOperator, isRHSClassType,
                            isLHSClassType);

    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    if (isLHSClassType && isRHSClassType) {
      llvm::Function *function = Builder->GetInsertBlock()->getParent();

      // Basic blocks for the conditional logic
      llvm::BasicBlock *lhsCheckBlock = Builder->GetInsertBlock();
      llvm::BasicBlock *rhsCheckBlock =
          llvm::BasicBlock::Create(*TheContext, "land.rhs", function);
      llvm::BasicBlock *bothNullBlock =
          llvm::BasicBlock::Create(*TheContext, "land.bothNull", function);
      llvm::BasicBlock *endBlock =
          llvm::BasicBlock::Create(*TheContext, "land.end", function);

      // LHS Check Block
      llvm::Value *lhsIsNotNull = Builder->CreateIsNotNull(lhsValue);
      Builder->CreateCondBr(lhsIsNotNull, endBlock, rhsCheckBlock);

      Builder->SetInsertPoint(rhsCheckBlock);
      llvm::Value *rhsIsNotNull = Builder->CreateIsNotNull(rhsValue);
      Builder->CreateCondBr(rhsIsNotNull, endBlock, bothNullBlock);

      Builder->SetInsertPoint(bothNullBlock);
      Builder->CreateBr(endBlock);

      Builder->SetInsertPoint(endBlock);
      llvm::PHINode *phi = Builder->CreatePHI(
          llvm::Type::getInt1Ty(*TheContext), 3, "land.result");

      phi->addIncoming(Builder->getTrue(), lhsCheckBlock);
      phi->addIncoming(Builder->getTrue(), rhsCheckBlock);
      phi->addIncoming(Builder->getFalse(), bothNullBlock);

      return phi;
    }

    if (isLHSClassType) {
      llvm::Function *function = Builder->GetInsertBlock()->getParent();

      // Basic blocks for the conditional logic
      llvm::BasicBlock *lhsCheckBlock = Builder->GetInsertBlock();
      llvm::BasicBlock *rhsCheckBlock =
          llvm::BasicBlock::Create(*TheContext, "land.rhs", function);
      llvm::BasicBlock *endBlock =
          llvm::BasicBlock::Create(*TheContext, "land.end", function);

      // LHS Check Block
      llvm::Value *lhsIsNotNull = Builder->CreateIsNotNull(lhsValue);
      Builder->CreateCondBr(lhsIsNotNull, endBlock, rhsCheckBlock);

      Builder->SetInsertPoint(rhsCheckBlock);
      Builder->CreateBr(endBlock);

      Builder->SetInsertPoint(endBlock);
      llvm::PHINode *phi = Builder->CreatePHI(
          llvm::Type::getInt1Ty(*TheContext), 3, "land.result");

      phi->addIncoming(Builder->getTrue(), lhsCheckBlock);
      phi->addIncoming(
          _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue),
          rhsCheckBlock);

      return phi;
    }

    return performOperation(rhsValue, lhsValue, binaryOperator, isRHSClassType,
                            isLHSClassType);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {

    if (isLHSClassType && isRHSClassType) {
      return Builder->CreateICmpEQ(lhsValue, rhsValue);
    }

    return Builder->getFalse();
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    if (isLHSClassType && isRHSClassType) {
      return Builder->CreateICmpNE(lhsValue, rhsValue);
    }

    return Builder->getTrue();
    break;
  }

  default: {

    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for class type ");
    break;
  }
  }
  return nullptr;
}

llvm::Value *ClassBinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {

  return nullptr;
}
