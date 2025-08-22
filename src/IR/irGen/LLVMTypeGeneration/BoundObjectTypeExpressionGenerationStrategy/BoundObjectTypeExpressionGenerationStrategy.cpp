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

#include "BoundObjectTypeExpressionGenerationStrategy.h"
#include "src/SemanticAnalyzer/BoundExpressions/BoundTypeExpression/BoundObjectTypeExpression/BoundObjectTypeExpression.h"

llvm::Type *BoundObjectTypeExpressionGenerationStrategy::getType(
    BoundTypeExpression *expression) {
  BoundObjectTypeExpression *objectTypeExpression =
      static_cast<BoundObjectTypeExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      objectTypeExpression->getLocation());

  llvm::StructType *structType =
      _codeGenerationContext
          ->_classLLVMTypes[objectTypeExpression->getTypeName()];

  std::string typeName = "";
  if (!structType) {
    typeName = objectTypeExpression->getTypeName();

    structType =
        _codeGenerationContext->getFlowWingType(typeName).getStructType();
    if (!structType) {
      _codeGenerationContext->getLogger()->LogError(
          "Expected an object type " + Utils::getActualTypeName(typeName) +
          " but, got " +
          _codeGenerationContext->getMapper()->getLLVMTypeName(structType));
      return nullptr;
    }
  }

  return structType;
}