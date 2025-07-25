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



#include "ForStatementBinder.h"

std::unique_ptr<BoundStatement>
ForStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                  StatementSyntax *statement) {

  ForStatementSyntax *forStatement =
      static_cast<ForStatementSyntax *>(statement);

  ctx->insertScope();

  ctx->getRootRef()->makeBreakableAndContinuable();

  std::unique_ptr<BoundStatement> boundIntializer = std::move(
      StatementBinderFactory::create(
          forStatement->getInitializationRef()->getKind())
          ->bindStatement(ctx, forStatement->getInitializationRef().get()));

  std::unique_ptr<BoundExpression> boundUpperBound = std::move(
      ExpressionBinderFactory::create(
          forStatement->getUpperBoundRef()->getKind())
          ->bindExpression(ctx, forStatement->getUpperBoundRef().get()));

  std::unique_ptr<BoundExpression> boundStepExpression = nullptr;

  if (forStatement->getStepExpressionRef().get())
    boundStepExpression = std::move(
        ExpressionBinderFactory::create(
            forStatement->getStepExpressionRef()->getKind())
            ->bindExpression(ctx, forStatement->getStepExpressionRef().get()));

  std::unique_ptr<BoundStatement> boundBody = std::move(
      StatementBinderFactory::create(forStatement->getStatementRef()->getKind())
          ->bindStatement(ctx, forStatement->getStatementRef().get()));

  ctx->removeScope();

  return std::make_unique<BoundForStatement>(
      forStatement->getSourceLocation(), std::move(boundIntializer),
      std::move(boundUpperBound), std::move(boundStepExpression),
      std::move(boundBody));
}
