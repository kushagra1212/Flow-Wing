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

#include "LiteralExpressionGenerationStrategy.h"
#include "src/syntax/SyntaxKindUtils.h"

LiteralExpressionGenerationStrategy::LiteralExpressionGenerationStrategy(
    CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *LiteralExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {

  BoundLiteralExpression<std::any> *literalExpression =
      static_cast<BoundLiteralExpression<std::any> *>(expression);
  std::any value = literalExpression->getValue();

  CODEGEN_DEBUG_LOG(
      "LiteralExpressionGenerationStrategy::generateExpression",
      SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  llvm::Value *val = _llvmValueConverter->convertToLLVMValue(
      value, literalExpression->getSyntaxKind());

  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Literal Type " +
        SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));
    return nullptr;
  }

  _codeGenerationContext->getValueStackHandler()->push("", val, "constant",
                                                       val->getType());
  return val;
}

llvm::Value *LiteralExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)expression;

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Literal Expression is not allowed in global scope ");

  return nullptr;
}

llvm::Value *LiteralExpressionGenerationStrategy::generateTypedExpression(
    BoundExpression *expression, SyntaxKindUtils::SyntaxKind variableType) {
  BoundLiteralExpression<std::any> *literalExpression =
      (BoundLiteralExpression<std::any> *)expression;
  std::any value = literalExpression->getValue();

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      literalExpression->getLocation());

  llvm::Value *val = _llvmValueConverter->convertToTypedLLVMValue(
      value, literalExpression->getSyntaxKind(), variableType);

  _codeGenerationContext->getValueStackHandler()->push("", val, "constant",
                                                       val->getType());
  if (val == nullptr) {
    _codeGenerationContext->getLogger()->LogError(
        "Unsupported Literal Type " +
        SyntaxKindUtils::to_string(literalExpression->getSyntaxKind()));
    return nullptr;
  }

  return val;
}
