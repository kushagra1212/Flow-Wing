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



#include "WhileStatementBinder.h"

std::unique_ptr<BoundStatement>
WhileStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {
  WhileStatementSyntax *whileStatement =
      static_cast<WhileStatementSyntax *>(statement);

  ctx->insertScope();

  ctx->getRootRef()->makeBreakableAndContinuable();

  std::unique_ptr<BoundExpression> boundCondition = std::move(
      ExpressionBinderFactory::create(
          whileStatement->getConditionRef()->getKind())
          ->bindExpression(ctx, whileStatement->getConditionRef().get()));

  std::unique_ptr<BoundStatement> boundBody = std::move(
      StatementBinderFactory::create(whileStatement->getBodyRef()->getKind())
          ->bindStatement(ctx, whileStatement->getBodyRef().get()));

  ctx->removeScope();

  return std::make_unique<BoundWhileStatement>(
      whileStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundBody));
}
