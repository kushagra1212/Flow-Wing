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


#include "BoundArrayTypeExpressionGenerationStrategy.h"

#include "../../../../SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"
#include "../../expressions/LiteralExpressionGenerationStrategy/LiteralExpressionGenerationStrategy.h"

llvm::Type *BoundArrayTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  BoundArrayTypeExpression *boundArrayTypeExpression =
      static_cast<BoundArrayTypeExpression *>(expression);
  llvm::Type *elementType = nullptr;

  if (boundArrayTypeExpression->isTrivialType()) {
    elementType = _codeGenerationContext->getMapper()->mapCustomTypeToLLVMType(
        boundArrayTypeExpression->getElementType());
  } else {
    auto objectType = static_cast<BoundObjectTypeExpression *>(
        boundArrayTypeExpression->getNonTrivialElementType().get());

    elementType =
        _codeGenerationContext->getFlowWingType(objectType->getTypeName())
            .getStructType();
  }
  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundArrayTypeExpression->getLocation());

  if (!elementType) {
    _codeGenerationContext->getLogger()->LogError(
        "Expected a array element type in custom type statement");
    return nullptr;
  }

  std::unique_ptr<LiteralExpressionGenerationStrategy>
      literalExpressionGenerationStrategy =
          std::make_unique<LiteralExpressionGenerationStrategy>(
              _codeGenerationContext);

  llvm::Type *finalType = elementType;
  std::vector<uint64_t> dimensions(
      boundArrayTypeExpression->getDimensions().size(), 0);

  for (int64_t k = boundArrayTypeExpression->getDimensions().size() - 1; k >= 0;
       k--) {
    llvm::Value *arraySize =
        literalExpressionGenerationStrategy->generateExpression(
            boundArrayTypeExpression->getDimensions()[k].get());

    _codeGenerationContext->getLogger()->setCurrentSourceLocation(
        boundArrayTypeExpression->getDimensions()[k]->getLocation());

    if (!llvm::isa<llvm::ConstantInt>(arraySize)) {
      _codeGenerationContext->getLogger()->LogError(
          "Array size must be a constant integer");
    }

    dimensions[k] = llvm::cast<llvm::ConstantInt>(arraySize)->getSExtValue();

    finalType = llvm::ArrayType::get(finalType, dimensions[k]);
  }
  return finalType;
  ;
}