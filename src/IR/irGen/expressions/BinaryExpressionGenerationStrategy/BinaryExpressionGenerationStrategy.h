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


#ifndef __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__
#define __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__

#include "src/IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/utility.h"
class BinaryExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  BinaryExpressionGenerationStrategy(CodeGenerationContext *context);

  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  void declare(BoundExpression *expression);

  llvm::Value *
  performOperation(llvm::Value *lhsValue, llvm::Value *rhsValue,
                   BinderKindUtils::BoundBinaryOperatorKind binaryOp,
                   bool isLHSClassType = false, bool isRHSClassType = false,
                   bool skipUnsupportedOperation = false);

  SyntaxKindUtils::SyntaxKind selectOperationStrategy(llvm::Value *lhsValue,
                                                      llvm::Value *rhsValue,
                                                      bool isClassType);
};

#endif // __FLOWWING__BINARY_EXPRESSION_GENERATION_STRATEGY_H__
