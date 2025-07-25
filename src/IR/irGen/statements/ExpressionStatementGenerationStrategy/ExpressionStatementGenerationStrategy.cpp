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


#include "ExpressionStatementGenerationStrategy.h"

#include "../../expressions/ExpressionGenerationStrategy/ExpressionGenerationStrategy.h"

ExpressionStatementGenerationStrategy::ExpressionStatementGenerationStrategy(
    CodeGenerationContext *context)
    : StatementGenerationStrategy(context) {}

llvm::Value *ExpressionStatementGenerationStrategy::generateStatement(
    BoundStatement *expression) {
  BoundExpressionStatement *boundExpressionStatement =
      static_cast<BoundExpressionStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundExpressionStatement->getLocation());

  BoundExpression *boundExpression =
      boundExpressionStatement->getExpressionPtr().get();

  return _expressionGenerationFactory
      ->createStrategy(boundExpression->getKind())
      ->generateExpression(boundExpression);
}

llvm::Value *ExpressionStatementGenerationStrategy::generateGlobalStatement(
    BoundStatement *expression) {

  BoundExpressionStatement *boundExpressionStatement =
      static_cast<BoundExpressionStatement *>(expression);

  _codeGenerationContext->getLogger()->setCurrentSourceLocation(
      boundExpressionStatement->getLocation());

  BoundExpression *boundExpression =
      boundExpressionStatement->getExpressionPtr().get();

  return _expressionGenerationFactory
      ->createStrategy(boundExpression->getKind())
      ->generateGlobalExpression(boundExpression);
}