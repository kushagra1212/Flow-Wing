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


#include "ClassUnaryOperationStrategy.h"
#include "../../../../diagnostics/Diagnostic/DiagnosticCodeData.h"

ClassUnaryOperationStrategy::ClassUnaryOperationStrategy(
    CodeGenerationContext *context)
    : UnaryOperationStrategy(context){};

llvm::Value *ClassUnaryOperationStrategy::performOperation(
    llvm::Value *val, BoundUnaryExpression *unaryExpression) {

  return performOperation(val, unaryExpression->getOperator());
}

llvm::Value *ClassUnaryOperationStrategy::performOperation(
    llvm::Value *val, BinderKindUtils::BoundUnaryOperatorKind unaryOperator) {

  if (!UnaryOperationSupport::isSupported(
          UnaryOperationSupport::ClassStrategyTag{}, unaryOperator)) {

    _codeGenerationContext->getLogger()->logError(
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::
            UnSupportedUnaryOperatorForClassType,
        {BinderKindUtils::to_string(unaryOperator)});
    return nullptr;
  }

  switch (unaryOperator) {
  case BinderKindUtils::BoundUnaryOperatorKind::LogicalNegation: {
    llvm::Function *function = Builder->GetInsertBlock()->getParent();

    // Basic blocks for the conditional logic
    llvm::BasicBlock *initialCheck = Builder->GetInsertBlock();
    llvm::BasicBlock *endBlock =
        llvm::BasicBlock::Create(*TheContext, "land.end", function);
    llvm::BasicBlock *nullCheck =
        llvm::BasicBlock::Create(*TheContext, "land.null", function);

    // LHS Check Block
    llvm::Value *isNotNull = Builder->CreateIsNotNull(val);
    Builder->CreateCondBr(isNotNull, endBlock, nullCheck);

    Builder->SetInsertPoint(nullCheck);
    Builder->CreateBr(endBlock);

    Builder->SetInsertPoint(endBlock);
    llvm::PHINode *phi = Builder->CreatePHI(llvm::Type::getInt1Ty(*TheContext),
                                            3, "land.result");

    phi->addIncoming(Builder->getFalse(), initialCheck);
    phi->addIncoming(Builder->getTrue(), nullCheck);

    return phi;
  }

  default: {

    _codeGenerationContext->getLogger()->logError(
        FLOW_WING::DIAGNOSTIC::DiagnosticCode::
            UnSupportedUnaryOperatorForClassType,
        {BinderKindUtils::to_string(unaryOperator)});
    break;
  }
  }

  return nullptr;
}
