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



#include "Int32BinaryOperationStrategy.h"

Int32BinaryOperationStrategy::Int32BinaryOperationStrategy(
    CodeGenerationContext *context)
    : BinaryOperationStrategy(context){};

llvm::Value *Int32BinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BoundBinaryExpression *binaryExpression) {

  return performOperation(lhsValue, rhsValue, binaryExpression->getOperator());
}

llvm::Value *Int32BinaryOperationStrategy::performOperation(
    llvm::Value *lhsValue, llvm::Value *rhsValue,
    BinderKindUtils::BoundBinaryOperatorKind binaryOperator) {
  llvm::Value *result = Builder->getInt32(1);

  if (!OperationSupport::isSupported(OperationSupport::Int32StrategyTag{},
                                     binaryOperator)) {
    this->_codeGenerationContext->getLogger()->LogError(
        "Unsupported binary operator " +
        BinderKindUtils::to_string(binaryOperator) + " for int32 type ");
    return nullptr;
  }

  switch (binaryOperator) {

  case BinderKindUtils::BoundBinaryOperatorKind::Addition: {
    return result = Builder->CreateAdd(lhsValue, rhsValue);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Subtraction:
    return result = Builder->CreateSub(lhsValue, rhsValue);
    break;
  case BinderKindUtils::BoundBinaryOperatorKind::Multiplication:
    return result = Builder->CreateMul(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::IntegerDivision: {
    // llvm::Value *divisionResult = nullptr;
    // llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue,
    // Builder->getInt32(0));

    // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    // llvm::BasicBlock *ifBlock =
    //     llvm::BasicBlock::Create(*TheContext, "if",
    //     currentBlock->getParent());
    // llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
    //     *TheContext, "else", currentBlock->getParent());
    // llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
    //     *TheContext, "merge", currentBlock->getParent());
    // // Create a conditional branch
    // Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // // Set up the 'if' block
    // Builder->SetInsertPoint(ifBlock);

    // _codeGenerationContext->getLogger()->LogError("Division by zero is not
    // allowed");

    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(elseBlock);
    // divisionResult = Builder->CreateSDiv(lhsValue, rhsValue);
    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(mergeBlock);

    return Builder->CreateSDiv(lhsValue, rhsValue);
    ;
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Division: {

    // llvm::Value *divisionResult = nullptr;
    // llvm::Value *isZero = Builder->CreateICmpEQ(rhsValue,
    // Builder->getInt32(0));

    // llvm::BasicBlock *currentBlock = Builder->GetInsertBlock();
    // llvm::BasicBlock *ifBlock =
    //     llvm::BasicBlock::Create(*TheContext, "if",
    //     currentBlock->getParent());
    // llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(
    //     *TheContext, "else", currentBlock->getParent());
    // llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(
    //     *TheContext, "merge", currentBlock->getParent());
    // // Create a conditional branch
    // Builder->CreateCondBr(isZero, ifBlock, elseBlock);

    // // Set up the 'if' block
    // Builder->SetInsertPoint(ifBlock);

    // _codeGenerationContext->getLogger()->LogError("Division by zero is not
    // allowed");

    // Builder->CreateBr(mergeBlock);

    // Builder->SetInsertPoint(elseBlock);

    // divisionResult =
    //     Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
    //                         _doubleTypeConverter->convertExplicit(rhsValue));
    // Builder->CreateBr(mergeBlock);
    // Builder->SetInsertPoint(mergeBlock);
    return Builder->CreateFDiv(_doubleTypeConverter->convertExplicit(lhsValue),
                               _doubleTypeConverter->convertExplicit(rhsValue));
    ;
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Modulus:
    return Builder->CreateSRem(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseAnd:
    return Builder->CreateAnd(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseOr:
    return Builder->CreateOr(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::BitwiseXor:
    return Builder->CreateXor(lhsValue, rhsValue);
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalAnd:
    return Builder->CreateLogicalAnd(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::LogicalOr:
    return Builder->CreateLogicalOr(
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), lhsValue),
        _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), rhsValue));
    break;

  case BinderKindUtils::BoundBinaryOperatorKind::Equals: {
    llvm::Value *_val = Builder->CreateICmpEQ(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::NotEquals: {

    llvm::Value *_val = Builder->CreateICmpNE(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::Less: {
    llvm::Value *_val = Builder->CreateICmpSLT(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::LessOrEquals: {
    llvm::Value *_val = Builder->CreateICmpSLE(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }

  case BinderKindUtils::BoundBinaryOperatorKind::Greater: {
    llvm::Value *_val = Builder->CreateICmpSGT(lhsValue, rhsValue);
    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  case BinderKindUtils::BoundBinaryOperatorKind::GreaterOrEquals: {
    llvm::Value *_val = Builder->CreateICmpSGE(lhsValue, rhsValue);

    return _typeSpecificValueVisitor->visit(_boolTypeConverter.get(), _val);
    break;
  }
  default: {
    break;
  }
  }

  _codeGenerationContext->getLogger()->LogError(
      "Unsupported binary operator " +
      BinderKindUtils::to_string(binaryOperator) + " for int32 type ");
  return nullptr;
}