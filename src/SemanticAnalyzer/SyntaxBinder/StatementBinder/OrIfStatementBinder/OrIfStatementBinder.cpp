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

#include "OrIfStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundOrIfStatement/BoundOrIfStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinder.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"

std::unique_ptr<BoundStatement>
OrIfStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                   StatementSyntax *statement) {

  OrIfStatementSyntax *orIfStatement =
      static_cast<OrIfStatementSyntax *>(statement);

  std::unique_ptr<BoundExpression> boundCondition = std::move(
      ExpressionBinderFactory::create(
          orIfStatement->getConditionPtr()->getKind())
          ->bindExpression(ctx, orIfStatement->getConditionPtr().get()));

  std::unique_ptr<BoundStatement> boundThenStatement = std::move(
      StatementBinderFactory::create(
          orIfStatement->getStatementPtr()->getKind())
          ->bindStatement(ctx, orIfStatement->getStatementPtr().get()));

  return std::make_unique<BoundOrIfStatement>(
      orIfStatement->getSourceLocation(), std::move(boundCondition),
      std::move(boundThenStatement));
}
