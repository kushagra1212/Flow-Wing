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


#ifndef __BOOL_BINARY_OPERATION_STRATEGY_H__
#define __BOOL_BINARY_OPERATION_STRATEGY_H__

#include "src/IR/strategies/BinaryOperationStrategy/BinaryOperationStrategy.h"
#include "src/IR/strategies/BinaryOperationStrategy/Int32BinaryOperationStrategy/Int32BinaryOperationStrategy.h"

class BoolBinaryOperationStrategy : public BinaryOperationStrategy {
public:
  BoolBinaryOperationStrategy(CodeGenerationContext *context);
  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BoundBinaryExpression *binaryExpression) override;

  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp) override;
};

#endif // __INT_BINARY_OPERATION_STRATEGY_H__