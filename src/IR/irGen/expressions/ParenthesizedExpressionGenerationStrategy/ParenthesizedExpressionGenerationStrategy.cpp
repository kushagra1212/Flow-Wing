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


#include "ParenthesizedExpressionGenerationStrategy.h"

ParenthesizedExpressionGenerationStrategy::
    ParenthesizedExpressionGenerationStrategy(CodeGenerationContext *context)
    : ExpressionGenerationStrategy(context) {}

llvm::Value *ParenthesizedExpressionGenerationStrategy::generateExpression(
    BoundExpression *expression) {
  BoundParenthesizedExpression *parenthesizedExpression =
      static_cast<BoundParenthesizedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      parenthesizedExpression->getLocation());

  return _expressionGenerationFactory
      ->createStrategy(
          parenthesizedExpression->getExpressionPtr().get()->getKind())
      ->generateExpression(parenthesizedExpression->getExpressionPtr().get());
}

llvm::Value *
ParenthesizedExpressionGenerationStrategy::generateGlobalExpression(
    BoundExpression *expression) {

  BoundParenthesizedExpression *parenthesizedExpression =
      static_cast<BoundParenthesizedExpression *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      parenthesizedExpression->getLocation());

  _codeGenerationContext->getLogger()->LogError(
      "Parenthesized Expression is not allowed in global scope ");

  return nullptr;
}