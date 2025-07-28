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

#include "IfStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundIfStatement/BoundIfStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/ExpressionBinder/ExpressionBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/syntax/expression/ExpressionSyntax.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"
#include "src/syntax/statements/ElseClauseSyntax/ElseClauseSyntax.h"
#include "src/syntax/statements/IfStatementSyntax/IfStatementSyntax.h"
#include "src/syntax/statements/OrIfStatementSyntax/OrIfStatementSyntax.h"

std::unique_ptr<BoundStatement>
IfStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                 StatementSyntax *statement) {
  IfStatementSyntax *ifStatement = static_cast<IfStatementSyntax *>(statement);

  std::unique_ptr<BoundIfStatement> boundIfStatement =
      std::make_unique<BoundIfStatement>(ifStatement->getSourceLocation());

  std::unique_ptr<BoundExpression> boundCondition =
      ExpressionBinderFactory::create(ifStatement->getConditionRef()->getKind())
          ->bindExpression(ctx, ifStatement->getConditionRef().get());

  std::unique_ptr<BoundStatement> boundThenStatement =
      (StatementBinderFactory::create(ifStatement->getStatementRef()->getKind())
           ->bindStatement(ctx, ifStatement->getStatementRef().get()));

  boundIfStatement->addCondition(std::move(boundCondition));
  boundIfStatement->addThenStatement(std::move(boundThenStatement));

  for (size_t i = 0; i < ifStatement->getOrIfStatementsRef().size(); i++) {
    std::unique_ptr<BoundOrIfStatement> boundOrIfStatement(
        static_cast<BoundOrIfStatement *>(
            StatementBinderFactory::create(
                ifStatement->getOrIfStatementsRef()[i]->getKind())
                ->bindStatement(ctx,
                                ifStatement->getOrIfStatementsRef()[i].get())
                .release()));

    boundIfStatement->addOrIfStatement(std::move(boundOrIfStatement));
  }

  std::unique_ptr<BoundStatement> boundElseStatement = nullptr;

  if (ifStatement->getElseClauseRef() != nullptr) {
    boundElseStatement =
        (StatementBinderFactory::create(
             ifStatement->getElseClauseRef()->getStatementRef()->getKind())
             ->bindStatement(
                 ctx,
                 ifStatement->getElseClauseRef()->getStatementRef().get()));

    boundIfStatement->addElseStatement(std::move(boundElseStatement));
  }

  return std::move(boundIfStatement);
}
