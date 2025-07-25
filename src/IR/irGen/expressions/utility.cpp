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


#include "utility.h"

namespace ExpressionSupport {

llvm::Value *getExpressionValue(CodeGenerationContext *context,
                                BoundExpression *expression, bool &isClassType,
                                int8_t &isDynamicValue) {

  context->getValueStackHandler()->popAll();

  std::unique_ptr<ExpressionGenerationFactory> expressionGenerationFactory =
      std::make_unique<ExpressionGenerationFactory>(context);

  llvm::Value *value =
      expressionGenerationFactory->createStrategy(expression->getKind())
          ->generateExpression(expression);

  if (context->getValueStackHandler()->isDynamicValueType()) {
    isDynamicValue = 1;
  }

  if (context->getValueStackHandler()->isStructType()) {
    if (!context->isValidClassType(llvm::cast<llvm::StructType>(
            context->getValueStackHandler()->getLLVMType()))) {
      context->getLogger()->LogError("Operation is not supported for objects");
      return nullptr;
    }
    value = context->getBuilder()->CreateLoad(
        llvm::Type::getInt8PtrTy(*context->getContext()),
        context->getValueStackHandler()->getValue());
    isClassType = true;
  }

  if (context->getValueStackHandler()->isPrimaryType()) {
    value = context->getBuilder()->CreateLoad(
        context->getValueStackHandler()->getLLVMType(),
        context->getValueStackHandler()->getValue());
  }

  if (context->getValueStackHandler()->isLLVMConstant()) {
    value = context->getValueStackHandler()->getValue();
  }

  context->getValueStackHandler()->popAll();

  return value;
}
} // namespace ExpressionSupport