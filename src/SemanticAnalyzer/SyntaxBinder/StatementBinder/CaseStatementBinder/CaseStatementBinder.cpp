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



#include "CaseStatementBinder.h"

std::unique_ptr<BoundStatement>
CaseStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                   StatementSyntax *statement) {

  CaseStatementSyntax *caseStatement =
      static_cast<CaseStatementSyntax *>(statement);

  std::unique_ptr<BoundCaseStatement> boundCaseStatement =
      std::make_unique<BoundCaseStatement>(caseStatement->getSourceLocation());

  boundCaseStatement->setIsDefaultCase(caseStatement->isDefaultCase());

  if (!boundCaseStatement->getIsDefaultCase()) {
    boundCaseStatement->setCaseExpression(
        std::move(ExpressionBinderFactory::create(
                      caseStatement->getCaseExpressionRef()->getKind())
                      ->bindExpression(
                          ctx, caseStatement->getCaseExpressionRef().get())));
  }

  boundCaseStatement->setBodyStatement(std::move(
      StatementBinderFactory::create(
          caseStatement->getBlockStatementRef()->getKind())
          ->bindStatement(ctx, caseStatement->getBlockStatementRef().get())));

  return std::move(boundCaseStatement);
}