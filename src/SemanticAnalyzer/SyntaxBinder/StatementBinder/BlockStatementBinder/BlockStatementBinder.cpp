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

#include "BlockStatementBinder.h"
#include "src/SemanticAnalyzer/BoundStatements/BoundBlockStatement/BoundBlockStatement.h"
#include "src/SemanticAnalyzer/SyntaxBinder/StatementBinder/StatementBinderFactory.h"
#include "src/SemanticAnalyzer/SyntaxBinder/SyntaxBinderContext/SyntaxBinderContext.h"
#include "src/syntax/statements/BlockStatementSyntax/BlockStatementSyntax.h"

std::unique_ptr<BoundStatement>
BlockStatementBinder::bindStatement(SyntaxBinderContext *ctx,
                                    StatementSyntax *statement) {

  BlockStatementSyntax *blockStatement =
      static_cast<BlockStatementSyntax *>(statement);

  ctx->insertScope();

  std::unique_ptr<BoundBlockStatement> boundBlockStatement =
      std::make_unique<BoundBlockStatement>(blockStatement->getSourceLocation(),
                                            false);

  for (int i = 0; i < blockStatement->getStatements().size(); i++) {
    std::unique_ptr<BoundStatement> statement = std::move(
        StatementBinderFactory::create(
            blockStatement->getStatements()[i]->getKind())
            ->bindStatement(ctx, blockStatement->getStatements()[i].get()));

    boundBlockStatement->addStatement(std::move(statement));
  }

  ctx->removeScope();

  return std::move(boundBlockStatement);
}