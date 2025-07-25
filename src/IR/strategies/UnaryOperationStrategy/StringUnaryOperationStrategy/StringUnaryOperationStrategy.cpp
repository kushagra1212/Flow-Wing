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


#include "StringUnaryOperationStrategy.h"

StringUnaryOperationStrategy::StringUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *StringUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *StringUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::StringStrategyTag{}, unaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for string type");
    return nullptr;
  }

  switch (unaryOperator) {

  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    llvm::BasicBlock *nullBlock =
        llvm::BasicBlock::Create(val->getContext(), "UnaryOP::NullBlock",
                                 Builder->GetInsertBlock()->getParent());
    llvm::BasicBlock *notNullBlock =
        llvm::BasicBlock::Create(val->getContext(), "UnaryOP::NotNullBlock",
                                 Builder->GetInsertBlock()->getParent());
    llvm::BasicBlock *mergeBlock =
        llvm::BasicBlock::Create(val->getContext(), "UnaryOP::MergeBlock",
                                 Builder->GetInsertBlock()->getParent());

    Builder->CreateCondBr(Builder->CreateIsNull(val), nullBlock, notNullBlock);

    Builder->SetInsertPoint(nullBlock);

    llvm::Value *resultFromNullBlock = Builder->getTrue();

    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(notNullBlock);

    llvm::Value *strLen = Builder->CreateCall(
        TheModule->getFunction(INNERS::FUNCTIONS::STRING_LENGTH),
        {_stringTypeConverter->convertExplicit(val)});

    llvm::Value *strLenIsZero =
        Builder->CreateICmpEQ(strLen, Builder->getInt32(0));

    llvm::Value *resultFromNotNullBlock = Builder->CreateSelect(
        strLenIsZero, llvm::ConstantInt::get(Builder->getInt1Ty(), 1),
        llvm::ConstantInt::get(Builder->getInt1Ty(), 0));
    Builder->CreateBr(mergeBlock);

    Builder->SetInsertPoint(mergeBlock);
    llvm::PHINode *conditionPHI = Builder->CreatePHI(Builder->getInt1Ty(), 2);
    conditionPHI->addIncoming(resultFromNullBlock, nullBlock);
    conditionPHI->addIncoming(resultFromNotNullBlock, notNullBlock);

    return conditionPHI;
  }

  default: {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported unary operator " +
        BinderKindUtils::to_string(unaryOperator) + " for string type");
    break;
  }
  }

  return nullptr;
}