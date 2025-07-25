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


#include "LLVMTypeGenerationFactory.h"

#include "BoundArrayTypeExpressionGenerationStrategy/BoundArrayTypeExpressionGenerationStrategy.h"
#include "BoundFunctionTypeExpressionGenerationStrategy/BoundFunctionTypeExpressionGenerationStrategy.h"
#include "BoundObjectTypeExpressionGenerationStrategy/BoundObjectTypeExpressionGenerationStrategy.h"
#include "BoundTypeExpressionGenerationStrategy/BoundTypeExpressionGenerationStrategy.h"

LLVMTypeGenerationFactory::LLVMTypeGenerationFactory(
    CodeGenerationContext *context)
    : _codeGenerationContext(context) {}

std::unique_ptr<LLVMTypeGenerationStrategy>
LLVMTypeGenerationFactory::createStrategy(BinderKindUtils::BoundNodeKind kind) {
  switch (kind) {
    case BinderKindUtils::BoundNodeKind::BoundTypeExpression:
      return std::make_unique<BoundTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundArrayTypeExpression:
      return std::make_unique<BoundArrayTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundObjectTypeExpression:
      return std::make_unique<BoundObjectTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    case BinderKindUtils::BoundNodeKind::BoundFunctionTypeExpression:
      return std::make_unique<BoundFunctionTypeExpressionGenerationStrategy>(
          _codeGenerationContext);

    default:
      _codeGenerationContext->getLogger()->LogError(
          "Unsupported Expression Type ");
      return nullptr;
  }
}