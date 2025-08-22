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


#pragma once

#include "src/IR/context/utils/DynamicValueHandler/DynamicValueHandler.h"
#include "src/IR/irGen/expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"
#include "src/IR/irGen/expressions/utility.h"

class UnaryExpressionGenerationStrategy : public ExpressionGenerationStrategy {
public:
  UnaryExpressionGenerationStrategy(CodeGenerationContext *context);

  SyntaxKindUtils::SyntaxKind selectOperationStrategy(llvm::Value *value,
                                                      int8_t isClassType);

  void declare(BoundExpression *expression);
  llvm::Value *generateExpression(BoundExpression *expression) override;
  llvm::Value *generateGlobalExpression(BoundExpression *expression) override;

  llvm::Value *performOperation(llvm::Value *value,
                                BinderKindUtils::BoundUnaryOperatorKind unaryOp,
                                bool isClassType = false,
                                bool skipUnsupportedOperation = false);
};
